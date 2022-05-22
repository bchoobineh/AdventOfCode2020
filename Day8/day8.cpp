#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>

struct Instruction
{
	std::string ID;
	int index;
	int argument;
};

bool checkValid(std::vector<Instruction> data, int* accum)
{
	std::unordered_set<int> visited;
	int index = 0;
	while (visited.find(index) == visited.end())
	{
		visited.insert(index);
		if (data.at(index).ID == "acc")
		{
			*accum = *accum + data.at(index).argument;
			index++;
		}
		else if (data.at(index).ID == "jmp")
		{
			index += data.at(index).argument;
		}
		else
		{
			index++;
		}

		if (index >= data.size())
			return true;

	}

}

int main(int argc, char* argv[])
{
	// Data buffer of Instructions
	std::vector<Instruction> data;

	// Parse data file
	std::fstream file("day8.txt");
	std::string str;
	int count = 0;

	while (std::getline(file, str))
	{
		Instruction inst;
		
		std::stringstream ss(str);
		std::string word;

		std::getline(ss, word, ' ');
		inst.ID = word;

		std::getline(ss, word, ' ');
		inst.argument = std::stoi(word);

		inst.index = count;
		count++;

		data.push_back(inst);
	}
	file.close();


	////////////
	// PART 1 //
	////////////

	int part1Sol = 0;
	std::unordered_set<int> seenInstructions;
	int index = 0;
	while (seenInstructions.find(index) == seenInstructions.end())
	{
		seenInstructions.insert(index);

		if (data.at(index).ID == "acc")
		{
			part1Sol += data.at(index).argument;
			index++;
		}
		else if (data.at(index).ID == "jmp")
		{
			index += data.at(index).argument;
		}
		else
		{
			index++;
		}
	}

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Accumulator Value: %d\n", part1Sol);
	printf("\n");


	////////////
	// PART 2 //
	////////////
	
	int part2Sol = 0;
	for (int i = 0; i < data.size(); i++)
	{
		int accum = 0;
		if (data.at(i).ID == "jmp")
		{
			data.at(i).ID = "nop";
			if (checkValid(data, &accum) == true)
			{
				part2Sol = accum;
				break;
			}
			data.at(i).ID = "jmp";
		}
		else if (data.at(i).ID == "nop")
		{
			data.at(i).ID = "jmp";
			if (checkValid(data, &accum) == true)
			{
				part2Sol = accum;
				break;
			}
			data.at(i).ID = "nop";
		}
	}

	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Accumulator Value: %d\n", part2Sol);
	printf("\n");

	return 0;
}