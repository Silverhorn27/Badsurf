////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "badsurflib/posix/error.hpp"
#include "badsurflib/udev/device.hpp"
#include "badsurflib/udev/udev.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace detail
{

// move udev stuff into detail namespace 8-o
#include <libudev.h>

void device_delete::operator()(udev_device* x) { udev_device_unref(x); }

}

////////////////////////////////////////////////////////////////////////////////
namespace
{

auto string(const char* s) noexcept
{ return s ? std::string(s) : std::string(); }

}

////////////////////////////////////////////////////////////////////////////////
namespace udev
{

////////////////////////////////////////////////////////////////////////////////
device::device(const udev& udv, const std::string& path) :
    dev_(detail::udev_device_new_from_syspath(udv.get(), path.data()))
{
    if(!dev_) throw posix::errno_error();
}

////////////////////////////////////////////////////////////////////////////////
device device::parent() const noexcept
{
    auto dev = detail::udev_device_get_parent(dev_.get());

    // udev_device_get_parent() returns reference
    // whose lifetime is tied to the child's lifetime,
    // so we have to make a "deep copy"

    if(dev) dev = detail::udev_device_new_from_syspath(
        detail::udev_device_get_udev(dev),
        detail::udev_device_get_syspath(dev)
    );
    return device(dev);
}

////////////////////////////////////////////////////////////////////////////////
device device::parent(const std::string& subsystem, const std::string& type) const noexcept
{
    auto dev = detail::udev_device_get_parent_with_subsystem_devtype(dev_.get(),
        subsystem.data(), type.size() ? type.data() : nullptr
    );

    // udev_device_get_parent() returns reference
    // whose lifetime is tied to the child's lifetime,
    // so we have to make a "deep copy"

    if(dev) dev = detail::udev_device_new_from_syspath(
        detail::udev_device_get_udev(dev),
        detail::udev_device_get_syspath(dev)
    );
    return device(dev);
}

////////////////////////////////////////////////////////////////////////////////
std::string device::subsystem() const noexcept
{ return string(detail::udev_device_get_subsystem(dev_.get())); }

////////////////////////////////////////////////////////////////////////////////
std::string device::type() const noexcept
{ return string(detail::udev_device_get_devtype(dev_.get())); }

////////////////////////////////////////////////////////////////////////////////
std::string device::path() const noexcept
{ return string(detail::udev_device_get_syspath(dev_.get())); }

////////////////////////////////////////////////////////////////////////////////
std::string device::name() const noexcept
{ return string(detail::udev_device_get_sysname(dev_.get())); }

////////////////////////////////////////////////////////////////////////////////
std::string device::num() const noexcept
{ return string(detail::udev_device_get_sysnum(dev_.get())); }

////////////////////////////////////////////////////////////////////////////////
std::string device::node() const noexcept
{ return string(detail::udev_device_get_devnode(dev_.get())); }

////////////////////////////////////////////////////////////////////////////////
std::string device::property(const std::string& name) const noexcept
{ return string(detail::udev_device_get_property_value(dev_.get(), name.data())); }

////////////////////////////////////////////////////////////////////////////////
std::string device::driver() const noexcept
{ return string(detail::udev_device_get_driver(dev_.get())); }

////////////////////////////////////////////////////////////////////////////////
enum action device::action() const noexcept
{
    auto action = string(detail::udev_device_get_action(dev_.get()));
    return action == "add" ? added : action == "remove" ? removed : other;
}

////////////////////////////////////////////////////////////////////////////////
std::string device::attribute(const std::string& name) const noexcept
{ return string(detail::udev_device_get_sysattr_value(dev_.get(), name.data())); }

////////////////////////////////////////////////////////////////////////////////
bool device::has_tag(const std::string& name) const noexcept
{ return detail::udev_device_has_tag(dev_.get(), name.data()); }

////////////////////////////////////////////////////////////////////////////////
}
