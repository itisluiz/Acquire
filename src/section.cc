#include <acquire/section.hh>

namespace acquire
{
	Section::Section(const char* targetSection, const WinModule& winModule) : m_module{ winModule }, m_section{ nullptr }
	{
		if (!winModule)
			return;

		PIMAGE_DOS_HEADER dosHeader{ reinterpret_cast<PIMAGE_DOS_HEADER>(&winModule) };
		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
			return;

		PIMAGE_NT_HEADERS ntHeader{ reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uintptr_t>(dosHeader) + dosHeader->e_lfanew) };
		if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
			return;

		PIMAGE_SECTION_HEADER sectionHeader{ IMAGE_FIRST_SECTION(ntHeader) };

		for (size_t sectionIndex{ 0 }; sectionIndex < ntHeader->FileHeader.NumberOfSections; ++sectionIndex)
		{
			if (stricmp(reinterpret_cast<const char*>(sectionHeader[sectionIndex].Name), targetSection) == 0)
			{
				m_section = sectionHeader + sectionIndex;
				break;
			}
		}
	}

	Section::Section(const char* targetSection) : Section(targetSection, WinModule()) { }

	HMODULE Section::getModule() const
	{
		return m_module;
	}

	IMAGE_SECTION_HEADER* Section::getHeader() const
	{
		return m_section;
	}

	void* Section::begin() const
	{
		if (!m_section)
			return nullptr;

		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(&m_module) + m_section->VirtualAddress);
	}

	void* Section::end() const
	{
		if (!m_section)
			return nullptr;

		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(begin()) + size());
	}

	size_t Section::size() const
	{
		if (!m_section)
			return 0;

		return m_section->SizeOfRawData;
	}

	IMAGE_SECTION_HEADER* Section::operator&() const
	{
		return m_section;
	}

	Section::operator IMAGE_SECTION_HEADER*() const
	{
		return m_section;
	}

	Section::operator bool() const
	{
		return m_section;
	}

}
