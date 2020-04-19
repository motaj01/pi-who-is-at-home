/*
 * Pi Who Is At Home
 *
 * main.cpp
 *
 * Copyright 2020  <hello@digitalwb.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include "commands.h"
#include "networkDevices.h"
#include "filecontrol.h"
#include "authentication.h"
#include "global.h"
#include "util.h"

using namespace std;

/*
*
* name: main
* @param
*  can receive argument "scan" this scan the network
* "scan" will scan one time your network for devices not in myEquipament.txt
* "scan <number>" will scan our network the number of times you insert. If 0 inserted it will be unlimited until you press Ctrl-C
* For other commands check commands.cpp
* @return
* return int 0 if application ends with no errors found
*/
int main(int argc, char* argv[])
{
    double version = 1.1;
    cout << "----VERSION " << version << "----\n";
    cout << "PI Who is at Home\n";
    cout << "Made by: Digital WB\n";
    cout << "hello@digitalwb.com\n";
    cout << "-------------------\n";

    myEquipmentsFileToStructure(); //read myEquipments.txt to a structure check filecontrol.cpp more details

    if (argc == 1) {
        whosHere();// it must do at least a scan. Scan network, more details check networkDevices.cpp
        int code; //loop until this variable code equal to variable exitApp
        do {
            if(authenticate() == 0) { //function that ask for credentials more details check authentication.cpp
                cout << "\n\n--WELCOME--\n" << endl;
                code = command(true);//function check commands that user write, more details check commands.cpp
            } else {
                cout << "\n\n--Incorrect Username or Password--" << endl;
            }
        } while (code != exitApp); //execute until user write command logout global variables on global.h
        system("clear"); //clear all text on the screen
        cout << "\n--END OF APPLICATION--\n" << endl;
    } else if (argc == 2) {
        string argument = argv[1];
        if (argument.compare("scan")==0) {
            whosHere();//scan network, more details check networkDevices.c
        } else {
            cout << "\nUnknow Command!\n" << endl;;
            return 0;
        }
    } else if(argc == 3) {
        string argument = argv[1];
        if (argument.compare("scan")==0) {
            istringstream in(argv[2]);
            int i;
            if (in >> i && in.eof()) { //if its a int number continue
                if (i == 0) { //if zero do it for ever until Ctrl + C to break
                    do { //only breaks with Ctrl+C
                        whosHere();//scan network, more details check networkDevices.cpp
                        sleepOneTimeFeedback("Next network search will be in: ",3600); //wait 1 hour until next search on network
                    } while(true);
                } else {//execute the number of time inserted in command line
                    for (int j=1; j<=i; j++) {
                        whosHere();//scan network, more details check networkDevices.cpp
                        sleepOneTimeFeedback("Next network search will be in: ",3600);
                    }
                }
            } else {
                cout << "\nUnknow Command!\n" << endl;;
                return 0;
            }
        }
    } else if(argc > 3) {
        cout << "\nUnknow Command!\n" << endl;;
        return 0;
    }
    return saveStructureToMyEquipmentsFile(); //save the structure to myEquipments.txt file
}
