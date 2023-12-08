#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

int getAdjacentNumber(std::string& line, const int& j)
{
    int col=j;
    int result = 0;
    while(col>0 && isdigit(line[col-1])) col--;
    while(col<line.size() && isdigit(line[col])){
        result *= 10;
        result += line[col]-'0';
        line[col] = '.';
        col++;
    }
    return result;
}

int getPartNumbers(std::vector<std::string>& grid, const int& i, const int& j)
{
    int result = 0;

    // Check for symbols around the number
    for(int di=-1; di<=1; di++)
    {
        for(int dj=-1; dj<=1; dj++)
        {
            if (di==0 && dj==0) continue; // Skip the cells containing the symbol

            // Check that cell is within the boundaries
            if(i+di>=0 && i+di<grid.size() && j+dj>=0 && j+dj<grid[0].size())
            {
                if(isdigit(grid[i+di][j+dj]))
                {
                    result += getAdjacentNumber(grid[i+di],j+dj);
                }
            }
        }
    }
    return result;
}



int getGearRatio(std::vector<std::string>& grid, const int& i, const int& j)
{
    int adjacentNumbersFound = 0;
    int result = 1;

    // Check for numbers around the symbol
    for(int di=-1; di<=1; di++)
    {
        for(int dj=-1; dj<=1; dj++)
        {
            if (di==0 && dj==0) continue; // Skip the cells containing the symbol

            // Check that cell is within the boundaries
            if(i+di>=0 && i+di<grid.size() && j+dj>=0 && j+dj<grid[0].size())
            {
                if(isdigit(grid[i+di][j+dj]))
                {
                    adjacentNumbersFound++;
                    result *= getAdjacentNumber(grid[i+di], j+dj);
                }
            }
        }
    }
    if(adjacentNumbersFound==2)
    {
        return result;
    }
    else
    {
        return 0;
    }
}

int main()
{
    // Read the input file
    std::fstream inputFile("../input_test.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file";
        return 1;
    }

    // Part 1
    int result = 0;
    std::string line;

    // Read the input and store in grid datastructure
    std::vector<std::string> grid;
    while(getline(inputFile,line))
    {
        grid.push_back(line);
    }

    for(int i=0; i<grid.size(); i++)
    {
        for(int j=0; j<grid[0].size(); j++)
        {
            if(!isdigit(grid[i][j]) && grid[i][j]!='.')
            {
                result+=getPartNumbers(grid, i, j);
            }
        }
    }


    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int result2 = 0;

    std::vector<std::string> grid2;
    while(getline(inputFile,line))
    {
        grid2.push_back(line);
    }

    for(int i=0; i<grid2.size(); i++)
    {
        for(int j=0; j<grid2[0].size(); j++)
        {
            if(grid2[i][j]=='*')
            {
                result2+=getGearRatio(grid2, i, j);
            }
        
        }
    }

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

