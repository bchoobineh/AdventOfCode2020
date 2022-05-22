#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>

struct Passport
{
	std::string byr, iyr, eyr, hgt, hcl, ecl, pid, cid;
	Passport()
	{
		byr = "";
		iyr = "";
		eyr = "";
		hgt = "";
		hcl = "";
		ecl = "";
		pid = "";
		cid = "";
	}
};


int main(int argc, char* argv[])
{
	// Linear Data buffer of Passport String Data
	std::vector<std::string> passportData;

	// Data Buffer of Passports
	std::vector<Passport> passports;

	// Parse data file line by line
	std::fstream file("day4.txt");
	std::string str;
	std::string pass = "";
	while (std::getline(file, str))
	{
		// Blank Line
		if (str.length() < 1)
		{
			passportData.push_back(pass);
			pass = "";
			continue;
		}

		if (pass.length() < 1)
			pass = str;
		else
			pass = pass + " " + str;
	}
	if (pass.length() > 0)
		passportData.push_back(pass);


	// Parse Passport strings into Passport struct
	for (int i = 0; i < passportData.size(); i++)
	{
		std::stringstream ss(passportData.at(i));
		std::string str;

		Passport pass;

		while (std::getline(ss, str, ' '))
		{
			std::stringstream ss2(str);
			std::string tmp;
			std::string key, val;

			std::getline(ss2, tmp, ':');
			key = tmp;

			std::getline(ss2, tmp, ':');
			val = tmp;

			if (key == "byr")
			{
				pass.byr = val;
			}
			else if (key == "iyr")
			{
				pass.iyr = val;
			}
			else if (key == "eyr")
			{
				pass.eyr = val;
			}
			else if (key == "hgt")
			{
				pass.hgt = val;
			}
			else if (key == "hcl")
			{
				pass.hcl = val;
			}
			else if (key == "ecl")
			{
				pass.ecl = val;
			}
			else if (key == "pid")
			{
				pass.pid = val;
			}
			else if (key == "cid")
			{
				pass.cid = val;
			}
		}

		passports.push_back(pass);
	}

	////////////
	// PART 1 //
	////////////

	int part1Sol = 0;
	for (int i = 0; i < passports.size(); i++)
	{
		Passport pass = passports.at(i);

		// Fail
		if (pass.byr.length() < 1 || pass.iyr.length() < 1 || pass.eyr.length() < 1 || pass.hgt.length() < 1 || pass.hcl.length() < 1 ||
			pass.ecl.length() < 1 || pass.pid.length() < 1)
		{
			continue;
		}

		part1Sol++;

	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Number of Valid Passports: %d\n", part1Sol);
	printf("\n");


	////////////
	// PART 2 //
	////////////

	int part2Sol = 0;
	for (int i = 0; i < passports.size(); i++)
	{
		Passport pass = passports.at(i);

		// Check Birth Year
		if (pass.byr.length() < 1)
			continue;

		int year = std::stoi(pass.byr);
		if (year < 1920 || year > 2002)
			continue;


		// Check Issue Year
		if (pass.iyr.length() < 1)
			continue;

		year = std::stoi(pass.iyr);
		if (year < 2010 || year > 2020)
			continue;


		// Check Expiration Year
		if (pass.eyr.length() < 1)
			continue;

		year = std::stoi(pass.eyr);
		if (year < 2020 || year > 2030)
			continue;


		// Check Height
		if (pass.hgt.length() < 1)
			continue;


		int index = 0;
		int digit = 0;
		while (index < pass.hgt.length())
		{
			if (isdigit(pass.hgt[index]))
			{
				digit = (digit * 10) + (pass.hgt[index] - '0');
				index++;
			}
			else
				break;
		}

		std::string unit = pass.hgt.substr(pass.hgt.length() - 2, 2);

		if (unit == "cm")
		{
			if (digit < 150 || digit > 193)
				continue;
		}
		else if (unit == "in")
		{
			if (digit < 59 || digit > 76)
				continue;
		}
		else
		{
			continue;
		}


		// Check Hair Colour
		if (pass.hcl.length() != 7)
			continue;

		if (pass.hcl[0] != '#')
			continue;

		bool fail = false;
		for (int j = 1; j < 7; j++)
		{
			char c = pass.hcl.at(j);
			if (c < '0' || (c > '9' && c < 'a') || c > 'f')
			{
				fail = true;
				break;
			}
		}
		if (fail)
			continue;


		// Check Eye Colour
		if (pass.ecl.length() < 1)
			continue;

		if (pass.ecl != "amb" && pass.ecl != "blu" && pass.ecl != "brn" && pass.ecl != "gry" && pass.ecl != "grn" && pass.ecl != "hzl" && pass.ecl != "oth")
			continue;


		// Check Passport ID
		if (pass.pid.length() < 1 || pass.pid.length() != 9)
			continue;

		fail = false;
		for (int j = 0; j < pass.pid.length(); j++)
		{
			char c = pass.pid.at(j);
			if (c < '0' || c > '9')
			{
				fail = true;
				break;
			}
		}

		if (fail)
			continue;

		part2Sol++;








	}


	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Number of Valid Passports: %d\n", part2Sol);
	printf("\n");



	return 0;
}