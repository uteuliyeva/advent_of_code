#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cmath>

bool searchWordInDirection(const std::vector<std::string>& grid, const std::string& keyword, size_t row, size_t col, int deltaRow, int deltaCol, size_t i) {
    if (i == keyword.length()) return true;
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].length() || grid[row][col] != keyword[i]) return false;
    return searchWordInDirection(grid, keyword, row + deltaRow, col + deltaCol, deltaRow, deltaCol, i + 1);
}

int searchWord(const std::vector<std::string>& grid, const std::string& keyword, size_t row, size_t col) {
    static const int directions[8][2] = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}, // Straight directions
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1} // Diagonal directions
    };

    int count = 0;
    for (int d = 0; d < 8; ++d) {
        count += searchWordInDirection(grid, keyword, row, col, directions[d][0], directions[d][1], 0);
    }
    return count;
}

bool searchXofMAS(const std::vector<std::string>& grid, size_t row, size_t col) {
    if(row==0||row==grid.size()-1||col==0||col==grid[0].length()-1||grid[row][col]!='A') return false;
    return ((grid[row-1][col-1]=='M'&&grid[row+1][col+1]=='S') || (grid[row-1][col-1]=='S'&&grid[row+1][col+1]=='M')) &&
    ((grid[row-1][col+1]=='M'&&grid[row+1][col-1]=='S') || (grid[row-1][col+1]=='S'&&grid[row+1][col-1]=='M'));
}

int main (){

    // Read the input data
    std::ifstream inputFile("../input.txt"); 
    if (!inputFile) {  
        std::cerr << "Unable to open the input file" << std::endl;
        return 1;  
    }

    // Task #1
    std::string line;
    int result = 0;
    std::vector<std::string> grid;

    while(getline(inputFile,line)){
        grid.push_back(line);
    }

    std::string keyword = "XMAS";
    for(size_t i=0; i<grid.size(); i++){
        for(size_t j=0; j<grid[0].length(); j++){
            result+=searchWord(grid, keyword, i, j);
        }
    }

    // Task #2
    int result2 = 0;
    for(size_t i=0; i<grid.size(); i++){
        for(size_t j=0; j<grid[0].length(); j++){
            result2+=searchXofMAS(grid, i, j);
        }
    }

    // Output the answer
    std::cout << "Answer #1: " << result << std::endl;
    std::cout << "Answer #2: " << result2 << std::endl;
}