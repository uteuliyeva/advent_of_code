#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cmath>

int extractNumber(const std::string& input, size_t position){
    std::string numberStr;
    for (size_t j = position; j < position+3 && std::isdigit(input[j]); ++j) {
        numberStr += input[j];
    }

    if (!numberStr.empty()) {
        return std::stoi(numberStr); 
    } else {
        return 1000;
    }
}

int mulOperation(const std::string& input, size_t& i){
    if(input.substr(i, 4) != "mul(") {return 0;}
    i += 4;
    int firstNumber = extractNumber(input, i);
    if(firstNumber==1000) {return 0;}
    i += 1 + (firstNumber>9) + (firstNumber>99);
    if(input[i]!=',') {return 0;}
    int secondNumber = extractNumber(input, ++i);
    if(secondNumber==1000) {return 0;}
    i += 1 + (secondNumber>9) + (secondNumber>99);
    if(input[i]!=')') {return 0;}
    return firstNumber * secondNumber;
}

void setPositionAfterDo(const std::string& input, size_t& i){
    while(i<input.length() && input.substr(i,4)!="do()"){
        i++;
    }
    i+=3;
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
    std::string input;

    while(getline(inputFile,line)){
        input += line;
    }

    int n = input.length();
    input += "############";
    for(size_t i=0; i<n; i++){
        result += mulOperation(input, i);
    }

    // Task #2
    int result2 = 0;
    for(size_t i=0; i<n; i++){
        if(input.substr(i, 7) == "don't()"){
            i+=7;
            setPositionAfterDo(input,i);
            continue;
        }
        result2 += mulOperation(input, i);
    }

    // Output the answer
    std::cout << "Answer #1: " << result << std::endl;
    std::cout << "Answer #2: " << result2 << std::endl;
}