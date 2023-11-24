#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <acquire/pattern.hh>

TEST(PatternTest, IdaConstructor)
{
	// Normalized notation
	{
		acquire::Pattern pattern("AA BB ?? DD");
		EXPECT_THAT(pattern.getBytes(), testing::ElementsAre(0xAA, 0xBB, std::nullopt, 0xDD));	
	}

	// Leading and trailing whitespace
	{
		acquire::Pattern pattern("  AA BB ?? DD  ");
		EXPECT_THAT(pattern.getBytes(), testing::ElementsAre(0xAA, 0xBB, std::nullopt, 0xDD));
	}

	// One-unit tokens
	{
		acquire::Pattern pattern("A B ? D");
		EXPECT_THAT(pattern.getBytes(), testing::ElementsAre(0x0A, 0x0B, std::nullopt, 0x0D));
	}

	// Hex-prefixing
	{
		acquire::Pattern pattern("0xAA 0xBB 0x?? 0xDD");
		EXPECT_THAT(pattern.getBytes(), testing::ElementsAre(0xAA, 0xBB, std::nullopt, 0xDD));
	}

}

TEST(PatternTest, BufferMaskConstructor)
{
	const uint8_t buffer[]{ 0xAA, 0xBB, 0xCC, 0xDD };
	acquire::Pattern pattern(buffer, "xx?x");

	EXPECT_THAT(pattern.getBytes(), testing::ElementsAre(0xAA, 0xBB, std::nullopt, 0xDD));
}

TEST(PatternTest, Match)
{
	const uint8_t haystack[]{ 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

	// Find existing with wildcard
	{
		acquire::Pattern pattern("BB CC ?? EE");
		EXPECT_THAT(pattern.match(haystack, haystack + sizeof(haystack)), haystack + 1);
	}

	// Find existing and offset to beginning
	{
		acquire::Pattern pattern("EE FF", -4);
		EXPECT_THAT(pattern.match(haystack, haystack + sizeof(haystack)), haystack);
	}

	// Find non-existent
	{
		acquire::Pattern pattern("BB CC AA EE");
		EXPECT_THAT(pattern.match(haystack, haystack + sizeof(haystack)), nullptr);
	}

}
