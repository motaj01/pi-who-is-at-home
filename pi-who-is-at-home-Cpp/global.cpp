/*
 * global.cpp
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
#include "util.h"
#include "global.h"

using namespace std;

users_structure myEquipments[MAXREGISTERS];
arpscan_structure scanEquipments[MAXARPSCAN];
newDevices_structure newDevices[MAXNEWDEVICES];

/*
 * 
 * name: addRegisterToMyEquipamentsStructure
 * @param
 * the function ask for name, model and mac
 * @return
 * add a new device to your devices structure users_structure
 */
int addRegisterToMyEquipamentsStructure() {
    string name;
    string model;
    string mac;

    cout << "\nName:";
    //clean keyboard buffer
    getchar();
    //reads keyboard until enter key pressed
    cin >> name;
    cout << "\nModel:";
    //clean keyboard buffer
    getchar();
    //reads keyboard until enter key pressed
    cin >> model;
    cout << "\nMAC:";
    getchar(); //clean keyboard buffer
    cin >> mac;
    getchar();
    for (int i=0; i<MAXREGISTERS; i++) {
        if(myEquipments[i].id.compare("\0")==0) {
            myEquipments[i].id = to_string(i+1);
            myEquipments[i].name = name;
            myEquipments[i].model = model;
            myEquipments[i].mac = mac;
            myEquipments[i].lastAccess = getTime();
            cout << "\nUser Added\n";
            i = MAXREGISTERS;
        }
    }
    return 0;
}

/*
 * 
 * name: listMyEquipments
 * @param
 * uses structure users_structure 
 * @return
 * writes to the screen all the equipements from file and added, modified or deleted registers
 */
int listMyEquipments() {
    cout << "\nList My Equipments\n" << endl;
    for (int i=0; i<MAXREGISTERS; i++) {
        if(myEquipments[i].id.compare("\0")!=0) {
            cout << "ID: " << myEquipments[i].id << endl;
            cout << "Name: " << myEquipments[i].name << endl;
            cout << "Model: " << myEquipments[i].model << endl;
            cout << "MAC: " << myEquipments[i].mac << endl;
            cout << "Last Access: " << myEquipments[i].lastAccess << endl;
            printf ("\n");
        }
    }
    return 0;
}

/*
 * 
 * name: listArpScanLog
 * @param
 * uses arpscan_structure
 * @return
 * list all new devices found on the network scan 
 */
int listArpScanLog() {
    cout << "\nList Arp Scan Log\n" << endl;
    for (int i=0; i<MAXARPSCAN; i++) {
        if(scanEquipments[i].ip.compare("\0")!=0) {
            //read the first line of the file
            cout << "IP: " << scanEquipments[i].ip << endl;
            //read the second line of the file
            cout << "MAC: " << scanEquipments[i].mac << endl;
            //read the third line of the file
            cout << "MAC Vendor: " << scanEquipments[i].macVendor << "\n" << endl;
        }
    }
    return 0;
}

/*
 * 
 * name: deleteMyEquipment
 * @param
 * uses users_structure
 * ask for a device id or name
 * @return
 * if found remove the device 
 */
int deleteMyEquipment() {
    printf ("\nInsert ID or Name to detele:");
    string idOrName;
    bool found = false;
    cin >> idOrName;
    for (int i=0; i<MAXREGISTERS; i++) {
        if(idOrName.compare(myEquipments[i].id)==0 || idOrName.compare(myEquipments[i].name)==0) {
            myEquipments[i].id = "\0";
            myEquipments[i].name = "\0";
            myEquipments[i].model = "\0";
            myEquipments[i].mac = "\0";
            myEquipments[i].lastAccess = "\0";
            cout << "\nDeleted " << idOrName << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "\nnot found " << idOrName << endl;
    }
    return 0;
}

/*
 * 
 * name: addNewDeviceToNewDevicesStructure
 * @param
 * uses newDevices_structure
 * string ip of the device
 * string mac mac address of the device
 * string macVendor vender name of the device
 * @return
 * add to the structure if found a new device or update if already exist
 */
int addNewDeviceToNewDevicesStructure(string ip, string mac, string macVendor) {

    for (int i=0; i<MAXNEWDEVICES; i++) { //check if the new device was already detected
        if(newDevices[i].mac.compare(mac)==0) { //if already exist updated it
            newDevices[i].ip = ip;
            newDevices[i].mac = mac;
            newDevices[i].macVendor = macVendor;
            newDevices[i].timesSeen = newDevices[i].timesSeen + 1;
            //newDevices[i].firstSeenDate = getTime(); its an update should update the first time seen
            newDevices[i].lastSeenDate = getTime();
            cout << "\nNew Device Updated\n";
            return 0;
        }
    }

    for (int i=0; i<MAXNEWDEVICES; i++) { //if newdevice was not found above insert here

        if(newDevices[i].mac.compare("\0")==0) { //find empty register
            newDevices[i].ip = ip;
            newDevices[i].mac = mac;
            newDevices[i].macVendor = macVendor;
            newDevices[i].timesSeen = newDevices[i].timesSeen + 1;
            newDevices[i].firstSeenDate = getTime();
            newDevices[i].lastSeenDate = getTime();
            cout << "\nNew Device Added\n";
            return 1;
        }
    }
    return 0;
}

