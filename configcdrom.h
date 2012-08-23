/**
* \class ConfigCDRom
*/
#ifndef CONFIGCDROM_H
#define CONFIGCDROM_H
#include <vector>
#include <string>
using namespace std;

/// This class is responsible for the Cd-Rom Configuration management.
/** In this class are are stored all the variables for CDROM configuration.\n
 * The use of the Cd-Rom is only permitted if the Amiga model selected si CDTV or CD32.\n
 * In all other cases the Cd-Rom Configuration tabs appears disabled.
*/
class ConfigCDRom
{
    string cdrom_drive_0;      ///< You specify paths for CD-ROM images in cdrom_drive_0.
    vector<string> cdrom_image;
public:
    ConfigCDRom();

    /** CUE/BIN and ISO images are supported.\n cdrom_drive_0 = path/to/cue_or_bin */
    string getCDRomDrive0ConfigString();       ///< Represents the string of cdrom_drive_0 to be written in Config File.
    string getCDRomDrive0String();             ///< Represent the effective value of cdrom_drive_0.

    int getCDRomImageSize();                   ///< Represent the image of a CD-Rom.
    string getCDRomImageAt(int position);      ///< Represent the position of a CD-Rom Image.
    void pushBackCDRomImage(string s);
    void erasCDRomImageAt(int position);

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
    bool hasParameter(string parameterName);
};

#endif // CONFIGCDROM_H
