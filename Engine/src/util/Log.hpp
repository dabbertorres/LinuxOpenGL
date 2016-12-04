#ifndef DBR_UTIL_LOG_HPP
#define DBR_UTIL_LOG_HPP

#include <ostream>

namespace dbr
{
	namespace util
	{
		class Log
		{
		public:
			enum class Level
			{
				Verbose,
				Debug,
				Info,
				Warning,
				Error,
				Fatal,
			};

			class Stream
			{
			public:
				template<typename T>
				Stream& operator<<(const T& t);

			private:
				friend class Log;

				Stream(std::streambuf* os);

				std::ostream stream;
			};

			Log(std::ostream&& stream, Level lvl = Level::Error);
			~Log() = default;

			Stream operator()(Level lvl) const;

		private:
			std::ostream stream;
			Level level;
		};

		template<typename T>
		Log::Stream& Log::Stream::operator<<(const T& t)
		{
			stream << t;
			return *this;
		}
	}
}

#endif
