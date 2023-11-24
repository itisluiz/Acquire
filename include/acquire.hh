#pragma once
#include <acquire/pattern.hh>
#include <acquire/section.hh>

namespace acquire
{	
	/**
	 * @brief Matches a pattern pattern in a given section into a typed pointer.
	 *
	 * @tparam T The type of the pointer to be returned. Default is void*.
	 * @param pattern The Pattern object representing the search pattern.
	 * @param section The Section object representing the memory section to search within.
	 * @return A typed pointer to the matched location, casted to the specified type.
	 */
	template<typename T = void*>
	T fromPattern(const Pattern& pattern, const Section& section)
	{
		return reinterpret_cast<T>(pattern.match(section.begin(), section.end()));
	}

	/**
	 * @brief Retrieves a typed pointer to the specified export name from a Windows module.
	 *
	 * @tparam T The type of the pointer to be returned. Default is void*.
	 * @param exportName The name of the export to retrieve.
	 * @param winModule The WinModule object representing the Windows module from which the export originates.
	 * @return A typed pointer to the export, casted to the specified type.
	 */
	template<typename T = void*>
	T fromExport(const char* exportName, const WinModule& winModule)
	{
		return reinterpret_cast<T>(GetProcAddress(winModule, exportName));
	}

	/**
	 * @brief Retrieves a typed pointer to the export at the specified ordinal from a Windows module.
	 *
	 * @tparam T The type of the pointer to be returned. Default is void*.
	 * @param exportOrdinal The ordinal of the export to retrieve.
	 * @param winModule The WinModule object representing the Windows module from which the export originates.
	 * @return A typed pointer to the export, casted to the specified type.
	 */
	template<typename T = void*>
	T fromExport(uint16_t exportOrdinal, const WinModule& winModule)
	{
		return reinterpret_cast<T>(GetProcAddress(winModule, MAKEINTRESOURCEA(exportOrdinal)));
	}

	/**
	 * @brief Retrieves a typed pointer from the virtual function table (vtable) of an object at a specified index.
	 *
	 * @tparam T The type of the pointer to be returned. Default is void*.
	 * @param object The pointer to the object whose vtable is to be accessed.
	 * @param index The index of the function in the vtable.
	 * @return A typed pointer to the function in the vtable, casted to the specified type.
	 */
	template<typename T = void*>
	T fromVTable(const void* object, size_t index)
	{
		const void* const* vTable{ *reinterpret_cast<const void** const*>(object) };
		return reinterpret_cast<T>(vTable[index]);
	}

}
