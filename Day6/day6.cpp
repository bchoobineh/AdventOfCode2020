#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
	// Question Buffer
	std::vector<std::unordered_set<char>> data;

	// Part 2 Question Buffer
	std::vector<std::vector<std::set<char>>> intersectedData;

	// Parse data file
	std::fstream file("day6.txt");
	std::string str;
	while (std::getline(file, str))
	{
		std::unordered_set<char> questions;
		std::vector<std::set<char>> questionGroup;


		while (str.length() > 0)
		{
			std::set<char> tmpQuestions;

			for (int i = 0; i < str.length(); i++)
			{
				questions.insert(str.at(i));
				tmpQuestions.insert(str.at(i));	
			}

			questionGroup.push_back(tmpQuestions);

			std::getline(file, str);
		}

		intersectedData.push_back(questionGroup);

		data.push_back(questions);
	}
	file.close();


	////////////
	// PART 1 //
	////////////

	int part1Sol = 0;
	for (int i = 0; i < data.size(); i++)
	{
		part1Sol += data.at(i).size();
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Sum of Counts: %d\n", part1Sol);
	printf("\n");

	////////////
	// PART 2 //
	////////////

	int part2Sol = 0;
	for (int i = 0; i < intersectedData.size(); i++)
	{
		std::set<char> group = intersectedData.at(i).at(0);
		for (int j = 1; j < intersectedData.at(i).size(); j++)
		{
			std::set<char> g2 = intersectedData.at(i).at(j);
			std::set<char> intersect;			
			std::set_intersection(group.begin(), group.end(), g2.begin(), g2.end(),
				std::inserter(intersect, intersect.begin()));
			group = intersect;
		}

		part2Sol += group.size();

	}


	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Sum of Counts: %d\n", part2Sol);
	printf("\n");




	return 0;
}