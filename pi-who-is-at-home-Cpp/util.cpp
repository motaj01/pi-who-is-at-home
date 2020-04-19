/*
 * util.cpp
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
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <sys/utsname.h>

using namespace std;

/*
 *
 * name: getTime
 * @param
 * none
 * @return
 * return a string with the curretn date|time on the followig format year-month-day|hour:minutes - example ->  2020-04-19|17:19
 */
string getTime() {
    time_t now;
    time (&now);
    struct tm * timeinfo;
    timeinfo = localtime (&now);
    char theDateTime[20];
    strftime (theDateTime,sizeof(theDateTime),"%F|%R",timeinfo);
    return theDateTime;
}

/*
 *
 * name: sleepWithFeedback
 * @param
 * string with the text that you want to show while the user is waiting
 * int with the number of seconds that you want the user waits until continue to the execution
 * @return
 * nothing
 */
void sleepWithFeedback(string text, int seconds) {
    for (int i = 0; i < seconds; i++) {
        cout << text << seconds - i << endl;
        sleep(1);
    }
}

/*
 *
 * name: sleepOneTimeFeedback
 * it clear the previous information to the user and show the new one
 * @param
 * string with the text that you want to show while the user is waiting
 * int with the number of seconds that you want the user waits until continue to the execution
 * @return
 * nothing
 */
void sleepOneTimeFeedback(string text, int seconds) {
    for (int i = 0; i < seconds; i++) {
        system("clear");
        cout << text << seconds - i << endl;
        sleep(1);
    }
}


/*
 *
 * name: getSystemInfo
 * @param
 * none
 * @return
 * writes to the screen the version info of the RPI or Linux
 * doesnt works on Windows
 */
void getSystemInfo() {
    struct utsname uname_pointer;
    uname(&uname_pointer);
    cout << "\nSystem name - " << uname_pointer.sysname << "\n";
    cout << "Nodename    - " << uname_pointer.nodename << "\n";
    cout << "Release     - " << uname_pointer.release << "\n";
    cout << "Version     - " << uname_pointer.version << "\n";
    cout << "Machine     - " << uname_pointer.machine << "\n";
    cout << "Domain name - " << uname_pointer.domainname << "\n" << endl;
}
