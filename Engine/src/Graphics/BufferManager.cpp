#include "BufferManager.hpp"

namespace dbr
{
	namespace eng
	{
        namespace gfx
        {
            BufferManager::BufferManager(Allocator allocator, Deallocator deallocator)
                : allocator(allocator),
                deallocator(deallocator),
                freeIndex(0)
            {}

            BufferManager::~BufferManager()
            {
                deallocator(buffers.size(), buffers.data());
            }

            void BufferManager::request(std::size_t num)
            {
                auto oldSize = buffers.size();
                auto newSize = buffers.size() + num;
                buffers.resize(newSize);

                allocator(num, &buffers[oldSize]);
            }

            std::size_t BufferManager::shrink()
            {
                auto numFree = unused();
                deallocator(numFree, &buffers[freeIndex]);

                buffers.resize(used());

                return numFree;
            }

            HandleU BufferManager::next()
            {
                if (freeIndex == buffers.size())
                    return 0;
                else
                    return buffers[freeIndex++];
            }

            std::vector<HandleU> BufferManager::next(std::size_t num)
            {
                num = std::min(num, unused());

                auto start = buffers.begin() + freeIndex;
                auto end = start + num;

                return{start, end};
            }

            void BufferManager::free(HandleU h)
            {
                auto last = buffers.begin() + freeIndex;
                auto freedIt = std::find(buffers.begin(), last, h);
                auto lastUsed = last - 1;

                if (freedIt != last)
                    std::iter_swap(freedIt, lastUsed);
            }

            std::size_t BufferManager::total() const
            {
                return buffers.size();
            }

            std::size_t BufferManager::used() const
            {
                // freeIndex == last used index + 1 == number used
                return freeIndex;
            }

            std::size_t BufferManager::unused() const
            {
                return buffers.size() - freeIndex;
            }
        }
	}
}
