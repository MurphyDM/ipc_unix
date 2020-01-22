//
//  main.cpp
//  dir_test
//
//  Created by Diana Melnick on 23.05.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//
#include <iostream>
#include "DataCollector.hpp"
#include "FilePlaceholder.hpp"
#include "PipeCreator.hpp"
#include "FileCreator.hpp"
#include "AsynchroFileReader.hpp"
using namespace std;


int main()
{
    vector<char*> fileNames;
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/resut_dir.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/resut_links.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/exes.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/cpps.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/txts.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/docs.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/xlss.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/mp3s.txt");
    fileNames.push_back("/Users/Diana/documents/exam2/asm/searcher/others.txt");
    
    FileCreator fileCreator(fileNames);
    DataCollector dataCollector;
    dataCollector.processDirectory("/Users/diana/documents", fileCreator);
    cout<<endl<<endl<<"OKAY"<<endl<<endl;
    AsynchroFileReader asynchroFileReader(fileNames, 9);
    asynchroFileReader.readIt();
    cout<<endl<<endl<<"OKAY"<<endl<<endl;
    return EXIT_SUCCESS;
}













