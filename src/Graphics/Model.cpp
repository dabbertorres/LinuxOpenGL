#include "Model.hpp"

#include <sstream>
#include <fstream>

namespace dbr
{
	namespace gl
	{
		Model Model::loadFromFile(const std::string& file)
		{
			Model ret;

			std::ifstream fin(file);

			if(fin)
			{
				
			}

			return ret;
		}

		Model::Model()
			: valid(false)
		{}

		bool Model::isValid() const
		{
			return valid;
		}
	}
}
