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

		virtual bool Update(uint32_t frame_number, float elasped) = 0;

		virtual int Shutdown() = 0;

		tinystl::string GetProgramName() const { return m_sProgramName; }

	protected:

		tinystl::string m_sProgramName;
	};
}
