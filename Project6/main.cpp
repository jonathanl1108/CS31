//
//  main.cpp
//  project6
//
//  Created by Jonathan on 11/25/18.
//  Copyright © 2018 Jonathan. All rights reserved.
//

#include <iostream>
using namespace std;

//int main()
//{
//    int arr[3] = { 5, 10, 15 };
//    int* ptr = arr;
//
//    *ptr = 30;          // set arr[0] to 30
//    *(ptr + 1) = 20;      // set arr[1] to 20
//    *(ptr+2)=10;
//
//    while ( ptr < arr+3)
//    {
//        cout << *ptr << endl;    // print values
//        ptr++;
//
//    }
//}

//############################
//void findMax(int arr[], int n, int* pToMax)
//{
//    if (n <= 0)
//        return;      // no items, no maximum!
//
//    pToMax = arr;
//
//    for (int i = 1; i < n; i++)
//    {
//        if (arr[i] > *pToMax)
//            pToMax = arr + i;
//    }
//}
//
//int main()
//{
//    int nums[4] = { 5, 3, 15, 6 };
//    int* ptr;
//
//    findMax(nums, 4, ptr);
//    cout << "The maximum is at address " << ptr << endl;
//    cout << "It's at position " << ptr - nums << endl;
//    cout << "Its value is " << *ptr << endl;
//}
//#################################
//void computeCube(int n, int* ncubed)
//{
//    *ncubed = n * n * n;
//}
//
//int main()
//{
//    int x;
//    int* ptr = &x;
//    computeCube(5, ptr);
//    cout << "Five cubed is " << *ptr << endl;
//}
//#################################
// return true if two C strings are equal
//bool strequal(const char str1[], const char str2[])
//{
//    while (*str1 != 0  &&  *str2 != 0)
//    {
//        if (*str1 != *str2)  // compare corresponding characters
//            return false;
//        cout<<
//        str1++;            // advance to the next character
//        str2++;
//    }
//    cout<<"gets here "<<endl;
//    return *str1 == *str2;   // both ended at same time?
//}
//
//int main()
//{
//    char a[15] = "Zhou";
//    char b[15] = "Zou";
//
//    if (strequal(a,b))
//        cout << "They're the same person!\n";
//    else
//        cout << "They're t7he same person!\n";
//}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//#include <iostream>
//using namespace std;
//
//int* nochange(int* p)
//{
//    return p;
//}
//
//int* getPtrToArray(int& m)
//{
//    int anArray[100];
//    for (int j = 0; j < 100; j++)
//        anArray[j] = 100-j;
//    m = 100;
//    return nochange(anArray);
//}
//
//void f()
//{
//    int junk[100];
//    for (int k = 0; k < 100; k++)
//        junk[k] = 123400000 + k;
//    junk[50]++;
//}
//
//int main()
//{
//    int n;
//    int* ptr = getPtrToArray(n);
//    f();
//    for (int i = 0; i < 3; i++)
//        cout << ptr[i] << ' ';
//    for (int i = n-3; i < n; i++)
//        cout << ptr[i] << ' ';
//    cout << endl;
//}
//For each of the following parts, write a single C++ statement that performs the indicated task. For each part, assume that all previous statements have been executed (e.g., when doing part e, assume the statements you wrote for parts a through d have been executed).
//a.    Declare a pointer variable named cat that can point to a variable of type double.  double* cat
//b.    Declare mouse to be a 5-element array of doubles.  double mouse[5];
//c.    Make the cat variable point to the last element of mouse. cat = &mouse[4]
//d.    Make the double pointed to by cat equal to 25, using the * operator.  *cat=25
//e.    Without using the cat pointer, and without using square brackets, set the fourth element (i.e., the one at position 3) of the mouse array to have the value 42. *(mouse+3)= 42
//f.    Move the cat pointer back by three doubles. cat-=3
//g.    Using square brackets, but without using the name mouse, set the third element (i.e., the one at position 2) of the mouse array to have the value 27. cat[0]=27
//h.    Without using the * operator or the name mouse, but using square brackets, set the double pointed to by cat to have the value 54.  cat[1]=54
//i.    Using the * operator in the initialization expression, declare a bool variable named b and initialize it to true if the double pointed to by catis equal to the double immediately following the double pointed to by cat, and false otherwise. Do not use the name mouse. bool b = if( *cat == *(cat+1))
//j.    Using the == operator in the initialization expression, declare a bool variable named d and initialize it to true if cat points to the double at the start of the mouse array, and false otherwise.
//bool d = (cat == &mouse[0]);

//double mean(const double* scores, int numScores)
//{
//    const double* ptr = scores;
//    double tot = 0;
//
//    for( int i =0 ; i < numScores ; i++)
//    {
//        tot += *(scores+1);
//    }
//    return tot/numScores;
//}

// This function searches through str for the character chr.
// If the chr is found, it returns a pointer into str where
// the character was first found, otherwise nullptr (not found).
//
//const char* findTheChar(const char str[], char chr)
//{
//    for (int k = 0; *(str+k) != 0; k++)
//        if (*(str+k) == chr)
//            return str+k;
//
//    return nullptr;
//}
//const char* flindTheChar(const char* str, char chr)
//{
//    for ( ;*str != 0; str++)
//        if ( *str == chr)
//            return str;
//
//    return nullptr;
//}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//void removeS( char* cStr)
//{
//    char* ptr = cStr;
//    for(;*cStr != 0 ; cStr++)
//    {
//        if( *cStr != 'S' && *cStr != 's')
//        {
//            *ptr = *cStr;
//            ptr++;
//        }
//    }
//    *ptr = 0;
//}
//int main()
//{
//    char msg[50] = "She'll be a massless princess.";
//    removeS(msg);
//    cout << msg;  // prints   he'll be a male prince.
//}
//

//int main()
//{
//    int arr[3] = { 5, 10, 15 };
//    int* ptr = arr;
//
//    *ptr = 30;          // set arr[0] to 30
//    *(ptr + 1) = 20;      // set arr[1] to 20
//    *(ptr + 2) = 10;       // set arr[2] to 10
//
//    for( ; ptr < arr+3 ; ptr++)
//    {
//        cout << *ptr << endl;    // print value
//    }
//}

//
//#include <iostream>
//using namespace std;
//
//int* maxwell(int* a, int* b)
//{
//    if (*a > *b)
//        return a;
//    else
//        return b;
//}
//
//void swap1(int* a, int* b)
//{
//    int* temp = a;
//    a = b;
//    b = temp;
//}
//
//void swap2(int* a, int* b)
//{
//    int temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
//int main()
//{
//    int array[6] = { 5, 3, 4, 17, 22, 19 };
//
//    int* ptr = maxwell(array, &array[2]);
//    *ptr = -1;
//    ptr += 2;
//    ptr[1] = 9;
//    *(array+1) = 79;
//
//    cout << &array[5] - ptr << endl;
//
//    swap1(&array[0], &array[1]);
//    swap2(array, &array[2]);
//
//    for (int i = 0; i < 6; i++)
//        cout << array[i] << endl;
//}
//
//
//
//

//int main()
//{
//    char msg[50] = "She'll be a massless princess.";
//    removeS(msg);
//    cout << msg;  // prints   he'll be a male prince.
//
//}
int main()
{
    int arr[3] = { 5, 10, 15 };
    int* ptr = arr;
    
    *ptr = 30;          // set arr[0] to 30
    *(ptr + 1) = 20;      // set arr[1] to 20
    ptr += 2;
    ptr[0] = 10;        // set arr[2] to 10
    ptr = arr;
    while ( ptr < arr+3)
    {
        cout << *ptr << endl;    // print values
        ptr++;
        
    }
}
