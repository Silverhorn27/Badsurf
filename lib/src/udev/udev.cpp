////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "badsurflib/posix/error.hpp"
#include "badsurflib/udev/udev.hpp"

#include <memory>

////////////////////////////////////////////////////////////////////////////////
namespace detail
{

// move udev stuff into detail namespace 8-o
#include <libudev.h>

}

////////////////////////////////////////////////////////////////////////////////
udev::udev udev::udev::instance()
{
    static std::weak_ptr<detail::udev> weak;

    auto strong = weak.lock();
    if(!strong)
    {
        strong = std::shared_ptr<detail::udev>(
            detail::udev_new(),
            &detail::udev_unref
        );
        if(!strong) throw posix::errno_error();

        weak = strong;
    }

    return udev(std::move(strong));
}
