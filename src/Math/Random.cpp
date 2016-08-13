#include "Random.hpp"

namespace dbr
{
	namespace math
	{
		std::random_device Random::randDevice;
		std::seed_seq Random::seed{randDevice(), randDevice(), randDevice(), randDevice(), randDevice(), randDevice(), randDevice(), randDevice()};
		std::mt19937 Random::engine{seed};
	}
}
