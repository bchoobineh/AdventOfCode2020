#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

// Switch to 2020 for Part 1
// Switch to 30000000 for Part 2
#define NUM_ITERS 30000000

int main(int argc, char* argv[])
{	
	// Input Data Buffer
	std::vector<int> input;

	// Parse Data File
	std::fstream file("day15.txt");
	std::string str;
	while (std::getline(file, str))
	{
		std::stringstream ss(str);
		std::string tmp;
		while (std::getline(ss, tmp, ','))
		{
			input.push_back(std::stoi(tmp));
		}
	}
	file.close();




	std::unordered_map<int, int> numSeen;
	int index = 0;

	// Process Starting Numbers
	while (index < input.size())
	{
		numSeen[input[index]] = index;
		index++;
	}
	
	// Process until NUM_ITER numbers
	index--;
	while (input.size() < NUM_ITERS)
	{
		// Last thing spoken
		int lastSpoken = input[index];

		// Seen before
		if (numSeen.find(lastSpoken) != numSeen.end())
		{
			int num = index - numSeen[lastSpoken];
			numSeen[lastSpoken] = index;
			input.push_back(num);
		}
		else
		{
			numSeen[lastSpoken] = index;
			input.push_back(0);
		}

		index++;
	}

	printf("Part 1 && Part 2: \n");
	printf("---------------------------------\n");
	printf("Number of Iterations: %d\n", NUM_ITERS);
	printf("Last Number: %d\n", input[NUM_ITERS -1]);
	printf("\n");



	return 0;
}