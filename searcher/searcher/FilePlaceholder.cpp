//
//  FilePlaceholder.cpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#include "FilePlaceholder.hpp"

void FilePlaceholder:: writeToDirectoriesList(char *pathName, long long st_size, FileCreator &fileCreator)
{
    ofstream out;
    out.open(fileCreator.getFileByType("directory"), ios::app);
    out<<"DIRECTORY: " <<pathName<<"  has " << st_size << " bytes"<<endl;
    out.close();
}

void FilePlaceholder:: writeToSymbollinksList(char* pathName, char*targetName, FileCreator &fileCreator)
{
    ofstream out;
    out.open(fileCreator.getFileByType("link"), ios::app);
    out<<"SYMBOL LINK: "<<pathName<<" its target name: "<< targetName <<endl;
    out.close();
}

void FilePlaceholder:: writeToFile(char* pathName, char* fileName, long long size)
{
    ofstream out;
    out.open(fileName, ios::app);
    out << pathName<<"  has " << size << " bytes" << endl;
    out.close();
}
