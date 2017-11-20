#include <iostream>
#include <cstdlib>
#include <cctype>

class Converter
{
	std::string infix, op;
	char opstack[200];
	int top;
	public:
	Converter()
	{
		top = -1;
		for (int i = 0; i < sizeof(opstack); i++)
		{
			opstack[i] = '\0';
		}
	}
	bool getInfix(std::string __infix)
	{
		if (__infix.empty()) return false;
		infix = "(" + __infix + ")";
		return true;
	}
	bool genPostfix() //Precedence is () > ^ > /,%,* > +,-
	{
		if (infix.empty()) return false;
		for (auto it = infix.begin(); it != infix.end(); it++)
		{
			if (!isalnum(*it))
			{
				if (*it == '(')
				{
					top++;
					opstack[top] = *it;
				}
				else if (*it == '^')
				{
					if (opstack[top] == '^')
					{
						op += opstack[top];
						opstack[top] = *it;
					}
					else
					{
						top++;
						opstack[top] = *it;
					}
				}
				else if (*it == '/' || *it == '*' || *it == '%')
				{
					int temptop = top, put = 0;
					while (temptop >= 0)
					{
						if ((opstack[temptop] == '^' || opstack[temptop] == '/' || opstack[temptop] == '*' || opstack[temptop] == '%') && put == 0)
						{
							op += opstack[temptop];
							put = 1;
							opstack[temptop] = *it;
						}
						else if (opstack[temptop] == '+' || opstack[temptop] == '-')
						{
							top++;
							put = 1;
							opstack[temptop + 1] = *it;
						}
						else if (opstack[temptop] == '(' && put == 0)
						{
							top++;
							put = 1;
							opstack[top] = *it;
							break;
						}
						temptop--;
					}
				}
				else if (*it == '+' || *it == '-')
				{
					int temptop = top, put = 0;
					while (temptop >= 0)
					{
						if ((opstack[temptop] == '^' || opstack[temptop] == '/' || opstack[temptop] == '*' || opstack[temptop] == '%' || opstack[temptop] == '+' || opstack[temptop] == '-'))
						{
							op += opstack[temptop];
							top--;
						}
						else if (opstack[temptop] == '(' && put == 0)
						{
							top++;
							put = 1;
							opstack[top] = *it;
							break;
						}
						temptop--;
					}
				}
				else if (*it == ')')
				{
					int temptop = top;
					while (opstack[temptop] != '(')
					{
						if (opstack[temptop] == '^' || opstack[temptop] == '/' || opstack[temptop] == '*' || opstack[temptop] == '%' || opstack[temptop] == '+' || opstack[temptop] == '-')
						{
							op += opstack[temptop];

							top = temptop - 1;
						}
						temptop--;
					}
					top = temptop-1;
				}
			}
			else
			{
				op += *it;
			}
			for (int i = top + 1; i < sizeof(opstack); i++)
			{
				opstack[i] = '\0';
			}
			if (top < 0)
				std::cout << "\nOperator: " << *it << "\t\tStack:  " << "\t\tOutput: " << op.c_str(); //Empty opstack (will not be perfectly tabular at last iteration when stack gets empty if this aint used)
			else
				std::cout << "\nOperator: " << *it << "\t\tStack: " << opstack << "\t\tOutput: " << op.c_str();
		}
		return true;
	}
	std::string getPostfix()
	{
		return op;
	}
};

int main()
{
	system("cls");
	std::string infix, postfix;
	char temp[200];
	std::cout << "Enter an infix expression: ";
	std::cin.getline(temp, 200);
	infix = temp;
	Converter pretopost;
	pretopost.getInfix(infix);
	pretopost.genPostfix();
	postfix = pretopost.getPostfix();
	std::cout << "\n\n\nPostfix: " << postfix.c_str() << std::endl << std::endl;
	system("pause");
	return 0;
}
