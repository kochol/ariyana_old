#pragma once

#if defined( _MSC_VER )
#ifdef ARI_EXPORT
	#define ARI_API __declspec(dllexport)
#else
	#define ARI_API __declspec(dllimport)
#endif
#else
	#define ARI_API
#endif

namespace bx
{
	struct AllocatorI;
}
namespace ari
{
	static bx::AllocatorI* getDefaultAllocator();

	struct ARI_API TinyStlAllocator
	{
		static void* static_allocate(size_t _bytes);
		static void static_deallocate(void* _ptr, size_t /*_bytes*/);
	};
} // namespace ari

#	define TINYSTL_ALLOCATOR ari::TinyStlAllocator
