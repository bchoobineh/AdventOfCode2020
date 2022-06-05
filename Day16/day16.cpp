#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <algorithm>

// Data Parsed from Input File
std::unordered_map<std::string, std::set<int>> ranges;
std::vector<int> myTicket;
std::vector<std::vector<int>> otherTickets;

void parseInputFile()
{
	std::fstream file("day16.txt");
	std::string str;

	// Parse Ranges
	std::getline(file, str); // Read First Line
	do
	{
		// Acquire Key
		std::string key;
		int i = 0;
		while (i < str.length())
		{
			if (str[i] == ':')
			{
				i += 2;
				break;
			}

			key += str[i];
			i++;
		}

		// Get Both Ranges
		std::set<int> range;
		for (int j = 0; j < 2; j++)
		{
			int lb, rb;
			std::string buffer = "";


			// Lower Bound
			while (str[i] != '-')
			{
				buffer += str[i];
				i++;
			}
			lb = std::stoi(buffer);
			i++;
			buffer = "";

			// Upper Bound
			while (i < str.length() && str[i] != ' ')
			{
				buffer += str[i];
				i++;
			}
			rb = std::stoi(buffer);
			i += 4;

			// Add range to set
			for (int k = lb; k <= rb; k++)
				range.insert(k);
		}

		// Add key to map
		ranges[key] = range;
		
		// Read New Line
		std::getline(file, str); 


	} while (str.length() > 0);

	// Parse My Ticket
	std::getline(file, str); // Skip to Data
	std::getline(file, str);
	std::stringstream ss(str);
	std::string buffer;
	while (std::getline(ss, buffer, ','))
		myTicket.push_back(std::stoi(buffer));

	// Parse Nearby Tickets
	std::getline(file, str); // Skip to Data
	std::getline(file, str);
	std::getline(file, str);
	do {
		std::vector<int> data;
		std::stringstream ss2(str);
		std::string buffer2;
		while (std::getline(ss2, buffer2, ','))
			data.push_back(std::stoi(buffer2));

		otherTickets.push_back(data);

		// Read New Line
		std::getline(file, str);
	} while (str.length() > 0);

}

int main(int argc, char* argv[])
{
	// Parse Input File
	parseInputFile();

	// Find Valid Tickets
	std::vector<std::vector<int>> validTickets;
	int errorRate = 0;
	for (int i = 0; i < otherTickets.size(); i++)
	{
		bool valid = true;
		for (int j = 0; j < otherTickets[i].size(); j++)
		{
			int val = otherTickets[i][j];
			
			// Attempt to find value in any range
			bool found = false;
			for (auto k = ranges.begin(); k != ranges.end(); k++)
			{
				if (k->second.find(val) != k->second.end())
				{
					found = true;
					break;
				}
			}

			// Invalid Ticket
			if (!found)
			{
				errorRate += val;
				valid = false;
			}
		}

		// This is a valid ticket
		if (valid)
			validTickets.push_back(otherTickets[i]);
	}

	// Determine possible label options for each column
	std::vector<std::set<std::string>> labels(validTickets[0].size(), std::set<std::string>());
	for (int i = 0; i < validTickets.size(); i++)
	{
		for (int j = 0; j < validTickets[i].size(); j++)
		{
			int val = validTickets[i][j];

			// Options for current value
			std::set<std::string> labelOptions;

			// Find Options for current value
			for (auto k = ranges.begin(); k != ranges.end(); k++)
			{
				if (k->second.find(val) != k->second.end())
					labelOptions.insert(k->first);
			}

			// First Time Initialization
			if (labels[j].empty())
				labels[j] = labelOptions;
			else
			{

				// Intersection of both sets
				std::set<std::string> intersection;
				std::set_intersection(labels[j].begin(), labels[j].end(), labelOptions.begin(),
					labelOptions.end(), std::inserter(intersection, intersection.begin()));

				labels[j] = intersection;
			}

		}
	}

	// Determine Column Labels
	std::vector<std::string> colLabels(validTickets[0].size(), "");
	int numLabeled = 0;
	while (numLabeled < validTickets[0].size())
	{
		for (int i = 0; i < labels.size(); i++)
		{
			if (labels[i].size() == 1)
			{
				std::string lb = *(labels[i].begin());

				// Remove from every other possibile label 
				for (int j = 0; j < labels.size(); j++)
					labels[j].erase(lb);

				colLabels[i] = lb;
				numLabeled++;
				break;
			}

		}
	}

	// Find and multiply instances of "departure"
	std::string target = "departure";
	long long product = 1;
	for (int i = 0; i < colLabels.size(); i++)
	{
		if (colLabels[i].find(target) != std::string::npos)
			product *= myTicket[i];
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Error Rate: %d\n", errorRate);
	printf("\n");

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Product: %lld\n", product);
	printf("\n");


	return 0;
}