#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h> 
#include <cmath>

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
    int result = 1;

    std::string token;
    int number;
    std::string line;
    std::vector<int> times;
    std::vector<int> distances;

    // Read times
    getline(inputFile,line);
    std::stringstream ss(line);
    ss>>token;
    while(ss>>number){
        times.push_back(number);
    }

    // Read distances
    getline(inputFile,line);
    std::stringstream ss2(line);
    ss2>>token;
    while(ss2>>number){
        distances.push_back(number);
    }

    for(int i=0; i< times.size(); ++i)
    {
        int t = times[i];
        int d = distances[i];
        // Calculate result by solving quadratic inequality (time-x)*x>distance
        float firstSolution = std::floor(0.5*(t-sqrt(t*t-4.0*d)) + 1);
        float secondSolution = std::ceil(0.5*(t+sqrt(t*t-4.0*d)) - 1);
        if (firstSolution<secondSolution)
        {
            result *= (secondSolution-firstSolution+1);
        }
    }
    
    // Part 2
    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    // Read time
    long long time = 0;
    getline(inputFile,line);
    std::stringstream ss3(line);
    ss3>>token;
    while(ss3>>token){
        time *= std::pow(10, token.size());
        time += std::stoi(token);
    }

    // Read distance
    long long distance = 0;
    getline(inputFile,line);
    std::stringstream ss4(line);
    ss4>>token;
    while(ss4>>token){
        distance *= std::pow(10, token.size());
        distance += std::stoi(token);
    }

    // Calculate result by solving quadratic inequality (time-x)*x>distance
    int firstSolution = std::floor(0.5*(time-sqrt(time*time-4.0*distance)) + 1);
    int secondSolution = std::ceil(0.5*(time+sqrt(time*time-4.0*distance)) - 1);
    int result2 = secondSolution-firstSolution+1;
    std::cout<<"Distance: "<<distance<<std::endl;

    // Output the answer
    std::cout << "Answer #1 " << result << std::endl;
    std::cout << "Answer #2 " << result2 << std::endl;
    inputFile.close();
    return 0;
}

