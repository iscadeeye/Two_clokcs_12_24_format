/*
 * @Author Mohamed Hassan
 * @Date 09/17/2022
 *
 * This project display two clocks, one 12 hour format
 * and one with military time
 */

#include <iostream>
# include <ctime>
# include <string>


using namespace std;

//global variables

int userOption;
int hours;
int minutes;
int seconds;


//menu instructions.
char const* menuItem[] = { "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };
//adds 0 if n < 10;
string twoDigitString(unsigned int n) {

    string formatTwoDigit;
    formatTwoDigit = (n >= 10 && n <= 59) ? to_string(n) : "0" + to_string(n);
    //return formatted string digits.
    return formatTwoDigit;
}


//generate asterisks or spaces depending on the character  passed in.
string nCharString(size_t numOfChars, char characters) {
    string asterisksOrSpace;
    for (unsigned int i = 0; i < numOfChars; ++i) {
        asterisksOrSpace += characters;
    }
    return asterisksOrSpace;//return asterisks or spaces.
}


//Format 24 hour
string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
    //returns hour in  military format.
    return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s);
}

//Format 12 hour
string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
    unsigned int hour;
    //if h greater or equal 12  amOrPm is assigned PM or AM otherwise.
    string amOrPm = (h >= 12) ? "P M" : "A M";
    if (h > 12) {
        hour = h - 12;
    }
    else {
        hour = h;
    }
    //checks midnight since machine's local time is always 24 format
    if (h == 0) {
        //midnight
        hour = 12;
    }
    //returns formatted 12 hour
    return (twoDigitString(hour) + ":" + twoDigitString(m) + ":" + twoDigitString(s) + " " + amOrPm);
}
//menu printer
void printMenu(char* strings[], unsigned int numStrings, unsigned int width) {
    int const LENGTH_BEFORE_ITEM = 7;//the length of characters before menu item in the cout.
    string currItem; //instruction menu item (i.e Add One Hour)

    //cout asterisks equal to width's width before loop.
    cout << nCharString(width, '*') << endl;

    for (unsigned int index = 0; index < numStrings; ++index) {

        currItem = strings[index]; //
        // used index + 1 as the menu item number.
        cout << "* " << index + 1 << " - " << currItem
            << nCharString(width - (currItem.length() + LENGTH_BEFORE_ITEM), ' ') << '*' << endl;
    }
    //cout asterisks equal to width's width after loop.
    cout << nCharString(width, '*') << endl;
}
//display two clocks.
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {

    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
    cout << '*' << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << '*' << nCharString(3, ' ');
    cout << '*' << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << '*' << endl;

    //cout a blank line to separate hour's title from the actual hour.
    cout << endl;
    //display hours, formatted in 12 and 24
    cout << '*' << nCharString(6, ' ') << formatTime12(h, m, s) << nCharString(7, ' ') << '*' << nCharString(3, ' ');
    cout << '*' << nCharString(8, ' ') << formatTime24(h, m, s) << nCharString(9, ' ') << '*' << endl;
    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
}


//adds one hour
void addOneHour() {
    hours = (hours == 23) ? 0 : hours += 1;
}

//adds one minute
void addOneMinutes() {
    if (minutes == 59) {
        minutes = 0;
        addOneHour();
    }
    else {
        minutes += 1;
    }
}
//add one second
void addOneSecond() {
    if (seconds == 59) {
        seconds = 0;
        addOneMinutes();
    }
    else {
        seconds += 1;
    }
}

//handle user's input.
int getMenuChoice() {
    int option;
    cout << "Make selection or enter 4 to quit the program\n";
    cin >> option;
    return option;
}


/**
 * repeats getting the user's choice and taking
 * the appropriate action until the user chooses 4 for exit
 */
int   main() {


    //construct time
    time_t elapsedSeconds = time(nullptr);
    tm* time_struct = localtime(&elapsedSeconds);

    // Initialize hours, minutes, and seconds variables with the current local time respectively
    hours = time_struct->tm_hour;
    minutes = time_struct->tm_min;
    seconds = time_struct->tm_sec;

    //Display instructions menu the first time user runs the program.
    printMenu(const_cast<char**>(menuItem), size(menuItem), 26);
    // And display the two clocks 
    displayClocks(hours, minutes, seconds);




  
    userOption = getMenuChoice(); // Get menu option 

    //repeats untill user enters 4. entering number (4) stops the program.
    while (userOption != 4) {
        if (userOption == 1) {
            addOneHour();
        }
        else if (userOption == 2) {
            addOneMinutes();
        }
        else if (userOption == 3) {
            addOneSecond();
        }
        else {
            cout << "Invalid input\n";
            break;
        }
     
        // Call display clock function to reflect the updated hours, minutes or seconds.
        displayClocks(hours, minutes, seconds);
        
        //Display menu instructions.
        printMenu(const_cast<char**>(menuItem), size(menuItem), 26);
        //And get menu option again and again until user enters 4.
        userOption = getMenuChoice();
    }

    return 0;
}