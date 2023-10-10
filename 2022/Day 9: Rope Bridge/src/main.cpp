#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

std::pair<int,int> getNextKnotPosition(int headRow,int headCol,int tailRow,int tailCol)
{
    int deltaRow = headRow - tailRow;
    int deltaCol = headCol - tailCol;

    if(!(deltaRow>=-1&&deltaRow<=1&&deltaCol>=-1&&deltaCol<=1))
    {
        tailRow += std::min(std::max(deltaRow,-1),1);
        tailCol += std::min(std::max(deltaCol,-1),1);
    }
    return std::make_pair(tailRow,tailCol);
}


int main()
{
    // Read the input file
    std::fstream inputFile("../adventofcode.com_2022_day_9_input.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file";
        return 1;
    }

    // Part 1
    std::string line;
    std::set<std::pair <int,int> > tailCoords;
    int headRow = 0;
    int headCol = 0;
    int tailRow = 0;
    int tailCol = 0;

    tailCoords.insert(std::make_pair(tailRow,tailCol)); // Add the initial position to the set

    while(getline(inputFile,line))
    {
        // Parse the direction and number of steps
        std::stringstream ss(line);
        char direction;
        int nSteps;
        ss>>direction>>nSteps;

        // Make the steps
        for (unsigned int i=0; i<nSteps; i++)
        {
            if(direction=='U') {headRow++;}
            else if(direction=='D') {headRow--;}
            else if(direction=='L') {headCol--;}
            else {headCol++;}

            std::pair<int,int> tailNewPos = getNextKnotPosition(headRow,headCol,tailRow,tailCol);
            tailRow = tailNewPos.first;
            tailCol = tailNewPos.second;
            tailCoords.insert(tailNewPos);
        }
    }

    int result = tailCoords.size();

    // Part 2

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    // Reset the variables
    std::set<std::pair <int,int> > tailCoords2;
    std::vector<std::pair <int,int> > currKnotCoords;
    
    //Set current coordinates to (0,0)
    for (unsigned i=0;i<10;i++)
    {
        currKnotCoords.push_back(std::make_pair(0,0));
    }

    while(getline(inputFile,line))
    {
        // Parse the direction and number of steps
        std::stringstream ss(line);
        char direction;
        int nSteps;
        ss>>direction>>nSteps;

        headRow = currKnotCoords[0].first;
        headCol = currKnotCoords[0].second;

        // Make the steps
        for (unsigned int i=0; i<nSteps; i++)
        {
            if(direction=='U') {headRow++;}
            else if(direction=='D') {headRow--;}
            else if(direction=='L') {headCol--;}
            else {headCol++;}

            currKnotCoords[0] = std::make_pair(headRow,headCol);
            for (unsigned int j=0; j<9; j++)
            {
                currKnotCoords[j+1] = getNextKnotPosition(currKnotCoords[j].first,currKnotCoords[j].second,currKnotCoords[j+1].first,currKnotCoords[j+1].second);
            }
            tailCoords2.insert(currKnotCoords[9]);
        }
    }

    int result2 = tailCoords2.size();

    // Output results
    std::cout<<"Answer #1: "<< result <<std::endl;
    std::cout<<"Answer #2: "<< result2 << std::endl;
    inputFile.close();
    return 0;
}