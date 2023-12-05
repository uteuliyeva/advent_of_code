#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>


int extractValue(const std::string& line)
{   
    int i = 0;
    while(!isdigit(line[i]))
    {
        i++;
    }
    
    int j = line.length() - 1;
    while(!isdigit(line[j]))
    {
        j--;
    }

    return (line[i]-'0')*10 + (line[j]-'0');
}

int extractValue2(const std::string& line, const std::map<std::string, int>& wordToDigitMap)
{  
    std::vector<std::string> digits = {"0","1","2","3","4","5","6","7","8","9","zero","one","two","three","four","five","six","seven","eight","nine"}; 
    int firstDigitIndex = line.length();
    int secondDigitIndex = 0;
    std::string firstDigitStr = "";
    std::string secondDigitStr = "";
    int result = 0;
    size_t indexFound;
    
    for(int i=0; i< digits.size();i++)
    {
        // Find first digit
        indexFound = line.find(digits[i]);
        if (indexFound!=std::string::npos)
        {
            if (indexFound < firstDigitIndex)
            {
                firstDigitIndex = indexFound;
                firstDigitStr = digits[i];
            }
        }

        // Find last digit
        for(int j=line.length()-1; j>=0; j--)
        {
            indexFound = line.substr(j).find(digits[i]);
            if (indexFound!=std::string::npos)
            {
                if (indexFound+j >= secondDigitIndex)
                {
                    secondDigitIndex = indexFound+j;
                    secondDigitStr = digits[i];
                }
            }
        }
    }

    if(firstDigitStr.length()>1)
    {
        result += wordToDigitMap.at(firstDigitStr);
    }
    else{
        result += (line[firstDigitIndex]-'0');
    }

    result *= 10;

    if(secondDigitStr.length()>1)
    {
        result += wordToDigitMap.at(secondDigitStr);
    }
    else{
        result += (line[secondDigitIndex]-'0');
    }

    return result;
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
    int result = 0;
    std::string line;
    while(getline(inputFile,line))
    {
        result += extractValue(line);
    }

    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    std::map<std::string, int> wordToDigitMap = {{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    
    int result2 = 0; 
    while(getline(inputFile,line))
    {
        result2 += extractValue2(line, wordToDigitMap);
    }

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

