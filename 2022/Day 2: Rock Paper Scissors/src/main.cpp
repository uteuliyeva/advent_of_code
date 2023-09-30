#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

int main()
{
    std::ifstream inputFile("../adventofcode.com_2022_day_2_input.txt");
    if (!inputFile)
    {
        std::cerr << "Unable to open the input file";
        return 1;
    }

    // Task #1

    // Define the maps decoding the input file
    std::unordered_map<std::string, std::string> winnerFor = {{"Rock","Paper"}, {"Paper","Scissors"}, {"Scissors", "Rock"}};
    std::unordered_map<std::string, std::string> elfPlay = {{"A", "Rock"}, {"B","Paper"}, {"C","Scissors"}};
    std::unordered_map<std::string, std::string> myPlay = {{"X", "Rock"}, {"Y","Paper"}, {"Z","Scissors"}};
    std::unordered_map<std::string, int> shapeScore = {{"Rock", 1}, {"Paper", 2}, {"Scissors", 3}};

    std::string line;
    std::string elfShape;
    std::string myShape;
    int totalScore = 0;

    while(getline(inputFile,line))
    {
        std::istringstream iss(line);
        iss >> elfShape >> myShape;
        
        elfShape = elfPlay[elfShape];
        myShape = myPlay[myShape];

        totalScore+=shapeScore[myShape];

        if (myShape == winnerFor[elfShape]) // I win
        {
            totalScore += 6;
        }
        else if(myShape == elfShape) // Draw
        {
            totalScore += 3;
        }
    }

    // Task #2

    // Define the maps decoding the input file
    std::unordered_map<std::string, int> myPlay2 = {{"X", 0}, {"Y", 3}, {"Z", 6}};

    // Reset the read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int totalScore2 = 0;
    int myOutcome;

    while(getline(inputFile,line))
    {
        std::istringstream iss(line);
        iss >> elfShape >> myShape;
        
        elfShape = elfPlay[elfShape];
        myOutcome = myPlay2[myShape];

        totalScore2 += myOutcome;

        if (myOutcome==6) // Win
        {
            myShape = winnerFor[elfShape];
        }
        else if(myOutcome==3) // Draw
        {
            myShape = elfShape;
        }
        else
        {
            myShape = winnerFor[winnerFor[elfShape]];
        }
        totalScore2 += shapeScore[myShape];
    }
    

    std::cout<<"Answer #1: "<<totalScore<<std::endl;
    std::cout<<"Answer #2: "<<totalScore2<<std::endl;
    return 0;
}