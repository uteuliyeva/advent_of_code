#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

int getGalaxyMap(std::fstream& inputFile, std::map<int,int>& galaxyRows, std::map<int,int>& galaxyCols)
{
    std::string line;
    int nLines = 0;
    int nGalaxies = 0;
    while(getline(inputFile,line))
    {
        for(int i=0; i<line.size(); i++)
        {
            if(line[i]=='#')
            {
                nGalaxies++;
                galaxyRows[nLines]++;
                galaxyCols[i]++;
            }
        }
        nLines++;
    }
    return nGalaxies;
}

long long sumShortestPaths(std::fstream& inputFile, const long long& expansionFactor)
{
    std::map<int,int> galaxyRows, galaxyCols;
    
    int numberOfGalaxies = getGalaxyMap(inputFile, galaxyRows, galaxyCols);
    
    // Vertical steps
    long long steps = 0;
    int prevGalaxyRow = galaxyRows.begin()->first;
    int nGalaxyTop = galaxyRows.begin()->second;
    int nGalaxyBottom = numberOfGalaxies - nGalaxyTop;
    for(const auto& row : galaxyRows)
    {
        int nextGalaxyRow = row.first;
        if (nextGalaxyRow == prevGalaxyRow) {continue;}
        long long numberOfRows = (nextGalaxyRow-prevGalaxyRow-1)*expansionFactor + 1;
        
        steps +=  numberOfRows * nGalaxyTop * nGalaxyBottom;
        prevGalaxyRow = nextGalaxyRow;
        nGalaxyTop += row.second;
        nGalaxyBottom -= row.second;
    }

    // Horizontal steps
    int prevGalaxyCol = galaxyCols.begin()->first;
    int nGalaxyLeft = galaxyCols.begin()->second;
    int nGalaxyRight = numberOfGalaxies - nGalaxyLeft;
    for(const auto& col : galaxyCols)
    {
        int nextGalaxyCol = col.first;
        if (nextGalaxyCol == prevGalaxyCol) {continue;}
        long long numberOfCols = (nextGalaxyCol-prevGalaxyCol-1)*expansionFactor + 1;
        
        steps +=  numberOfCols * nGalaxyLeft * nGalaxyRight;

        prevGalaxyCol = nextGalaxyCol;
        nGalaxyLeft += col.second;
        nGalaxyRight -= col.second;
    }

    return steps;
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

    // Part 1
    long long result = sumShortestPaths(inputFile, 2);

    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    long long result2 = sumShortestPaths(inputFile, 1000000);

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}



