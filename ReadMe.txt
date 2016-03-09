To build:
Use Visual Studio 2015 - I used Update 2 RC, because that was the first version that could build the rest of the main software I cared about.
Get Boost binaries from here: https://sourceforge.net/projects/boost/files/boost-binaries/1.60.0/ - you wan thte msvc14 ones, in 32 or 64, or you want the msvc all package.

There's a property sheet specifying how to find Boost and link to the required libraries - you'll have to pardon my lack of experience with raw visual studio projects, I usually use CMake.

Look at the .cpp file - you'll see there's one #define or #undef line: switching between #define and #undef will change between two chunks of code that either do or don't build with MSVC 2015 Update 2 RC.

The one that doesn't build is the define - it has the additional parameter on the end to specify that we want alignment for the offset ptr. Consequently we get a whole pile of errors like those below.

Note that the code that doesn't build here, builds fine in VS 2013, as well as GCC on MinGW64 in MSYS2 (though I don't know what ifdefs live inside boost that make the code built there different).

This is the minimum Boost IPC consuming code to exhibit this.

(Note: I tried to build with clang/c2, but it was wholly unsatisfying, presumably because Boost isn't ready to deal with clang/c2: lots of ignored pragmas and references to intrinsics, and the errors that are fatal are "can't mangle this C11 atomic type yet" in boost\smart_ptr\detail\sp_counted_base_clang.hpp - so sorry, not sure if it's front-end or back-end or, perhaps, a latent bug in usage.)

1>------ Build started: Project: BoostIPCSample, Configuration: Release Win32 ------
1>  BoostIPCSample.cpp
1>C:\local\boost_1_60_0\boost/intrusive/detail/bstree_algorithms_base.hpp(97): error C2719: 'node': formal parameter with requested alignment of 8 won't be aligned
1>  C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(169): note: see reference to class template instantiation 'boost::intrusive::bstree_algorithms_base<NodeTraits>' being compiled
1>          with
1>          [
1>              NodeTraits=boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/rbtree_algorithms.hpp(170): note: see reference to class template instantiation 'boost::intrusive::bstree_algorithms<NodeTraits>' being compiled
1>          with
1>          [
1>              NodeTraits=boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/detail/generic_hook.hpp(138): note: see reference to class template instantiation 'boost::intrusive::rbtree_algorithms<boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<T,my_ptrdiff,my_uintptr,8>,true>>' being compiled
1>          with
1>          [
1>              T=void
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/detail/get_value_traits.hpp(105): note: see reference to class template instantiation 'boost::intrusive::generic_hook<boost::intrusive::rbtree_algorithms<boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<T,my_ptrdiff,my_uintptr,8>,true>>,boost::intrusive::hook_defaults::tag,boost::intrusive::normal_link,boost::intrusive::RbTreeBaseHookId>' being compiled
1>          with
1>          [
1>              T=void
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/detail/get_value_traits.hpp(105): note: see reference to class template instantiation 'boost::intrusive::detail::internal_base_hook_bool<T>' being compiled
1>          with
1>          [
1>              T=boost::intrusive::generic_hook<boost::intrusive::rbtree_algorithms<boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>>,boost::intrusive::hook_defaults::tag,boost::intrusive::normal_link,boost::intrusive::RbTreeBaseHookId>
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/detail/get_value_traits.hpp(204): note: see reference to class template instantiation 'boost::intrusive::detail::internal_base_hook_bool_is_true<SupposedValueTraits>' being compiled
1>          with
1>          [
1>              SupposedValueTraits=boost::intrusive::generic_hook<boost::intrusive::rbtree_algorithms<boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>>,boost::intrusive::hook_defaults::tag,boost::intrusive::normal_link,boost::intrusive::RbTreeBaseHookId>
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/set.hpp(890): note: see reference to class template instantiation 'boost::intrusive::detail::get_value_traits<T,boost::intrusive::generic_hook<boost::intrusive::rbtree_algorithms<boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>>,boost::intrusive::hook_defaults::tag,boost::intrusive::normal_link,boost::intrusive::RbTreeBaseHookId>>' being compiled
1>          with
1>          [
1>              T=boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl
1>          ]
1>  C:\local\boost_1_60_0\boost/interprocess/mem_algo/rbtree_best_fit.hpp(143): note: see reference to class template instantiation 'boost::intrusive::make_multiset<boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<T,my_ptrdiff,my_uintptr,8>,0>::block_ctrl,boost::intrusive::base_hook<boost::intrusive::generic_hook<boost::intrusive::rbtree_algorithms<boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<T,my_ptrdiff,my_uintptr,8>,true>>,boost::intrusive::hook_defaults::tag,boost::intrusive::normal_link,boost::intrusive::RbTreeBaseHookId>>,void,void,void,void,void>' being compiled
1>          with
1>          [
1>              T=void
1>          ]
1>  C:\local\boost_1_60_0\boost/interprocess/managed_shared_memory.hpp(44): note: see reference to class template instantiation 'boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<T,my_ptrdiff,my_uintptr,8>,0>' being compiled
1>          with
1>          [
1>              T=void
1>          ]
1>  C:\local\boost_1_60_0\boost/interprocess/managed_shared_memory.hpp(61): note: see reference to class template instantiation 'boost::interprocess::ipcdetail::shmem_open_or_create<AllocationAlgorithm>' being compiled
1>          with
1>          [
1>              AllocationAlgorithm=boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>
1>          ]
1>  BoostIPCSample.cpp(55): note: see reference to class template instantiation 'boost::interprocess::basic_managed_shared_memory<char,boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<T,my_ptrdiff,my_uintptr,8>,0>,index_type>' being compiled
1>          with
1>          [
1>              T=void
1>          ]
1>C:\local\boost_1_60_0\boost/intrusive/detail/bstree_algorithms_base.hpp(114): error C2719: 'node': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(1777): error C2719: 'vine_tail': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(1804): error C2719: 'scanner': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(1955): error C2719: 'x': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(1971): error C2719: 'x': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(1971): error C2719: 'y': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(1987): error C2719: 'x': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/bstree_algorithms.hpp(1987): error C2719: 'y': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/rbtree_algorithms.hpp(435): error C2719: 'x': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/rbtree_algorithms.hpp(435): error C2719: 'x_parent': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/rbtree_algorithms.hpp(519): error C2719: 'p': formal parameter with requested alignment of 8 won't be aligned
1>C:\local\boost_1_60_0\boost/intrusive/detail/is_stateful_value_traits.hpp(67): error C2719: 'unnamed-parameter': formal parameter with requested alignment of 8 won't be aligned
1>  C:\local\boost_1_60_0\boost/intrusive/bstree.hpp(102): note: see reference to class template instantiation 'boost::intrusive::detail::is_stateful_value_traits<boost::intrusive::bhtraits<T,boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>,boost::intrusive::normal_link,boost::intrusive::dft_tag,3>>' being compiled
1>          with
1>          [
1>              T=boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/bstree.hpp(280): note: see reference to class template instantiation 'boost::intrusive::bstbase3<ValueTraits,boost::intrusive::RbTreeAlgorithms,HeaderHolder>' being compiled
1>          with
1>          [
1>              ValueTraits=boost::intrusive::bhtraits<boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl,boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>,boost::intrusive::normal_link,boost::intrusive::dft_tag,3>,
1>              HeaderHolder=boost::intrusive::bstree_defaults::header_holder_type
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/bstree.hpp(508): note: see reference to class template instantiation 'boost::intrusive::bstbase2<ValueTraits,VoidOrKeyOfValue,VoidOrKeyComp,boost::intrusive::RbTreeAlgorithms,HeaderHolder>' being compiled
1>          with
1>          [
1>              ValueTraits=boost::intrusive::bhtraits<boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl,boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>,boost::intrusive::normal_link,boost::intrusive::dft_tag,3>,
1>              VoidOrKeyOfValue=boost::intrusive::bstree_defaults::key_of_value,
1>              VoidOrKeyComp=boost::intrusive::bstree_defaults::compare,
1>              HeaderHolder=boost::intrusive::bstree_defaults::header_holder_type
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/bstree.hpp(562): note: see reference to class template instantiation 'boost::intrusive::bstbase_hack<ValueTraits,VoidOrKeyOfValue,VoidOrKeyComp,true,SizeType,boost::intrusive::RbTreeAlgorithms,HeaderHolder>' being compiled
1>          with
1>          [
1>              ValueTraits=boost::intrusive::bhtraits<boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl,boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>,boost::intrusive::normal_link,boost::intrusive::dft_tag,3>,
1>              VoidOrKeyOfValue=boost::intrusive::bstree_defaults::key_of_value,
1>              VoidOrKeyComp=boost::intrusive::bstree_defaults::compare,
1>              SizeType=boost::intrusive::bstree_defaults::size_type,
1>              HeaderHolder=boost::intrusive::bstree_defaults::header_holder_type
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/bstree.hpp(619): note: see reference to class template instantiation 'boost::intrusive::bstbase<ValueTraits,VoidOrKeyOfValue,VoidOrKeyComp,true,SizeType,boost::intrusive::RbTreeAlgorithms,HeaderHolder>' being compiled
1>          with
1>          [
1>              ValueTraits=boost::intrusive::bhtraits<boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl,boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>,boost::intrusive::normal_link,boost::intrusive::dft_tag,3>,
1>              VoidOrKeyOfValue=boost::intrusive::bstree_defaults::key_of_value,
1>              VoidOrKeyComp=boost::intrusive::bstree_defaults::compare,
1>              SizeType=boost::intrusive::bstree_defaults::size_type,
1>              HeaderHolder=boost::intrusive::bstree_defaults::header_holder_type
1>          ]
1>  C:\local\boost_1_60_0\boost/intrusive/set.hpp(541): note: see reference to class template instantiation 'boost::intrusive::bstree_impl<ValueTraits,VoidOrKeyOfValue,Compare,SizeType,true,boost::intrusive::RbTreeAlgorithms,HeaderHolder>' being compiled
1>          with
1>          [
1>              ValueTraits=boost::intrusive::bhtraits<boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl,boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>,boost::intrusive::normal_link,boost::intrusive::dft_tag,3>,
1>              VoidOrKeyOfValue=boost::intrusive::bstree_defaults::key_of_value,
1>              Compare=boost::intrusive::bstree_defaults::compare,
1>              SizeType=boost::intrusive::bstree_defaults::size_type,
1>              HeaderHolder=boost::intrusive::bstree_defaults::header_holder_type
1>          ]
1>  C:\local\boost_1_60_0\boost/interprocess/mem_algo/rbtree_best_fit.hpp(145): note: see reference to class template instantiation 'boost::intrusive::multiset_impl<boost::intrusive::bhtraits<T,boost::intrusive::rbtree_node_traits<boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,true>,boost::intrusive::normal_link,boost::intrusive::dft_tag,3>,boost::intrusive::bstree_defaults::key_of_value,boost::intrusive::bstree_defaults::compare,boost::intrusive::bstree_defaults::size_type,true,boost::intrusive::bstree_defaults::header_holder_type>' being compiled
1>          with
1>          [
1>              T=boost::interprocess::rbtree_best_fit<boost::interprocess::mutex_family,boost::interprocess::offset_ptr<void,my_ptrdiff,my_uintptr,8>,0>::block_ctrl
1>          ]