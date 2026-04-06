#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <list>

# define RPN_STACK_LIST std::stack<int, std::list<int> >

bool argsCheck(int argc, char **argv)
{
	if (argc != 2)
		return (false);
	std::string arg = argv[1];
	for (size_t i = 0; i < arg.size(); i++)
		if (arg.find_first_not_of("+-*/1234567890 ") != std::string::npos)
			return (false);
	return (true);
}

bool isOperator(std::string &token)
{
	if (token.size() != 1)
		return (false);
	if (token.find_first_not_of("+-*/") != std::string::npos)
		return (false);
	return (true);
}

bool isValidNumber(std::string &token)
{
	if (token.size() != 1)
		return (false);
	if (token.find_first_not_of("0123456789") != std::string::npos)
		return (false);
	return (true);
}

bool	manageOpe(std::string &token, RPN_STACK_LIST &stack)
{
	if (stack.size() < 2)
		return (false);
	int result;
	int a = stack.top();
	stack.pop();
	int b = stack.top();
	stack.pop();
	if (token[0] == '*')
		result = b * a;
	else if (token[0] == '-')
		result = b - a;
	else if (token[0] == '+')
		result = b + a;
	else if (token[0] == '/')
	{
		if (a == 0)
			return (false);	//divide by 
		result = b / a;
	}
	stack.push(result);
	return (true);
}

void	addNumber(std::string &token, RPN_STACK_LIST &stack)
{
	std::istringstream iss(token);
	int val;

	iss >> val;
	stack.push(val);
}

bool	manageToken(std::string &token, RPN_STACK_LIST &stack)
{
	if (isOperator(token))
		return (manageOpe(token, stack));
	else if (isValidNumber(token))
		addNumber(token, stack);
	else
		return (false);
	return (true);
}

void printStack(RPN_STACK_LIST stack)
{
	std::cout << " -- ";
	while (stack.size())
	{
		std::cout << "[" << stack.top() << "] ";
		stack.pop();
	}
	std::cout << "--" << std::endl;
}

int main(int argc, char **argv)
{
	if (!argsCheck(argc, argv))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	RPN_STACK_LIST stack;
	std::istringstream iss(argv[1]);
	std::string token;
	while (iss >> token)
	{
		if (!manageToken(token, stack))
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		//printStack(stack);
	}
	if (stack.size() != 1)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	std::cout << stack.top() << std::endl;
	return (0);
}