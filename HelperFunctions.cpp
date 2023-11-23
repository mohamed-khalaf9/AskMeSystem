#include "HelperFunctions.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


HelperFunctions::HelperFunctions() {
}
std::vector<std::string> HelperFunctions::ReadFileLines(std::string path)
{
	std::vector<std::string> lines;

	std::fstream file_handler(path.c_str());

	if (file_handler.fail()) {
		std::cout << "\n\nERROR: Can't open the file\n\n";
		return lines;
	}
	std::string line;

	while (getline(file_handler, line)) {
		if (line.size() == 0)
			continue;
		lines.push_back(line);
	}

	file_handler.close();
	return lines;
}

void HelperFunctions::WriteFileLines(std::string path, std::vector<std::string> lines, bool append ) {
	auto status = std::ios::in | std::ios::out | std::ios::app;

	if (!append)
		status = std::ios::in | std::ios::out | std::ios::trunc;

	std::fstream file_handler(path.c_str(), status);

	if (file_handler.fail()) {
		std::cout << "\n\nERROR: Can't open the file\n\n";
		return;
	}
	for (auto line : lines)
		file_handler << line << "\n";

	file_handler.close();

}
std::vector<std::string> HelperFunctions::SplitString(std::string s, std::string delimiter )
{
	std::vector<std::string> strs;

	int pos = 0;
	std::string substr;
	while ((pos = (int)s.find(delimiter)) != -1) {
		substr = s.substr(0, pos);
		strs.push_back(substr);
		s.erase(0, pos + delimiter.length());
	}
	strs.push_back(s);
	return strs;
}

int HelperFunctions::ToInt(std::string str)
{
	std::istringstream iss(str);
	int num;
	iss >> num;

	return num;
}
int HelperFunctions::ReadInt(int low, int high)
{
	std::cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;

	std::cin >> value;

	if (low <= value && value <= high)
		return value;

	std::cout << "ERROR: invalid number...Try again\n";
	return ReadInt(low, high);
}

int HelperFunctions::ShowReadMenu(std::vector<std::string> choices)
{
	std::cout << "\nMenu:\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		std::cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return ReadInt(1, choices.size());
}