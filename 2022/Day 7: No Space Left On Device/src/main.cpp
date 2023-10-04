#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>


struct File
{
    std::string name;
    long long size;
};

struct Directory
{
    std::string name;
    long long size;
    std::vector<std::unique_ptr<Directory> > dirs;
    std::vector<std::unique_ptr<File> > files;
    Directory *parent; 
};

Directory * changeDir(Directory *currDir, const std::string& nextDirName)
{
    // Change to the root dir
    if(nextDirName == "/") 
    {
        while(currDir -> parent)
        {
            currDir = currDir -> parent;
        }
    }
    // Change to the parent dir
    else if(nextDirName == "..")
    {
        if(currDir->parent)
        {
            currDir = currDir -> parent;
        }
    }
    // Change to the child dir
    else
    {
        for (auto& dir : currDir->dirs)
        {
            if (dir->name == nextDirName)
            {
                return dir.get();
            }
        }

        // Directory not found; create a new one
        auto newDir = std::make_unique<Directory>();
        newDir->name = nextDirName;
        newDir->parent = currDir;
        currDir->dirs.push_back(std::move(newDir));
        currDir = currDir->dirs.back().get();
    }
    return currDir;
}

void parseFileSystem(std::fstream& inputFile, Directory *root)
{
    std::string line;
    Directory* currDir = root;
    while(getline(inputFile,line))
    {   
        // Change directory
        if(line.find("$ cd") != std::string::npos)
        {
            std::string nextDirName;
            std::stringstream ss(line);
            ss>>nextDirName>>nextDirName>>nextDirName;
            currDir = changeDir(currDir, nextDirName);
        }
        // List 
        else if(line.find("$ ls") != std::string::npos)
        {
            while(getline(inputFile,line))
            {
                // Add new directory
                if(line.find("dir")!= std::string::npos)
                {
                    std::string childDirName;
                    std::stringstream ss(line);
                    ss>>childDirName>>childDirName;
                    auto newDir = std::make_unique<Directory>();
                    newDir->name = childDirName;
                    newDir->parent = currDir;
                    currDir->dirs.push_back(std::move(newDir));
                }
                // Add new file
                else
                {
                    long long fileSize;
                    std::string fileName;
                    std::stringstream ss(line);
                    ss>>fileSize>>fileName;
                    auto newFile = std::make_unique<File>();
                    newFile->name = fileName;
                    newFile->size = fileSize;
                    currDir->files.push_back(std::move(newFile));
                }

                if(inputFile.peek()=='$')
                {
                    break;
                }
            }
        }
    }
}

long long updateSize(Directory *currDir)
{
    currDir->size = 0;
    // Add the file sizes if any
    for(auto &file: currDir->files)
    {
        currDir->size += file->size;
    }
    // Recursively update the sizes of dirs
    for(auto &dir: currDir->dirs)
    {
        currDir->size += updateSize(dir.get());
    }
    return currDir->size;
}

long long totalSize100k(Directory *currDir)
{
    long long result = 0;
    if(currDir->size <= 100000)
    {
        result+=currDir->size;
    }
    for(auto &dir: currDir->dirs)
    {
        result+=totalSize100k(dir.get());
    }
    return result;
}

long long sizeOfCandidateForDel(Directory *currDir, long long minLimit, long long maxLimit)
{
    long long result = maxLimit; 
    if(currDir->size>= minLimit)
    {
        result = std::min(result, currDir->size);
    }
    for(auto &dir: currDir->dirs)
    {
        result = sizeOfCandidateForDel(dir.get(), minLimit, result);
    }
    return result;
}

int main()
{
    std::fstream inputFile ("../adventofcode.com_2022_day_7_input.txt");
    if(!inputFile)
    {
        std::cerr<<"Unable to read the input file."<<std::endl;
        return 1;
    }

    // Task #1
    auto root = std::make_unique<Directory>();
    root->parent = nullptr;
    parseFileSystem(inputFile, root.get());
    long long totalSize = updateSize(root.get());
    long long result = totalSize100k(root.get());

    // Task #2
    long long totalSpace = 70000000;
    long long targetUnusedSpace = 30000000;
    long long currUnusedSpace = totalSpace-totalSize;
    long long minSizeToDelete = targetUnusedSpace - currUnusedSpace;
    long long result2 = sizeOfCandidateForDel(root.get(), minSizeToDelete, totalSize);
    //Output the answers
    std::cout<<"Answer #1 "<<result<<std::endl;
    std::cout<<"Answer #2 "<<result2<<std::endl;
    inputFile.close();
    return 0;
}