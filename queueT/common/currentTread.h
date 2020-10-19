#pragma once
#include <stdint.h> // int64_t
#include <string>   // string

namespace queueT
{
    namespace CurrentThread
    {
        //iternal
        extern __thread int t_cachedTid;
        extern __thread char t_tidString[32];
        extern __thread int t_tidSttringLength;
        extern __thread const char *t_threadName;
        void cacheTid();

        inline int tid()
        {
            //作用：分支预判
            //绝大部分情况下，a>0为假，函数func1在绝大部分情况下不执行，完成了对代码的技能预判。
            if (__builtin_expect(t_cachedTid == 0, 0))
            {
                cacheTid();
            }
            return t_cachedTid;
        }

        inline const char *tidString() //for logging
        {
            return t_tidString;
        }

        inline int tidStringLength() //for logging
        {
            return t_tidSttringLength;
        }

        inline const char *name()
        {
            return t_threadName;
        }

        bool isMainThread();
        void sleepUsec(int64_t usec); //for testing

        std::string stackTrace(bool demangle);

    } // namespace CurrentThread
} // namespace queueT