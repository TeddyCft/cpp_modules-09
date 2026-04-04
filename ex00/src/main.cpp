#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

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
	if (!ret)
		std::cerr << "Error: invalid argument." << std::endl;
	return (ret);
}

bool isFloat(const std::string &str)
{
	std::istringstream iss(str);

	float	fl;
	char 	c;
	if (!(iss >> fl))
		return (false);
	if (iss >> c)
		return (false);
	return (true);
}

bool	parseFile(BTC_MAP &data, std::string path)
{
	std::ifstream file(path.c_str());
	std::string line;
	size_t		line_count = 1;

	std::string date;
	std::string	strvalue;
	float		value;

	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::getline(iss, date, ',');
		std::getline(iss, strvalue);
		if (!isFloat(strvalue))
			return (line_count);
		value = static_cast<float>(std::atof(strvalue.c_str()));
		data.insert(std::make_pair(date, value));
		line_count++;
	}
	return (0);
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