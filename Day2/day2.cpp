#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

struct Rule
{
	char letter;
	int lowBound;
	int hiBound;
};

int main(int argc, char* argv[])
{
	// Buffer of Rules
	std::vector<Rule> rules;

	// Buffer of passwords
	std::vector<std::string> passwords;

	// Parse data file line by line
	std::fstream file("day2.txt");
	std::string str;
	while (std::getline(file, str))
	{
		std::stringstream ss(str);
		std::string tmp;
		Rule rule;

		// Calculate Rule
		
		// Determine Bound
		std::getline(ss, tmp, ' ');
		std::stringstream ss2(tmp);
		std::string tmp2;
		
		// Get Low Bound
		std::getline(ss2, tmp2, '-');
		rule.lowBound = std::stoi(tmp2);

		// Get Hi Bound
		std::getline(ss2, tmp2, '-');
		rule.hiBound = std::stoi(tmp2);

		// Get Letter
		std::getline(ss, tmp, ' ');
		rule.letter = tmp[0];

		// Add rule to data buffer
		rules.push_back(rule);

		// Get Password
		std::getline(ss, tmp, ' ');
		passwords.push_back(tmp);
	}
	file.close();


	////////////
	// PART 1 //
	////////////

	int part1Sol = 0;
	for (int i = 0; i < passwords.size(); i++)
	{
		std::string str = passwords.at(i);
		std::unordered_map<char, int> letters;
		
		// Map out letters
		for (int j = 0; j < str.length(); j++)
		{
			char c = str[j];
			if (letters.find(c) == letters.end())
				letters[c] = 1;
			else
				letters[c] = letters[c] + 1;
		}

		// Cross check against ruleset
		Rule r = rules.at(i);
		int letterCount = 0;

		// How many of that letter do we have
		if (letters.find(r.letter) != letters.end())
			letterCount = letters[r.letter];

		if (letterCount >= r.lowBound && letterCount <= r.hiBound)
			part1Sol++;
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Number of Valid Passwords: %d\n", part1Sol);
	printf("\n");


	////////////
	// PART 2 //
	////////////

	int part2Sol = 0;
	for (int i = 0; i < passwords.size(); i++)
	{
		std::string str = passwords.at(i);
		Rule r = rules.at(i);
		
		// Invalid due to length
		if (str.length() <= (r.hiBound - 1))
			continue;

		char l1 = str[r.lowBound - 1];
		char l2 = str[r.hiBound - 1];

		if ((l1 == r.letter && l2 != r.letter) || (l1 != r.letter && l2 == r.letter))
			part2Sol++;
	}


	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Number of Valid Passwords: %d\n", part2Sol);
	printf("\n");


	return 0;
}