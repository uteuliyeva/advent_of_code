#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <regex>

void getLoop(std::vector<std::string>& pipes, std::set<std::pair<int,int> >& loopCoords, size_t& prevRow, size_t& prevCol, size_t& currRow, size_t& currCol);
void getPipes(std::fstream& inputFile, std::vector<std::string>& pipes, size_t& startRow, size_t& startCol, size_t& nextRow, size_t& nextCol);
int enclosedArea(std::fstream& inputFile);
void markNonLoop(std::vector<std::string>& pipes, const std::set<std::pair<int,int> >& loopCoords);
void cleanMap(std::vector<std::string>& pipes);
int countNonLoop(std::vector<std::string>& pipes);
void changeStart(std::vector<std::string>& pipes, size_t& startRow, size_t& startCol);

std::map<char, std::pair<std::pair<int,int>, std::pair<int,int> > > pipeConnections;

void initializePipeConnections() {
    pipeConnections['|'] = std::make_pair(std::make_pair(-1, 0), std::make_pair(1, 0));
    pipeConnections['-'] = std::make_pair(std::make_pair(0, -1), std::make_pair(0, 1));
    pipeConnections['L'] = std::make_pair(std::make_pair(-1, 0), std::make_pair(0, 1));
    pipeConnections['J'] = std::make_pair(std::make_pair(-1, 0), std::make_pair(0, -1));
    pipeConnections['7'] = std::make_pair(std::make_pair(0, -1), std::make_pair(1, 0));
    pipeConnections['F'] = std::make_pair(std::make_pair(1, 0), std::make_pair(0, 1));
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

    initializePipeConnections();
    int result = enclosedArea(inputFile);

    std::cout << "Answer #2 " << result << std::endl;
    inputFile.close();
    return 0;
}

int enclosedArea(std::fstream& inputFile)
{
    std::vector<std::string> pipes;
    size_t startRow, startCol, nextRow, nextCol;
    getPipes(inputFile, pipes, startRow, startCol, nextRow, nextCol);

    std::set<std::pair<int,int> > loopCoords;
    getLoop(pipes, loopCoords, startRow, startCol, nextRow, nextCol);
    
    changeStart(pipes, startRow, startCol);
    markNonLoop(pipes, loopCoords);
    cleanMap(pipes);
    return countNonLoop(pipes);
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

void getLoop(std::vector<std::string>& pipes, std::set<std::pair<int,int> >& loopCoords, size_t& prevRow, size_t& prevCol, size_t& currRow, size_t& currCol)
{
    loopCoords.insert(std::make_pair(currRow, currCol));
    if(pipes[currRow][currCol]=='S') return;

    size_t nextRow = currRow + pipeConnections.at(pipes[currRow][currCol]).first.first;
    size_t nextCol = currCol + pipeConnections.at(pipes[currRow][currCol]).first.second;
    
    if(prevRow==nextRow && prevCol==nextCol)
    {
        nextRow = currRow + pipeConnections.at(pipes[currRow][currCol]).second.first;
        nextCol = currCol + pipeConnections.at(pipes[currRow][currCol]).second.second;
    }

    getLoop(pipes,loopCoords,currRow,currCol,nextRow,nextCol);
}

void markNonLoop(std::vector<std::string>& pipes, const std::set<std::pair<int,int> >& loopCoords) {
    for (int i = 0; i < pipes.size(); ++i) {
        for (int j = 0; j < pipes[i].length(); ++j) {
            if (loopCoords.find(std::make_pair(i, j)) == loopCoords.end()) {
                pipes[i][j] = '.';
            }
        }
    }
}

void cleanMap(std::vector<std::string>& pipes) {
    std::regex pattern1("F-*7|L-*J");
    std::regex pattern2("F-*J|L-*7");

    for (int i=0; i<pipes.size(); ++i) {
        pipes[i] = std::regex_replace(pipes[i], pattern1, " ");
        pipes[i] = std::regex_replace(pipes[i], pattern2, "|");
    }
}

int countNonLoop(std::vector<std::string>& pipes)
{
    int result = 0;
    for (int i=0; i<pipes.size(); ++i)
    {
        bool inside = false; 
        for(int j=0; j<pipes[i].size(); ++j)
        {
            if(pipes[i][j]=='|') 
            {
                inside = !inside;
            }
            else if(pipes[i][j]=='.' && inside)
            {
                result++;
                pipes[i][j]='X';
            }
        }
    }
    return result;
}

void changeStart(std::vector<std::string>& pipes, size_t& startRow, size_t& startCol) {
    bool connectedLeft = false, connectedRight = false;
    bool connectedTop = false, connectedBottom = false;

    // Check left
    if (startCol > 0) {
        char leftChar = pipes[startRow][startCol - 1];
        if (leftChar == 'L' || leftChar == '-' || leftChar == 'F') {
            connectedLeft = true;
        }
    }

    // Check right
    if (startCol < pipes[startRow].length() - 1) {
        char rightChar = pipes[startRow][startCol + 1];
        if (rightChar == 'J' || rightChar == '-' || rightChar == '7') {
            connectedRight = true;
        }
    }

    // Check top
    if (startRow > 0) {
        char topChar = pipes[startRow - 1][startCol];
        if (topChar == 'F' || topChar == '|' || topChar == '7') {
            connectedTop = true;
        }
    }

    // Check bottom
    if (startRow < pipes.size() - 1) {
        char bottomChar = pipes[startRow + 1][startCol];
        if (bottomChar == 'J' || bottomChar == '|' || bottomChar == 'L') {
            connectedBottom = true;
        }
    }

    // Determine the character based on connections
    if (connectedLeft && connectedRight) {
        pipes[startRow][startCol] = '-';
    } else if (connectedLeft && connectedTop) {
        pipes[startRow][startCol] = 'J';
    } else if (connectedLeft && connectedBottom) {
        pipes[startRow][startCol] = '7';
    } else if (connectedTop && connectedBottom) {
        pipes[startRow][startCol] = '|';
    } else if (connectedTop && connectedRight) {
        pipes[startRow][startCol] = 'L';
    } else if (connectedRight && connectedBottom) {
        pipes[startRow][startCol] = 'F';
    }
}

