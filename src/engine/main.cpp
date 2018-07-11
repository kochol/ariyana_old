#include "../../include/ari/aridef.hpp"
#include "bx/allocator.h"

bx::AllocatorI* g_allocator = ari::getDefaultAllocator();

namespace ari
{
	bx::AllocatorI* getDefaultAllocator()
	{
		BX_PRAGMA_DIAGNOSTIC_PUSH();
		BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
		BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
		static bx::DefaultAllocator s_allocator;
		return &s_allocator;
		BX_PRAGMA_DIAGNOSTIC_POP();
	}

	void* TinyStlAllocator::static_allocate(size_t _bytes)
	{
		return BX_ALLOC(g_allocator, _bytes);
	}

	void TinyStlAllocator::static_deallocate(void* _ptr, size_t)
	{
		if (_ptr)
		{
			BX_FREE(g_allocator, _ptr);
		}
	}

}
