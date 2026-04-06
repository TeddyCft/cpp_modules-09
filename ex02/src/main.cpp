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

long ft_getTime()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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
	PMERGE_VEC::iterator small_it = small.begin();
	PMERGE_VEC::iterator mc_it;
	while (small_it != small.end())
	{
		if (*small_it == -1)
			return ;
		mc_it = std::lower_bound(mainChain.begin(), mainChain.end(), *small_it);
		mainChain.insert(mc_it, *small_it);
		small_it++;
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
	// long dq_start = ft_getTime();
	// long dq_end = pmergeDq(argc, argv);
	
	std::cout << "Time to process with std::vector : " << vec_end - vec_start << "ms" << std::endl;
	// std::cout << "Time to process with std::deque : " << dq_end - dq_start << "ms" << std::endl;
}
