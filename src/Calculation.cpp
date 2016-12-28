#include "Calculation.h"
#include <string>
#include <cctype>
#include <iostream>
#include <math.h>
using namespace std;

Calculation::Calculation()
{
	Vars = new Var;
	Vars->next = NULL;
}
Calculation::~Calculation()
{
	delete Vars;
}
double Calculation::Calculate(string input)
{
    string output = SetVariables(input);
	output = Parsing(output);

    double result = Counting(output);
    return result;
}
void Calculation::addVars(char a, double v)
{
	Var* buf = Vars;
	int ex = 0;
	while (buf) {
		if (a == buf->ch) {
			ex = 1;
			break;
		}
		buf = buf->next;
	}

	if (ex)
		buf->val = v;
	else {
		Var* newvar = new Var;
		newvar->ch = a;
		newvar->val = v;
		newvar->next = Vars;
		Vars = newvar;
	}
}
string Calculation::SetVariables(string input) // �����, ��������������� ������������ ��������� ���������� ��������� ����������� (��� ������� �����������)
{
    for (int i = 0; i < input.length(); i++) //��� ������� ������� � ������
    {
		if(IsVariable(input[i])){
			Var* buf = Vars;
			bool flag = true;
			while(flag)
			{
				if(buf->ch == input[i]){
					input[i] = buf->val + '0';
					flag = false;
				}
				buf = buf->next;
			}
		}
	}
	return input;
}
string Calculation::Parsing(string input)
{
	string output = ""; //������ ��� �������� ���������
    Stack<char> operStack; //���� ��� �������� ����������
	bool flag = false;
	for (int i = 0; i < input.length(); i++) // �������� �� ������� ����������� ��������
    {
		if((!IsVariable(input[i])) && (!IsDelimeter(input[i])) && (!isdigit(input[i])) && (!IsOperator(input[i])))
			Error(4);
	}

	for (int i = 0; i < input.length(); i++) //��� ������� ������� � ������� ������
    {
		
        //����������� ����������
        if (IsDelimeter(input[i]))
             continue; //��������� � ���������� �������
        
        //���� ������ - �����, �� ��������� ��� �����
        if (isdigit(input[i])) //���� �����
        {
             //������ �� ����������� ��� ���������, ��� �� �������� �����
             while (!IsDelimeter(input[i]) && !IsOperator(input[i]))
             {
                 output += input[i]; //��������� ������ ����� ����� � ����� ������
                 i++; //��������� � ���������� �������

				 if (i == input.length()) break; //���� ������ - ���������, �� ������� �� �����
             }

             output += " "; //���������� ����� ����� ������ � ������ � ����������
             i--; //������������ �� ���� ������ �����, � ������� ����� ������������
        }
        //���� ������ - ��������
        if (IsOperator(input[i])) //���� ��������
        {
            if (input[i] == '(') //���� ������ - ����������� ������
                operStack.push(input[i]); //���������� � � ����
            else if (input[i] == ')') //���� ������ - ����������� ������
            {
                //���������� ��� ��������� �� ����������� ������ � ������
                char s = operStack.gettop();
				operStack.pop();

                while (s != '(')
                {
                    output += s;
					output += " ";
                    s = operStack.gettop();
					operStack.pop();
                }
            }else if (input[i] == '|' && !flag) //���� ������ - ����������� ������
			{
                operStack.push(input[i]); //���������� � � ����
				flag = true;
			}
            else if (input[i] == '|' && flag) //���� ������ - ����������� ������
            {
                //���������� ��� ��������� �� ����������� ������ � ������
                char s = operStack.gettop();
				operStack.pop();

				while (s != '|')
                {
                    output += s;
					output += " ";
                    s = operStack.gettop();
					operStack.pop();
                }
                operStack.push(input[i]); //���� ���� ����, ��� �� ��������� ��������� ���� - ��������� ���������� �� ������� �����
				flag = false;
            }
            else //���� ����� ������ ��������
            {
				if (input.length() == i+1 || (IsOperator(input[i+1]) && (input[i+1] != '(') && (input[i+1] != ')') && (input[i+1] != '|') && !((input[i]=='-' || input[i]=='+') && (input[i+1]=='-' || input[i+1]=='+')) ))
					Error(2);
				if (!operStack.empty()) //���� � ����� ���� ��������
						if (GetPriority(input[i]) <= GetPriority(operStack.gettop()) ){ //� ���� ��������� ������ ��������� ������ ��� ����� ���������� ��������� �� ������� �����
							output += operStack.gettop(); //�� ��������� ��������� �������� �� ����� � ������ � ����������
							output += " ";
							operStack.pop();
						}
                operStack.push(input[i]); //���� ���� ����, ��� �� ��������� ��������� ���� - ��������� ���������� �� ������� �����
				while(input.length() > i+1 && ((input[i+1] =='-' || input[i+1]=='+') && (operStack.gettop() =='-' || operStack.gettop() =='+')) ) // ���������� ���������� ���� --++-+-+-
				{
					operStack.push(input[i]);
					i++;
				}
            }
        }
    }

	

    //����� ������ �� ���� ��������, ���������� �� ����� ��� ���������� ��� ��������� � ������
	while (!operStack.empty()){
        output += operStack.gettop();
		output += " ";
		operStack.pop();
	
	}
    return output; //���������� ��������� � ����������� ������
}

double Calculation::Counting(string input)
{
	double result = 0; //���������
    Stack<double> temp; //��������� ���� ��� �������

    for (int i = 0; i < input.length(); i++) //��� ������� ������� � ������
    {
        //���� ������ - �����, �� ������ ��� ����� � ���������� �� ������� �����
        if (isdigit(input[i])) 
        {
            string a = "";

            while (!IsDelimeter(input[i]) && !IsOperator(input[i])) //���� �� �����������
            {
                a += input[i]; //���������
                i++;
				if (i == input.length()) break;
            }
            temp.push(stod(a)); //���������� � ����
            i--;
        }
        else if (IsOperator(input[i])) //���� ������ - ��������
        {
            //����� ��� ��������� �������� �� �����
            double a = temp.gettop(); 
			temp.pop();
			if(!temp.empty())
			{
				double b = temp.gettop();
				temp.pop();
				switch (input[i]) //� ���������� ��� ���� ��������, �������� ���������
				{ 
					case '+': result = b + a; break;
					case '-': result = b - a; break;
					case '*': result = b * a; break;
					case '/': if(a==0) Error(3); result = b / a;  break;
					case '^': result = pow(b,a); break;
				}
				temp.push(result); //��������� ���������� ���������� ������� � ����
			}
			else if(input[i] == '|')
				temp.push(abs(a));
			else if(input[i] == '-')
				temp.push(a*(-1));
			else if(input[i] == '+')
				temp.push(a);
			else
				Error(2);
            
        }
    }
	if(!temp.empty())
		return temp.gettop(); //�������� ��������� ���� ���������� �� ����� � ���������� ���
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
		case 5: _return = "ERROR: unknow varibale!"; break;
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
bool Calculation::IsOperator(char �)
{
	string str = "+-/*^()|";
    if ((str.find(�) != -1))
        return true;
    return false;
}
int Calculation::GetPriority(char s)
{
    switch (s)
    {
        case '|': return 0;
        case '(': return 1;
		case ')': return 2;
        case '+': return 3;
        case '-': return 4;
        case '*': return 5;
        case '/': return 6;
        case '^': return 7;
        default: return 8;
    }
}