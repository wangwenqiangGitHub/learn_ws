#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

namespace queueT
{
    namespace detail
    {
        template <typename T>
        struct has_no_destroy
        {
            /* data */
            template <typename c>
            static char test(decltype(&C::no_destroy));
            template <typename c>
            static int32_t test(...);
            const static bool value = sizeof(test<>)
        };
    } // namespace detail

    template <typename T>
    class Singleton : noncopyable
    {
    public:
        Singleton() = delete;
        ~Singleton() = delete;

        static T &instance()
        {
            pthread_once(&pconce_, &Singleton::init);
            assert(value != NULL);
            return *value_;
        }

    private:
        static void init()
        {
            value_ = new T();
            if (!detail::has_no_destroy<T>::value)
            {
                ::atexit(destroy);
            }
        }

        static void destroy()
        {
            typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
            T_must_be_complete_type dummy;
            (void)dummy;

            delete value_;
            value_ = NULL;
        }

    private:
        static pthread_once_t ponce_;
        static T *value_;
    };

    template<typename T>
    pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

    template<typename T>
    T* Singleton<T>::value_ = NULL;
} // namespace queueT