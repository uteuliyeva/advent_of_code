#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>

int getNSteps(std::fstream& inputFile);
void getMapNodes(std::fstream& inputFile, std::unordered_map< std::string,std::pair< std::string, std::string> >& mapNodes);
long long getGhostSteps(std::fstream& inputFile);
void getGhostMapNodes(std::fstream& inputFile, std::unordered_map< std::string,std::pair< std::string, std::string> >& mapNodes, std::vector<std::string>& startNodes);
long long gcd(long long a, long long b);
long long findlcm(std::vector<long long>& numbers);

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
    //int result = getNSteps(inputFile);



    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    long long result2 = getGhostSteps(inputFile);

    // Output the answer
    //std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

int getNSteps(std::fstream& inputFile)
{
    // Read directions
    std::string directions;
    getline(inputFile, directions);

    std::unordered_map< std::string, std::pair< std::string, std::string> > mapNodes;
    getMapNodes(inputFile, mapNodes);

    int result = 0;
    size_t directionsIndex = 0;
    std::string currNode = "AAA";
    while(currNode!="ZZZ")
    {
        if(directionsIndex>= directions.size()) directionsIndex = 0;
        if (directions[directionsIndex] =='L')
        {
            currNode = mapNodes.at(currNode).first;
        }
        else
        {
            currNode = mapNodes.at(currNode).second;
        }
        result++;
        directionsIndex++;
    }

    return result;
}

void getMapNodes(std::fstream& inputFile, std::unordered_map< std::string,std::pair< std::string, std::string> >& mapNodes)
{
    std::string line;
    while(getline(inputFile,line))
    {
        if(line.empty()) continue;

        std::stringstream ss(line);

        std::string mainNode;
        std::string leftNode;
        std::string rightNode;
        std::string token;
        ss>>mainNode>>token>>leftNode>>rightNode;

        leftNode.erase(remove(leftNode.begin(), leftNode.end(), '('));
        leftNode.erase(remove(leftNode.begin(), leftNode.end(), ','));
        rightNode.erase(remove(rightNode.begin(), rightNode.end(), ')'));

        mapNodes[mainNode] = std::make_pair(leftNode, rightNode);
    }
}

long long getGhostSteps(std::fstream& inputFile)
{
    // Read directions
    std::string directions;
    getline(inputFile, directions);

    std::unordered_map< std::string, std::pair< std::string, std::string> > mapNodes;
    std::vector<std::string> currNodes;
    getGhostMapNodes(inputFile, mapNodes, currNodes);

    std::vector<long long> nSteps;
    
    for(int i=0; i<currNodes.size(); ++i)
    {
        std::cout<<"Node #"<<i<<std::endl;
        size_t directionsIndex = 0;
        long long steps = 0;
        while(currNodes[i][2]!='Z')
        {
            if(directionsIndex>=directions.size()) directionsIndex=0;
            if (directions[directionsIndex] =='L')
            {
                currNodes[i] = mapNodes.at(currNodes[i]).first;
            }
            else
            {
                currNodes[i] = mapNodes.at(currNodes[i]).second;
            }
            steps ++;
            directionsIndex++;
        }
        std::cout<<"Steps: "<<steps<<std::endl;
        nSteps.push_back(steps);
    }

    return findlcm(nSteps);
}

void getGhostMapNodes(std::fstream& inputFile, std::unordered_map< std::string,std::pair< std::string, std::string> >& mapNodes, std::vector<std::string>& startNodes)
{
    std::string line;
    while(getline(inputFile,line))
    {
        if(line.empty()) continue;

        std::stringstream ss(line);

        std::string mainNode;
        std::string leftNode;
        std::string rightNode;
        std::string token;
        ss>>mainNode>>token>>leftNode>>rightNode;

        leftNode.erase(remove(leftNode.begin(), leftNode.end(), '('));
        leftNode.erase(remove(leftNode.begin(), leftNode.end(), ','));
        rightNode.erase(remove(rightNode.begin(), rightNode.end(), ')'));

        mapNodes[mainNode] = std::make_pair(leftNode, rightNode);

        if(mainNode[2]=='A') startNodes.push_back(mainNode);
    }
}

long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
 
// Returns Least Common Multiple of array elements
long long findlcm(std::vector<long long>& numbers)
{
    std::cout<<"Finding LCM"<<std::endl;
    long long result = numbers[0];

    for (int i = 1; i < numbers.size(); i++)
        result = (((numbers[i] * result)) / (gcd(numbers[i], result)));
 
    return result;
}