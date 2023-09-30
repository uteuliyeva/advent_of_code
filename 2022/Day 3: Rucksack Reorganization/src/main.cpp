#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

int getCharIndex(char c)
{
    if (c>='a' && c<='z')
    {
        return c-'a';
    }
    else
    {
        return c-'A' + 26;
    }
}

int main()
{
    // Read input file
    std::fstream inputFile ("../adventofcode.com_2022_day_3_input.txt");

    if (!inputFile)
    {
        std::cerr<< "Unable to open the input file"<<std::endl;
        return 1;
    }

    // Task #1
    int charInFirstHalf[52] = {0};
    std::string line;
    int sumPriorities = 0;
    char c;
    while(getline(inputFile,line))
    {
        for(unsigned int i=0; i< line.size()/2; i++)
        {
            c = line[i];
            charInFirstHalf[getCharIndex(c)]=1;
        }
        for(unsigned int j=line.size()/2; j< line.size(); j++)
        {
            c = line[j];
            if (charInFirstHalf[getCharIndex(c)]==1)
            {
                sumPriorities += getCharIndex(c)+ 1;
                break;
            }
        }
        std::fill(charInFirstHalf, charInFirstHalf+52, 0);
    }

    // Task #2

    // Reset read position to the beginning of the file
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);

    int sumPriorities2 = 0;
    int elfNumber = 0;
    int charMetThisLine[52] = {0};
    int charMetInGroup[52] = {0};
    while(getline(inputFile,line))
    {        
        for(unsigned int i=0; i< line.size(); i++)
        {
            c = line[i];
            int c_order = getCharIndex(c);
            if(!charMetThisLine[c_order]){
                charMetInGroup[getCharIndex(c)]+=1;
            }
            charMetThisLine[c_order] = 1;
        }
        std::fill(charMetThisLine, charMetThisLine+52, 0);
        elfNumber++;

        // New group of Elves
        if (elfNumber ==3){
            elfNumber = 0;
            for (unsigned int i=0; i<52; i++)
            {
                if(charMetInGroup[i]==3)
                {
                    sumPriorities2 += i+1;
                    break;
                }
            }
            std::fill(charMetInGroup, charMetInGroup+52, 0);
        }
    }


    std::cout<<"Answer #1: "<<sumPriorities<<std::endl;
    std::cout<<"Answer #2: "<<sumPriorities2<<std::endl;
    return 0;
}