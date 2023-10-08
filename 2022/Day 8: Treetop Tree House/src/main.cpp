#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

bool isVisible(std::vector<std::vector<int> >& grid, int row, int col)
{
    int nRows = grid.size();
    int nCols = grid[0].size();
    int height = grid[row][col];

    if (row==0||col ==0||row ==nRows-1||col==nCols-1)
    {
        return true;
    }
    
    std::vector<std::pair<int, int> > neighborsCoord;
    neighborsCoord.push_back(std::make_pair(row-1, col));
    neighborsCoord.push_back(std::make_pair(row, col-1));
    neighborsCoord.push_back(std::make_pair(row+1, col));
    neighborsCoord.push_back(std::make_pair(row, col+1));
    
    for (int i=0; i<4;i++)
    {
        int neighborRow = neighborsCoord[i].first;
        int neighborCol = neighborsCoord[i].second;

        while(neighborRow>=0&&neighborCol>=0&&neighborRow<nRows&&neighborCol<nCols&&height>grid[neighborRow][neighborCol])
        {
            // Change neighborCoord
            if (neighborRow==row)
            {
                if(neighborCol<col) { neighborCol--;}
                else {neighborCol++;}
            }
            else
            {
                if(neighborRow<row) { neighborRow--;}
                else {neighborRow++;}
            }
        }
        if (neighborRow<0||neighborRow==nRows||neighborCol<0||neighborCol==nCols)
        {
            return true;
        }
    }
    return false;
}

int getScenicScore(std::vector<std::vector<int> >& grid, int row, int col)
{
    int nRows = grid.size();
    int nCols = grid[0].size();
    int height = grid[row][col];

    if (row==0||col ==0||row ==nRows-1||col==nCols-1)
    {
        return 0;
    }

    std::vector<std::pair<int, int> > neighborsCoord;
    neighborsCoord.push_back(std::make_pair(row-1, col));
    neighborsCoord.push_back(std::make_pair(row, col-1));
    neighborsCoord.push_back(std::make_pair(row+1, col));
    neighborsCoord.push_back(std::make_pair(row, col+1));

    int totalScore = 1;
    
    for (int i=0; i<4;i++)
    {
        int neighborRow = neighborsCoord[i].first;
        int neighborCol = neighborsCoord[i].second;
        int sideScore = 1;

        while(neighborRow>=0&&neighborCol>=0&&neighborRow<nRows&&neighborCol<nCols&&height>grid[neighborRow][neighborCol])
        {
            sideScore++;
            
            // Change neighborCoord
            if (neighborRow==row)
            {
                if(neighborCol<col) { neighborCol--;}
                else {neighborCol++;}
            }
            else
            {
                if(neighborRow<row) { neighborRow--;}
                else {neighborRow++;}
            }
        }
        if (neighborRow<0||neighborRow==nRows||neighborCol<0||neighborCol==nCols)
        {
            sideScore--;
        }
        totalScore *=sideScore;
    }
    return totalScore;
}



int main()
{
    // Read the input data
    std::ifstream inputFile("../adventofcode.com_2022_day_8_input.txt"); 
    if (!inputFile) {  
        std::cerr << "Unable to open the input file" << std::endl;
        return 1;  
    }

    // Create and populate the grid
    std::vector<std::vector<int> > grid;
    std::string line;
    
    while(getline(inputFile,line))
    {
        std::vector<int> row;
        for(char c: line)
        {
            row.push_back(c-'0');
        }
        grid.push_back(row);
    }

    // Part 1
    int nRows = grid.size();
    int nCols = grid[0].size();
    int result = 0;
    for(int i=0; i<nRows; i++)
    {
        for(int j=0; j<nCols; j++)
        {
            if(isVisible(grid,i,j))
            {
                result++;
            }
        }
    }

    // Part 2
    int result2 = 0;
    for(int i=0; i<nRows; i++)
    {
        for(int j=0; j<nCols; j++)
        {
            result2 = std::max(result2, getScenicScore(grid,i,j));
        }
    }

    // Output results
    std::cout<<"Answer #1: "<< result <<std::endl;
    std::cout<<"Answer #2: "<< result2 << std::endl;
    return 0;
}