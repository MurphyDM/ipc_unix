//
//  main.cpp
//  Lab6
//
//  Created by Diana Melnick on 05.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 16
#define PAGE_AMOUNT 10

int getIndex(void*);
int getPtrSize(void*);
int myFree(void*);
void collectGarbage();

bool PT_INIT = false;
struct PageInfo
{
    int inUse = 0;                // currentry in use
    int npage = 0;                // next page
    void* pointer = NULL;         // pointer to current page
} PageTable[PAGE_AMOUNT];         // Page Table

void printPT()
{
    printf("\nPAGE TABLE:");
    printf("\nIND\tUSED\tNP\tADDRESS");
    for (int i = 0; i < PAGE_AMOUNT; ++i)
    {
        if (PageTable[i].pointer) //if page address is valid
        {
            printf("\n%d)\t%d\t%d\t%p", i, PageTable[i].inUse, PageTable[i].npage, PageTable[i].pointer);
        }
        else
        {
            printf("\nerror");
        }
    }
}

int getFreePagesAmount()
{
    int counter = 0;
    for (int i = 0; i < PAGE_AMOUNT; ++i)
    {
        if (!PageTable[i].inUse) //if page is used
        {
            counter++;
        }
    }
    return counter;
}

//in: pointer in page table
//out: page amount
//error: -1
int getPtrSize(void* pointer)
{
    int index = getIndex(pointer);
    if (index == -1)
        return -1;
    int counter = 0;
    while (PageTable[index].npage != index) {
        index = PageTable[index].npage;
        counter++;
    }
    return ++counter;
}

//initializes page table
//error: 1
int initPT()
{
    for (int i = 0; i < PAGE_AMOUNT; ++i)
    {
        if (!(PageTable[i].pointer = malloc(PAGE_SIZE)))
        {
            return 1;
        }
        PageTable[i].npage = -1;
        *(int*)PageTable[i].pointer = i;
    }
    return 0;
}

//in: pointer in page table
//out: page index
//error: -1
int getIndex(void* pointer)
{
    for (int index = 0; index < PAGE_AMOUNT; ++index)
    {
        if (PageTable[index].pointer == pointer)
        {
            return index;
        }
    }
    return -1;
}

//in: requested memory size
//out: pointer to first allocated page
//error: 0
void* myMalloc(int size)
{
    if (!PT_INIT)
    {
        if (initPT())
        {
            return NULL;
        }
        else
        {
            PT_INIT = true;
        }
    }
    
    if (size <= 0)
    {
        return NULL;
    }
    
    void* pointer = NULL;
    double memNeededInPages = size / PAGE_SIZE;
    int pagesNeeded = size / PAGE_SIZE;
    if (memNeededInPages - pagesNeeded < 0.01)
        pagesNeeded++;
    int cleanFlag = 0;
    
    if (pagesNeeded > getFreePagesAmount())
    {
        return NULL;
    }
    
    int pagesNeeded_left = pagesNeeded;        //how many left
    int nextPageNum;                                //
    //int startIndex = 0;
    for (int i = PAGE_AMOUNT - 1; i >= 0; i--)
    {
        if (!PageTable[i].inUse) {
            if (pagesNeeded == pagesNeeded_left)
                nextPageNum = i;
            PageTable[i].npage = nextPageNum;
            PageTable[i].inUse = true;
            nextPageNum = i;
            pagesNeeded_left--;
            if (pagesNeeded_left == 0)
            {
                return PageTable[i].pointer;
            }
        }
    }
    return 0;
}

//in: requested pointer
//error: 1
int myFree(void* pointer)
{
    int index = getIndex(pointer);
    if (index == -1)
        return 1;
    
    for (index; index < PAGE_AMOUNT;) {
        if (PageTable[index].inUse)
        {
            PageTable[index].inUse = false;
            if (index == PageTable[index].npage)
                break;
            else
                index = PageTable[index].npage;
        }
        else
        {
            return 1;
        }
    }
    
    return 0;
}

//error: 1
void collectGarbage() {
    int npage = PAGE_AMOUNT - 1;
    for (int i = 0; i < PAGE_AMOUNT; i++)
    {
        if (!PageTable[i].inUse && PageTable[i].npage != -1)
        {
            PageTable[i].npage = -1;
        }
    }
}

int main()
{
    char c;
    void* parray[PAGE_AMOUNT];
    int num = 0, temp;
    void* pointer = NULL;
    initPT();
    
    while(true)
    {
        printf("\n================================");
        printf("\n*********MEMORY MANAGER*********");
        printf("\nFREE SPACE:%20d\n", getFreePagesAmount()*PAGE_SIZE);
        printf("\n================================");
        printPT();
        printf("\n================================");
        printf("\nYOUR POINTERS:");
        if (num != 0) {
            puts("\nNUM\tIND\tSIZE");
            for (int i = 0; i < num; ++i)
            {
                printf("%d\t%d\t%d\n", i, getIndex(parray[i]), getPtrSize(parray[i]) * PAGE_SIZE);
            }
        }
        else
        printf("\n\tAllocate some memory.");
        printf("================================");
        printf("\nChoose action:");
        printf("\n1) malloc");
        printf("\n2) free");
        printf("\nOr press q to exit...\n");
        rewind(stdin);
        c = getchar();
        switch (c)
        {
            case '1':
                printf("\nInput requested size:");
                if (!scanf("%d", &temp))
                {
                    rewind(stdin);
                    break;
                }
                if (pointer = myMalloc(temp))
                {
                    ++num;
                    parray[num - 1] = pointer;
                }
                break;
            case '2':
                printf("\nInput pointer number:");
                if (!scanf("%d", &temp) || temp >= num)
                {
                    rewind(stdin);
                    break;
                }
                if (!myFree(parray[temp]))
                {
                    for (int i = temp; i < num - 1; ++i)
                    {
                        parray[i] = parray[i + 1];
                    }
                }
                --num;
                break;
            case 'q':
                return 0;
        }
        collectGarbage();
    }
    
    return 0;
}
