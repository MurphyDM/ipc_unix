//
//  DataCollector.hpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#ifndef DataCollector_hpp
#define DataCollector_hpp

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include "FilePlaceholder.hpp"
#include "DataParser.hpp"
#include "FileCreator.hpp"
using namespace std;

class DataCollector {
private:
    FilePlaceholder fph;
    DataParser dataParser;
public:
    unsigned processDirectory( char *theDir, FileCreator &fileCreator );
};


#endif /* DataCollector_hpp */

