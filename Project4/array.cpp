//
//  main.cpp
//  project4
//
//  Created by Jonathan on 11/2/18.
//  Copyright © 2018 Jonathan. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

// helper
void exchange(string& n1, string& n2)
{
    string temp = n1;
    n1 = n2;
    n2 = temp;
}
int appendToAll(string a[], int n, string value)
{
    if( n < 0 )
        return -1;
    for(int i =0 ; i < n ; i++) // add the stirng after each element
        a[i]+= value;
    return n;
}

int lookup(const string a[], int n, string target)
{
    if( n < 0)
        return -1;
    for(int i =0 ; i < n ; i++)
    {
        if( a[i] == target)
            return i;
    }
    return -1;  // Return −1 if there is no such string.
}
//Return the position of a string in the array such that
//that string is >= every string in the array.
int positionOfMax(const string a[], int n)
{
    if(n<=0)
        return -1;
    int maxIndex =0; // let the first element be the fiest max
    for(int i =0 ; i < n ; ++i) // loop through n element and update the max pos along
    {
        if(a[i] > a[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
}
int rotateLeft(string a[], int n, int pos)
{
    if (pos >= n || n < 0 || pos < 0 ) // in case of accessing out of bound so add pos>= n
        return -1;
    string temp = a[pos]; // first element will be store in temp vairbale first
    for( int i = pos ; i < n-1 ; i++) // move up each element except the first to the pos before
    {
        a[i]=a[i+1];
    }
    a[n-1] = temp; // store the first element to the last position in array
    return pos;
}

int countRuns(const string a[], int n)
{
    // one or more consecutive identical items in a.
    if(n < 0)
        return -1;
    if(n == 0)
        return 0;
    
    int countRun = 1; // there should be at leat one
    string setElement= a[0];
    for(int i =1 ; i <n ; i++)
    {
        if( a[i] == setElement) //it will skip bottom statment until it finds another item
            continue;
        countRun++; // once we find another item increment countRun
        setElement=a[i]; // set the new taget item
    }
    return countRun;
}

int flip(string a[], int n)
{
    if(n < 0)
        return -1;
    // like a mirror we can just loop thorught half of n and swap the corresponding elements
    // even or odd number of n will both works
    for( int i = 0 ; i < n/2 ; i++)
    {
        exchange(a[i],a[n-i-1]);
    }
    return n ;
}
int differ(const string a1[], int n1, const string a2[], int n2)
{
    if( n1 <0 || n2<0 || (n1 == 0 && n2 == 0))
        return -1;
    int length = n1; // find the smaller length
    if(n2 < n1)
        length =n2;
    for( int i =0 ; i < length ; i++)
    {
        if(a1[i]!=a2[i]) // when there is mismatch return the index right away
            return i;
    }
    return length; //return whichever value of n1 and n2 is less than or equal to the other
}

int subsequence(const string a1[], int n1, const string a2[], int n2) // not sure
{
    if( n1 <0 || n2 <0 || (n1 < n2))
        return -1;
    // If all n2 elements of a2 appear in a1 then n2 <= n1
    //consecutively and same order =>then return the position in a1
    for( int i =0 ; i <= n1-n2 ; i++) // for each index i in a1 there is a possible lenght n2 to be check
    {
        int match = 0;
        for( int k =0 ; k< n2 ; k++)// find the ith of a1 that is the start of a2
        {
            if(a1[i+k] != a2[k])
            {
                match =0;   // if there is a mismatch break the inner loop and move on to the next index i in a1
                break;
            }
            else
                match++;
            
            if(match == n2) // if the number match is the lenght of the n2 we found one
                return i;
        }
        
    }
   return -1; // doesn't exsit one a2 sequence in a1
}

//Return the smallest position in a1 of an element
//that is equal to any of the n2 elements in a2.
//Return −1 if no element of a1 is equal to any element of a2.
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0  ||  n2 < 0)
        return -1;
    for (int i = 0; i < n1; i++)
        if (lookup(a2, n2, a1[i]) != -1) // find the first equal with the lookup function
            return i;
    return -1;
}
//Rearrange the elements of the array
//value < divider come before all the other elements
//value > divider come after all the other elements
/* when the divider test find the first greater element,
 //       this element will be throw to the end of the array
 //        by rotateLeft() which is at the index n-1.
 //    */
int divide(string a[], int n, string divider)
{
    if (n < 0)
        return -1;
    
    int metIndex = 0;
    
    for (int i = n-1; i >= 0; i--)  //iterating from the end of the array
        if (a[i] >= divider)       //if the element  >= divder
            rotateLeft(a, n, i);    //call rotateLeft function throw item to the end of the array
        else
            metIndex++;
    
    for (int i = 0; i < n; i++)
        if (a[i] == divider)       //if the current element is divder
        {
            exchange(a[i], a[metIndex]); // exchange
            metIndex++;
        }
    
    for (int x = 0; x < n; x++)
        if (a[x] >= divider)
            return x;
    
    return n;
}

void printArray(string a[], int n)
{
    for(int i =0 ; i< n ; i++)
    {
        if( i == n-1)
            cout<< a[i]<<endl;
        else
            cout<<a[i]<<",";
    }
}


int main() {

    // test appendToall
    string append[5] = {"WHAT", "WHO", "WHY"};

    int apt = appendToAll(append, 3, "?!!!");
    cout<< "apt: "<<apt<<endl;
    printArray(append, 3);
//    assert(apt == 3);
    apt = appendToAll(append, 0, "?!!!");
    cout<< "apt: "<<apt<<endl;
    printArray(append, 3);
    apt = appendToAll(append, 1, "?!!!");
    cout<< "apt: "<<apt<<endl;
    printArray(append, 3);
    cout<< "Append Test Pass\n"<<endl;
    
    // lookup test
    string h[8] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona", "ed" };
    assert(lookup(h, 7, "eleni") == 5);
    assert(lookup(h, 7, "ed") == 2);
    assert(lookup(h, 2, "ed") == -1);
    assert(lookup(h, 0, "ed") == -1);
    // if there is more than one same return the smallest ed at pos 2 and 7
    assert(lookup(h, 8, "ed") == 2);
    cout<< "lookup Pass\n"<<endl;
    
    
    // max pos test
    string max[5] ={"1","2","3","4","4"};
    // return -1 if there is no interesting element
    assert(positionOfMax(max, 0) == -1);
    //return smallest pos if there is two max
    assert(positionOfMax(max, 5) == 3);
    assert(positionOfMax(h, 7) == 3);
    assert(positionOfMax(h, -1) == -1);
    cout<< "positionOfMax Pass\n"<<endl;
    
    //rotate left test
    string folks[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string politician[5] = { "eleni", "dianne", "fiona", "kevin", "gavin" };
    assert(rotateLeft(politician, 5, 1) == 1);
    printArray(politician, 5); // politician now should contains:  "eleni", "fiona", "kevin", "gavin", "dianne"
    
    // return -1 when there is 0 element to rotate
    assert(rotateLeft(folks, 0, 1) == -1);
    assert(rotateLeft(folks, 0, -1) == -1);
    // function test
    assert(rotateLeft(folks, 5, 3) == 3);
     assert(rotateLeft(folks, 6, 5) == 5);
    printArray(folks, 6 ); // should be { "betty", "john", "xavier", "kevin"," ", "dianne" };
    
    cout<< "rotateLeft Pass\n"<<endl;
    
    //count Runs Test
    string k[9] = {"xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "john"};
    assert(countRuns(k, 9) == 5);  //  returns 5
    string alpa[11] ={"A", "B","B","C","C","C","c","D","D","D","d"}; // A B C c D d should have 6 sets
    assert(countRuns(alpa, 11) == 6);  //  returns 6
    assert(countRuns(alpa, 5) == 3); // return 3 A B C
    // 0 element retuns 0
    assert(countRuns(alpa, 0) == 0); // return 3
    // negative
    assert(countRuns(alpa, -1) == -1); // return -1
    cout<< "count Runs pass\n"<<endl;
    
    // flip test
    string folk[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    cout<< "before flip: ";
    printArray(folk, 6);
    assert(flip(folk, 4)==4);  // returns 4
    assert(flip(folk, 3)==3);  // returns 3
    
    // 0 element return 0 -1 return -1
    assert(flip(folk,0) ==0);
    assert(flip(folk, -1) ==-1);
     cout<< "after  flip: ";
    printArray(folk, 6);// folks now contains:  "xavier"  ""  "john"  "betty"  "kevin"  "dianne"
    cout<<"flip test pass"<<endl;
    
    // differ test
    string folkss[6] = { "betty", "john", "", "xavier", "kevin", "dianne" };
    string groups[5] = { "betty", "john", "dianne", "", "xavier" };
    int r = differ(folkss, 6, groups, 5);  //  returns 2
    int s = differ(folkss, 2, groups, 1);  //  returns 1
    cout<< "r: "<<r<<" s: "<<s<<endl;
    assert(differ(folkss, -1, groups, 5)== -1);
    string t1[5] ={"1","2","3","4","5"};
    string t2[4] ={"1","2","3","4"};
    assert(differ(t1, 5, t2, 3)== 3); // should return3 because thery are same up to t2 run out, ans ot shoud return the samller n
    cout<<"differ pass"<<endl;
    
    //subsequence
    string names[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string names1[10] = { "gavin", "kevin", "greg" };
    int t = subsequence(names, 6, names1, 3);  // returns 1
    cout<< "t: "<<t<<endl;
    string names2[10] = { "eleni", "greg" };
    int u = subsequence(names, 5, names2, 2);  // returns -1
    cout<< "u: "<<u<<endl;
    string r1[5]={"1","2","3","1","2"};
    string r2[2] ={"1","2"};
    // 2 r2 sequaence appears in r1, shoud return small pos
    assert(subsequence(r1, 5, r2, 2)== 0);
    assert(subsequence(names, 0, names1, 3)== -1);
    assert(subsequence(names, -1, names1, 3)== -1);
    cout<<"subsequence pass"<<endl;
    
    
    // look up any test
    string name[10] = { "eleni", "gavin", "kevin", "greg", "betty", "fiona" };
    string set1[10] = { "dianne", "betty", "greg", "gavin" };
    assert(lookupAny(name, 6, set1, 4) ==1);  // returns 1 (a1 has "gavin" there)
    string set2[10] = { "xavier", "ed" };
    assert(lookupAny(name, 6, set2, 2) == -1);  // returns -1 (a1 has none)
    assert(lookupAny(name, -1, set2, 2) == -1);  // returns -1 (n1 is negative)
    assert(lookupAny(name, 3, set2, 0) == -1);  // returns -1 (n2 has 0 element)
    assert(lookupAny(r1, 5, r2, 2) == 0);  // returns 0  smallest pos of the same element in a1
    assert(lookupAny(name, 5, r2, 2) == -1);  // returns -1  no element in a1
    cout<<"look up test pass"<<endl;
    
    // divide test
    cout<< "\n:: DEVIDE FUNCTION TEST ::"<<endl;
//    string candidate[6] = { "dianne", "fiona", "gavin", "xavier", "ed", "betty" };
//    cout<<"Before Divide: \n";
//    printArray(candidate, 6);
//    assert(divide(candidate, 6, "eleni")==3);  //  returns 3
//    cout<<"After  Divide: \n";
//    printArray(candidate, 6);
//
//    // candidate must now be
//    //      "dianne"  "ed"  "betty"  "fiona"  "xavier"  "gavin"
//    // or   "ed"  "betty"  "dianne"  "gavin"  "fiona"  "xavier"
//    // or one of several other orderings.
//    // All elements < "eleni" (i.e., "ed", "betty", and "dianne")
//    //   come before all others
//    // All elements > "eleni" (i.e., "xavier", "fiona", and "gavin")
//    //   come after all others
//    string candidate2[4] = { "gavin", "kevin", "fiona", "john" };
//    assert(divide(candidate2, 4, "john")==2);  //  returns 2

    string randOrder[9]={"6","5","7","9","3","4","1","2","8"};
    cout<<"Before Divide: \n";
    printArray(randOrder, 9);
    cout<<"After  Divide respect 4: \n";
    divide(randOrder, 9, "4");
    printArray(randOrder, 9);
    
//    cout<<"\nBefore Divide: \n";
//    printArray(randOrder, 5);
//    cout<<"After  Divide respect 4 when 4 is not in the set: \n";
//    divide(randOrder, 5, "4"); // when divider is not part of the array
//    printArray(randOrder, 5);
//
//    printArray(randOrder, 3);
//    assert(divide(randOrder, 3, "9")==3);
//
//
//    string randOrder1[5]={"3","5","4","9","2"};
//    cout<<"Before Divide: \n";
//    printArray(randOrder1, 5);
//    cout<<"After  Divide respect 9: \n";
//    int i =divide(randOrder1, 5, "9");
//    cout<<"i: "<<i<<endl;
//    printArray(randOrder1, 5);

   cout << "All tests succeeded" << endl;
    

    
}

