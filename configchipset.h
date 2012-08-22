/**
* \class ConfigChipset
*/
#include <string>
#ifndef CONFIGCHIPSET_H
#define CONFIGCHIPSET_H
using namespace std;
/// This class is responsible for the Chipset Configuration.
/** In this class are defined all the variables for the correct management
 * of chipset configuration's tab.\n
 * In this tab, you can choose the type of model you want to emulate FS-UAE (A500, A500+,...,CDTV),
 * the paths for the kickstart and extended kickstart.\n
 * You can also select the emulation accuracy, the refresh rate of the video (50 Hz PAL or 60 Hz NTSC)
 * and the various types of RAM mountable.\n
 * The extended kickstart path explorer is only permitted if the Amiga model selected si CDTV or CD32.\n
 * In all other cases the Cd-Rom Configuration tabs appears disabled.
*/
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
