//
//  FileCreator.hpp
//  searcher
//
//  Created by Diana Melnick on 02.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#ifndef FileCreator_hpp
#define FileCreator_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <stdlib.h>
#include "ThreadCreator.hpp"
#include "PipeCreator.hpp"

using namespace std;

class FileCreator {
    vector<char*> fileNames;
    
public:
    FileCreator(vector<char*> fileNames)
    {
         this->fileNames = fileNames;
         createFiles();
    }
    
    ~FileCreator()
    {
        for (int i=0;i<fileNames.size();i++)
            remove(fileNames[i]);
    }
    
    void createFiles()
    {
        ofstream out;
        for (auto &i: fileNames)
         {
             out.open(i);
             out.close();
         }
    }
    vector<char*> getVectorOfFileNames()
    {
        return fileNames;
    }
    
    
    int getNumbOfFiles()
    {
        return fileNames.size();
    }
    
    char * getFileByType(string type)
    {
        if(type == "cpp") return fileNames[3];
        else if(type == "txt") return fileNames[4];
        else if(type == "doc") return fileNames[5];
        else if(type == "exe") return fileNames[2];
        else if(type == "mp3") return fileNames[7];
        else if(type == "xls") return fileNames[6];
        else if(type == "directory") return fileNames[0];
        else if(type == "link") return fileNames[1];
        else return fileNames[8];
    }
    
};
#endif /* FileCreator_hpp */
