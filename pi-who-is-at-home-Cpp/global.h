#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <string>
#define MAXREGISTERS 100
#define MAXARPSCAN 100
#define MAXNEWDEVICES 100

//Configuration variables
static const int exitApp = -1984;

struct users_structure {
    std::string id;
    std::string name;
    std::string model;
    std::string mac;
    std::string lastAccess;
};

struct arpscan_structure {
    std::string ip;
    std::string mac;
    std::string macVendor;
};

struct newDevices_structure {
    std::string ip;
    std::string mac;
    std::string macVendor;
    int timesSeen;
    std::string firstSeenDate;
    std::string lastSeenDate;
};

int addNewDeviceToNewDevicesStructure(std::string ip, std::string mac, std::string macVendor);
int addRegisterToMyEquipamentsStructure();
int listMyEquipments();
int deleteMyEquipment();
int listArpScanLog();
#endif
