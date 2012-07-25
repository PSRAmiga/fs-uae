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
    string getAccuracyConfigString();
    string getAccuracyString();
    string getNTSCModeConfigString();
    string getNTSCModeString();
    string getAmigaModelConfigString();
    string getAmigaModelString();
    string getKickstartFileConfigString();
    string getKickstartFileString();
    string getKickstartExtFileConfigString();
    string getKickstartExtFileString();

    void setParameter(string parameter,string value);
    void setToDefaultConfiguration();
    //void updateGraphicsFromInternalConfiguration(Amiga amiga);
};

#endif // CONFIGCHIPSET_H
