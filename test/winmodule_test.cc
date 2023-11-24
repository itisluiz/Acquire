#include <gtest/gtest.h>
#include <acquire/winmodule.hh>

TEST(WinModuleTest, DefaultConstructor)
{
	acquire::WinModule winModule;

	ASSERT_TRUE(winModule);
	EXPECT_EQ(&winModule, GetModuleHandleW(NULL));
}

TEST(WinModuleTest, ModuleNameConstructor)
{
	// Narrow chars
	{
		acquire::WinModule winModule("kernel32.dll");

		ASSERT_TRUE(winModule);
		EXPECT_EQ(winModule, GetModuleHandleA("kernel32.dll"));
	}

	// Wide chars
	{
		acquire::WinModule winModule(L"kernel32.dll");

		ASSERT_TRUE(winModule);
		EXPECT_EQ(winModule, GetModuleHandleW(L"kernel32.dll"));
	}

}

TEST(WinModuleTest, BoolOperator)
{
	// Existing module name
	{
		acquire::WinModule winModule("kernel32.dll");
		EXPECT_TRUE(winModule);
	}

	// Empty module name
	{
		acquire::WinModule winModule("");
		EXPECT_FALSE(winModule);
	}

}
