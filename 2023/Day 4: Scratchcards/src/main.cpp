#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include <unordered_set>

int countMatches(const std::string& line)
{
    int count = 0;
    std::stringstream ss(line);
    std::string token;
    std::unordered_set<int> winningNumbers;

    // Read the beginning of the line "Card i: "
    ss>>token>>token;

    // Read the winning numbers until '|' symbol
    while(ss>>token)
    {
        if(token=="|") break;
        winningNumbers.insert(std::stoi(token));
    }

    // Count the matches
    while(ss>>token)
    {
        if(winningNumbers.find(std::stoi(token)) != winningNumbers.end())
        {
            count++;
        }
    }
    return count;
}

// Calculate point for Part 1
int calculatePoints(const std::string& line)
{
    int matches = countMatches(line);
    if(matches==0){ return 0;}
    else{ return std::pow(2, matches-1);}
}

// Update number of card copies for Part 2
int updateCardCopies(const std::string& line, std::map<int, int>& cardCopies, int& i)
{
    int matches = countMatches(line);
    for(int j=1; j<=matches; j++)
    {
        cardCopies[i+j]+= cardCopies[i];
    }
    return cardCopies[i];
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
    int nLines = 0;

    while(getline(inputFile,line))
    {
        result += calculatePoints(line);
        nLines++;
    }

    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int result2 = 0;
    // Map of the card ID to the number of copies
    std::map<int, int> cardCopies; 
    for (int i = 1; i <= nLines; ++i) {
        cardCopies[i] = 1;
    }

    // Update the number of copies for each card
    // Sum the number of copies
    for (int i = 1; i <= nLines; ++i) {
        getline(inputFile,line);
        result2 += updateCardCopies(line, cardCopies, i);
    }

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

