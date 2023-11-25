#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <filesystem>

namespace acquire
{
    /**
     * @brief Represents a Windows module (DLL or executable).
     *
     * The WinModule class provides functionality to acquiring loaded modules in an overloaded fashion.
     */
    class WinModule
    {
        HMODULE m_module;

    public:
        /**
         * @brief Constructs a WinModule object associated with the base executable module for the current process.
         */
        WinModule();

        /**
         * @brief Constructs a WinModule object associated with an existing module handle.
         *
         * @param hModule The handle to the Windows module.
         */
        WinModule(HMODULE hModule);

        /**
         * @brief Constructs a WinModule object associated with a module handle acquried via module name.
         *
         * @param moduleName The name of the Windows module to acquire the handle for.
         */
        WinModule(const char* moduleName);

        /**
         * @brief Constructs a WinModule object associated with a module handle acquried via module name.
         *
         * @param moduleName The wide-character name of the Windows module to acquire the handle for.
         */
        WinModule(const wchar_t* moduleName);

    public:
        /**
         * @brief Gets the handle to the Windows module.
         *
         * @return The underlying handle to the Windows module.
         */
        HMODULE getModule() const;

        /**
         * @brief Gets the qualified path of the associated module.
         *
         * @return The file name of the associated module or an empty path if no module is associated.
         */
        std::filesystem::path modulePath();

    public:
        /**
         * @brief Overloads the address-of operator to return the module's handle.
         *
         * @return The underlying handle to the Windows module.
         */
        HMODULE operator&() const;

        /**
         * @brief Conversion operator to implicitly convert the WinModule object to a handle.
         *
         * @return The underlying handle to the Windows module.
         */
        operator HMODULE() const;

        /**
         * @brief Conversion operator to implicitly convert the WinModule object to a boolean value.
         *
         * @return true if the WinModule is valid (contains a module handle), false otherwise.
         */
        operator bool() const;

    };

}
