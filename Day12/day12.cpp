#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

#define PI 3.141592653589793238462643383279502884

int main(int argc, char* argv[])
{
	// Commands Buffer
	std::vector<std::pair<char, double>> commands;

	// Parse data file
	std::fstream file("day12.txt");
	std::string str;
	while (std::getline(file, str))
	{
		std::pair<char, int> cmd;
		cmd.first = str[0];

		str = str.substr(1, str.length() - 1);
		cmd.second = std::stod(str);

		commands.push_back(cmd);
	}
	file.close();


	////////////
	// PART 1 //
	////////////

	// Position of the ship
	std::pair<double, double> shipPosition(0.0, 0.0);
	double shipAngle = 90.0;

	// Handle all commands
	for (int i = 0; i < commands.size(); i++)
	{
		double arg = commands.at(i).second;
		switch (commands.at(i).first)
		{
			case 'N':
			{
				shipPosition.second += arg;
				break;
			}

			case 'S':
			{
				shipPosition.second -= arg;
				break;
			}

			case 'E':
			{
				shipPosition.first += arg;
				break;
			}

			case 'W':
			{
				shipPosition.first -= arg;
				break;
			}

			case 'L':
			{
				shipAngle -= arg;
				while (shipAngle < 0)
					shipAngle += 360;

				break;
			}

			case 'R':
			{
				shipAngle += arg;
				while (shipAngle > 360)
					shipAngle -= 360;

				break;
			}

			case 'F':
			{
				double rad = shipAngle * (PI / 180.0);

				shipPosition.first += arg * sin(rad);
				shipPosition.second += arg * cos(rad);

				break;
			}

			default:
				break;

		}
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Manhattan Position: %lf\n", abs(shipPosition.first) + abs(shipPosition.second));
	printf("\n");


	////////////
	// PART 2 //
	////////////

	// Reset ship position
	shipPosition.first = 0.0;
	shipPosition.second = 0.0;

	// Waypoint Position
	std::pair<double, double> wayPosition(10.0, 1.0);

	// Handle all commands
	for (int i = 0; i < commands.size(); i++)
	{
		double arg = commands.at(i).second;
		switch (commands.at(i).first)
		{
		case 'N':
		{
			wayPosition.second += arg;
			break;
		}

		case 'S':
		{
			wayPosition.second -= arg;
			break;
		}

		case 'E':
		{
			wayPosition.first += arg;
			break;
		}

		case 'W':
		{
			wayPosition.first -= arg;
			break;
		}

		case 'L':
		{
			double rad = arg * (PI / 180.0);

			double posX = (cos(rad) * wayPosition.first) - (sin(rad) * wayPosition.second);
			double posY = (sin(rad) * wayPosition.first) + (cos(rad) * wayPosition.second);

			wayPosition.first = posX;
			wayPosition.second = posY;

			break;
		}

		case 'R':
		{
			double rad = -(arg * (PI / 180.0));
			
			double posX = (cos(rad) * wayPosition.first) - (sin(rad) * wayPosition.second);			
			double posY = (sin(rad) * wayPosition.first) + (cos(rad) * wayPosition.second);

			wayPosition.first = posX;
			wayPosition.second = posY;

			break;
		}

		case 'F':
		{
			for (int i = 0; i < (int)arg; i++)
			{
				shipPosition.first += wayPosition.first;
				shipPosition.second += wayPosition.second;
			}

			break;
		}

		default:
			break;

		}
	}

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Manhattan Position: %lf\n", abs(shipPosition.first) + abs(shipPosition.second));
	printf("\n");


	return 0;
}