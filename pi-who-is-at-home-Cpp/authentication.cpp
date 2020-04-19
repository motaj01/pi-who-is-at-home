/*
 * authentication.cpp
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

using namespace std;

/*
 * 
 * name: authenticateInternal
 * @param
 * receive two strings as user and pass and compare if its correct
 * this function can be expanded because now its very simple/unsecure user and password hard coded :-P
 * @return
 * return int 1 if incorrect user
 * return -1 if incorrect password
 * return 0 if user and password are correct
 */
int authenticateInternal(string user,string pass) {
    if (user.compare("admin")!=0) {
        return 1;
    } else if (pass.compare("admin")!=0) {
        return -1;
    }
    return 0;
}

/*
 * 
 * name: authenticate
 * @param
 * @return
 * authenticate()
 * available to call external without any arguments. Because internally it takes care of that
 */
int authenticate() {

    //skip authentication
    //remove this return when implementation of commands end
    //return 0;

    string username;
    string password;

    printf ("\nLogin\n");
    printf ("\nUsername: ");
    cin >> username;
    printf ("Password: ");
    //command to hide password caracters
    system("stty -echo");
    cin >> password;
    //command to show again caracters
    system("stty echo");
    return authenticateInternal(username,password);
}
