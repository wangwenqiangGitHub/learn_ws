#pragma once

namespace queueT
{

    class noncopyable
    {
    public:
        noncopyable() = delete;
        void operator=(const noncopyable&) = delete;

    protected:
        noncopyable() = default;
        ~noncopyable() = default;
    };

} // namespace queueT