/*
 * sendEmail.cpp
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

using namespace std;

/*
 * 
 * name: sendEmail
 * @param
 * needs external application to send the email MSMTP and mailutils
 * sudo apt-get install msmtp msmtp-mta
 * sudo apt install mailutils
 * @return
 * sends an email to the defined hard coded email, should be reviewed on the next version
 */
int sendEmail() {

    string destinationEmail, emailSubject, emailBody, file;
    //getchar();

    /*
    cout << "\nDestination Email: ";
    getline (std::cin,destinationEmail);
    cout << "\nSubject: ";
    getline (std::cin,emailSubject);
    cout << "\nBody: ";
    getline (std::cin,emailBody);
    cout << "\n\n";
    */

    destinationEmail = "example@example.com";
    emailSubject = "Pi WhosHere New Devices Alert";
    emailBody = "";
    file = "newEquipments.txt";

    stringstream ss;

    //send email with body text but without attach file. its not possible to send body text and attach file
    //ss << "echo '" << emailBody << "' | mail -s '" << emailSubject << "' " <<  destinationEmail;

    //send email with attached file
    ss << "echo | mail -s '" << emailSubject << "' --attach=" << file << " " <<  destinationEmail;

    //cout << ss.str().c_str() << endl;

    system(ss.str().c_str());

    return 0;
}

