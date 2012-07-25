#include <string>
#ifndef CONFIGCHIPSET_H
#define CONFIGCHIPSET_H
using namespace std;

class ConfigChipset
{
    string amiga_model;
    string kickstart_file;
    string kickstart_ext_file;
    string accuracy;
    string ntsc_mode;


public:
    ConfigChipset();
    void setAccuracy(bool least,bool normal,bool most);
    string getAccuracyString();
};

#endif // CONFIGCHIPSET_H
