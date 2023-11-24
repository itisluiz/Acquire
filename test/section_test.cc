#include <gtest/gtest.h>
#include <acquire/section.hh>

namespace
{
	void someMethod() { };
}

TEST(SectionTest, SectionNameConstructor)
{
	// Main module non-existent section
	{
		acquire::Section section("");
		EXPECT_FALSE(section);
	}

	// Main module existent section
	{
		acquire::Section sectionLower(".text");
		acquire::Section sectionUpper(".TEXT");

		ASSERT_TRUE(sectionLower);
		EXPECT_EQ(&sectionLower, &sectionUpper);
	}

	// Main module's code is in code section
	{
		acquire::Section section(".text");

		ASSERT_TRUE(section);
		EXPECT_LT(someMethod, section.end());
		EXPECT_GT(someMethod, section.begin());
	}

}

TEST(SectionTest, SectionNameWinModuleConstructor)
{
	// Main module existent section, non existent module
	{
		acquire::Section section(".text", "");
		EXPECT_FALSE(section);
	}

	// Main module existent section in existent module
	{
		acquire::Section section(".text", "kernel32.dll");
		EXPECT_TRUE(section);
		EXPECT_EQ(section.getModule(), GetModuleHandleA("kernel32.dll"));
	}

	// External module's code is in code section
	{
		acquire::Section section(".text", "kernel32.dll");

		ASSERT_TRUE(section);
		EXPECT_LT(GetModuleHandleA, section.end());
		EXPECT_GT(GetModuleHandleA, section.begin());
	}

}
