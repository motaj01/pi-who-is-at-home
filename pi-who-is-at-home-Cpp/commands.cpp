/*
 * commands.cpp
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
#include "global.h"
#include "filecontrol.h"
#include "util.h"
#include "sendEmail.h"

using namespace std;

string comando;

int commandsWithoutAuthentication() {//to be implemented, some commands can be acessed without authentication
    return 0;
}

/*
 * 
 * name: administrator
 * function for commands allowed for admins
 * @param
 * it ask for a command if exist execute if not does nothing
 * @return
 * call the function to execute the command that you choose
 */
int administrator() {
    do {
        cout << "@prompt>:";
        cin >> comando;
        if(comando.compare("exit")==0) { //exit command end application
            return exitApp;
        }
        if(comando.compare("add")==0) { //command add new equipment to myEquipments.txt
            addRegisterToMyEquipamentsStructure();
        }
        if(comando.compare("del")==0) { //command del equipment that exists on myEquipments.txt or all that you add or change during the execution
            deleteMyEquipment();
        }
        if(comando.compare("list")==0) { //command list equipments that are on myEquipments.txt and all that you del or change during the execution
            listMyEquipments();
        }
        if(comando.compare("log")==0) { //comand log that show the network scan logs that are in scanEquipments.txt
            listArpScanLog();
        }
        if(comando.compare("mail")==0) { //command send email
            sendEmail();
        }
        if(comando.compare("sys")==0) { //comand to see my system info
            getSystemInfo();
        }
    } while (comando.compare("logout") !=0); //comand logout keep the application running asking for credentials
    system("clear");
    printf ("\nEND SESSION\n");
    //when logout it doesnt save to file the new registers that you add or del during the execution
    //something to work in the next version
    return 0;
}


/*
 * 
 * name: command
 * @param
 * bool to control if need authentication if not only allow commands without authentication
 * @return
 * goes to the function depending if you authenticate or not
 */
int command(bool commandRequiresAuthentication) { //can implement authorized commands depending on the authentication
    if(commandRequiresAuthentication) {
        return administrator();
    } else {
        return commandsWithoutAuthentication();
    }
    return 0;
}
