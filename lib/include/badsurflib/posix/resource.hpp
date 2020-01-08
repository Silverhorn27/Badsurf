////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-2018 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef POSIX_RESOURCE_HPP
#define POSIX_RESOURCE_HPP

////////////////////////////////////////////////////////////////////////////////
#include <chrono>

////////////////////////////////////////////////////////////////////////////////
namespace posix
{

////////////////////////////////////////////////////////////////////////////////
// descriptor type
using desc = int;

// no/invalid descriptor
static constexpr desc ndesc = -1;

// adopt tag
struct adopt_t { explicit adopt_t() noexcept = default; };
constexpr adopt_t adopt { };

////////////////////////////////////////////////////////////////////////////////
// posix resource with descriptor (eg, file, socket, pipe, etc)
//
class resource
{
public:
    ////////////////////
    resource() noexcept = default;
    resource(posix::desc desc) noexcept : desc_(desc) { }
    resource(posix::desc desc, adopt_t) noexcept : desc_(desc), adopt_(true) { }
   ~resource();

    resource(const resource& rhs) noexcept : resource(rhs.desc_) { }
    resource(resource&& rhs) noexcept { swap(rhs); }

    resource& operator=(const resource& rhs) noexcept;
    resource& operator=(resource&& rhs) noexcept { swap(rhs); return *this; }

    void swap(resource&) noexcept;

    ////////////////////
    bool empty() const noexcept { return desc_ == ndesc; }
    explicit operator bool() const noexcept { return !empty(); }

    auto desc() const noexcept { return desc_; }
    operator posix::desc() const noexcept { return desc(); }

    void adopt(posix::desc desc) noexcept;
    void close();

    ////////////////////
    bool can_read() const;
    bool try_read_forever() const;

    template<typename Rep, typename Period>
    bool try_read_for(const std::chrono::duration<Rep, Period>&) const;

    template<typename Clock, typename Duration>
    bool try_read_until(const std::chrono::time_point<Clock, Duration>&) const;

    bool can_write() const;
    bool try_write_forever() const;

    template<typename Rep, typename Period>
    bool try_write_for(const std::chrono::duration<Rep, Period>&) const;

    template<typename Clock, typename Duration>
    bool try_write_until(const std::chrono::time_point<Clock, Duration>&) const;

private:
    ////////////////////
    posix::desc desc_ = ndesc;
    bool adopt_ = false;

    using msec = std::chrono::milliseconds;
    enum event { read, write };
    bool wait_for(const msec&, event) const;

    void throw_empty() const;
    void maybe_close() noexcept;
};

////////////////////////////////////////////////////////////////////////////////
inline bool resource::can_read() const { return try_read_for(msec::zero()); }
inline bool resource::try_read_forever() const { return try_read_for(msec::max()); }

////////////////////////////////////////////////////////////////////////////////
template<typename Rep, typename Period>
inline bool
resource::try_read_for(const std::chrono::duration<Rep, Period>& time) const
{ return wait_for(std::chrono::duration_cast<msec>(time), read); }

////////////////////////////////////////////////////////////////////////////////
template<typename Clock, typename Duration>
inline bool
resource::try_read_until(const std::chrono::time_point<Clock, Duration>& tp) const
{
    auto now = Clock::now();
    return try_read_for(tp - (tp < now ? tp : now));
}

////////////////////////////////////////////////////////////////////////////////
inline bool resource::can_write() const { return try_write_for(msec::zero()); }
inline bool resource::try_write_forever() const { return try_write_for(msec::max()); }

////////////////////////////////////////////////////////////////////////////////
template<typename Rep, typename Period>
inline bool
resource::try_write_for(const std::chrono::duration<Rep, Period>& time) const
{ return wait_for(std::chrono::duration_cast<msec>(time), write); }

////////////////////////////////////////////////////////////////////////////////
template<typename Clock, typename Duration>
inline bool
resource::try_write_until(const std::chrono::time_point<Clock, Duration>& tp) const
{
    auto now = Clock::now();
    return try_write_for(tp - (tp < now ? tp : now));
}

////////////////////////////////////////////////////////////////////////////////
inline void swap(resource& lhs, resource& rhs) noexcept { lhs.swap(rhs); }

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
