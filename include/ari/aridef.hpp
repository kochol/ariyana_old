#pragma once

#if defined( _MSC_VER )
#	pragma warning(disable:4251) // dll interface for std types
#	define ARI_EXPORT_DLL __declspec(dllexport)
#	define ARI_IMPORT_DLL __declspec(dllimport)
#else
#	define ARI_EXPORT_DLL __attribute__((visibility("default")))
#	define ARI_IMPORT_DLL
#endif

#ifdef ARI_EXPORT
#	define ARI_API ARI_EXPORT_DLL
#else
#	define ARI_API ARI_IMPORT_DLL
#endif

#ifdef ARI_PLUGIN_EXPORT
#	define ARI_PLUGIN_API ARI_EXPORT_DLL
#else
#	define ARI_PLUGIN_API ARI_IMPORT_DLL
#endif

#define ARI_CONFIG_MAX_WINDOW		   8
#define ENTRY_CONFIG_MAX_GAMEPADS	   4
#define ENTRY_WINDOW_FLAG_NONE         UINT32_C(0x00000000)
#define ENTRY_WINDOW_FLAG_ASPECT_RATIO UINT32_C(0x00000001)
#define ENTRY_WINDOW_FLAG_FRAME        UINT32_C(0x00000002)

// Define ARI_NO_RTTI to turn off RTTI. This requires using the ARI_DEFINE_TYPE and ARI_DECLARE_TYPE macros on all types
// that you wish to use as components or events. If you use ARI_NO_RTTI, also place ARI_TYPE_IMPLEMENTATION in a single cpp file.
//#define ARI_NO_RTTI

#ifndef ARI_NO_RTTI

#include <typeindex>
#include <typeinfo>
#define ARI_TYPE_IMPLEMENTATION

#else

#define ARI_TYPE_IMPLEMENTATION \
	ari::TypeIndex ari::Internal::TypeRegistry::nextIndex = 1; \
	\
	ARI_DEFINE_TYPE(ari::Events::OnEntityCreated);\
	ARI_DEFINE_TYPE(ari::Events::OnEntityDestroyed); \

#endif

namespace bx
{
	struct AllocatorI;
}
namespace ari
{
	ARI_API bx::AllocatorI* getDefaultAllocator();

	struct ARI_API TinyStlAllocator
	{
		static void* static_allocate(size_t _bytes);
		static void static_deallocate(void* _ptr, size_t /*_bytes*/);
	};

#ifndef ARI_NO_RTTI
	typedef std::type_index TypeIndex;

#define ARI_DECLARE_TYPE
#define ARI_DEFINE_TYPE(name)

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return std::type_index(typeid(T));
	}

#else
	typedef uint32_t TypeIndex;

	namespace Internal
	{
		class TypeRegistry
		{
		public:
			TypeRegistry()
			{
				index = nextIndex;
				++nextIndex;
			}

			TypeIndex getIndex() const
			{
				return index;
			}

		private:
			static TypeIndex nextIndex;
			TypeIndex index;
		};
	}

#define ARI_DECLARE_TYPE public: static ari::Internal::TypeRegistry __ari_type_reg
#define ARI_DEFINE_TYPE(name) ari::Internal::TypeRegistry name::__ari_type_reg

	template<typename T>
	TypeIndex getTypeIndex()
	{
		return T::__ari_type_reg.getIndex();
	}
#endif

} // namespace ari

#	define TINYSTL_ALLOCATOR ari::TinyStlAllocator
