////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef UDEV_ENUMERATE_HPP
#define UDEV_ENUMERATE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "badsurflib/udev/device.hpp"
#include "badsurflib/udev/udev.hpp"

#include <memory>
#include <string>
#include <vector>

namespace detail
{

struct udev_enumerate;
struct enumerate_delete { void operator()(udev_enumerate*); };

}

////////////////////////////////////////////////////////////////////////////////
namespace udev
{

////////////////////////////////////////////////////////////////////////////////
// Udev device enumerator.
//
// As needed, call one or more of the match_*() functions
// to only match specific devices. Then, call the get() function
// to get a list of matching devices.
//
class enumerate
{
public:
    ////////////////////
    enumerate();

    enumerate(const enumerate&) = delete;
    enumerate(enumerate&&) noexcept = default;

    enumerate& operator=(const enumerate&) = delete;
    enumerate& operator=(enumerate&&) noexcept = default;

    ////////////////////
    void match_subsystem(const std::string&);
    void nomatch_subsystem(const std::string&);

    void match_attribute(const std::string& name, const std::string& value = std::string());
    void nomatch_attribute(const std::string& name, const std::string& value = std::string());

    void match_property(const std::string& name, const std::string& value = std::string());

    void match_name(const std::string&);
    void match_tag(const std::string&);

    void match_parent(const device&);

    ////////////////////
    std::vector<device> get();

private:
    ////////////////////
    udev udev_;
    std::unique_ptr<detail::udev_enumerate, detail::enumerate_delete> enum_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
