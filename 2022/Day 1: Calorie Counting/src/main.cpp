#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
    // Read the input data
    std::ifstream inputFile("../adventofcode.com_2022_day_1_input.txt"); 
    if (!inputFile) {  
        std::cerr << "Unable to open the input file" << std::endl;
        return 1;  
    }

    // Task #1
    int maxCalories = 0;
    std::string line;
    int calories;
    int currElfTotal = 0;

    while(getline(inputFile,line))
    {
        std::stringstream ss(line);

        if(ss >> calories)
        {
            currElfTotal += calories;
        }
        else
        {
            maxCalories = std::max(maxCalories,currElfTotal);
            currElfTotal = 0;
        }
    }

    // Task #2
    int threeMaxCalories[3] = {0,0,0};
    currElfTotal = 0;
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    while(getline(inputFile,line))
    {
        std::stringstream ss(line);

        if(ss >> calories)
        {
            currElfTotal += calories;
        }
        else
        {
            threeMaxCalories[0] = std::max(threeMaxCalories[0],currElfTotal);
            std::sort(threeMaxCalories, threeMaxCalories + 3);
            currElfTotal = 0;
        }
    }

    int sumThreeMaxCalories = threeMaxCalories[0]+threeMaxCalories[1]+threeMaxCalories[2];
    
    std::cout<<"Answer #1: "<< maxCalories <<std::endl;
    std::cout<<"Answer #2: "<< sumThreeMaxCalories << std::endl;
    return 0;
}