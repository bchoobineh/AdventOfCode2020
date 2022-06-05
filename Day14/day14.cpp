#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>


// Function to convert a long into a 36bit binary representation in a string
std::string longToString(long long x)
{
	std::string str = "";
	while (x > 0)
	{
		if ((x % 2) == 0)
			str = "0" + str;
		else
			str = "1" + str;

		x = x / 2;
	}

	// Add Leading 0's
	while (str.length() < 36)
		str = "0" + str;

	return str;
}


// Function to convert a 36bit binary represntation in a string to a long
long long stringToLong(std::string str)
{
	long long val = 0;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[str.length() - 1 - i];
		if (c == '1')
		{
			val += std::pow(2, i);
		}
	}

	return val;
}


// Function to apply mask to a long
long long applyMask(std::string mask, long long x)
{
	// Convert long to a 36 bit binary representation
	std::string ln = longToString(x);

	// Apply Mask
	std::string result;
	for (int i = 0; i < mask.length(); i++)
	{
		if (mask[i] == 'X')
			result += ln[i];
		else if (mask[i] == '1')
			result += '1';
		else
			result += '0';
	}

	// Convert
	long long val = stringToLong(result);

	return val;
}

void addrHelper(std::string mask, std::string addr, std::string current, std::vector<long long>& res, int index)
{
	if (index >= mask.length())
	{
		res.push_back(stringToLong(current));
		return;
	}

	if (mask[index] == '0')
	{
		addrHelper(mask, addr, current + addr[index], res, index + 1);
	}
	else if (mask[index] == '1')
	{
		addrHelper(mask, addr, current + "1", res, index + 1);
	}
	else
	{
		addrHelper(mask, addr, current + "0", res, index + 1);
		addrHelper(mask, addr, current + "1", res, index + 1);
	}
}

std::vector<long long> getMaskedAddr(std::string mask, long long addr)
{
	std::vector<long long> res;

	// Convert address to string
	std::string a = longToString(addr);

	addrHelper(mask, a, "", res, 0);

	return res;
}


struct Cmd
{
	long long addr, val;
	std::string mask;
	Cmd()
	{
		addr = -1;
		val = -1;
	}
};

int main(int argc, char* argv[])
{
	// Data buffer of commands
	std::vector<Cmd> input;

	// Parse Input Data
	std::fstream file("day14.txt");
	std::string str;
	while (std::getline(file, str))
	{
		Cmd command;

		// Attempt to find what kind of command this is
		std::string tmp = str.substr(0, 4);

		// Mask Command
		if (tmp == "mask")
		{
			std::stringstream ss(str);
			std::getline(ss, tmp, ' ');
			std::getline(ss, tmp, ' ');
			std::getline(ss, tmp, ' ');

			command.mask = tmp;
		}

		// Memory Command
		else
		{
			// Acquire Address
			std::stringstream ss(str);
			std::getline(ss, tmp, ' ');
			tmp = tmp.substr(4, tmp.length() - 4);
			tmp = tmp.substr(0, tmp.length() - 1);
			command.addr = std::stol(tmp);

			// Acquire Val
			std::getline(ss, tmp, ' ');
			std::getline(ss, tmp, ' ');
			command.val = std::stol(tmp);
		}

		// Add command to input buffer
		input.push_back(command);
	}
	file.close();


	////////////
	// PART 1 //
	////////////

	std::string mask = "";
	std::unordered_map<long long, long long> mem;

	// Go through commands
	for (int i = 0; i < input.size(); i++)
	{
		// Mask Setting Command
		if (input[i].addr == -1 && input[i].val == -1)
		{
			mask = input[i].mask;
		}

		// Memory Setting Command
		else
		{
			long long val = applyMask(mask, input[i].val);
			mem[input[i].addr] = val;
		}
	}

	// Get sum
	long long sum = 0;
	for (auto i = mem.begin(); i != mem.end(); i++)
		sum += i->second;

	printf("Part 1: \n");
	printf("---------------------------------\n");
	printf("Sum: %lld\n", sum);
	printf("\n");


	////////////
	// PART 2 //
	////////////

	// Reset
	mask = "";
	mem.clear();
	sum = 0;

	// Go through every command
	for (int i = 0; i < input.size(); i++)
	{
		// Mask Setting Command
		if (input[i].addr == -1 && input[i].val == -1)
		{
			mask = input[i].mask;
		}

		// Memory Setting Command
		else
		{
			std::vector<long long> addr = getMaskedAddr(mask, input[i].addr);
			for (auto j : addr)
				mem[j] = input[i].val;

		}
	}

	// Get sum
	for (auto i = mem.begin(); i != mem.end(); i++)
		sum += i->second;


	printf("Part 2: \n");
	printf("---------------------------------\n");
	printf("Sum: %lld\n", sum);
	printf("\n");



	return 0;
}