#pragma once
#include <optional>
#include <vector>
#include <string>

namespace acquire
{
    /**
     * @brief Represents a pattern for searching byte sequences within memory.
     *
     * The Pattern class allows the creation and application of patterns to search for specific byte
     * sequences within memory regions. It includes methods for obtaining offset, accessing bytes,
     * and searching for matches within a given memory range. Allows for byte wildcards in searches.
     */
    class Pattern
    {
        ptrdiff_t m_offset;
        std::vector<std::optional<uint8_t>> m_bytes;

    public:
        /**
         * @brief Constructs a Pattern using an IDA-style pattern string.
         *
         * @param idaPattern The IDA-style pattern string to initialize the Pattern. E.g: "AA ?? ?? CC DD".
         * @param offset The offset to be used in pattern matching. Default is 0.
         */
        Pattern(const char* idaPattern, ptrdiff_t offset = 0);

        /**
         * @brief Constructs a Pattern using a buffer and a mask string.
         *
         * @param buffer The buffer containing the byte sequence pattern.
         * @param mask The mask string specifying which bytes in the buffer to consider. E.g: "xx??x?x".
         * @param offset The offset to be used in pattern matching. Default is 0.
         */
        Pattern(const void* buffer, const std::string& mask, ptrdiff_t offset = 0);

    public:
        /**
         * @brief Gets the offset used in pattern matching.
         *
         * @return The offset value.
         */
        ptrdiff_t getOffset() const;

        /**
         * @brief Gets the byte sequence pattern.
         *
         * @return A reference to the vector containing optional byte values.
         */
        const decltype(m_bytes)& getBytes() const;

        /**
         * @brief Matches the pattern within a specified memory range.
         *
         * This method searches for the pattern within the specified memory range,
         * returning a pointer to the first occurrence if found, otherwise nullptr.
         *
         * @param begin The beginning of the memory range to search.
         * @param end The end of the memory range to search.
         * @return A pointer to the first occurrence of the pattern, or nullptr if not found.
         */
        void* match(const void* begin, const void* end) const;

    };

}
