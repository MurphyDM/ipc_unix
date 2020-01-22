//
//  FilePlaceholder.hpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#ifndef FilePlaceholder_hpp
#define FilePlaceholder_hpp

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <stdlib.h>
#include "ThreadCreator.hpp"
#include "FileCreator.hpp"
#include "PipeCreator.hpp"

using namespace std;

class FilePlaceholder {
    FileCreator *fc;
public:
    void writeToFilesList(char* pathName, long long st_size);
    
    void writeToDirectoriesList(char *pathName, long long st_size, FileCreator &fileCreator);
    
    void writeToSymbollinksList(char* pathName, char*targetName, FileCreator &fileCreator);
    
    void writeToFile(char* pathName, char* fileName, long long size);
    };


#endif /* FilePlaceholder_hpp */

