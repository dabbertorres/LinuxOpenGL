#ifndef DBR_GL_MODEL_HPP
#define DBR_GL_MODEL_HPP

#include <string>
#include <vector>

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>

namespace dbr
{
	namespace gl
	{
		class Model
		{
		public:
			static Model loadFromFile(const std::string& file);

			Model();
			~Model() = default;

			bool isValid() const;

		private:
			struct Face
			{
				std::size_t vert0;
				std::size_t vert1;
				std::size_t vert2;
			};

			bool valid;

			std::vector<math::Vector3f> vertices;
			std::vector<Face> faces;
		};
	}
}

#endif
