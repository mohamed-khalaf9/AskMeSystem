#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include <vector>
#include <string>



class HelperFunctions {

public:

    HelperFunctions();
    std::vector<std::string> ReadFileLines(std::string path);
    void WriteFileLines(std::string path, std::vector<std::string> lines, bool append = true);
    std::vector<std::string> SplitString(std::string s, std::string delimiter = ",");
    int ToInt(std::string str);
    int ReadInt(int low, int high);
    int ShowReadMenu(std::vector<std::string> choices);

};



#endif