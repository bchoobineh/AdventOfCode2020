#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Seat
{
	int row, col, ID;
	Seat()
	{
		row = 0;
		col = 0;
		ID = 0;
	}
};

Seat getSeat(std::string str)
{
	Seat seat;



	// Find Row
	int lb = 0;
	int rb = 127;
	for (int i = 0; i < 7; i++)
	{
		char c = str.at(i);
		int half = (rb - lb)/2;

		// Lower Half
		if (c == 'F')		{
			rb = rb - half - 1;		}
		// Upper Half
		else
			lb = lb + half + 1;
	}
	seat.row = lb;

	// Find Col
	lb = 0;
	rb = 7;
	for (int i = 7; i < 10; i++)
	{
		char c = str.at(i);
		int half = (rb - lb) / 2;

		// Lower half
		if (c == 'L')
			rb = rb - half - 1;
		// Upper Half
		else
			lb = lb + half + 1;
	}
	seat.col = lb;

	seat.ID = (seat.row * 8) + seat.col;

	return seat;
}

int main(int argc, char* argv[])
{
	// Seat Data Buffer
	std::vector<std::string> data;

	// Parse data file line by line
	std::fstream file("day5.txt");
	std::string str;
	while (std::getline(file, str))
	{
		data.push_back(str);
	}
	file.close();

	// Calculate all Seats
	std::vector<Seat> seats;
	for (int i = 0; i < data.size(); i++)
		seats.push_back(getSeat(data.at(i)));



	////////////
	// PART 1 //
	////////////

	int part1Sol = 0;
	for (auto i : seats)
	{
		part1Sol = std::max(part1Sol, i.ID);
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Highest Seat ID: %d\n", part1Sol);
	printf("\n");


	////////////
	// PART 2 //
	////////////

	// List of seats
	std::vector<int> seatNums;
	for (auto i : seats)
		seatNums.push_back(i.ID);

	// Sort seats
	std::sort(seatNums.begin(), seatNums.end());

	// Calculate Seat
	int part2Sol = -1;
	for (int i = 1; i < seatNums.size(); i++)
	{
		if (seatNums[i] != (seatNums[i - 1] + 1))
		{
			part2Sol = seatNums[i] - 1;
			break;
		}
	}

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("My Seat ID: %d\n", part2Sol);
	printf("\n");


	return 0;
}