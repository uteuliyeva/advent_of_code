#include <iostream>
#include <fstream>
#include <string>
#include <queue>

int main()
{
    // Read the input file
    std::fstream inputFile("../adventofcode.com_2022_day_6_input.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file."<<std::endl;
        return 1;
    }

    // Task #1
    int count = 0;
    int freqCharsInQ[26] = {0};
    std::queue<char> preMarkerQueue;
    bool preMarkerComplete = false;

    std::string line;
    getline(inputFile,line);
  
    while(!preMarkerComplete)
    {
        char c = line[count];
        count+=1;
        
        preMarkerQueue.push(c);
        freqCharsInQ[c-'a']+=1;

        if(preMarkerQueue.size()==4)
        {
            for (unsigned int j=0; j<26; j++)
            {
                if(freqCharsInQ[j]>1)
                {
                    preMarkerComplete = false;
                    break;
                }
                preMarkerComplete = true;
            }
            char f = preMarkerQueue.front();
            preMarkerQueue.pop();
            freqCharsInQ[f -'a']-=1;
        }
    }

    // Task #2
    int count2 = 0;
    int freqCharsInQ2[26] = {0};
    std::queue<char> preMarkerQueue2;
    preMarkerComplete = false;

    while(!preMarkerComplete)
    {
        char c = line[count2];
        count2+=1;
        
        preMarkerQueue2.push(c);
        freqCharsInQ2[c-'a']+=1;

        if(preMarkerQueue2.size()==14)
        {
            for (unsigned int j=0; j<26; j++)
            {
                if(freqCharsInQ2[j]>1)
                {
                    preMarkerComplete = false;
                    break;
                }
                preMarkerComplete = true;
            }
            char f = preMarkerQueue2.front();
            preMarkerQueue2.pop();
            freqCharsInQ2[f -'a']-=1;
        }
    }

    //Output the answers
    std::cout<<"Answer #1 "<<count<<std::endl;
    std::cout<<"Answer #2 "<<count2<<std::endl;
    
    return 0;
}