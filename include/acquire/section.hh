#pragma once
#include <acquire/winmodule.hh>

namespace acquire
{
    /**
     * @brief Represents a section within an module's memory layout.
     *
     * The Section class provides functionality acquire a specific section within
     * a module via it's name.
     */
    class Section
    {
        WinModule m_module;
        IMAGE_SECTION_HEADER* m_section;

    public:
        /**
         * @brief Constructs a Section object associated with a target section in a module.
         *
         * @param targetSection The case-insensitive name of the target section within the WinModule. E.g ".text".
         * @param winModule The WinModule object representing the module containing the section.
         */
        Section(const char* targetSection, const WinModule& winModule);

        /**
         * @brief Constructs a Section object associated with the base executable module.
         *
         * @param targetSection The case-insensitive name of the target section within the WinModule. E.g ".text".
         */
        Section(const char* targetSection);

    public:
        /**
         * @brief Gets the handle to the module associated with the section.
         *
         * @return A handle to the Windows module to which the associated section pertains to. NULL if no section is associated.
         */
        HMODULE getModule() const;

        /**
         * @brief Gets a pointer to the IMAGE_SECTION_HEADER structure of the section.
         *
         * @return Pointer to the associated IMAGE_SECTION_HEADER structure. nullptr if no section is associated.
         */
        IMAGE_SECTION_HEADER* getHeader() const;

        /**
         * @brief Gets a pointer to the beginning of the section's memory range.
         *
         * @return A pointer to the beginning of the section. nullptr if no section is associated.
         */
        void* begin() const;

        /**
         * @brief Gets a pointer to the end of the section's memory range.
         *
         * @return A pointer to the end of the section. nullptr if no section is associated.
         */
        void* end() const;

        /**
         * @brief Gets the size of the section in bytes.
         *
         * @return The size of the section in bytes. 0 if no section is associated.
         */
        size_t size() const;

    public:
        /**
         * @brief Overloads the address-of operator to return the section's header pointer.
         *
         * @return Pointer to the IMAGE_SECTION_HEADER structure.
         */
        IMAGE_SECTION_HEADER* operator&() const;

        /**
         * @brief Conversion operator to implicitly convert the Section object to a pointer to the IMAGE_SECTION_HEADER structure.
         *
         * @return Pointer to the IMAGE_SECTION_HEADER structure.
         */
        operator IMAGE_SECTION_HEADER*() const;

        /**
         * @brief Conversion operator to implicitly convert the Section object to a boolean value.
         *
         * @return true if the Section is valid (associated with a module), false otherwise.
         */
        operator bool() const;
    };

}
