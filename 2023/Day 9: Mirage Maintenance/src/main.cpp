#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>

int sumOfPredictions(std::fstream& inputFile);
void getData(std::fstream& inputFile, std::vector<std::vector<int> >& data);
int getPrediction(const std::vector<int>& sequence);
bool checkAllZero(const std::vector<int>& sequence);

int sumOfPrevious(std::fstream& inputFile);
int getPrevious(const std::vector<int>& sequence);

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
    int result = sumOfPredictions(inputFile);

    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int result2 = sumOfPrevious(inputFile);

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

int sumOfPredictions(std::fstream& inputFile)
{
    std::vector<std::vector<int> > data;
    getData(inputFile, data);
    int result = 0;

    for(int i=0; i<data.size(); ++i)
    {
        result += getPrediction(data[i]);
    }
    return result;
}

void getData(std::fstream& inputFile, std::vector<std::vector<int> >& data)
{
    std::string line;
    int number;
    int nLines = 0;

    while(getline(inputFile,line))
    {
        std::stringstream ss(line);
        data.push_back(std::vector<int> ());
        while(ss>>number)
        {
            data[nLines].push_back(number);
        }

        nLines++;
    }
}

int getPrediction(const std::vector<int>& sequence)
{
    if (checkAllZero(sequence)) {
        return 0;
    }

    std::vector<int> differences;
    for(int i=1; i<sequence.size(); i++)
    {
        differences.push_back(sequence[i]-sequence[i-1]);
    }

    return getPrediction(differences) + sequence.back();
}

bool checkAllZero(const std::vector<int>& sequence) {
    for (int i=0; i<sequence.size(); i++) {
        if (sequence[i] != 0) {
            return false;
        }
    }
    return true;
}

int sumOfPrevious(std::fstream& inputFile)
{
    std::vector<std::vector<int> > data;
    getData(inputFile, data);
    int result = 0;

    for(int i=0; i<data.size(); ++i)
    {
        result += getPrevious(data[i]);
    }
    return result;
}

int getPrevious(const std::vector<int>& sequence)
{
    if (checkAllZero(sequence)) {
        return 0;
    }

    std::vector<int> differences;
    for(int i=1; i<sequence.size(); i++)
    {
        differences.push_back(sequence[i]-sequence[i-1]);
    }

    return sequence[0] - getPrevious(differences);
}