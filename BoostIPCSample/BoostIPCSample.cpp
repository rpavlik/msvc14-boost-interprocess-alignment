// BoostIPCSample.cpp : Defines the entry point for the console application.
//

#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <cstdint>

// The point of this chunk of code is to provide, using Boost, for 32/64
// interoperable shared memory.
// Boost IPC uses this concept of an "Offset Pointer", a sort of relative
// pointer, to be able to store more usefully complex/c++-like things in shared
// memory.

// As far as I can tell, the two parts switched between by this define operate
// relatively equivalently: at least, they're interoperable to the extent that I
// use them, but the underlying code is deep enough that I haven't mentally
// parsed the whole thing to figure out if they're actually the same.
#define WANT_TO_SEE_MSVC2015_2RC_NOT_BUILD

typedef std::int64_t my_ptrdiff;
typedef std::uint64_t my_uintptr;

#ifdef WANT_TO_SEE_MSVC2015_2RC_NOT_BUILD
template <typename T>
using ipc_offset_ptr =
    boost::interprocess::offset_ptr<T, my_ptrdiff, my_uintptr, 8>;
#else
template <typename T>
using ipc_offset_ptr =
    boost::interprocess::offset_ptr<T, my_ptrdiff, my_uintptr>;
#endif

template <class MutexFamily>
using my_mem_alloc_algo =
    boost::interprocess::rbtree_best_fit<MutexFamily, ipc_offset_ptr<void>>;

template <class IndexConfig>
using index_type = boost::interprocess::iset_index<IndexConfig>;

using basic_managed_shm = boost::interprocess::basic_managed_shared_memory<
    char, my_mem_alloc_algo<boost::interprocess::mutex_family>, index_type>;

int main() {
  basic_managed_shm segment(boost::interprocess::open_or_create, "sample_test", 65536);
  return 0;
}
