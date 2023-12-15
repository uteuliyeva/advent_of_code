#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

std::map<char, std::pair<std::pair<int,int>, std::pair<int,int> > > pipeConnections;

void initializePipeConnections() {
    pipeConnections['|'] = std::make_pair(std::make_pair(-1, 0), std::make_pair(1, 0));
    pipeConnections['-'] = std::make_pair(std::make_pair(0, -1), std::make_pair(0, 1));
    pipeConnections['L'] = std::make_pair(std::make_pair(-1, 0), std::make_pair(0, 1));
    pipeConnections['J'] = std::make_pair(std::make_pair(-1, 0), std::make_pair(0, -1));
    pipeConnections['7'] = std::make_pair(std::make_pair(0, -1), std::make_pair(1, 0));
    pipeConnections['F'] = std::make_pair(std::make_pair(1, 0), std::make_pair(0, 1));
}

int farthestInLoop(std::fstream& inputFile);
void getPipes(std::fstream& inputFile, std::vector<std::string>& pipes, size_t& startRow, size_t& startCol, size_t& nextRow, size_t& nextCol);
int traverseLoop(std::vector<std::string>& pipes, size_t& prevRow, size_t& prevCol, size_t& currRow, size_t& currCol);

int main()
{
    // Read the input file
    std::fstream inputFile("../input.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file";
        return 1;
    }

    initializePipeConnections();
    int result = farthestInLoop(inputFile);

    std::cout << "Answer #1 " << result << std::endl;
    inputFile.close();
    return 0;
}

int farthestInLoop(std::fstream& inputFile)
{
    std::vector<std::string> pipes;
    size_t startRow, startCol, nextRow, nextCol;

    getPipes(inputFile, pipes, startRow, startCol, nextRow, nextCol);

    int result = traverseLoop(pipes, startRow, startCol, nextRow, nextCol)/ 2 ;
    return result;
}

void getPipes(std::fstream& inputFile, std::vector<std::string>& pipes, size_t& startRow, size_t& startCol, size_t& nextRow, size_t& nextCol)
{
    std::string line;
    while(getline(inputFile, line))
    {
        pipes.push_back(line);
        if (line.find('S')!=std::string::npos){
            startRow = pipes.size()-1;
            startCol = line.find('S');
        }
    }

    if(pipes[startRow-1][startCol]=='|' || pipes[startRow-1][startCol]=='7' || pipes[startRow-1][startCol]=='F')
    {
        nextRow = startRow-1;
        nextCol = startCol;
    }  
    else if (pipes[startRow][startCol-1]=='-' || pipes[startRow][startCol-1]=='L' || pipes[startRow][startCol-1]=='F'){
        nextRow = startRow;
        nextCol = startCol-1;
    }
    else{
        nextRow = startRow+1;
        nextCol = startCol;
    }
}

int traverseLoop(std::vector<std::string>& pipes, size_t& prevRow, size_t& prevCol, size_t& currRow, size_t& currCol)
{
    if(pipes[currRow][currCol]=='S') return 1;

    size_t nextRow = currRow + pipeConnections.at(pipes[currRow][currCol]).first.first;
    size_t nextCol = currCol + pipeConnections.at(pipes[currRow][currCol]).first.second;
    
    if(prevRow==nextRow && prevCol==nextCol)
    {
        nextRow = currRow + pipeConnections.at(pipes[currRow][currCol]).second.first;
        nextCol = currCol + pipeConnections.at(pipes[currRow][currCol]).second.second;
    }

    return 1 + traverseLoop(pipes, currRow, currCol, nextRow, nextCol);
}

