/**
* \class ConfigChipset
* This class is responsible for the Chipset Configuration
*/
#include <string>
#ifndef CONFIGCHIPSET_H
#define CONFIGCHIPSET_H
using namespace std;
/// Create the Chipset Configuration Class
class ConfigChipset			  
{
    string amiga_model;          ///< Specify the Amiga model you want to emulate.
    string kickstart_file;       ///< Specify the path to a specific kickstart file.
    string kickstart_ext_file;   ///< Specify the path to the extended kickstart ROM (for CD32, ...).
    string accuracy;             ///< Represet the accuracy of the emulation
    string ntsc_mode;            ///< Represent the video mode of the emulation (NTSC/PAL)


public:
    ConfigChipset();
    string getAccuracyConfigString();           ///< Represents the string of Accuracy to be written in Config File. If Accuracy is the default value, it returns an empty string.\n accuracy = 1
    string getAccuracyString();                 ///< Represent the effective value of Accuracy
    string getNTSCModeConfigString();           ///< Represents the string of NTSCMode to be written in Config file. If NTSCMode is the default value, it returns an empty string.\n ntsc_mode = 0
    string getNTSCModeString();                 ///< Represent the effective value of NTSCMode
    string getAmigaModelConfigString();         ///< Represents the string of AmigaModel to be written in Config file. If AmigaModel is the default value, it returns an empty string.\n amiga_model = A500
    string getAmigaModelString();               ///< Represent the effective value of AmigaModel
    string getKickstartFileConfigString();      ///< Represents the string of KickstartFile to be written in Config file. If KickstartFile is the default value, it returns an empty string.\n kickstart_file = path/to/kickstart.rom [or path/to/kickstart.adf]
    string getKickstartFileString();            ///< Represent the effective value of KickstartFile
    string getKickstartExtFileConfigString();	///< Represents the string of KickstartExtFile to be written in Config file. If KickstartExtFile is the default value, it returns an empty string.\n kickstart_ext_file = path/to/extended-kickstart.rom
    string getKickstartExtFileString(); 		///< Represent the effective value of KickstartExtFile

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
    bool hasParameter(string parameterName);
};

#endif // CONFIGCHIPSET_H
