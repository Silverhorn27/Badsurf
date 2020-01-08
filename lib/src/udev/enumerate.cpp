////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "badsurflib/posix/error.hpp"
#include "badsurflib/udev/enumerate.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace detail
{

// move udev stuff into detail namespace 8-o
#include <libudev.h>

void enumerate_delete::operator()(udev_enumerate* x) { udev_enumerate_unref(x); }

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
enumerate::enumerate() : udev_(udev::instance()),
    enum_(detail::udev_enumerate_new(udev_.get()))
{
    if(!enum_) throw posix::errno_error();
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::match_subsystem(const std::string& subsystem)
{
    throw_on(detail::udev_enumerate_add_match_subsystem(
        enum_.get(), subsystem.data()
    ));
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::nomatch_subsystem(const std::string& subsystem)
{
    throw_on(detail::udev_enumerate_add_nomatch_subsystem(
        enum_.get(), subsystem.data()
    ));
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::match_attribute(const std::string& name, const std::string& value)
{
    throw_on(detail::udev_enumerate_add_match_sysattr(
        enum_.get(), name.data(), value.size() ? value.data() : nullptr
    ));
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::nomatch_attribute(const std::string& name, const std::string& value)
{
    throw_on(detail::udev_enumerate_add_nomatch_sysattr(
        enum_.get(), name.data(), value.size() ? value.data() : nullptr
    ));
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::match_property(const std::string& name, const std::string& value)
{
    throw_on(detail::udev_enumerate_add_match_property(
        enum_.get(), name.data(), value.size() ? value.data() : nullptr
    ));
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::match_name(const std::string& name)
{
    throw_on(detail::udev_enumerate_add_match_sysname(
        enum_.get(), name.data()
    ));
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::match_tag(const std::string& name)
{
    throw_on(detail::udev_enumerate_add_match_tag(
        enum_.get(), name.data()
    ));
}

////////////////////////////////////////////////////////////////////////////////
void enumerate::match_parent(const device& dev)
{
    throw_on(detail::udev_enumerate_add_match_parent(
        enum_.get(), dev.dev_.get()
    ));
}

////////////////////////////////////////////////////////////////////////////////
std::vector<device> enumerate::get()
{
    std::vector<device> devices;
    throw_on(detail::udev_enumerate_scan_devices(enum_.get()));

    detail::udev_list_entry* e;
    udev_list_entry_foreach(e, detail::udev_enumerate_get_list_entry(enum_.get()))
    {
        if(auto path = detail::udev_list_entry_get_name(e))
            devices.push_back(device(udev_, path));
    }

    return devices;
}

////////////////////////////////////////////////////////////////////////////////
}
