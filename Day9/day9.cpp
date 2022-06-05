#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <unordered_set>

#define PREAMBLE_SIZE 25

bool checkValid(std::queue<double> buffer, double value)
{
	// Convert to Set
	std::unordered_set<double> tmp;
	while (!buffer.empty())
	{
		tmp.insert(buffer.front());
		buffer.pop();
	}

	for (auto i = tmp.begin(); i != tmp.end(); i++)
	{
		double sub = value - *i;

		// Pair must be different
		if (sub == *i)
			continue;
		
		if (tmp.find(sub) != tmp.end())
			return true;

	}

	return false;
}

int main(int argc, char* argv[])
{
	// Input data buffer
	std::vector<double> data;

	// Parse data file
	std::fstream file("day9.txt");
	std::string str;

	while (std::getline(file, str))
	{
		data.push_back(std::stod(str));
	}
	file.close();


	////////////
	// PART 1 //
	////////////

	std::queue<double> buffer;
	for (int i = 0; i < PREAMBLE_SIZE; i++)
		buffer.push(data[i]);

	double part1Sol = 0;
	for (int i = PREAMBLE_SIZE; i < data.size(); i++)
	{
		if (!checkValid(buffer, data[i]))
		{
			part1Sol = data[i];
			break;
		}

		buffer.pop();
		buffer.push(data[i]);	
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Invalid Number: %lf\n", part1Sol);
	printf("\n");


	////////////
	// PART 2 //
	////////////

	int lb = 0;
	int rb = 1;
	double sum = data[lb] + data[rb]; // Initial subset sum

	while (sum != part1Sol)
	{
		if (sum > part1Sol)
		{
			sum -= data[lb];
			lb++;
			if (lb == rb)
				rb++;
		}
		else
		{
			rb++;
			if (rb < data.size())
				sum += data[rb];
			else
				break;
		}
	}

	double minVal = data[lb];
	double maxVal = data[lb];
	for (int i = lb + 1; i <= rb; i++)
	{
		if (data[i] < minVal)
			minVal = data[i];

		if (data[i] > maxVal)
			maxVal = data[i];
	}
	


	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Bounds are: %lf and %lf summing to: %lf\n", minVal, maxVal, minVal + maxVal);
	printf("\n");





	return 0;
}