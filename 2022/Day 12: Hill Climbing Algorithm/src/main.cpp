#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>

// Custom hash function for pairs of integers
struct CoordinateHash {
    size_t operator()(const std::pair<int, int>& key) const {
        return std::hash<int>()(key.first) ^ (std::hash<int>()(key.second) << 1);
    }
};

// Function to read the grid from an input file
void readGrid(std::fstream& inputFile, std::vector<std::vector<int> >& grid, std::pair<int, int>& startPos, std::pair<int, int>& endPos)
{
    std::string line;
    while(getline(inputFile,line))
    {
        std::vector<int> row;
        // Iterate over each character in the line
        for(unsigned int i = 0; i < line.size(); i++)
        {
            if(line[i] == 'E')      // If 'E' is found, set end position and push back 25
            {
                endPos = std::make_pair(grid.size(), i);
                row.push_back(25);
            }
            else if(line[i] == 'S') // If 'S' is found, set start position and push back 0
            {
                startPos = std::make_pair(grid.size(), i);
                row.push_back(0);
            }
            else                    // Otherwise, convert character to integer and push back
            {
                row.push_back(line[i] - 'a');
            }
        }
        grid.push_back(row);
    }
}

// Function to find the shortest path using Breadth-First Search (BFS)
void ShortestPathBFS(std::vector<std::vector<int> >& grid, std::unordered_map<std::pair<int, int>, int, CoordinateHash>& distanceToEnd, std::pair<int, int>& endPos)
{
    std::queue<std::pair<int, int> > nodesQueue;
    nodesQueue.push(endPos);
    distanceToEnd[endPos] = 0;
    
    // While there are nodes to process
    while(!nodesQueue.empty())
    {
        std::pair<int, int> currNode = nodesQueue.front();
        nodesQueue.pop();
        int currRow = currNode.first;
        int currCol = currNode.second;
        
        // Define the 4 possible neighbors (up, down, left, right)
        std::vector<std::pair<int, int> > neighbors;
        neighbors.push_back(std::make_pair(currRow-1, currCol));
        neighbors.push_back(std::make_pair(currRow+1, currCol));
        neighbors.push_back(std::make_pair(currRow, currCol-1));
        neighbors.push_back(std::make_pair(currRow, currCol+1));

        // Check each neighbor
        for(unsigned int i = 0; i < 4; i++)
        {
            int neighborRow = neighbors[i].first;
            int neighborCol = neighbors[i].second;
            // Check if the neighbor is within bounds, has a valid value, and has not been visited
            if(neighborRow >= 0 && neighborRow < grid.size() &&
               neighborCol >= 0 && neighborCol < grid[0].size() &&
               grid[neighborRow][neighborCol] >= grid[currRow][currCol] - 1 &&
               distanceToEnd.find(neighbors[i]) == distanceToEnd.end())
            {
                nodesQueue.push(neighbors[i]);
                distanceToEnd[neighbors[i]] = distanceToEnd[currNode] + 1;
            }
        }
    }
}

int main()
{
    // Read the input file
    std::fstream inputFile("../adventofcode.com_2022_day_12_input.txt");
    if(!inputFile)
    {
        std::cerr << "Unable to read the input file";
        return 1;
    }

    // Part 1
    std::vector<std::vector<int> > grid;
    std::unordered_map<std::pair<int, int>, int, CoordinateHash> distanceToEnd;
    std::pair<int, int> startPos, endPos;
    
    // Read the grid and initialize start and end positions
    readGrid(inputFile, grid, startPos, endPos);
    
    // Find the shortest path from end to start
    ShortestPathBFS(grid, distanceToEnd, endPos);
    
    // The result is the distance from start to end
    int result = distanceToEnd[startPos];

    // Part 2
    int result2 = result;
    for(unsigned int i=0; i<grid.size(); i++)
    {
        for (unsigned int j=0; j<grid[0].size(); j++)
        {
            // Check if the current cell has a value of 0 and if its distance to the end is less than result2
            if(grid[i][j]==0 && distanceToEnd.find(std::make_pair(i, j))!=distanceToEnd.end())
            {
                result2 = std::min(result2,distanceToEnd[std::make_pair(i, j)]);
            }
        }
    }
    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}
