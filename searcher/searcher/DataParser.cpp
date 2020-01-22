//
//  DataParser.cpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#include "DataParser.hpp"

void DataParser:: parse( char* pathName, long long size, FileCreator &fileCreator){
    int j=0;
    string type="";
    for(int i = 0; i<PATH_MAX; i++)
    {
        if(pathName[i]=='.'){
            j=i;
            break;
        }
    }
    
    for (int i=j+1, k=0; k<10 ; i++, k++) {
        type+=pathName[i];
    }
    
    if(type[0]=='c'&& type[1]=='p' && type[2]=='p')
        fph.writeToFile(pathName, fileCreator.getFileByType("cpp"), size);
    
    else if(type[0]=='t'&& type[1]=='x' && type[2]=='t')
        fph.writeToFile(pathName, fileCreator.getFileByType("txt"), size);
    
    else if(type[0]=='m'&& type[1]=='p' && type[2]=='3')
        fph.writeToFile(pathName, fileCreator.getFileByType("mp3"), size);
    
    else if(type[0]=='d'&& type[1]=='o' && type[2]=='c')
        fph.writeToFile(pathName, fileCreator.getFileByType("doc"), size);
    
    else if(type[0]=='e'&& type[1]=='x' && type[2]=='e')
        fph.writeToFile(pathName, fileCreator.getFileByType("exe"), size);
    
    else if(type[0]=='x'&& type[1]=='l' && type[2]=='s')
        fph.writeToFile(pathName, fileCreator.getFileByType("xls"), size);
    else
        fph.writeToFile(pathName, fileCreator.getFileByType("other"), size);
    
    }
