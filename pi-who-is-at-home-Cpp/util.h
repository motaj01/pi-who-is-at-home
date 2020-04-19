#ifndef _UTIL_H_
#define _UTIL_H_
#include <string>
std::string getTime();
void sleepWithFeedback(std::string text, int seconds);
void sleepOneTimeFeedback(std::string text, int seconds);
void getSystemInfo();
#endif
