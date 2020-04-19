/*
 * networkDevices.cpp
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
#include <thread>
#include "util.h"
#include "global.h"
#include "filecontrol.h"
#include "sendEmail.h"

using namespace std;

extern users_structure myEquipments[MAXREGISTERS];
extern arpscan_structure scanEquipments[MAXREGISTERS];

/*
 *
 * name: executeSystemArpScanCommand
 * @param
 * you need an external application plase install arp-scan
 * sudo apt-get install arp-scan
 * @return
 * save to file devices found during the network scan
 */
void executeSystemArpScanCommand() {
    //command that search for a specific MAC address and save the result to txt
    //sudo arp-scan -l -x -T 04:cf:8c:d2:2f:48 >> results.txt
    //command that search on the network for all MAC address available and saves to file txt
    //this command doesnt overwrite, just add more lines
    //system("sudo arp-scan -l -x >> arpscanlog.txt");
    //write to a text file if exist overwrite
    system("sudo arp-scan -l -x > scanEquipments.txt");
}

/*
 *
 * name: findNewDevicesAndSaveToFile
 * @param
 * uses global defined structures arpscan_structure and users_structure
 * @return
 * if some device is found for the first time it sends an email with attached file of all new devices
 * also updates the structures data like date last seen device
 */
int findNewDevicesAndSaveToFile() {

    int deviceScanId;
    bool newDevice;
    bool anyNewDeviceFound = false;

    for (int i =0 ; i<MAXARPSCAN; i++) {
        deviceScanId = i;
        newDevice = true;
        if(scanEquipments[i].mac.compare("\0")!=0) {
            for (int j =0 ; j<MAXREGISTERS; j++) {

                if(myEquipments[j].mac.compare("\0")!=0) {
                    if(scanEquipments[i].mac.compare(myEquipments[j].mac)==0) {
                        newDevice = false;
                        //device found update date
                        myEquipments[j].lastAccess=getTime();
                    }
                }
            }

            if(newDevice) {
                anyNewDeviceFound = true;
                //found a MAC device that doesnt exist in registers
                cout << "\nUnknown DeviceFound IP: -> " << scanEquipments[deviceScanId].ip << endl;
                cout << "Unknown Device Found MAC -> " << scanEquipments[deviceScanId].mac << endl;
                cout << "Unknown Device Found Vendor -> " << scanEquipments[deviceScanId].macVendor << "\n" << endl;

                //open file new devices if exist and load to newDevice registers
                //add or update device found
                newDevicesFileToStructure();

                int send;

                send = addNewDeviceToNewDevicesStructure(scanEquipments[deviceScanId].ip, scanEquipments[deviceScanId].mac, scanEquipments[deviceScanId].macVendor);

                //save to file
                saveStructureToNewDevicesFile();

                if(send == 1) { //if the new device is the first time found send email alarm
                    //send alert email
                    sendEmail();
                }

            }
        }
    }

    if(!anyNewDeviceFound) {
        //no devices found
        printf("\n----------------------\n");
        printf("\nNew devices not found\n");
        printf("\n----------------------\n");
    }

    return 0;
}

/*
 *
 * name: whosHere
 * @param
 * uses networkDevices.cpp to scan the network
 * also uses thread to give feedback to the user while the function search your network
 * @return
 * saves to file, reads the file to the structure and try to find new devices
 */
int whosHere() {
    //printf("Before Thread\n");
    //starting the thread
    thread t1(executeSystemArpScanCommand);

    //put some interaction while wait for the thread to finish
    //Or I can put a simple text saying that is searching
    sleepWithFeedback("Scanning Network: ",10);

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
    //printf("After Thread\n");

    //get the data from the file to structure
    scanEquipmentsFileToStructure();

    /*
    std::cout << "scanEquipments[0].ip " << scanEquipments[0].ip << "\n";
    std::cout << "scanEquipments[0].mac " << scanEquipments[0].mac << "\n";
    std::cout << "scanEquipments[0].macVendor " << scanEquipments[0].macVendor << "\n";
    std::cout << "scanEquipments[1].ip " << scanEquipments[1].ip << "\n";
    */
    /*
    std::cout << "myEquipments[0].ip " << myEquipments[0].id << "\n";
    std::cout << "myEquipments[0].name " << myEquipments[0].name << "\n";
    std::cout << "myEquipments[0].model " << myEquipments[0].model << "\n";
    std::cout << "myEquipments[0].mac " << myEquipments[0].mac << "\n";
    std::cout << "myEquipments[0].lastAccess " << myEquipments[0].lastAccess << "\n";
    */
    findNewDevicesAndSaveToFile();
    return 0;
}
