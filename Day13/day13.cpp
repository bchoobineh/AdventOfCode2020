#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
	// Parse data file
	std::fstream file("day13.txt");
	std::string str;

	// Get Earliest time
	std::getline(file, str);
	int startTime = std::stoi(str);

	// Get Bus ID's
	std::getline(file, str);
	std::vector<int> buses;
	std::vector<int> busesP2;
	
	std::stringstream ss(str);
	std::string tmp;
	while (std::getline(ss, tmp, ','))
	{
		if (tmp != "x")
		{
			buses.push_back(std::stoi(tmp));
			busesP2.push_back(std::stoi(tmp));
		}
		else
		{
			busesP2.push_back(1);
		}
	}

	// Close the data file
	file.close();

	

	////////////
	// PART 1 //
	////////////

	// Time Counter
	int timeCounter = startTime;
	bool running = true;
	int busID = -1;
	while (running)
	{
		for (auto i : buses)
		{
			if (timeCounter % i == 0)
			{
				busID = i;
				running = false;
				break;
			}
		}

		if (running)
			timeCounter++;
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Soonest: %d\n", timeCounter);
	printf("Bus ID: %d\n", busID);
	printf("Product: %d\n", (timeCounter - startTime) * busID);
	printf("\n");



	////////////
	// PART 2 //
	////////////

	long long time = 0;
	long long step = busesP2.at(0);

	for (int i = 1; i < busesP2.size(); i++)
	{
		int val = busesP2.at(i);

		while (((time + i) % val) != 0)
		{
			time += step;
		}

		step *= val;
	}

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Time: %lld\n", time);
	printf("\n");

	return 0;
}