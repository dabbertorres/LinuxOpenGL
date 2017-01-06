#ifndef DBR_ENG_GFX_BUFFER_MANAGER_HPP
#define DBR_ENG_GFX_BUFFER_MANAGER_HPP

// a class for managing OpenGL buffers
// ie: requests and holds onto a requested number,
// and keeps track of used/unused buffers
// this is done for memory reuse, resulting in
// (ideally) less memory allocations and deallocations

#include <vector>
#include <queue>
#include <algorithm>

#include "Types.hpp"

namespace dbr
{
    namespace eng
    {
        namespace gfx
        {
            class BufferManager
            {
            public:
                // functions used to allocate and deallocate buffers (ie: glGenBuffers, glDeleteBuffers)
                using Allocator = void(CODEGEN_FUNCPTR *)(GLsizei, GLuint*);
                using Deallocator = void(CODEGEN_FUNCPTR *)(GLsizei, const GLuint*);

                BufferManager(Allocator allocator, Deallocator deallocator);

                // non-copyable
                BufferManager(const BufferManager& other) = delete;

                ~BufferManager();

                // requests an additional num buffers on top of the current total
                void request(size_t num);

                // releases all unused buffers, returning the number freed
                size_t shrink();

                // returns the Handle of the next free buffer
                // returns 0 if there are no unused buffers (all buffers are used)
                HandleU next();

                // returns the next num unused Handles
                // if there are not num unused Handles, the returned vector's size
                // will NOT be num. Don't assume the size is always the same
                std::vector<HandleU> next(size_t num);

                // adds given Handle to the free list
                // does NOT release the buffer
                void free(HandleU h);

                // returns number of allocated buffers
                size_t total() const;

                // returns the number of used/unused buffers currently allocated
                size_t used() const;
                size_t unused() const;

            private:
                Allocator allocator;
                Deallocator deallocator;

                // all used buffer handles are towards the front,
                // all unused buffer handles are at the end
                std::vector<GLuint> buffers;

                // contains the index of the first unused buffer
                size_t freeIndex;
            };
        }
    }
}

#endif
