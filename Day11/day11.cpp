#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

enum floorType
{
	FLOOR,
	EMPTY,
	OCCUPIED
};

struct Tile
{
	floorType type;
	std::vector<Tile*> neighbors;
	std::vector<Tile*> neighborsP2;
	bool finalized;
};

bool validPosition(std::vector<std::vector<Tile>> deck, int row, int col)
{
	if (row < 0 || col < 0 || row >= deck.size() || col >= deck[0].size())
		return false;

	return true;
}

void printDeck(std::vector<std::vector<Tile>> deck)
{
	for (int i = 0; i < deck.size(); i++)
	{
		printf("\n");
		for (int j = 0; j < deck[i].size(); j++)
		{
			if (deck[i][j].type == floorType::FLOOR)
			{
				printf("%c", '.');
			}
			else if (deck[i][j].type == floorType::OCCUPIED)
			{
				printf("%c", '#');
			}
			else
			{
				printf("%c", 'L');
			}
		}
	}
}


int main(int argc, char* argv[])
{
	// Floor Map Buffer
	std::vector<std::vector<Tile>> deck;

	// Parse data file
	std::fstream file("day11.txt");
	std::string str;	
	while (std::getline(file, str))
	{
		std::vector<Tile> row;
		for (int i = 0; i < str.length(); i++)
		{
			Tile t;
			t.finalized = false;

			if (str[i] == '.')
				t.type = floorType::FLOOR;
			else if (str[i] == 'L')
				t.type = floorType::EMPTY;
			else
				t.type = floorType::OCCUPIED;

			row.push_back(t);
		}
		deck.push_back(row);
	}
	file.close();


	// Setup neighbors for Part 1
	for (int i = 0; i < deck.size(); i++)
	{
		for (int j = 0; j < deck[i].size(); j++)
		{
			std::vector<Tile*> neighbors;

			// Check 8 directions
			if((i+1) < deck.size())
				neighbors.push_back(&deck[i + 1][j]);

			if((i-1) >= 0)
				neighbors.push_back(&deck[i - 1][j]);

			if ((j + 1) < deck[0].size())
				neighbors.push_back(&deck[i][j + 1]);

			if ((j - 1) >= 0)
				neighbors.push_back(&deck[i][j - 1]);

			// Diagonals
			if ((i + 1) < deck.size() && (j+1) < deck[0].size())
				neighbors.push_back(&deck[i + 1][j+1]);

			if ((i + 1) < deck.size() && (j - 1) >= 0)
				neighbors.push_back(&deck[i + 1][j - 1]);

			if ((i - 1) >= 0 && (j + 1) < deck[0].size())
				neighbors.push_back(&deck[i - 1][j + 1]);

			if ((i - 1) >= 0 && (j - 1) >= 0)
				neighbors.push_back(&deck[i - 1][j - 1]);


			deck[i][j].neighbors = neighbors;
		}
	}

	// Setup neighbors for Part 2
	for (int i = 0; i < deck.size(); i++)
	{
		for (int j = 0; j < deck[i].size(); j++)
		{
			std::vector<Tile*> neighbors;

			// Direction 1
			int x = i + 1;
			while (x < deck.size())
			{
				if (deck[x][j].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[x][j]);
					break;
				}
				x++;
			}

			// Direction 2
			x = i - 1;
			while (x >= 0)
			{
				if (deck[x][j].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[x][j]);
					break;
				}
				x--;
			}

			// Direction 3
			int y = j + 1;
			while (y < deck[0].size())
			{
				if (deck[i][y].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[i][y]);
					break;
				}
				y++;
			}

			// Direction 4
			y = j - 1;
			while (y >= 0)
			{
				if (deck[i][y].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[i][y]);
					break;
				}
				y--;
			}

			// Direction 5
			x = i + 1;
			y = j + 1;
			while (x < deck.size() && y < deck[0].size())
			{
				if (deck[x][y].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[x][y]);
					break;
				}
				x++;
				y++;
			}

			// Direction 6
			x = i + 1;
			y = j - 1;
			while (x < deck.size() && y >= 0)
			{
				if (deck[x][y].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[x][y]);
					break;
				}
				x++;
				y--;
			}

			// Direction 7
			x = i - 1;
			y = j + 1;
			while (x >= 0 && y < deck[0].size())
			{
				if (deck[x][y].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[x][y]);
					break;
				}
				x--;
				y++;
			}

			// Direction 8
			x = i - 1;
			y = j - 1;
			while (x >= 0 && y >= 0)
			{
				if (deck[x][y].type != floorType::FLOOR)
				{
					neighbors.push_back(&deck[x][y]);
					break;
				}
				x--;
				y--;
			}

			deck[i][j].neighborsP2 = neighbors;
		}
	}


	
	////////////
	// PART 1 //
	////////////

	//bool changed = true;
	//while (changed)
	//{
	//	changed = false;
	//	std::vector<std::vector<Tile>> buffer;

	//	for (int i = 0; i < deck.size(); i++)
	//	{
	//		std::vector<Tile> row;
	//		for (int j = 0; j < deck[0].size(); j++)
	//		{
	//			// Floor never changes
	//			if (deck[i][j].type == floorType::FLOOR)
	//			{
	//				row.push_back(deck[i][j]);
	//			}

	//			// Free Seat
	//			else if (deck[i][j].type == floorType::EMPTY)
	//			{
	//				bool avail = true;
	//				for (int k = 0; k < deck[i][j].neighbors.size(); k++)
	//				{
	//					if (deck[i][j].neighbors.at(k)->type == floorType::OCCUPIED)
	//					{
	//						avail = false;
	//						break;
	//					}
	//				}

	//				// Becomes occupied
	//				if (avail)
	//				{
	//					row.push_back(deck[i][j]);
	//					row[j].type = floorType::OCCUPIED;

	//					if (!changed)
	//						changed = true;
	//				}
	//				else
	//				{
	//					row.push_back(deck[i][j]);
	//				}
	//			}

	//			// Occupied Seat
	//			else
	//			{
	//				int seatCount = 0;
	//				for (int k = 0; k < deck[i][j].neighbors.size(); k++)
	//				{
	//					if (deck[i][j].neighbors.at(k)->type == floorType::OCCUPIED)
	//					{
	//						seatCount++;
	//						if (seatCount >= 4)
	//						{
	//							break;
	//						}
	//					}
	//				}

	//				// Becomes Free
	//				if (seatCount >= 4)
	//				{
	//					row.push_back(deck[i][j]);
	//					row[j].type = floorType::EMPTY;

	//					if (!changed)
	//						changed = true;
	//				}
	//				else
	//				{
	//					row.push_back(deck[i][j]);

	//				}
	//			}

	//		}

	//		buffer.push_back(row);
	//	}

	//	deck = buffer;
	//}

	//// Count Occupied Seats
	//int seatCount = 0;
	//for (int i = 0; i < deck.size(); i++)
	//{
	//	for (int j = 0; j < deck[i].size(); j++)
	//	{
	//		if (deck[i][j].type == floorType::OCCUPIED)
	//			seatCount++;
	//	}
	//}

	//printf("Part 1: \n");
	//printf("---------------------------------\n");
	//printf("Number of Occupied Seats: %d\n", seatCount);
	//printf("\n");


	////////////
	// PART 2 //
	////////////

	bool changed = true;
	while (changed)
	{
		changed = false;
		std::vector<std::vector<Tile>> buffer;

		for (int i = 0; i < deck.size(); i++)
		{
			std::vector<Tile> row;
			for (int j = 0; j < deck[0].size(); j++)
			{
				// Floor never changes
				if (deck[i][j].type == floorType::FLOOR)
				{
					row.push_back(deck[i][j]);
				}

				// Free Seat
				else if (deck[i][j].type == floorType::EMPTY)
				{
					bool avail = true;
					for (int k = 0; k < deck[i][j].neighborsP2.size(); k++)
					{
						if (deck[i][j].neighborsP2.at(k)->type == floorType::OCCUPIED)
						{
							avail = false;
							break;
						}
					}

					// Becomes occupied
					if (avail)
					{
						row.push_back(deck[i][j]);
						row[j].type = floorType::OCCUPIED;

						if (!changed)
							changed = true;
					}
					else
					{
						row.push_back(deck[i][j]);
					}
				}

				// Occupied Seat
				else
				{
					int seatCount = 0;
					for (int k = 0; k < deck[i][j].neighborsP2.size(); k++)
					{
						if (deck[i][j].neighborsP2.at(k)->type == floorType::OCCUPIED)
						{
							seatCount++;
							if (seatCount >= 5)
							{
								break;
							}
						}
					}

					// Becomes Free
					if (seatCount >= 5)
					{
						row.push_back(deck[i][j]);
						row[j].type = floorType::EMPTY;

						if (!changed)
							changed = true;
					}
					else
					{
						row.push_back(deck[i][j]);

					}
				}

			}

			buffer.push_back(row);
		}

		deck = buffer;
	}

	// Count Occupied Seats
	int seatCountP2 = 0;
	for (int i = 0; i < deck.size(); i++)
	{
		for (int j = 0; j < deck[i].size(); j++)
		{
			if (deck[i][j].type == floorType::OCCUPIED)
				seatCountP2++;
		}
	}

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Number of Occupied Seats: %d\n", seatCountP2);
	printf("\n");



	return 0;
}