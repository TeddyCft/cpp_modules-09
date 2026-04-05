#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

#define BTC_MAP std::map<std::string, float>

bool	argCheck(int argc, char **argv)
{
	bool ret = true;
	std::ifstream data("./assets/data.csv");
	if (!data)
	{
		std::cerr << "'./assets/data.csv' not found." << std::endl;
		return (1);
	}
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

bool	parseData(BTC_MAP &data)
{
	std::ifstream file("./assets/data.csv");
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

bool	isIntWithMaxValue(std::string str, int max)
{
	std::istringstream iss(str);

	int i;
	char c;
	if (!(iss >> i))
		return (false);
	if (iss >> c)
		return (false);
	if (i > max)
		return (false);
	return (true);
}

bool isLeap(std::string str)
{
	std::istringstream iss(str);
	int year;
	iss >> year;
	if (!(year % 100))
	{
		if (!(year % 400))
			return (true);
		return (false);
	}
	if (!year % 4)
		return (true);
	return (false);
}

bool checkDateValues(std::string year, std::string month, std::string day)
{
	if (!isIntWithMaxValue(year, 2026) ||
		!isIntWithMaxValue(month, 12) ||
		!isIntWithMaxValue(day, 31))
		return (false);
	std::string maxfeb;
	if (isLeap(year))
		maxfeb = "29";
	else
		maxfeb = "28";
	if (month == "02" && day > maxfeb)
		return (false);
	else if ((month == "01" || month == "03" || month == "05" || month == "07" ||
			month == "08" || month == "10" || month == "12") && day > "31")
		return (false);
	else if ((month == "04" || month == "06" || month == "09" || month == "11") && day > "30")
		return (false);
	return (true);
}

bool checkDate(std::string date)
{
	std::istringstream iss(date);
	std::string year;
	std::string month;
	std::string day;
	std::getline(iss, year, '-');
	std::getline(iss, month, '-');
	std::getline(iss, day);
	if (year.size() != 4 || month.size() != 2 || day.size() != 2)
		std::cerr << "Error: Date must be in YYYY-MM-DD format." << std::endl;
	else if (!checkDateValues(year, month, day))
		std::cerr << "Error: Wrong date => " << date << std::endl;
	else
		return (true);
	return (false);
}

bool	checkSeparator(std::string sep, std::string line)
{
	if (sep != "|")
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	return (true);
}

bool	checkFactor(float factor)
{
	if (factor < 0)
		std::cerr << "Error: not a positive number." << std::endl;
	else if (factor > 1000)
		std::cerr << "Error: too large a number." << std::endl;
	else
		return (true);
	return (false);
}

float convertValue(std::string date, float factor, BTC_MAP &data)
{
	BTC_MAP::iterator it = data.find(date);
	if (it == data.end())
	{
		it = data.lower_bound(date);
		if (it != data.begin())
			it--;
	}
	return (it->second * factor);
}

void	printLine(std::string &line, BTC_MAP &data)
{
	std::istringstream iss(line);
	std::string date;
	std::string separator;
	float		factor;

	if (!(iss >> date >> separator >> factor))
		std::cerr << "Error: bad input => " << line << std::endl;
	else if (checkDate(date) && checkSeparator(separator, line) && checkFactor(factor))
		std::cout << date << " => " << factor << " = " << convertValue(date, factor, data) << std::endl;
}

void	printValues(BTC_MAP data, std::string path)
{
	std::ifstream file(path.c_str());
	std::string line;
	while (std::getline(file, line))
		printLine(line, data);
}

int main(int argc, char **argv)
{
	if (!argCheck(argc, argv))
		return(1);
	BTC_MAP data;
	if (parseData(data))
	{
		std::cerr << "Error with data.csv file" << std::endl;
		return (1);
	}
	printValues(data, argv[1]);
	return (0);
}