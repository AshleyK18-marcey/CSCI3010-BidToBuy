// Name: Tyler Scripps, Ashley Kastler

#include "Driver.h"

/*
To run the program run make, then execute the resulting "main" file
When prompted enter a name identical to one in the runtime_data/user.csv file
whenever a leter is in parenthesis that letter is a valid command for the current prompt.
*/

int main() {
    // Driver &mainDriver = Driver::GetInstance();
    Driver * mainDriver = Driver::GetInstance();

    while(mainDriver->IsRunning()) {
        mainDriver->MainLoop();
    }
    
   
}