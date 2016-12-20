#include "Calculation.h"
#include <stack>
#include <string>
#include <cctype>
#include <iostream>
#include <math.h>
using namespace std;

double Calculation::Calculate(string input)
{
    string output = SetVariables(input);
	output = Parsing(output);

    double result = Counting(output);
    return result;
}
string Calculation::SetVariables(string input) // Ввод переменных в выражении
{
    for (int i = 0; i < input.length(); i++) //Для каждого символа в строке
    {
		while(IsVariable(input[i]))
		{
			cout<< "Enter "<<input[i]<<" = ";
			cin >> input[i];
		}
	}
	return input;
}
string Calculation::Parsing(string input)
{
	string output = ""; //Строка для хранения выражения
    stack<char> operStack; //Стек для хранения операторов

	for (int i = 0; i < input.length(); i++) // Проверка на наличие неизвестных символов
    {
		if((!IsVariable(input[i])) && (!IsDelimeter(input[i])) && (!isdigit(input[i])) && (!IsOperator(input[i])))
			Error(4);
	}

	for (int i = 0; i < input.length(); i++) //Для каждого символа в входной строке
    {
		
        //Разделители пропускаем
        if (IsDelimeter(input[i]))
             continue; //Переходим к следующему символу
        
        //Если символ - цифра, то считываем все число
        if (isdigit(input[i])) //Если цифра
        {
             //Читаем до разделителя или оператора, что бы получить число
             while (!IsDelimeter(input[i]) && !IsOperator(input[i]))
             {
                 output += input[i]; //Добавляем каждую цифру числа к нашей строке
                 i++; //Переходим к следующему символу

				 if (i == input.length()) break; //Если символ - последний, то выходим из цикла
             }

             output += " "; //Дописываем после числа пробел в строку с выражением
             i--; //Возвращаемся на один символ назад, к символу перед разделителем
        }
        //Если символ - оператор
        if (IsOperator(input[i])) //Если оператор
        {
            if (input[i] == '(') //Если символ - открывающая скобка
                operStack.push(input[i]); //Записываем её в стек
            else if (input[i] == ')') //Если символ - закрывающая скобка
            {
                //Выписываем все операторы до открывающей скобки в строку
                char s = operStack.top();
				operStack.pop();

                while (s != '(')
                {
                    output += s;
					output += " ";
                    s = operStack.top();
					operStack.pop();
                }
            }
            else //Если любой другой оператор
            {
				if (input.length() == i+1 || (IsOperator(input[i+1]) && (input[i+1] != '(') && (input[i+1] != ')')))
					Error(2);
				if (!operStack.empty()) //Если в стеке есть элементы
                    if (GetPriority(input[i]) <= GetPriority(operStack.top())){ //И если приоритет нашего оператора меньше или равен приоритету оператора на вершине стека
                        output += operStack.top(); //То добавляем последний оператор из стека в строку с выражением
						output += " ";
						operStack.pop();
					}
                operStack.push(input[i]); //Если стек пуст, или же приоритет оператора выше - добавляем операторов на вершину стека

            }
        }
    }

	

    //Когда прошли по всем символам, выкидываем из стека все оставшиеся там операторы в строку
	while (!operStack.empty()){
        output += operStack.top();
		output += " ";
		operStack.pop();
	
	}
    return output; //Возвращаем выражение в постфиксной записи
}

double Calculation::Counting(string input)
{
	double result = 0; //Результат
    stack<double> temp; //Временный стек для решения

    for (int i = 0; i < input.length(); i++) //Для каждого символа в строке
    {
        //Если символ - цифра, то читаем все число и записываем на вершину стека
        if (isdigit(input[i])) 
        {
            string a = "";

            while (!IsDelimeter(input[i]) && !IsOperator(input[i])) //Пока не разделитель
            {
                a += input[i]; //Добавляем
                i++;
				if (i == input.length()) break;
            }
            temp.push(stod(a)); //Записываем в стек
            i--;
        }
        else if (IsOperator(input[i])) //Если символ - оператор
        {
            //Берем два последних значения из стека
            double a = temp.top(); 
			temp.pop();
			if(!temp.empty())
			{
				double b = temp.top();
				temp.pop();
				switch (input[i]) //И производим над ними действие, согласно оператору
				{ 
					case '+': result = b + a; break;
					case '-': result = b - a; break;
					case '*': result = b * a; break;
					case '/': if(a==0) Error(3); result = b / a;  break;
					case '^': result = pow(b,a); break;
				}
				temp.push(result); //Результат вычисления записываем обратно в стек
			}else
				Error(2);
            
        }
    }
	if(!temp.empty())
		return temp.top(); //Забираем результат всех вычислений из стека и возвращаем его
	else
		Error(1);
}

bool Calculation::IsDelimeter(char c)
{
	string str = " =";
    if ((str.find(c) != -1))
        return true;
    return false;
}
void Calculation::Error(const int key)
{
	string _return;
	switch (key)
	{ 
		case 1: _return = "ERROR: expression is empty!"; break;
		case 2: _return = "ERROR: expression is not correct!"; break;
		case 3: _return = "ERROR: division by zero is not allowed!"; break;
		case 4: _return = "ERROR: unknow operator!"; break;
		default: _return = "ERROR"; break;
	}
	cout << _return << endl;
	throw key;
}
bool Calculation::IsVariable(char c)
{
	string str = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    if ((str.find(c) != -1))
        return true;
    return false;
}
bool Calculation::IsOperator(char с)
{
	string str = "+-/*^()";
    if ((str.find(с) != -1))
        return true;
    return false;
}
int Calculation::GetPriority(char s)
{
    switch (s)
    {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 4;
        case '^': return 5;
        default: return 6;
    }
}