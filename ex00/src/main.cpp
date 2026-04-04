#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#define BTC_MAP std::map<std::string, float>

bool	argCheck(int argc, char **argv)
{
	bool ret = true;
	if (argc != 2)
		ret = false;
	else
	{
		std::ifstream file(argv[1]);
		if (!file)
			ret = false;
	}
	if (ret)
		std::cerr << "Error: invalid argument." << std::endl;
	return (ret);
}

bool	parseFile(BTC_MAP &data, std::string path)
{
	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line, ','))
	{
		std::string date;
		float		value;
	}
}
}

int main(int argc, char **argv)
{
	if (!argCheck(argc, argv))
		return(1);
	BTC_MAP data;
	if (parseFile(data, argv[1]))
	{
		std::cerr << "Error with data.csv file" << std::endl;
		return (1);
	}
	return (0);
}