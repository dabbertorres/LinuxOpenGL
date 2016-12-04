#include "Log.hpp"

namespace dbr
{
	namespace util
	{
		Log::Stream::Stream(std::streambuf* os)
			: stream(os)
		{}

		Log::Log(std::ostream&& s, Level lvl)
			: stream(s.rdbuf()),
			level(lvl)
		{}

		Log::Stream Log::operator()(Level lvl) const
		{
			return{lvl >= level ? stream.rdbuf() : nullptr};
		}
	}
}
