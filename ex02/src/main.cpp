#include <iostream>
#include <sstream>
#include <istream>
#include <ostream>
#include <vector>
#include <deque>
#include <utility>
#include <sys/time.h>

#define PMERGE_VEC std::vector<int>
#define PMERGE_DQ std::deque<int>

#pragma region UTILS

long ft_getTime()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec);
}

bool checkValues(int argc, char **argv)
{
	int		i = 1;
	int		val;
	char 	c;

	while (i < argc)
	{
		std::istringstream iss(argv[i]);
		if (!(iss >> val))
			return (false);
		if (iss >> c || val < 0)
			return (false);
		i++;
	}
	return (true);
}
#pragma endregion

#pragma region VECTOR ALGORITHM

PMERGE_VEC buildJacobsthalVec(int n)
{
	PMERGE_VEC result;
	PMERGE_VEC jacob;

	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < n)
		jacob.push_back(jacob[jacob.size()-1] + 2 * jacob[jacob.size()-2]);

	for (size_t i = 1; i < jacob.size(); i++)
	{
		int from = jacob[i];
		int to = jacob[i-1];
		for (int j = from; j > to && j <= n; j--)
			result.push_back(j);
	}

	int last = jacob[jacob.size()-2];
	while (last < n)
		result.push_back(++last);

	return (result);
}

void	parseVect(int argc, char **argv, PMERGE_VEC &vect)
{
	int		i = 1;
	int		val;

	while (i < argc)
	{
		std::istringstream iss(argv[i]);
		iss >> val;
		vect.push_back(val);
		i++;
	}
}

void makePairsVect(PMERGE_VEC &vect, PMERGE_VEC &small, PMERGE_VEC &big)
{
	PMERGE_VEC::iterator it = vect.begin();
	int a;
	int b;

	while (it != vect.end())
	{
		a = *it;
		it++;
		if (it != vect.end())
		{
			b = *it;
			it++;
		}
		else
		{
			b = a;
			a = -1;
		}
		if (a < b)
		{
			small.push_back(a);
			big.push_back(b);
		}
		else
		{
			small.push_back(b);
			big.push_back(a);	
		}
	}
}

void insertVect(PMERGE_VEC &small, PMERGE_VEC &mainChain)
{
	PMERGE_VEC::iterator	it;
	PMERGE_VEC				jacobsthal = buildJacobsthalVec(small.size());
	int value;

	for (size_t i = 0; i < small.size(); i++)
	{
		value = small[jacobsthal[i] - 1];
		if (value == -1)
		{
			i++;
			continue ;
		}
		it = std::lower_bound(mainChain.begin(), mainChain.end(), value);
		mainChain.insert(it, value);
	}
}

PMERGE_VEC recVect(PMERGE_VEC toSort)
{
	PMERGE_VEC mainChain;
	PMERGE_VEC small;
	PMERGE_VEC big;
	if (toSort.size() <= 1)
		return (toSort);
	makePairsVect(toSort, small, big);
	mainChain = recVect(big);
	insertVect(small, mainChain);
	return (mainChain);
}

long pmergeVect(int argc, char **argv)
{
	PMERGE_VEC vect;
	parseVect(argc, argv, vect);
	vect = recVect(vect);
	PMERGE_VEC::iterator it = vect.begin();
	while (it != vect.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
	return (ft_getTime());
}

#pragma endregion

#pragma region DEQUE ALGORITHM

PMERGE_DQ buildJacobsthalDq(int n)
{
	PMERGE_DQ result;
	PMERGE_DQ jacob;

	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < n)
		jacob.push_back(jacob[jacob.size()-1] + 2 * jacob[jacob.size()-2]);

	for (size_t i = 1; i < jacob.size(); i++)
	{
		int from = jacob[i];
		int to = jacob[i-1];
		for (int j = from; j > to && j <= n; j--)
			result.push_back(j);
	}

	int last = jacob[jacob.size()-2];
	while (last < n)
		result.push_back(++last);

	return (result);
}

void	parseDq(int argc, char **argv, PMERGE_DQ &dq)
{
	int		i = 1;
	int		val;

	while (i < argc)
	{
		std::istringstream iss(argv[i]);
		iss >> val;
		dq.push_back(val);
		i++;
	}
}

void makePairsDq(PMERGE_DQ &dq, PMERGE_DQ &small, PMERGE_DQ &big)
{
	PMERGE_DQ::iterator it = dq.begin();
	int a;
	int b;

	while (it != dq.end())
	{
		a = *it;
		it++;
		if (it != dq.end())
		{
			b = *it;
			it++;
		}
		else
		{
			b = a;
			a = -1;
		}
		if (a < b)
		{
			small.push_back(a);
			big.push_back(b);
		}
		else
		{
			small.push_back(b);
			big.push_back(a);	
		}
	}
}

void insertDq(PMERGE_DQ &small, PMERGE_DQ &mainChain)
{
	PMERGE_DQ::iterator	it;
	PMERGE_DQ				jacobsthal = buildJacobsthalDq(small.size());
	int value;

	for (size_t i = 0; i < small.size(); i++)
	{
		value = small[jacobsthal[i] - 1];
		if (value == -1)
		{
			i++;
			continue ;
		}
		it = std::lower_bound(mainChain.begin(), mainChain.end(), value);
		mainChain.insert(it, value);
	}
}

PMERGE_DQ recDq(PMERGE_DQ toSort)
{
	PMERGE_DQ mainChain;
	PMERGE_DQ small;
	PMERGE_DQ big;
	if (toSort.size() <= 1)
		return (toSort);
	makePairsDq(toSort, small, big);
	mainChain = recDq(big);
	insertDq(small, mainChain);
	return (mainChain);
}

long pmergeDq(int argc, char **argv)
{
	PMERGE_DQ dq;
	parseDq(argc, argv, dq);

	std::cerr << "after : ";
	PMERGE_DQ::iterator it = dq.begin();
	while (it != dq.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
	return (ft_getTime());
}

#pragma endregion

int main(int argc, char **argv)
{
	if (argc == 1 || !checkValues(argc, argv))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::cout << "before : ";
	for (int i = 1; i < argc; i++)
		std::cout << argv[i] << " ";
	std::cout << std::endl;

	long vec_start = ft_getTime();
	long vec_end = pmergeVect(argc, argv);
	long dq_start = ft_getTime();
	long dq_end = pmergeDq(argc, argv);
	
	std::cout << "Time to process with std::vector : " << vec_end - vec_start << "us" << std::endl;
	std::cout << "Time to process with std::deque : " << dq_end - dq_start << "us" << std::endl;
}