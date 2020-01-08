////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-18 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "error.hpp"
#include "resource.hpp"

#include <stdexcept>
#include <utility>

#include <poll.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
namespace posix
{

////////////////////////////////////////////////////////////////////////////////
resource::~resource() { maybe_close(); }

////////////////////////////////////////////////////////////////////////////////
resource& resource::operator=(const resource& rhs) noexcept
{
    maybe_close();
    desc_ = rhs.desc_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
void resource::swap(resource& rhs) noexcept
{
    using std::swap;
    swap(desc_ , rhs.desc_ );
    swap(adopt_, rhs.adopt_);
}

////////////////////////////////////////////////////////////////////////////////
void resource::adopt(posix::desc desc) noexcept
{
    *this = desc;
    adopt_ = true;
}

////////////////////////////////////////////////////////////////////////////////
void resource::close()
{
    throw_empty();
    maybe_close();
}

////////////////////////////////////////////////////////////////////////////////
bool resource::wait_for(const msec& time, event e) const
{
    throw_empty();

    short events = (e == read) ? POLLIN | POLLPRI : (e == write) ? POLLOUT : 0;
    pollfd fd_poll = { desc_, events, 0 };

    auto count = ::poll(&fd_poll, 1,
        time == msec::max() ? -1 : static_cast<int>(time.count())
    );
    if(count == -1) throw posix::errno_error();

    return fd_poll.events & fd_poll.revents;
}

////////////////////////////////////////////////////////////////////////////////
void resource::throw_empty() const
{
    if(empty()) throw std::logic_error(
        "Attempt to access empty posix::resource instance"
    );
}

////////////////////////////////////////////////////////////////////////////////
void resource::maybe_close() noexcept
{
    if(adopt_ && desc_ != ndesc)
    {
        ::close(desc_);
        desc_ = ndesc;
        adopt_ = false;
    }
}

////////////////////////////////////////////////////////////////////////////////
}
