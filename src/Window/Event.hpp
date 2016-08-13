#ifndef DBR_GL_WINDOW_EVENT_HPP
#define DBR_GL_WINDOW_EVENT_HPP

#include <functional>
#include <vector>

namespace dbr
{
	namespace gl
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

			std::vector<Ret> operator()(Args... args)
			{
				std::vector<Ret> rets;
				rets.reserve(callbacks.size());

				for(auto& cb : callbacks)
				{
					auto r = cb(args...);
					rets.push_back(r);
				}

				return rets;
			}

			void operator+=(Callback&& cb)
			{
				callbacks.push_back(std::move(cb));
			}

			void operator+=(const Callback& cb)
			{
				callbacks.emplace_back(cb);
			}

			// no movable operator-=, because that seems... wrong

			void operator-=(const Callback& cb)
			{
				callbacks.erase(std::find(callbacks.begin(), callbacks.end(), cb));
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

			void operator()(Args... args)
			{
				for(auto& cb : callbacks)
					cb(args...);
			}

			void operator+=(Callback&& cb)
			{
				callbacks.push_back(std::move(cb));
			}

			void operator+=(const Callback& cb)
			{
				callbacks.emplace_back(cb);
			}

			// no movable operator-=, because that seems... wrong

			void operator-=(const Callback& cb)
			{
				callbacks.erase(std::find(callbacks.begin(), callbacks.end(), cb));
			}

		private:
			std::vector<Callback> callbacks;
		};
	}
}

#endif
