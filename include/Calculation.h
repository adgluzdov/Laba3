#pragma once
#include <stack>
#include <string>
using namespace std;
class Calculation
{
public:
	static double Calculate(string);
	static string Parsing(string);
	static double Counting(string);
	static string SetVariables(string);
private:
	static bool IsDelimeter(char);
	static bool IsOperator(char);
	static int GetPriority(char);
	static bool IsVariable(char);
	static void Error(int);
};

