#include <acquire/pattern.hh>
#include <sstream>
#include <algorithm>

namespace acquire
{
	Pattern::Pattern(const char* idaPattern, ptrdiff_t offset) : m_offset{ offset }
	{
		std::stringstream parser(idaPattern);

		parser.flags(std::ios::skipws | std::ios::hex);

		for (uint16_t buffer; parser >> buffer || !parser.eof();)
		{
			if (!parser.fail())
				m_bytes.push_back(static_cast<uint8_t>(buffer));
			else
			{
				m_bytes.push_back(std::nullopt);
				parser.clear();
				parser.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
			}
		}
	}

	Pattern::Pattern(const void* buffer, const std::string& mask, ptrdiff_t offset) : m_offset{ offset }
	{
		const uint8_t* pByte{ reinterpret_cast<const uint8_t*>(buffer) };

		for (size_t i{ 0 }; i < mask.size(); ++i)
			m_bytes.emplace_back(mask[i] == '?' ? std::nullopt : std::make_optional(pByte[i]));
	}

	ptrdiff_t Pattern::getOffset() const
	{
		return m_offset;
	}

	const decltype(Pattern::m_bytes)& Pattern::getBytes() const
	{
		return m_bytes;
	}

	void* Pattern::match(const void* begin, const void* end) const
	{
		auto findPredicate{ [](const uint8_t actualByte, const std::optional<uint8_t> expectedByte) { return !expectedByte || expectedByte.value() == actualByte; } };
		const void* result{ std::search(reinterpret_cast<const uint8_t*>(begin), reinterpret_cast<const uint8_t*>(end), m_bytes.begin(), m_bytes.end(), findPredicate) };

		if (result == end)
			return nullptr;

		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(result) + m_offset);
	}

}
