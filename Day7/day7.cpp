#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

bool bagDFS(std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> data, std::string current,
	std::unordered_map<std::string, bool>& dp)
{
	if (dp.find(current) != dp.end())
		return dp.at(current);

	if (current == "shinygold")
	{
		dp[current] = true;
		return true;
	}

	for (int i = 0; i < data.at(current).size(); i++)
	{
		if (bagDFS(data, data.at(current).at(i).first, dp) == true)
		{
			dp[current] = true;
			return true;
		}
	}

	dp[current] = false;
	return false;
}

int bagCounter(std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> data, std::string current)
{
	int count = 1;
	for (int i = 0; i < data.at(current).size(); i++)
	{
		count += (data.at(current).at(i).second * bagCounter(data, data.at(current).at(i).first));
	}

	return count;
}

int main(int argc, char* argv[])
{
	// Mapping of rules
	std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> data;

	// Parse Data File
	std::fstream file("day7.txt");
	std::string str;

	while (std::getline(file, str))
	{
		std::stringstream ss(str);
		std::string word;

		// Find Key. Everything until keyword "bags"
		std::string key;
		while (std::getline(ss, word, ' '))
		{
			if (word == "bags")
				break;

			key += word;
		}

		// Skip over "contains
		std::getline(ss, word, ' ');
		

		// Vector of values for key
		std::vector<std::pair<std::string, int>> ruleset;

		while (1)
		{
			std::pair<std::string, int> rule;

			// Get number of bags
			std::getline(ss, word, ' ');

			// If no bags then break
			if (word == "no" || word == "bags." || word == "bag." ||  word.length() < 1)
				break;

			int numBags = std::stoi(word);

			// Find Key. Everything until keyword "bags"
			std::string reqKey;
			while (std::getline(ss, word, ' '))
			{
				if (word == "bags," || word == "bag," || word == "bags." || word == "bag.")
					break;

				reqKey += word;
			}

			rule.first = reqKey;
			rule.second = numBags;

			ruleset.push_back(rule);
		}

		// Add Key Value to map
		data[key] = ruleset;

	}
	file.close();


	////////////
	// PART 1 //
	////////////

	// Create DP Map
	std::unordered_map<std::string, bool> dp;

	// Fill out DP Map
	for (auto i = data.begin(); i != data.end(); i++)
		bagDFS(data, i->first, dp);

	int part1Sol = 0;
	for(auto i = dp.begin(); i != dp.end(); i++)
	{
		if (i->first != "shinygold" && i->second == true)
			part1Sol++;
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Number of Bags: %d\n", part1Sol);
	printf("\n");



	////////////
	// PART 2 //
	////////////

	int part2Sol = 0;

	part2Sol = bagCounter(data, "shinygold") - 1;

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Number of Bags: %d\n", part2Sol);
	printf("\n");

	return 0;
}