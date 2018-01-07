//Description: This program will output the month and year of the user input. Much like a calendar application.

#include <iostream>
#include <string>

using namespace std;

//This constant represent the week size
const int WEEKSIZE = 7;

// Function Initialization
void displayMonth(string monthName, int year);
void displayYear(int year);
void printWeekHeader(string monthName,int year,bool printYear);
void printMonthDays(int day, int offsetDays);
void inputChecking(string inp);

int getDayOfMonth(int monthNum, bool leapYear);
int getMonthNum(string monthName);
int getStartDayOfYear(int year);
int getStartDayOfMonth(int offsets, int monthDays);

string getMonthName(int monthNum);

bool isLeapYear(int year);


int main(){
    string inp;
    cout<< "Enter the month you want" << endl;
    getline(cin,inp);
    //Checks what the user inputs
    inputChecking(inp);
    return 0;
}
// This function will display the appropriare days in that month
void displayMonth(string monthName, int year){
    int offsetsDay = getStartDayOfYear(year);
    int targetMonth = getMonthNum(monthName);
    cout << targetMonth << endl;
    //This loop will figure out the off sets in the month
    for(int m = 1; m < targetMonth;m++){
        offsetsDay = getStartDayOfMonth(offsetsDay,getDayOfMonth(m,isLeapYear(year)));
    }
    //Prints the month with the appropriate off sets
    printWeekHeader(monthName, year, true);
    printMonthDays(getDayOfMonth(getMonthNum(monthName), isLeapYear(year)),offsetsDay);
}
//This function will display the whole calendar of that given year
void displayYear(int year){
    cout << "********" << year << "********" << endl;
    int offsetsDay = getStartDayOfYear(year);
    //This loop will go through all the month and displaying them with their appropriate off sets
    for(int m = 1; m < 13; m++){
        cout << endl;
        printWeekHeader(getMonthName(m),year, false);
        printMonthDays(getDayOfMonth(getMonthNum(getMonthName(m)), isLeapYear(year)),offsetsDay);
        offsetsDay = getStartDayOfMonth(offsetsDay,getDayOfMonth(m,isLeapYear(year)));

    }
}
//This function will display the Weekheader of any month.
void printWeekHeader(string monthName, int year, bool printYear){
    string weekDays[WEEKSIZE] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

    cout << endl;
    if(printYear){
        cout << "********" << monthName << "********" << endl;
        cout << "********" << year << "********" << endl;
    }
    else{
        cout << "********" << monthName << "********" << endl;
    }
    cout << endl;

    for(int i = 0; i < WEEKSIZE; i++){
        cout<< weekDays[i] << "\t";
    }
    cout << endl;
    for(int i = 0; i < WEEKSIZE; i++){
        for(int j =0; j<4; j++){
            cout << "__";
        }
    }
    cout << endl;
}
//This function will print the month days
void printMonthDays(int dayM, int offsetDays){
    int count = 0;

    for(int j = 0; j<offsetDays;j++){
        cout <<" "<<"\t";
        count+=1;
    }
    for(int i =1; i <dayM+1; i++){
        cout << i << "\t";
        count+=1;
        if(count % 7 == 0){
            cout<<endl;
            count = 0;
        }
    }
    cout << endl;
}

//Checks if its leap year
bool isLeapYear(int year){
    return ((year%4==0) && (year%100 !=0))||(year%400==0);
}

//This function when called, takes in a string and checks what the user have inputed.
//Then this function will call the appropriate function toward what the user have inputed.
void inputChecking(string inp){
    string tmp;
    string month;
    int year =0;
    int spaceN;
    //checks if the user inputed year
    if(isdigit(inp[0])){
        for(int i = 0; i <4; i++){
            tmp += inp[i];
        }
        year = stoi(tmp);
        //call print year
        displayYear(year);

    }
    //Checks if the user inputed month and year
    else{
        spaceN = inp.find(" ");

        for(int i = 0; i < (spaceN);i++){
            month+=inp[i];
        }

        for(int i = 0; i < 5 ;i++){
            tmp += inp[i+spaceN];
        }
        year = stoi(tmp);
        // call print month
        displayMonth(month, year);
    }
    
}
//This function will return the off sets of beggining of the month for that year

int getStartDayOfYear(int year){
    int x1 = (year-1)/4;
    int x2 = (year-1)/100;
    int x3 = (year-1)/400;

    return (year + x1 -x2 +x3)%7;
}

//Will determine the offsets of any month.
int getStartDayOfMonth(int offsets, int monthDays){
    int count = 0;

    for(int j = 0; j<offsets;j++){
        count+=1;
    }
    for(int i =1; i <monthDays+1; i++){
        count+=1;
        if(count % 7 == 0){
            count = 0;
        }
    }
    return count;  
}

//This function will check the month number and will return the month name
string getMonthName(int monthNum){
    if(monthNum == 1){return "January";}
    else if(monthNum == 2){return "Febuary";}
    else if(monthNum == 3){return "March";}
    else if(monthNum == 4){return "April";}
    else if(monthNum == 5){return "May";}
    else if(monthNum == 6){return "June";}
    else if(monthNum == 7){return "July";}
    else if(monthNum == 8){return "August";}
    else if(monthNum == 9){return "September";}
    else if(monthNum == 10){return "October";}
    else if(monthNum == 11){return "November";}
    else if(monthNum == 12){return "December";}
}
//This function will check the month name and return the month number
int getMonthNum(string targetMonth){
    if(targetMonth == "January"){return 1;}
    else if(targetMonth == "February"){return 2;}
    else if(targetMonth == "March"){return 3;}
    else if(targetMonth == "April"){return 4;}
    else if(targetMonth == "May"){return 5;}
    else if(targetMonth == "June"){return 6;}
    else if(targetMonth == "July"){return 7;}
    else if(targetMonth == "August"){return 8;}
    else if(targetMonth == "September"){return 9;}
    else if(targetMonth == "October"){return 10;}
    else if(targetMonth == "November"){return 11;}
    else if(targetMonth == "December"){return 12;}
}
//This function will return the number of days in that specific month.
int getDayOfMonth(int monthNum,bool leapYear){
    if(monthNum == 1){return 31;}
    else if(monthNum == 2){if(leapYear){return 29;}else {return 28;}}
    else if(monthNum == 3){return 31;}
    else if(monthNum == 4){return 30;}
    else if(monthNum == 5){return 31;}
    else if(monthNum == 6){return 30;}
    else if(monthNum == 7){return 31;}
    else if(monthNum == 8){return 31;}
    else if(monthNum == 9){return 30;}
    else if(monthNum == 10){return 31;}
    else if(monthNum == 11){return 30;}
    else if(monthNum == 12){return 31;}

}

