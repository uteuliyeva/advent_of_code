#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
    std::fstream inputFile ("../adventofcode.com_2022_day_4_input.txt");

    if(!inputFile)
    {
        std::cerr<<"Unable to open the input file"<<std::endl;
        return 1;
    }

    // Task #1
    int result = 0;
    std::string line;
    int firstElfStart, firstElfEnd, secondElfStart, secondElfEnd;

    while(getline(inputFile,line))
    {
        std::stringstream ss(line);
        std::string sectionRange;

        //Elf #1
        std::getline(ss, sectionRange, ',');
        std::sscanf(sectionRange.c_str(), "%d-%d", &firstElfStart, &firstElfEnd);

        //Elf #2
        std::getline(ss, sectionRange, ',');
        std::sscanf(sectionRange.c_str(), "%d-%d", &secondElfStart, &secondElfEnd);

        //Check if one range fully contains the other
        if((firstElfStart<=secondElfStart) && (firstElfEnd>=secondElfEnd))
        {
            result += 1;
        }
        else if((firstElfStart>=secondElfStart) && (firstElfEnd<=secondElfEnd))
        {
            result += 1;
        }
    }

    // Task #2
    int result2 = 0;

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    while(getline(inputFile,line))
    {
        std::stringstream ss(line);
        std::string sectionRange;

        //Elf #1
        std::getline(ss, sectionRange, ',');
        std::sscanf(sectionRange.c_str(), "%d-%d", &firstElfStart, &firstElfEnd);

        //Elf #2
        std::getline(ss, sectionRange, ',');
        std::sscanf(sectionRange.c_str(), "%d-%d", &secondElfStart, &secondElfEnd);

        //Check if ranges overlap
        if( !((firstElfEnd<secondElfStart) || (firstElfStart>secondElfEnd)) )
        {
            result2 += 1;
        }
    }

    //Output the answers
    std::cout<<"Answer #1 "<<result<<std::endl;
    std::cout<<"Answer #2 "<<result2<<std::endl;
    return 0;
}