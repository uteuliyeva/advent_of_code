#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <memory>
#include <cmath>
#include <iomanip>

struct Monkey
{    
    std::queue<long long> itemWorryLevels;
    long long activityCount;

    std::string operationSign;
    std::string firstOperand;
    std::string secondOperand;

    int testValue;
    int trueThrowMonkeyIdx;
    int falseThrowMonkeyIdx;
};

void parseOperation(std::string& line, std::vector<Monkey>& monkeys, int monkeyCount)
{
    std::stringstream ss(line);
    std::string newVar, equalSign, firstOperand, operationSign, secondOperand;
    if(ss>>newVar>>newVar>>equalSign>>firstOperand>>operationSign>>secondOperand)
    {
        monkeys[monkeyCount].operationSign = operationSign;
        monkeys[monkeyCount].firstOperand = firstOperand;
        monkeys[monkeyCount].secondOperand = secondOperand;
    }
}

void parseItemQueue(std::string& line, std::vector<Monkey>& monkeys, int monkeyCount)
{
    std::stringstream ss(line);
    std::string token;
    while(ss>>token)
    {
        try{
            long long itemWorryLevel = std::stoi(token);
            monkeys[monkeyCount].itemWorryLevels.push(itemWorryLevel);
        }
        catch (const std::invalid_argument& e) { }
    }
}

void parseMonkeys(std::fstream& inputFile, std::vector<Monkey>& monkeys)
{
    std::string line;
    int monkeyCount = -1;
    while(getline(inputFile,line))
    {
        std::stringstream ss(line);
        std::string token;
        ss>>token;
        // Create new monkey
        if(token=="Monkey")
        {
            monkeyCount++;
            monkeys.push_back(Monkey());
            monkeys[monkeyCount].activityCount = 0;
        }

        // Create a queue of initial items
        else if(token=="Starting")
        {
            parseItemQueue(line, monkeys, monkeyCount);
        }

        // Read an operation
        else if(token=="Operation:")
        {
            parseOperation(line, monkeys, monkeyCount);
        }

        // Read test value
        else if(token=="Test:")
        {
            ss>>token>>token; // Read "divisible" and "by"
            ss>>monkeys[monkeyCount].testValue;
        }

        // Read throw monkeys indices
        else if(ss>>token && token=="true:")
        {
            ss>>token>>token>>token>>monkeys[monkeyCount].trueThrowMonkeyIdx;
        }
        else if(token=="false:")
        {
            ss>>token>>token>>token>>monkeys[monkeyCount].falseThrowMonkeyIdx;
        }
    }
}

void performRound(std::vector<Monkey>& monkeys, int worryLevelDropFactor)
{
    if (worryLevelDropFactor==1)
    {
        for(unsigned int i=0; i<monkeys.size(); i++)
        {
            worryLevelDropFactor *= monkeys[i].testValue;
        }
    }
    for(unsigned int i=0; i<monkeys.size(); i++)
    {
        while(!monkeys[i].itemWorryLevels.empty())
        {
            monkeys[i].activityCount++;
            long long oldWorryLevel = monkeys[i].itemWorryLevels.front();

            // Perform operation
            long long first,second;
            if(monkeys[i].firstOperand=="old") 
            { 
                first = oldWorryLevel;
            }
            else 
            { 
                first = std::stoi(monkeys[i].firstOperand);
            }

            if(monkeys[i].secondOperand=="old") 
            { 
                second = oldWorryLevel;
            }
            else 
            { 
                second = std::stoi(monkeys[i].secondOperand);
            }

            long long newWorryLevel;
            if(monkeys[i].operationSign=="+")
            {
                newWorryLevel = first + second;
            }
            else if(monkeys[i].operationSign=="-")
            {
                newWorryLevel = first - second;
            }
            else if(monkeys[i].operationSign=="*")
            {
                newWorryLevel = first * second;
            }
            else
            {
                newWorryLevel = std::round(first / second);
            }

            if (worryLevelDropFactor==3)
            {
                newWorryLevel = std::round(newWorryLevel / worryLevelDropFactor);
            }
            else
            {
                newWorryLevel = newWorryLevel % worryLevelDropFactor;
            }

            // Perform test & throw item
            int nextMonkeyIdx;
            if(newWorryLevel%monkeys[i].testValue ==0)
            {
                nextMonkeyIdx = monkeys[i].trueThrowMonkeyIdx;
            }
            else
            {
                nextMonkeyIdx = monkeys[i].falseThrowMonkeyIdx;
            }
            monkeys[nextMonkeyIdx].itemWorryLevels.push(newWorryLevel);
            monkeys[i].itemWorryLevels.pop();
        }
    }
}

int main()
{
    // Read the input file
    std::fstream inputFile("../adventofcode.com_2022_day_11_input.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file";
        return 1;
    }
    
    // Part 1
    std::vector<Monkey> monkeys;
    parseMonkeys(inputFile,monkeys);
    for(unsigned int i=0; i<20; i++)
    {
        performRound(monkeys,3);
    }

    std::vector<long long> monkeyActivity;
    for (unsigned int i=0; i<monkeys.size(); i++)
    {
        monkeyActivity.push_back(monkeys[i].activityCount);
    }
    std::sort(monkeyActivity.begin(), monkeyActivity.end(),std::greater<long long>());
    long long result = monkeyActivity[0] * monkeyActivity[1];

    // Part 2

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    std::vector<Monkey> monkeys2;
    parseMonkeys(inputFile,monkeys2);
    for(unsigned int i=0; i<10000; i++)
    {
        performRound(monkeys2,1);
    }

    std::vector<long long> monkeyActivity2;
    for (unsigned int i=0; i<monkeys2.size(); i++)
    {
        monkeyActivity2.push_back(monkeys2[i].activityCount);
    }
    std::sort(monkeyActivity2.begin(), monkeyActivity2.end(),std::greater<long long>());
    long long result2 = monkeyActivity2[0] * monkeyActivity2[1];

    //Output the answers
    std::cout<<"Answer #1 "<<result<<std::endl;
    std::cout<<"Answer #2 "<<result2<<std::endl;
    inputFile.close();
    return 0;
}