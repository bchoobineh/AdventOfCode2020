#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_map>

#define TARGET 2020

struct Triplet
{
	int x, y, z;
};

std::pair<int, int> findPair(int target, std::unordered_map<int, int> data)
{
	// Iterate through map
	std::pair<int, int> sol;
	sol.first = 0;
	sol.second = 0;
	for (auto i = data.begin(); i != data.end(); i++)
	{
		int pair = target - i->first;
		if (data.find(pair) == data.end())
			continue;

		if (pair == i->first)
		{
			if (data[pair] > 1)
			{
				sol.first = pair;
				sol.second = pair;
				break;
			}
		}

		sol.first = i->first;
		sol.second = pair;
		break;
	}

	return sol;
}


int main(int argc, char* argv[])
{
	// Map of input numbers
	std::unordered_map<int, int> data;

	// Extract Data from Data File
	std::fstream file("day1.txt");
	std::string str;
	while (std::getline(file, str))
	{
		// Get number
		int num = std::stoi(str);

		// Add to Map
		if (data.find(num) == data.end())
			data[num] = 1;
		else
			data[num] = data[num] + 1;

	}
	file.close();


	////////////
	// PART 1 //
	////////////

	std::pair<int, int> sol = findPair(TARGET, data);

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Two Entries: %d %d\n", sol.first, sol.second);
	printf("Product: %d\n", sol.first * sol.second);
	printf("\n");


	////////////
	// PART 2 //
	////////////

	Triplet sol2;
	sol2.x = 0;
	sol2.y = 0;
	sol2.z = 0;

	for (auto i = data.begin(); i != data.end(); i++)
	{
		int pairTarget = TARGET - i->first;	

		// Create temp map and update
		std::unordered_map<int, int> tmpData = data;
		if (i->second < 2)
			tmpData.erase(i->first);
		else
			tmpData[i->first] = tmpData[i->first] - 1;

		// Attempt to find pair
		std::pair<int, int> opt = findPair(pairTarget, tmpData);

		if (opt.first == 0 || opt.second == 0)
			continue;
		else
		{
			sol2.x = i->first;
			sol2.y = opt.first;
			sol2.z = opt.second;
			break;
		}
	}

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Three Entries: %d %d %d\n", sol2.x, sol2.y, sol2.z);
	printf("Product: %d\n", sol2.x * sol2.y * sol2.z);




	return 0;
}