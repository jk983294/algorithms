#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>

namespace ktl {

/** alloc is SGI mechnism based.
    it will manage small objects ( < 128 bytes) using 16 lists.
    each list contains the same block size nodes.
    requested size will be aligned to 8 bytes, then find its free list.
    for big object, just use malloc / free.
*/
class alloc {
private:
    enum { _ALIGN = 8 };
    enum { _MAX_BYTES = 128 };
    enum { _NFREELIST = _MAX_BYTES / _ALIGN };  // number of free list
    enum { _NOBJS = 20 };                       // every time increase by _NOBJS blocks

    union obj {  // free list node
        union obj *free_list_next;
        char client[1];
    };

    // different block size free list
    static obj *volatile free_list[_NFREELIST];

    static char *start_free;  // memory pool start address
    static char *end_free;    // memory pool end address
    static size_t heap_size;

    // choose freelist index by block size, it will align to nearest eight bytes
    static size_t FREELIST_INDEX(size_t bytes) { return ((bytes + _ALIGN - 1) / _ALIGN - 1); }

    // align to nearest eight bytes
    static size_t ROUND_UP(size_t bytes) { return ((bytes + _ALIGN - 1) & ~(_ALIGN - 1)); }

    // init empty free list, return 1 to client, add n - 1 to free list
    static void *refill(size_t bytes);

    // get memory from pool, pool will try to allocate enough memory,
    // when failed, nobjs will be change to block count which pool can afford
    static char *chunk_alloc(size_t bytes, size_t &nobjs);

public:
    static void *allocate(size_t bytes);

    static void deallocate(void *ptr, size_t bytes);

    static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
};

}  // end of namespace EasySTL

#endif
