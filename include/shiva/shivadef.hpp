#pragma once

#if defined( _MSC_VER )
#	pragma warning(disable:4251) // dll interface for std types
#	ifdef SHIVA_EXPORT
#		define SHIVA_API __declspec(dllexport)
#	else
#		define SHIVA_API __declspec(dllimport)
#	endif
#else
#	ifdef SHIVA_EXPORT
#		define SHIVA_API __attribute__((visibility("default")))
#	else
#		define SHIVA_API
#	endif
#endif
