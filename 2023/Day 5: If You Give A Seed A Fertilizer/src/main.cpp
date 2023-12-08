#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <limits.h>
#include <algorithm>

struct RangeMapping {
    long long destinationStart;
    long long rangeLength;
};

// Part 1 //////////////////////////////////////
////////////////////////////////////////////////

void readSeedsLine(const std::string& line, std::vector<long long>& seeds)
{
    std::stringstream ss(line);
    std::string token;
    long long number;
    ss>>token;
    while(ss>>number)
    {
        seeds.push_back(number);
    }
}

void getMaps(std::fstream& inputFile, std::vector<std::map<long long, RangeMapping> >& maps)
{
    std::string line;
    int mapIndex = -1;
    while(getline(inputFile, line))
    {
        if(line.empty()) continue;
        if(!isdigit(line[0]))
        {
            mapIndex++;
            maps.push_back(std::map<long long, RangeMapping>());
            continue;
        }

        long long destinationStart;
        long long sourceStart;
        long long rangeLength;

        std::stringstream ss(line);
        ss>>destinationStart>>sourceStart>>rangeLength;
        RangeMapping newRangeMapping = {destinationStart, rangeLength};
        maps[mapIndex][sourceStart] = newRangeMapping;
    }
}

long long lowestLocation(std::fstream& inputFile)
{
    std::string line;
    std::vector<long long> seeds;
    std::vector<std::map<long long, RangeMapping> > maps;

    getline(inputFile, line);
    readSeedsLine(line, seeds);
    getMaps(inputFile, maps);

    long long result =  LLONG_MAX;
    for(int i=0; i<seeds.size(); i++)
    {
        long long location = seeds[i];
        for(int j=0;j<maps.size();j++)
        {
            for (const auto& element : maps[j])
            {
                long long sourceStart = element.first;
                long long range = element.second.rangeLength;
                long long destinationStart = element.second.destinationStart;
                if(location>=sourceStart&&location<=sourceStart+range-1)
                {
                    location = destinationStart+(location-sourceStart);
                    break;
                }
            }
        }

        if(location<result) result=location;
    }
    return result;
}

// Part 2 //////////////////////////////////////
////////////////////////////////////////////////

void sortRangesByFirst(std::vector<std::pair<long long, long long>>& ranges) {
    std::sort(ranges.begin(), ranges.end(), 
        [](const std::pair<long long, long long>& a, const std::pair<long long, long long>& b) {
            return a.first < b.first;
        });
}

void readSeedsLine2(const std::string& line, std::vector<std::pair<long long, long long> >& seedRanges)
{
    std::stringstream ss(line);
    std::string token;
    long long rangeStart;
    long long rangeLength;
    ss>>token;
    while (ss >> rangeStart >> rangeLength) {
        seedRanges.push_back({rangeStart, rangeStart+rangeLength-1});
    }
    sortRangesByFirst(seedRanges);
}

std::vector<std::pair<long long, long long> > preprocessRanges(std::vector<std::pair<long long, long long> >& ranges, const std::map<long long, RangeMapping > map)
{
    std::vector<std::pair<long long, long long> > preprocessed;

    for (const auto& range : ranges) {
        long long start = range.first;
        long long end = range.second;

        for (const auto& element : map) 
        {
            long long sourceRangeStart = element.first;
            long long sourceRangeEnd = element.first+element.second.rangeLength-1;
            if (end < sourceRangeStart) {
                preprocessed.push_back({start, end});
                break;
            } else if (start > sourceRangeEnd) {
                continue;
            } else {
                if (start < sourceRangeStart) {
                    preprocessed.push_back({start, sourceRangeStart - 1});
                }
                preprocessed.push_back({ std::max(start,sourceRangeStart) , std::min(end,sourceRangeEnd) });
                start = sourceRangeEnd + 1;

                if (start > end) {
                    break;
                }
            }
        }
    }
    sortRangesByFirst(preprocessed);
    return preprocessed;
}

std::vector<std::pair<long long, long long> > mapRanges(std::vector<std::pair<long long, long long> >& ranges, const std::map<long long, RangeMapping > map)
{
    std::vector<std::pair<long long, long long> > processed;
    int i=0;
    
    for (const auto& element : map)
    {
        long long sourceStart = element.first;
        long long range = element.second.rangeLength;
        long long destinationStart = element.second.destinationStart;
        while(i<ranges.size())
        {
            long long start = ranges[i].first;
            long long end = ranges[i].second;
            if(start>sourceStart+range-1) {break;}
            else if(start<sourceStart)
            {
                processed.push_back({start,end});
            }
            else
            {
                processed.push_back({destinationStart+start-sourceStart,destinationStart+end-sourceStart});
            }
            i++;
        }
        if(i>=ranges.size()) break;
    }
    sortRangesByFirst(processed);
    return processed;
}

long long lowestLocation2(std::fstream& inputFile) {
    std::string line;
    std::vector<std::pair<long long, long long> > currRanges;
    std::vector<std::map<long long, RangeMapping> > maps;

    getline(inputFile, line);
    readSeedsLine2(line, currRanges);
    getMaps(inputFile, maps);

    long long result = LLONG_MAX;
    for (const auto& currMap : maps) 
    {
        currRanges = preprocessRanges(currRanges,currMap);
        currRanges = mapRanges(currRanges,currMap);
    }
    return currRanges[0].first;
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
    long long result = lowestLocation(inputFile);

    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    long long result2 = lowestLocation2(inputFile);

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

