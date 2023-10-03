#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>

std::string concatenateTops(const std::vector<std::stack<char> >& stacks) {
    std::string tops;
    for (size_t i = 0; i < stacks.size(); i++) {
        if (!stacks[i].empty()) {
            tops += stacks[i].top();
        }
    }
    return tops;
}

std::vector< std::stack<char> > parseStacks(std::fstream& inputFile, size_t numStacks)
{
    std::vector<std::stack<char> > reversed_stacks;
    std::string line;

    // Parse the stacks
    while(getline(inputFile,line))
    {
        reversed_stacks.resize(numStacks);

        // Break if the line with numbers of stacks is reached
        if(line[1]=='1')
        {
            break;
        }

        // Populate the stacks in reversed order
        for(size_t i=0; i<reversed_stacks.size();i++)
        {
            char c = line[i*4+1]; // Take the char from the brackets
            if(c!=' ')
            {
                reversed_stacks[i].push(c);
            }
        }
    }

    return reversed_stacks;
}

std::vector< std::stack<char> > reverseStacks(std::vector< std::stack<char> > reversed_stacks)
{
    size_t numStacks = reversed_stacks.size();
    std::vector<std::stack<char> > stacks(numStacks);

    for (size_t i=0; i<reversed_stacks.size();i++)
    {
        while(!reversed_stacks[i].empty())
        {
            stacks[i].push(reversed_stacks[i].top());
            reversed_stacks[i].pop();
        }
    }

    return stacks;
}

int main() {

    // Read the input file
    std::fstream inputFile("../adventofcode.com_2022_day_5_input.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to open the input file."<<std::endl;
        return 1;
    }

    // Task #1

    std::string line;
    size_t numStacks;
    
    // Get the number of stacks
    while(getline(inputFile,line))
    {
        if(line[1]=='1'){
            numStacks = line.size()/4 + 1; // The width of each stack is 4, the last stack is of width 3.
            break;
        }
    }

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    // Parse the stacks in reversed order & reverse the stacks
    std::vector<std::stack<char> > reversed_stacks = parseStacks(inputFile,numStacks);
    std::vector<std::stack<char> > stacks = reverseStacks(reversed_stacks);

    // Parse the move commands and implement them
    while(getline(inputFile,line))
    {
        // Skip the non-command lines
        if(line[0]!='m'){
            continue;
        }

        std::istringstream iss(line);
        std::string word;
        int numCrates;
        int fromStack;
        int toStack;

        // Parse the line
        iss>>word>>numCrates>>word>>fromStack>>word>>toStack;

        //Implement moves
        for (int i=0; i<numCrates; i++)
        {
            stacks[toStack-1].push(stacks[fromStack-1].top());
            stacks[fromStack-1].pop();
        }
    }

    // Task #2 

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    // Parse the stacks in reversed order & reverse the stacks
    std::vector<std::stack<char> > reversed_stacks2 = parseStacks(inputFile,numStacks);
    std::vector<std::stack<char> > stacks2 = reverseStacks(reversed_stacks2);

    // Parse the move commands and implement them
    while(getline(inputFile,line))
    {
        // Skip the non-command lines
        if(line[0]!='m'){
            continue;
        }

        std::istringstream iss(line);
        std::string word;
        int numCrates;
        int fromStack;
        int toStack;

        // Parse the line
        iss>>word>>numCrates>>word>>fromStack>>word>>toStack;

        //Implement moves: First push the crates to a temporary stack and then from temporary stack to toStack
        std::stack<char> temp_stack;
        for (int i=0; i<numCrates; i++)
        {
            temp_stack.push(stacks2[fromStack-1].top());
            stacks2[fromStack-1].pop();
        }

        for (int i=0; i<numCrates; i++)
        {
            stacks2[toStack-1].push(temp_stack.top());
            temp_stack.pop();
        }
    }

    //Output the answers
    std::cout<<"Answer #1 "<<concatenateTops(stacks)<<std::endl;
    std::cout<<"Answer #2 "<<concatenateTops(stacks2)<<std::endl;

    return 0;
}
