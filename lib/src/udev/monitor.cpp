////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "badsurflib/posix/error.hpp"
#include "badsurflib/udev/monitor.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace detail
{

// move udev stuff into detail namespace 8-o
#include <libudev.h>

void monitor_delete::operator()(udev_monitor* x) { udev_monitor_unref(x); }

}

////////////////////////////////////////////////////////////////////////////////
namespace
{

void throw_on(int code)
{
    if(code) throw std::system_error(
        static_cast<posix::errc>(code < 0 ? -code : code)
    );
}

}

////////////////////////////////////////////////////////////////////////////////
namespace udev
{

////////////////////////////////////////////////////////////////////////////////
monitor::monitor() : udev_(udev::instance()),
    mon_(detail::udev_monitor_new_from_netlink(udev_.get(), "udev"))
{
    if(!mon_) throw posix::errno_error();
}

////////////////////////////////////////////////////////////////////////////////
void monitor::match_device(const std::string& subsystem, const std::string& type)
{
    throw_on(detail::udev_monitor_filter_add_match_subsystem_devtype(
        mon_.get(), subsystem.data(), type.size() ? type.data() : nullptr
    ));
}

////////////////////////////////////////////////////////////////////////////////
void monitor::match_tag(const std::string& name)
{
    throw_on(detail::udev_monitor_filter_add_match_tag(
        mon_.get(), name.data()
    ));
}

////////////////////////////////////////////////////////////////////////////////
device monitor::try_get_for_(const monitor::msec& time)
{
    if(!active())
    {
        throw_on(detail::udev_monitor_enable_receiving(mon_.get()));

        int fd = detail::udev_monitor_get_fd(mon_.get());
        if(fd < 0) throw_on(fd);

        res_ = posix::resource(fd);
    }

    return res_.try_read_for(time)
        ? device(detail::udev_monitor_receive_device(mon_.get()))
        : device();
}

////////////////////////////////////////////////////////////////////////////////
}
