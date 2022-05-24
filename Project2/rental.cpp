//
//  rental.cpp
//  Product2
///Users/jonathan/Desktop/CS31/Project2/Product2/Product2/rental.cpp
//  Created by Jonathan on 10/10/18.
//  Copyright © 2018 Jonathan. All rights reserved.
//

#include <iostream>
using namespace std ;

int main()
{
    // declearation & constant
    const int BASIC_BASE_CHARGE = 33;
    const int LUXURY_BASE_CHARGE = 61;
    const double MILE_RATE_100 = 0.27;
    const double MILE_RATE_AFTER_400 = 0.19;
    const double APR_NOV_MILE_RATE = 0.21;
    const double DEC_MAR_MILE_RATE = 0.27;
    
    double totalCost=0.0 ;
    double costBasic=0.0 ;
    double dayRate=0.0;
    // cout set up
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    // I/O
    
    // prompt1
    cout << "Odometer at start: ";
    int startReading ;
    cin >> startReading;
    
    // prompt2
    cout << "Odometer at end: " ;
    int endReading;
    cin >> endReading;
    
    
    // prompt3
    cout << "Rental days: ";
    int rentalDay;
    cin >> rentalDay;
    
    
    // prompt4
    cout << "Customer name: ";
    string userName;
    cin.ignore(1000, '\n'); // clear buffer before getline()
    getline(cin, userName);
   
    // prompt5
    cout << "Luxury car? (y/n): ";
    string answer ;
    getline(cin, answer);
   
    
    // prompt6
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month;
    
    // hyphens
    cout << "---" << endl;
    
    // error test
    if(startReading < 0){
        cout << "The starting odometer reading must be nonnegative."<< endl;
        return 1;
    }
    if(startReading > endReading)
    {
        cout << "The final odometer reading must be at least as large as the starting reading."
        << endl;
        return 1;
    }
    if( rentalDay <= 0) // ~def of positive
    {
        
        cout << "The number of rental days must be positive."<< endl;
        return 1;
    }
    if ( userName == "")
    {
        cout << "You must enter a customer name." << endl;
        return 1;
    }
    
    
    if ( answer != "y" && answer != "n")
    {
         cout<< "You must enter y or n."<< endl;
        return 1;
    }
    
    else if( answer == "n")
        dayRate = BASIC_BASE_CHARGE;
    else
        dayRate = LUXURY_BASE_CHARGE;
    
    if (month > 12 || month < 1)
    {
        cout << "The month number must be in the range 1 through 12."<< endl;
        return 1;
    }
    
    
    
    // select season rate
    double seasonMileRate ;
    if ( month >= 4 && month <= 11)
        seasonMileRate = APR_NOV_MILE_RATE;
    else
        seasonMileRate = DEC_MAR_MILE_RATE;
    
    // calulation for basic charge
     costBasic = dayRate * rentalDay;
    
    // caluclation for mileage rate charge
    double costMileage = 0.0 ;
    int totalMileage = endReading - startReading;
    
    if ( totalMileage <= 100 )
        costMileage = MILE_RATE_100 * totalMileage;
    else if ( totalMileage <= 400)
    {
        costMileage = MILE_RATE_100*100;
        costMileage += seasonMileRate*(totalMileage - 100);
    }else
    {
        costMileage = MILE_RATE_100*100;
        costMileage += seasonMileRate*300;
        costMileage += MILE_RATE_AFTER_400*(totalMileage - 400);
    }
    
    totalCost =  costBasic + costMileage ;
    
    cout<< "The rental charge for "<<userName<<" is $"<<totalCost<<endl;
}
