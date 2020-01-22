//
//  DataCollector.cpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#include "DataCollector.hpp"

unsigned DataCollector:: processDirectory( char *theDir, FileCreator &fileCreator )
{
    DIR *dir = NULL;
    struct dirent entry;
    struct dirent *entryPtr = NULL;
    int retval = 0;
    unsigned count = 0;
    char pathName[PATH_MAX + 1], buff[PATH_MAX+1];
    
    /* открыть указанный каталог, если возможно. */
    dir = opendir( theDir );
    if( dir == NULL ) {
        printf( "Error opening %s: %s", theDir, strerror( errno ) );
        return 0;
    }
    
    retval = readdir_r( dir, &entry, &entryPtr );
    

    while( entryPtr != NULL ) {
        memset(&pathName, 0, sizeof(char));
        struct stat entryInfo;
        
        if( ( strncmp( entry.d_name, ".", PATH_MAX ) == 0 ) ||
           ( strncmp( entry.d_name, "..", PATH_MAX ) == 0 ) ) {
            /* Short-circuit the . and .. entries. */
            retval = readdir_r( dir, &entry, &entryPtr );
            continue;
        }
        
        (void)strncpy( pathName, theDir, PATH_MAX );
        (void)strncat( pathName, "/", PATH_MAX );
        (void)strncat( pathName, entry.d_name, PATH_MAX );
        
        if( lstat( pathName, &entryInfo ) == 0 ) {
            /* вызов stat() был успешным, так что продолжаем. */
            count++;
            
            if( S_ISDIR( entryInfo.st_mode ) )
            {
                // каталог
                (void)strncpy( buff, pathName, PATH_MAX );
                fph.writeToDirectoriesList(buff, (long long)entryInfo.st_size, fileCreator);
                cout<<"open"<<endl;
                count += processDirectory( pathName, fileCreator);
            }
            
            
            else if( S_ISREG( entryInfo.st_mode ) )
            {
                // обычный файл
                dataParser.parse( pathName, (long long)entryInfo.st_size, fileCreator);
            }
            
            else if( S_ISLNK( entryInfo.st_mode ) )
            {
                // символическая ссылка
                char targetName[PATH_MAX + 1];
                if( readlink( pathName, targetName, PATH_MAX ) != -1 ) {                    
                    fph.writeToSymbollinksList(pathName, targetName, fileCreator);
                } else {
                    printf( "\t%s -> (invalid symbolic link!)\n", pathName );
                }
            }
            
            
        } else {
            printf( "Error statting %s: %s\n", pathName, strerror( errno ) );
        }
        
        retval = readdir_r( dir, &entry, &entryPtr );
    }
    
    /* закрытие каталога и возвращение числа элементов. */
    (void)closedir( dir );
    return count;
}





