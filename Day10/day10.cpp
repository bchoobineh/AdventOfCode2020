#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
	// Buffer of Adapters
	std::vector<int> adapters;

	// Parse Data file
	std::fstream file("day10.txt");
	std::string str;
	while (std::getline(file, str))
	{
		adapters.push_back(std::stoi(str));
	}
	file.close();


	////////////
	// PART 1 //
	////////////
	
	std::vector<int> sortedAdapters = adapters;
	std::sort(sortedAdapters.begin(), sortedAdapters.end());

	int numOneDiff = 0;
	int numThreeDiff = 0;

	for (int i = 1; i < sortedAdapters.size(); i++)
	{
		int diff = sortedAdapters[i] - sortedAdapters[i - 1];
		if (diff == 1)
			numOneDiff++;
		else if (diff == 3)
			numThreeDiff++;
	}

	// Account for phone charger
	numThreeDiff++;

	// Account for wall socket.
	int diff = sortedAdapters[0];
	if (diff == 1)
		numOneDiff++;
	else if (diff == 3)
		numThreeDiff++;


	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Num One Diff: %d\n", numOneDiff);
	printf("Num Three Diff: %d\n", numThreeDiff);
	printf("Product: %d\n", numOneDiff * numThreeDiff);
	printf("\n");


	////////////
	// PART 2 //
	////////////

	// Add outlet to data set
	adapters.push_back(0);
	sortedAdapters = adapters;
	std::sort(sortedAdapters.begin(), sortedAdapters.end());

	// Create a DP array
	std::vector<double> dp(sortedAdapters[sortedAdapters.size() - 1] + 3 + 1, 0);

	// Last adapter initialization
	dp[sortedAdapters[sortedAdapters.size() - 1]] = 1;
	
	//printf("TESTING: %d\n", sortedAdapters[sortedAdapters.size()-1]);

	for (int i = sortedAdapters.size() - 2; i >= 0; i--)
	{
		int element = sortedAdapters[i];
		dp[element] = dp[element + 1] + dp[element + 2] + dp[element + 3];
	}

	// Sum up the final
	dp[0] = dp[1] + dp[2] + dp[3];

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Number of Permutations: %lf\n", dp[0]);
	printf("\n");




	return 0;
}