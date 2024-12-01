#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cmath>

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
    std::vector<int> leftList;
    std::vector<int> rightList;

    while(getline(inputFile,line)){

        std::istringstream lineStream(line);
        int left, right;

        if (lineStream >> left >> right) {
            leftList.push_back(left);
            rightList.push_back(right);
        }
    }

    // Sort lists
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    //Find the distance
    for(size_t i=0; i<leftList.size(); i++){
        result += std::abs(leftList[i] - rightList[i]);
    }

    // Task #2
    int result2 = 0;
    size_t leftIndex = 0;
    size_t rightIndex = 0;

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    while(leftIndex<leftList.size() && rightIndex<rightList.size()){
        int appears = 0;
        if(leftList[leftIndex]<rightList[rightIndex]){
            leftIndex++;
        } else if (leftList[leftIndex]>rightList[rightIndex]){
            rightIndex++;
        } else {
            result2 += leftList[leftIndex];
            rightIndex++;
        }
    }

    // Output the answer
    std::cout << "Answer #1: " << result << std::endl;
    std::cout << "Answer #2: " << result2 << std::endl;
}