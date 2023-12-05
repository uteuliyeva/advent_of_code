#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

int evaluateGame(const std::string& line, const std::map<std::string,int>& colorToIntMap)
{
    std::string word;
    int gameIndex;
    int nCubes;

    std::stringstream ss(line);
    ss>>word>>gameIndex>>word;
    while(ss>>nCubes)
    {
        ss>>word;
        word.erase(remove(word.begin(), word.end(), ','));
        word.erase(remove(word.begin(), word.end(), ';'));
        if(nCubes>colorToIntMap.at(word))
        {
            return 0;
        }
    }
    return gameIndex;
}

int powerOfSet(const std::string& line)
{
    std::string color;
    int nCubes;
    std::map<std::string,int> colorMaxSet = {{"red",0},{"green",0},{"blue",0}};

    std::stringstream ss(line);
    ss>>color>>color;
    while(ss>>nCubes)
    {
        ss>>color;
        color.erase(remove(color.begin(), color.end(), ','));
        color.erase(remove(color.begin(), color.end(), ';'));
        if(nCubes>colorMaxSet.at(color))
        {
            colorMaxSet.at(color) = nCubes;
        }
    }
    return colorMaxSet.at("red")*colorMaxSet.at("green")*colorMaxSet.at("blue");
}

int main()
{
    // Read the input file
    std::fstream inputFile("../input.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file";
        return 1;
    }

    // Part 1
    const std::map<std::string,int> colorToIntMap = {{"red",12},{"green",13},{"blue",14}};
    int result = 0;

    std::string line;
    while(getline(inputFile,line))
    {
        result += evaluateGame(line, colorToIntMap);

    }
    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int result2 = 0;
    while(getline(inputFile,line))
    {
        result2 += powerOfSet(line);
    }

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

