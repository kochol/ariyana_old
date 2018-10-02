#pragma once
#include <tinystl/string.h>

namespace ari
{
	class IProgram
	{
	public:
		IProgram(const char* programName): m_sProgramName(programName) 
		{ }

		virtual ~IProgram() = default;

		virtual void Init() = 0;

		virtual bool Update() = 0;

		virtual int Shutdown() = 0;

	protected:

		tinystl::string m_sProgramName;
	};
}
