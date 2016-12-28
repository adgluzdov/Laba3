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
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate(""));
}
TEST(Calculation, throw_empty_expression_only_brackets)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("()"));
}
TEST(Calculation, CanConst)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("1"),1);
}
TEST(Calculation, throw_brackets_is_not_valid)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("((1)"));
}
TEST(Calculation, can_variable1)
{
	Calculation calc;
	calc.addVars('x',2);
	EXPECT_EQ(calc.Calculate("x"),2);
}
TEST(Calculation, CanSum)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("1+1"),2);
}
TEST(Calculation, can_variable2)
{
	Calculation calc;
	calc.addVars('x',2);
	calc.addVars('y',3);
	EXPECT_EQ(calc.Calculate("x+y"),5);
}
TEST(Calculation, CanMult)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("2*2"),4);
}
TEST(Calculation, CanSub)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("3-2"),1);
}
TEST(Calculation, CanDiv)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("2/2"),1);
}
TEST(Calculation, throw_div_by_zero)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("3/0"));
}
TEST(Calculation, CanPow)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("2^3"),8);
}
TEST(Calculation, CanAbs)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("|2-4|"),2);
}
TEST(Calculation, throw_operators_is_not_valid_on_middle)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("3*+3"));
}
TEST(Calculation, throw_operators_is_not_valid_on_start)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("*3"));
}
TEST(Calculation, throw_operators_is_not_valid_on_finish)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("3*"));
}
TEST(Calculation, throw_operator_unknow)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("3%2"));
}
TEST(Calculation, CanCombo_1)	
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("2^(2+1)+3*2"),14);
}
TEST(Calculation, CanCombo_2)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("(4^2-1+1)/(2+2)^2"),1);
}
TEST(Calculation, CanCombo_3)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("(1+3)*(3-1)^2"),16);
}
TEST(Calculation, CanCombo_4)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("2+2*(3^2)^2"),164);
}
TEST(Calculation, CanCombo_5)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("15/5 + (2+12)/7"),5);
}
TEST(Calculation, can_unar_op1)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("-1"),-1);
}
TEST(Calculation, can_unar_op2)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("+1"),1);
}
TEST(Calculation, throw_112234214)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("-+-1"));
}
TEST(Calculation, throw_11233214)
{
	Calculation calculation;
	ASSERT_ANY_THROW(calculation.Calculate("--1"));
}
TEST(Calculation, CanCombo_6)
{
	Calculation calculation;
	EXPECT_EQ(calculation.Calculate("2^3^2"),64);
}



int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  int _return = RUN_ALL_TESTS();
  system("pause");
  return _return;
}