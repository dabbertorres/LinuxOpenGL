#ifndef DBR_ENG_UTIL_EVENT_HPP
#define DBR_ENG_UTIL_EVENT_HPP

#include <functional>
#include <vector>

namespace dbr
{
	namespace eng
	{
        namespace util
        {
            template<typename Ret, typename... Args>
            class Event;

            template<typename Ret, typename... Args>
            class Event<Ret(Args...)>
            {
            public:
                using Callback = std::function<Ret(Args...)>;

                Event() = default;
                ~Event() = default;

                template<typename... Ts>
                std::vector<Ret> operator()(Ts&&... args)
                {
                    std::vector<Ret> rets;
                    rets.reserve(callbacks.size());

                    for (auto& cb : callbacks)
                    {
                        auto r = cb(std::forward<Ts>(args)...);
                        rets.push_back(r);
                    }

                    return rets;
                }

                void operator+=(Callback cb)
                {
                    callbacks.push_back(cb);
                }

                void clear()
                {
                    callbacks.clear();
                }

            private:
                std::vector<Callback> callbacks;
            };

            // no return specialization
            template<typename... Args>
            class Event<void(Args...)>
            {
            public:
                using Callback = std::function<void(Args...)>;

                Event() = default;
                ~Event() = default;

                template<typename... Ts>
                void operator()(Ts&&... args)
                {
                    for (auto& cb : callbacks)
                        cb(std::forward<Ts>(args)...);
                }

                void operator+=(Callback cb)
                {
                    callbacks.push_back(cb);
                }

                void clear()
                {
                    callbacks.clear();
                }

            private:
                std::vector<Callback> callbacks;
            };
        }
	}
}

#endif
