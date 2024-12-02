#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cmath>


bool isSafe(const std::vector<int>& numbers){
    bool increasing = true;
    bool decreasing = true;

    for (size_t i = 1; i < numbers.size(); ++i) {
        int difference = numbers[i] - numbers[i - 1];
        if (!(1 <= std::abs(difference) && std::abs(difference) <= 3)) {
            return false;
        }
        if (difference>0) {
            decreasing = false;
        } else if (difference<0) {
            increasing = false;
        }
    }
    return increasing || decreasing;
}

bool isSafeWithProblemDampener(const std::vector<int>& numbers){
    for (size_t i = 0; i < numbers.size(); ++i){
        std::vector<int> redacted = numbers;
        redacted.erase(redacted.begin() + i);
        if(isSafe(redacted)){
            return true;
        }
    }
    return false;
}


int main (){

    // Read the input data
    std::ifstream inputFile("../input.txt"); 
    if (!inputFile) {  
        std::cerr << "Unable to open the input file" << std::endl;
        return 1;  
    }

    std::string line;
    int result = 0;
    int result2 = 0;

    while(getline(inputFile,line)){

        std::istringstream iss(line);
        std::vector<int> report;
        int level;

        while (iss >> level) {
            report.push_back(level);
        }
        bool reportIsSafe = isSafe(report);
        result += reportIsSafe;
        result2 += reportIsSafe;
        if(!reportIsSafe){
            result2 += isSafeWithProblemDampener(report);
        }
    }

    // Output the answer
    std::cout << "Answer #1: " << result << std::endl;
    std::cout << "Answer #2: " << result2 << std::endl;
}