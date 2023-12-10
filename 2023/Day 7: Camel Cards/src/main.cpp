#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>

int determineHandType(const std::string& hand, const bool& isJokerMode);
void firstOrder(std::fstream& inputFile, std::map<int, std::vector<std::pair<std::string, int> > >& organizedByTypes, const bool& isJokerMode);
bool compareHands(const std::pair<std::string, int>& hand1, const std::pair<std::string, int>& hand2, const bool& isJokerMode);
void sortHandsOfSameType(std::vector<std::pair<std::string, int> >& hands, const bool& isJokerMode);
void secondOrder(std::map<int, std::vector<std::pair<std::string, int> > >& organizedByTypes, const bool& isJokerMode);
int getTotalWinnings(std::fstream& inputFile, const bool& isJokerMode = false);


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
    int result = getTotalWinnings(inputFile);

    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int result2 = getTotalWinnings(inputFile, true);

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

int determineHandType(const std::string& hand, const bool& isJokerMode)
{
    std::unordered_map<char, int> frequency;
    for (char card : hand) {
        frequency[card]++;
    }

    // Game with jokers
    if(isJokerMode)
    {
        int jokerCount = frequency['J'];
        frequency['J'] = 0;
        if(jokerCount==5) return 6; // Five of a kind

        int maxFrequency = 0;
        char frequentCard;
        for (auto& card : frequency) {
            if (card.second>maxFrequency)
            {
                maxFrequency = card.second;
                frequentCard = card.first;
            }
        }

        frequency[frequentCard] += jokerCount;
    }

    bool hasThree = false;
    bool hasTwo = false;
    int pairs = 0;

    for (auto& card : frequency) {
        if (card.second == 5) return 6; // Five of a kind
        if (card.second == 4) return 5; // Four of a kind
        if (card.second == 3) hasThree = true;
        if (card.second == 2) {
            hasTwo = true;
            pairs++;
        }
    }

    if (hasThree && hasTwo) return 4; // Full house
    if (hasThree) return 3; // Three of a kind
    if (pairs == 2) return 2; // Two pairs
    if (pairs == 1) return 1;  // One pair
    return 0;  // High card

}

void firstOrder(std::fstream& inputFile, std::map<int, std::vector<std::pair<std::string, int> > >& organizedByTypes, const bool& isJokerMode)
{
    std::string line;
    std::string hand;
    int bid;

    while(getline(inputFile,line))
    {
        std::stringstream ss(line);
        ss>>hand>>bid;

        int type = determineHandType(hand, isJokerMode);

        if (organizedByTypes.find(type) == organizedByTypes.end()) 
        {
            organizedByTypes[type] = std::vector<std::pair<std::string, int> >();
        }

        organizedByTypes.at(type).push_back(std::pair<std::string, int> {hand,bid});
    }
}

bool compareHands(const std::pair<std::string, int>& hand1, const std::pair<std::string, int>& hand2, const bool& isJokerMode) 
{
    static std::unordered_map<char, int> cardStrength = {
        {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
        {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
    };
    if (isJokerMode)
    {
        cardStrength['J'] = 1;
    }

    const std::string& cards1 = hand1.first;
    const std::string& cards2 = hand2.first;

    for (size_t i = 0; i < cards1.length() && i < cards2.length(); ++i) {
        if (cards1[i] != cards2[i]) {
            return cardStrength.at(cards1[i]) < cardStrength.at(cards2[i]); 
        }
    }
    return false;
}

void sortHandsOfSameType(std::vector<std::pair<std::string, int>>& hands, const bool& isJokerMode) {
    std::sort(hands.begin(), hands.end(), [isJokerMode](const std::pair<std::string, int>& hand1, const std::pair<std::string, int>& hand2) {
        return compareHands(hand1, hand2, isJokerMode);
    });
}

void secondOrder(std::map<int, std::vector<std::pair<std::string, int> > >& organizedByTypes, const bool& isJokerMode)
{
    for (auto& handType : organizedByTypes)
    {
        sortHandsOfSameType(handType.second, isJokerMode);
    }
}

int getTotalWinnings(std::fstream& inputFile, const bool& isJokerMode)
{
    int result = 0;
    std::map<int, std::vector<std::pair<std::string, int> > > organizedByTypes;
    firstOrder(inputFile, organizedByTypes, isJokerMode);
    secondOrder(organizedByTypes, isJokerMode);

    int rank = 1;
    for (const auto& handType : organizedByTypes)
    {
        for (const auto& handBid : handType.second)
        {
            result += rank * handBid.second;
            rank++;
        }
    }
    return result;
}
