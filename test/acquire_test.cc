#include <gtest/gtest.h>
#include <acquire.hh>

namespace
{
	const uint8_t someBuffer[]{ 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x10, 0x20, 0x30 };

	class ISomeInterface
	{
		virtual int get10() { return 10; }
		virtual int get20() { return 20; }
	};

	using SomeFn = int(__thiscall*)();
}

TEST(AcquireTest, FromPattern)
{
	// Existing pattern in this module's constant data section
	{
		void* acquired{ acquire::fromPattern("AA BB CC DD EE FF 10 20 30", ".rdata") };
		ASSERT_NE(acquired, nullptr);
		EXPECT_EQ(acquired, &someBuffer);
	}

	// Non-existing pattern in this module's constant data section
	{
		void* acquired{ acquire::fromPattern("AA BB CC DD EE FF 30 20 10", ".rdata") };
		ASSERT_EQ(acquired, nullptr);
	}

}

TEST(AcquireTest, FromExport)
{
	// Get export via name from external module
	{
		void* exported{ acquire::fromExport("GetModuleHandleA", "kernel32.dll") };
		EXPECT_EQ(exported, &GetModuleHandleA);
	}

	// Get export via ordinal from external module
	{
		// I don't know how prone these are to change
#ifdef _WIN64
		uint16_t ordinalGetModuleHandleA{ 659 };
#else
		uint16_t ordinalGetModuleHandleA{ 655 };
#endif

		void* exported{ acquire::fromExport(ordinalGetModuleHandleA, "kernel32.dll") };
		EXPECT_EQ(exported, &GetModuleHandleA);
	}

}

TEST(AcquireTest, FromVTable)
{
	ISomeInterface someInterface;

	// Call get10 via vTable pointer
	{
		SomeFn vTableMethod{ acquire::fromVTable<SomeFn>(&someInterface, 0) };
		ASSERT_FALSE(IsBadReadPtr(vTableMethod, 1));

		EXPECT_EQ(vTableMethod(), 10);
	}

	// Call get20 via vTable pointer
	{
		SomeFn vTableMethod{ acquire::fromVTable<SomeFn>(&someInterface, 1) };
		ASSERT_FALSE(IsBadReadPtr(vTableMethod, 1));

		EXPECT_EQ(vTableMethod(), 20);
	}

	// Call non-existent (out-of-bounds) method via vTable pointer
	{
		SomeFn vTableMethod{ acquire::fromVTable<SomeFn>(&someInterface, 2) };
		EXPECT_DEATH(vTableMethod(), ".*");
	}

}
