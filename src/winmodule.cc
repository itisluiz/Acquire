#include <acquire/winmodule.hh>

namespace acquire
{
	WinModule::WinModule() : m_module{ GetModuleHandleW(NULL) } { }

	WinModule::WinModule(HMODULE hModule) : m_module{ hModule } { }

	WinModule::WinModule(const char* moduleName) : m_module{ GetModuleHandleA(moduleName) } { }

	WinModule::WinModule(const wchar_t* moduleName) : m_module{ GetModuleHandleW(moduleName) } { }

	HMODULE WinModule::getModule() const
	{
		return m_module;
	}

	HMODULE WinModule::operator&() const
	{
		return m_module;
	}

	WinModule::operator HMODULE() const
	{
		return m_module;
	}

	WinModule::operator bool() const
	{
		return m_module;
	}

}
