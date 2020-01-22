//
//  DataParser.hpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#ifndef DataParser_hpp
#define DataParser_hpp


#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include "FilePlaceholder.hpp"
using namespace std;

class DataParser{
private:
    FilePlaceholder fph;
public:
    void parse( char* pathName, long long size, FileCreator &fileCreator);
};


#endif * //* DataParser_hpp */
