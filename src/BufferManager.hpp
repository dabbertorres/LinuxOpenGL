#ifndef DBR_GL_BUFFER_MANAGER_HPP
#define DBR_GL_BUFFER_MANAGER_HPP

// a class for managing OpenGL buffers
// ie: requests and holds onto a requested number,
// and keeps track of used/unused buffers
// this is done for memory reuse, resulting in less 
// memory allocations and deallocations

#include <vector>
#include <queue>
#include <algorithm>

#include "Core.hpp"

namespace dbr
{
	namespace gl
	{
		template<typename H>
		class BufferManager
		{
			public:
				using Generator = void(*)(GLsizei, const GLuint*);
				using Deleter = void(*)(GLsizei, const GLuint*);
				
				BufferManager(Generator generator, Deleter deleter);
				~BufferManager();

				// requests an additional num buffers on top of the current total
				void request(std::size_t num);

				// releases all unused buffers, returning the number freed
				std::size_t shrink();

				// returns the Handle of the next free buffer
				// returns 0 if there are no unused buffers (all buffers are used)
				H next();

				// returns the next num unused Handles
				// if there are not num unused Handles, the returned vector's size
				// will NOT be num. Don't assume the size is always the same
				std::vector<H> next(std::size_t num);

				// adds given Handle to the free list
				// does NOT release the buffer
				void free(H h);

				// returns number of allocated buffers
				std::size_t count() const;

				// returns the number of used/unused buffers currently allocated
				std::size_t used() const;
				std::size_t unused() const;

			private:
				Generator generator;
				Deleter deleter;
				
				// all used buffer handles are towards the front,
				// all unused buffer handles are at the end
				std::vector<GLuint> buffers;

				// contains the index of the first unused buffer
				std::size_t freeIndex;
		};

		template<typename H>
		BufferManager<H>::BufferManager(Generator generator, Deleter deleter)
		:	generator(generator),
			deleter(deleter),
			freeIndex(0)
		{}

		template<typename H>
		BufferManager<H>::~BufferManager()
		{
			deleter(buffers.size(), buffers.data());
		}

		template<typename H>
		void BufferManager<H>::request(std::size_t num)
		{
			auto oldSize = buffers.size();
			auto newSize = buffers.size() + num;
			buffers.resize(newSize);

			generator(num, &buffers[oldSize]);
		}

		template<typename H>
		std::size_t BufferManager<H>::shrink()
		{
			auto numFree = unused();
			deleter(numFree, &buffers[freeIndex]);

			buffers.resize(used());

			return numFree;
		}

		template<typename H>
		H BufferManager<H>::next()
		{
			if(freeIndex == buffers.size())
				return 0;
			else
				return buffers[freeIndex++];
		}

		template<typename H>
		std::vector<H> BufferManager<H>::next(std::size_t num)
		{
			num = std::min(num, unused());

			auto start = buffers.begin() + freeIndex;
			auto end = start + num;

			return {start, end};
		}

		template<typename H>
		void BufferManager<H>::free(H h)
		{
			auto last = buffers.begin() + freeIndex;
			auto freedIt = std::find(buffers.begin(), last, h);
			auto moveTo = last - 1;

			if(freedIt != last)
			{
				std::iter_swap(freedIt, moveTo);
			}
		}

		template<typename H>
		std::size_t BufferManager<H>::count() const
		{
			return buffers.size();
		}

		template<typename H>
		std::size_t BufferManager<H>::used() const
		{
			// freeIndex == last used index + 1 == size
			return freeIndex;
		}

		template<typename H>
		std::size_t BufferManager<H>::unused() const
		{
			return buffers.size() - freeIndex;
		}
	}
}

#endif
