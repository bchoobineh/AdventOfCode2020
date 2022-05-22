#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct Slope
{
	int rise, run;
};

int numCollisions(std::vector<std::vector<char>> dataMap, Slope slope)
{
	int numCollisions = 0;
	int posX = 0;
	int posY = 0;

	while (posY < dataMap.size())
	{
		if (dataMap[posY][posX] == '#')
			numCollisions++;

		posX = (posX + slope.run) % dataMap[0].size();
		posY += slope.rise;
	}

	return numCollisions;
}

int main(int argc, char* argv[])
{
	// Slope Map Buffer
	std::vector<std::vector<char>> dataMap;

	// Parse data files
	std::fstream file("day3.txt");
	std::string str;
	while (std::getline(file, str))
	{
		std::vector<char> row;
		for (int i = 0; i < str.length(); i++)
			row.push_back(str.at(i));

		dataMap.push_back(row);
	}
	file.close();


	////////////
	// PART 1 //
	////////////

	Slope slope;
	slope.rise = 1;
	slope.run = 3;

	int part1Sol = numCollisions(dataMap, slope);

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Number of Trees Hit: %d\n", part1Sol);
	printf("\n");
	
	////////////
	// PART 2 //
	////////////

	Slope slope1;
	slope1.rise = 1;
	slope1.run = 1;
	int col1 = numCollisions(dataMap, slope1);

	Slope slope2;
	slope2.rise = 1;
	slope2.run = 3;
	int col2 = numCollisions(dataMap, slope2);

	Slope slope3;
	slope3.rise = 1;
	slope3.run = 5;
	int col3 = numCollisions(dataMap, slope3);

	Slope slope4;
	slope4.rise = 1;
	slope4.run = 7;
	int col4 = numCollisions(dataMap, slope4);

	Slope slope5;
	slope5.rise = 2;
	slope5.run = 1;
	int col5 = numCollisions(dataMap, slope5);

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Number of Trees Hit in Slope 1: %d\n", col1);
	printf("Number of Trees Hit in Slope 1: %d\n", col2);
	printf("Number of Trees Hit in Slope 1: %d\n", col3);
	printf("Number of Trees Hit in Slope 1: %d\n", col4);
	printf("Number of Trees Hit in Slope 1: %d\n", col5);
	printf("Product: %d\n", col1 * col2 * col3 * col4 * col5);
	printf("\n");



	return 0;
}