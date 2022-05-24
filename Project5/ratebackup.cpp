//
//  main.cpp
//  project5
//
//  Created by Jonathan on 11/17/18.
//  Copyright © 2018 Jonathan. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cctype>
#include <iostream>
#include <cassert>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH =250;

// helper function that do some "soft deleation"

void rotateLeft( char a[][MAX_WORD_LENGTH+1],int pos, int nPattern)
{
    for(int i = pos; i < nPattern-1; i++)
        strcpy(a[i], a[i+1]);
}
void sepRotateLeft(int seperaction[],int pos, int nPattern)
{
    for(int i = pos; i < nPattern-1; i++)
        seperaction[i] = seperaction[i+1];
}


void toLowerCase( char a[][MAX_WORD_LENGTH+1],char b[][MAX_WORD_LENGTH+1], int n)
{
    for( int i = 0 ; i < n ; i++)
    {
        for( int k =0 ; a[i][k] != '\0'; k++)
            if( isupper(a[i][k]))
                a[i][k] = tolower(a[i][k]);
    }
    for( int i = 0 ; i < n ; i++)
    {
        for( int k =0 ; k != strlen(b[i]); k++)
            if( isupper(b[i][k]))
                b[i][k] = tolower(b[i][k]);
    }
}

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns)
{
    if( nPatterns < 0)
        return 0;
    
    // The function must transform every upper case letter in the pattern words into its lower case
    toLowerCase( word1, word2, nPatterns);
    
    
    // The function must remove from the collection
    //A word in the pattern contains
    // no characters, or contains a character that is not a letter.

    for( int patternIndex = 0 ; patternIndex < nPatterns ; patternIndex++)
    {
        
        bool isProper = true;
        
        // inspect each char of each word
        // check word in word1
        // no chracter
        if(strcmp(word1[patternIndex], "")== 0 ||strcmp(word2[patternIndex], "")==0 )
            isProper=false;
        for( int i =0 ; word1[patternIndex][i] != '\0'; i++ )
        {
            char inspectChr = word1[patternIndex][i] ;
            if( inspectChr == '\0' || !isalpha(inspectChr)){
                isProper = false;
            }
        }
        
        // check word in  word2
        for( int k =0 ; word2[patternIndex][k] != '\0' ; k++ )
        {
            char inspectChr = word2[patternIndex][k] ;
            if( inspectChr == '\0' || !isalpha(inspectChr))
                isProper = false;
        }
        // check if seperation is nagative
        if(separation[patternIndex] < 0)
            isProper = false;
        
        // if two patterns have the same w1 and the same w2 values in either order
        // remove the pattern whose separation value is the lesser of the two separation values
        for( int pIndex2 = 0 ; pIndex2 < patternIndex ; pIndex2++)
        {
            // case1  {"hello", "hello"}
            //        {"world", "world"}
            if(strcmp(word1[patternIndex], word1[pIndex2]) == 0
               && strcmp(word2[patternIndex], word2[pIndex2]) == 0)
            {
                isProper = false;
                if(separation[patternIndex] > separation[pIndex2])
                    separation[pIndex2] = separation[patternIndex];
            }
            // case2  {"world", "hello"}
            //        {"hello", "world"}
            if(strcmp(word1[patternIndex], word2[pIndex2]) == 0
               && strcmp(word2[patternIndex], word1[pIndex2]) == 0)
            {
                isProper = false;
                if(separation[patternIndex] > separation[pIndex2])
                    separation[pIndex2] = separation[patternIndex];
            }
        }
        // remove if its not proper
        if( !isProper)
        {
            rotateLeft(word1, patternIndex, nPatterns);
            rotateLeft(word2, patternIndex, nPatterns);
            sepRotateLeft(separation,patternIndex, nPatterns);
            nPatterns --;
            patternIndex--;
        }
    }
    //    for(int i=0 ; i < strlen(word1[i]) ; i++)
    //        cout<< word1[i]<<", ";
    //    cout<<endl;
    //    for(int i=0 ; i < strlen(word2[i]) ; i++)
    //        cout<< word2[i]<<", ";
    //    cout<<endl;
    //    for(int i=0 ; i < nPatterns ; i++)
    //        cout<< separation[i]<<", ";
    //    cout<<endl;
    //    cout<<nPatterns<<endl;
    return nPatterns;
}

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns)
{
    // can't modify document
    char documentCpy[MAX_DOCUMENT_LENGTH];
    strcpy(documentCpy, document);
    
    //after debug, noticed it shoud be maxword+2 becuse [MAX_WORD_LENGTH+1 )+1]
    char documentCopy[MAX_DOCUMENT_LENGTH][MAX_WORD_LENGTH+2]; //
    
    int wordTotal=0 ;
    int wordLength=0;
    int counter =1;
    for( int i = 0 ; documentCpy[i] != '\0' ; i++)
    {
        if( isalpha(documentCpy[i]) && (wordLength < MAX_WORD_LENGTH+1))
        {
            documentCopy[wordTotal][wordLength] = tolower(documentCpy[i]);
            wordLength++;
        }
        else if( documentCpy[i] == ' ' && wordLength > 0) // spece only matters when at leat a word is formed
        {
            documentCopy[wordTotal][wordLength]='\0';
            wordTotal++;
            wordLength =0;
        }
        counter++;
    }
    documentCopy[wordTotal][wordLength]='\0';
    wordTotal++;
    
    // finally add null at end of the whole docArray
    
    
    // find any pattern match
    // DEF pattern match :: w2 appears before or after w1 with no more than separation intervening words
    int found =0 ;
    // check each pattern and if found we check the next so max found shoud == nPattern
    for( int pcheck =0 ; pcheck < nPatterns ; pcheck++ )
    {
        bool isFound = false;
        for( int i =0 ; i < wordTotal ; i++)
        {
            if( strcmp(documentCopy[i], word1[pcheck]) == 0)
            {
                for( int k =0 ; k < wordTotal ; k++)
                {
                    if( strcmp(documentCopy[k], word2[pcheck]) == 0)
                    {
                        int sep = k-i;
                        sep = abs(sep)-1;
                        int maxSep= separation[pcheck];
                        if( sep <= maxSep)
                        {
                            isFound = true;
                            found ++;
                            break;
                        }
                    }
                }
            }if(isFound)
                break;
        }
    }
    return found;
}

int main()
{
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    cout << "All tests succeeded" << endl;
    
    char test1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious"
    };
    char test2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot"
    };
    int test3[TEST1_NRULES] = {
        -99,           3,          0
    };
    cout<< makeProper(test1, test2, test3, 3);
}

