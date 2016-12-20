#include <gtest/gtest.h>
#include <cstdlib>
#include "Calculation.h"
#include <stack>
#include <string>
#include <cctype>
#include <iostream>
#include <math.h>
TEST(Calculation, throw_empty_expression)
{
	ASSERT_ANY_THROW(Calculation().Calculate(""));
}
TEST(Calculation, throw_empty_expression_only_brackets)
{
	ASSERT_ANY_THROW(Calculation().Calculate("()"));
}
TEST(Calculation, CanConst)
{
	EXPECT_EQ(Calculation().Calculate("1"),1);
}
TEST(Calculation, throw_brackets_is_not_valid)
{
	ASSERT_ANY_THROW(Calculation().Calculate("((1)"));
}
TEST(Calculation, CanSum)
{
	EXPECT_EQ(Calculation().Calculate("1+1"),2);
}
TEST(Calculation, CanMult)
{
	EXPECT_EQ(Calculation().Calculate("2*2"),4);
}
TEST(Calculation, CanSub)
{
	EXPECT_EQ(Calculation().Calculate("3-2"),1);
}
TEST(Calculation, CanDiv)
{
	EXPECT_EQ(Calculation().Calculate("2/2"),1);
}
TEST(Calculation, throw_div_by_zero)
{
	ASSERT_ANY_THROW(Calculation().Calculate("3/0"));
}
TEST(Calculation, CanPow)
{
	EXPECT_EQ(Calculation().Calculate("2^3"),8);
}
TEST(Calculation, throw_operators_is_not_valid_on_middle)
{
	ASSERT_ANY_THROW(Calculation().Calculate("3*+3"));
}
TEST(Calculation, throw_operators_is_not_valid_on_start)
{
	ASSERT_ANY_THROW(Calculation().Calculate("*3"));
}
TEST(Calculation, throw_operators_is_not_valid_on_finish)
{
	ASSERT_ANY_THROW(Calculation().Calculate("3*"));
}
TEST(Calculation, throw_operator_unknow)
{
	ASSERT_ANY_THROW(Calculation().Calculate("3%2"));
}
TEST(Calculation, CanCombo_1)	
{
	EXPECT_EQ(Calculation().Calculate("2^(2+1)+3*2"),14);
}
TEST(Calculation, CanCombo_2)
{
	EXPECT_EQ(Calculation().Calculate("(4^2-1+1)/(2+2)^2"),1);
}
TEST(Calculation, CanCombo_3)
{
	EXPECT_EQ(Calculation().Calculate("(1+3)*(3-1)^2"),16);
}
TEST(Calculation, CanCombo_4)
{
	EXPECT_EQ(Calculation().Calculate("2+2*(3^2)^2"),164);
}
TEST(Calculation, CanCombo_5)
{
	EXPECT_EQ(Calculation().Calculate("15/5 + (2+12)/7"),5);
}


int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  int _return = RUN_ALL_TESTS();
  system("pause");
  return _return;
}