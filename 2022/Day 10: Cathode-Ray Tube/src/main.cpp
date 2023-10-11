#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

int print_pixel(int spriteCenter, int pixelId)
{
    if (pixelId==spriteCenter || pixelId ==spriteCenter-1 ||pixelId ==spriteCenter+1)
    {
        std::cout<<"#";
    }
    else
    {
        std::cout<<".";
    }
    if((pixelId+1)%40==0)
    {
        std::cout<<"\n";
        pixelId = -1;
    }
    return pixelId;
}

int main()
{
    // Read the input file
    std::fstream inputFile("../adventofcode.com_2022_day_10_input.txt");

    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file";
        return 1;
    }

    // Part 1
    int currentCycle = 0;
    int X = 1;
    int specialCycle = 20;
    int result = 0;

    std::string line;
    while(getline(inputFile,line))
    {
        std::stringstream ss(line);
        std::string command;
        int increment;

        ss>>command;

        currentCycle++;
        if (currentCycle>=specialCycle)
        {
            result += specialCycle * X;
            specialCycle += 40;
        }
        if (command=="addx")
        {
            currentCycle++;
            if (currentCycle>=specialCycle)
            {
                result += specialCycle * X;
                specialCycle += 40;
            }
            ss>>increment;
            X += increment;
        }
    }

    // Output results
    std::cout<<"Answer #1: "<< result <<std::endl;

    // Part 2

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    currentCycle = -1;
    X = 1;

    while(getline(inputFile,line))
    {
        // Read the command
        std::stringstream ss(line);
        std::string command;
        int increment;
        ss>>command;

        currentCycle++;
        currentCycle = print_pixel(X, currentCycle);

        if (command=="addx")
        {
            currentCycle++;
            currentCycle = print_pixel(X, currentCycle);
            ss>>increment;
            X += increment;
        }
    }

    inputFile.close();
    return 0;
}