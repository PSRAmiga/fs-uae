/**
* \class ConfigCdRom
* This class is responsible for the Cd-Rom Configuration
*/
#ifndef CONFIGCDROM_H
#define CONFIGCDROM_H
#include <vector>
#include <string>
using namespace std;

class ConfigCDRom
{
    string cdrom_drive_0;      ///< You specify paths for floppy images in floppy_drive_0.
    vector<string> cdrom_image;
public:
    ConfigCDRom();

    string getCDRomDrive0ConfigString();       ///< Represents the string of floppy_drive_0 to be written in Config File.\n floppy_drive_0 = path/to/adt_or_ipf
    string getCDRomDrive0String();             ///< Represent the effective value of floppy_drive_0.

    int getCDRomImageSize();
    string getCDRomImageAt(int position);
    void pushBackCDRomImage(string s);
    void erasCDRomImageAt(int position);

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGCDROM_H
