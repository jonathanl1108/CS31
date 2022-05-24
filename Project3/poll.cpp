//
//  poll.cpp
//  project3
//
//  Created by Jonathan on 10/22/18.
//  Copyright © 2018 Jonathan. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

bool isValidUppercaseStateCode(string stateCode);
void makeUpperCase( string& s);

bool hasProperSyntax(string pollData)
{
    
    const char segPoint = ',';
    int length = pollData.size();
    
    // zero case pass
    if( length == 0)
        return true;
    // No comma precedes the first state forecast or follows the last state forecast
    if(pollData[0] == segPoint || pollData[pollData.size()-1]== segPoint)
        return false;
    
    // convert eveything to upper case so we dont have to worry about lower case
    makeUpperCase(pollData);
    
    // check each state forecast contianed in poll string
    int i = 0 ;
    while( i != length)
    {
        // check if the frist and second char are alphabet or even a valid state code
        if(isalpha(pollData[i])&&isalpha(pollData[i+1]))
        {
            // create the possible state code
            string stateCode = "";
            stateCode+=pollData[i];
            stateCode+=pollData[i+1];
            
            if(!isValidUppercaseStateCode(stateCode))
                return false;
            // case where there is no data after state code that locats at first and last position
            if(i+1 ==length-1)
                return true;
            else
                i+=2;
        }else
            return false; // if not why bother to check the rest
        
        // if syntax for state code is valid, we then loop through the rest and check by its defintions
        while( pollData[i] != segPoint) // each iteration can check each segment of poll String
        {
            if(!isdigit(pollData[i]))
                return false;
            i++;
            
            // 2 possible cases ==> following 1 digit or 2 digit then follow by a letter(D,R,I,..etc)
            if(isdigit(pollData[i]))//2 digit case
            {
                i++;
                if(!isalpha(pollData[i])) // must be letter
                    return false;
                i++;
            }else if(!isalpha(pollData[i]))//1 digit case then next must be letter
                return false;
            else
                i++;
            
            if( i == length) // for the last stateForcast within poll Strings
            {
                i--;
                break;
            }
        }
        i++;
    }
    return true;
}
int tallySeats(string pollData, char party, int& seatTally)
{
    if(!hasProperSyntax(pollData)&& !isalpha(party))
        return 2;
    // If the parameter pollData is not a poll data string, this function returns 1
    if(!hasProperSyntax(pollData))
        return 1;
    //If the parameter party is not a letter, this function returns 2.
    if(!isalpha(party))
        return 2;
   
    char targetParty = party;
    int totalSeats = 0;
    for(int k =0 ; k < pollData.size(); k++)
    {
        // since syntax is guaranteed, it is safe to just loop through and find the data of our target party
        // 1 or 2 char before party char must be digits, this is guaranteed by hasProperSyntax(pollData)
        if( toupper(pollData[k]) == toupper(targetParty))
        {
            char digitInOnce = pollData[k-1];
            char digitInTens = pollData[k-2];
            // 2 cases like 17D or 6D
            if( isdigit(digitInOnce) && isdigit(digitInTens)) // 2 digit case
            {
                totalSeats+= digitInOnce-'0';
                totalSeats+= (digitInTens-'0')*10;
            }else{
                totalSeats+= digitInOnce-'0';
            }
        }
    }
    //If neither of those situations occurs,
    //then the function returns 0 after setting seatTally to the total number of seats
    seatTally=totalSeats;
    return 0;
}

// helper functions::
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
void makeUpperCase( string& s)
{
    // the condtion in for loop will tkae care the case of empty string
    for(int k =0 ; k != s.size(); k++)
        s[k] = toupper(s[k]);
}


int main(int argc, const char * argv[])
{
    
    // TEST CASE GROUP 1
    
    if (hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"))
        cout << "Passed test 1: hasProperSyntax(\"CT5D,NY9R17D1I,VT,ne3r00D\")" << endl;
    else
        cout<<"bad"<<endl;
    if (!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"))
        cout << "Passed test 2: !hasProperSyntax(\"ZT5D,NY9R17D1I,VT,ne3r00D\")" << endl;
    int seats;
    seats = -999;    // so we can detect whether tallySeats sets seats
    if (tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22)
        cout << "Passed test 3: tallySeats(\"CT5D,NY9R17D1I,VT,ne3r00D\", 'd', seats)" << endl;
    seats = -999;    // so we can detect whether tallySeats sets seats
    if (tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999)
        cout << "Passed test 4: tallySeats(\"CT5D,NY9R17D1I,VT,ne3r00D\", '%', seats)" << endl;
    
    assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
    assert(hasProperSyntax(""));
    assert(!hasProperSyntax("ZT5D,NY9R17D1I,VT,ne3r00D"));
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22);
    seats = -999;    // so we can detect whether tallySeats sets seats
    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    
    assert(hasProperSyntax("MA9D,KS4R")  &&  hasProperSyntax("KS4R,MA9D"));
    assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D"));
    
    //TEST GROUP 2
    int s;
    int r1 = tallySeats("MA9D", '@', s);
    // r1 must be 2, since the party parameter '@' is not a letter.
    // r1 must not be 1, since "MA9D" *is* a poll data string.
    
    int r2 = tallySeats("MA9@", 'D', s);
    // r2 must be 1, since "MA9@" is not a poll data string.
    // r2 must not be 2, since the party parameter 'D' *is* a letter.
    
    int r3 = tallySeats("MA9@", '@', s);
    // r3 must be 1 or 2, your choice which one.
    cout<< "r1 "<< r1 << " r2 "<< r2 << " r3 "<< r3<< endl;
    
    int r = tallySeats("", 'D', s);
    if(r != 0)
        cout<< "fail test case tallSeats "<<endl;
    else
        cout<< "pass empty string tallSeats"<<endl;
    
    // TEST GROUP 3
    // bad state code in first string
    if(hasProperSyntax("AP5D,NY9R17D1I,VT,ne3r00D"))
        cout<<"fail bad state code in first poll string"<<endl;
    // bad state code in middle of poll strings
    if(hasProperSyntax("AK5D,MP9R17D1I,VT,ne3r00D"))
        cout<<"fail bad state code in middle poll string"<<endl;
    // upper case good state code
    if(!hasProperSyntax("AK5D,NY9R17D1I,VT,OR3r00D"))
        cout<<"fail state code in upper case"<<endl;
    // lower case good state code
    if(!hasProperSyntax("sc5D,pa9R17D1I,VT,ca3r00D"))
        cout<<"fail state code in loweer case"<<endl;
    // lower and upper case combianton good state code
    if(!hasProperSyntax("Ak5D,Ny9R17D1I,VT,or3r00D"))
        cout<<"fail state code in combination of upper and loweer"<<endl;
    // bad state code in loweer and upper case
    if(hasProperSyntax("Ap5D,Na9R17D1I,VT,or3r00D"))
        cout<<"fail state code in combination of upper and loweer"<<endl;
    else
        cout<< "pass test for bad state code in combination of upper and loweer case"<< endl;
    
    
    // TEST GROUP 4
    // COMMA AT END
    if(hasProperSyntax("AK5D,NY9R17D1I,VT,OR3r00D,"))
        cout<<"fail COMMA AT END"<<endl;
    // COMMA AT FIRST POSITION
    if(hasProperSyntax(",AK5D,NY9R17D1I,VT,OR3r00D"))
        cout<<"fail COMMA AT FIRST POSITION"<<endl;
    // 3 DIGIT IN PARTY RESULT
    if( !hasProperSyntax("AK5D,NY9R17D1I,VT030D,OR3r00D"))// SHOULD FAIL
        cout<< "pass test for 3 DIGIT IN PARTY RESULT (AK5D,NY9R17D1I,VT030D,OR3r00D)"<<endl;
    else
        cout<<"fail test for 3 DIGIT IN PARTY RESULT (AK5D,NY9R17D1I,VT030D,OR3r00D)"<<endl;
    // extra space
    if( !hasProperSyntax("AK5D,NY9R17D1I, VT030D,OR3r00D"))// SHOULD FAIL
        cout<< "pass test for extra space"<<endl;
    else
        cout<<"fail test for extra space"<<endl;
    // space instead of comma ####
    if( !hasProperSyntax("AK5D,NY9R17D1I VT030D,OR3r00D"))// SHOULD FAIL
        cout<< "pass test for space instead of comma"<<endl;
    else
        cout<<"fail test for space instead of comma"<<endl;
    
    // tallySeats test case with bad syntax
    int t1;
    t1 =tallySeats("CT 5D,NY9R17D1I,VT,ne3r00D", 'd', seats);
    if (t1 == 1)
        cout<< "tallySeats pass bad syntax and returns 1"<<endl;
    // good syntax but undefine party code
    
    t1 =tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'k', seats);
    if(seats == 0)
        cout<< "tallySeats pass undefine party code and returns 2"<<endl;
    else
        cout<<"fail  good syntax but undefine party code t1= "<<t1<<endl;
    // 0 party code test
    t1 =tallySeats("CT0D,NY9R00D1I,VT,ne3r01D", 'd', seats);
    if(t1 == 0 && seats== 1)
        cout<<"pass  0 party code test"<<endl;
    else
        cout<<"fail  0 party code test"<<endl;
    
    // test case where there are state code but no data
    if(hasProperSyntax("ca,ny,FL,La"))
        cout<<"pass test where there is no data after state code"<<endl;
    else
        cout<<"fail test for no data following state code" << endl;
    
    
    //cout << "All tests succeeded" << endl;
    
    
    for (;;)
    {
        cout << "Enter poll data string: ";
        string pds;
        getline(cin, pds);
        if (pds == "quit")
            break;
        seats=-199;
        int t = tallySeats(pds, 'd', seats);
        
        cout << "t returns : "<<t<<endl;
        cout << "seats : "<<seats<<endl;
        cout << "hasProperSyntax returns ";
        if (hasProperSyntax(pds))
            cout << "true";
        else
            cout << "false";
        cout << endl;
    }
    
    
}
