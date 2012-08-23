/**
* \class ConfigCDRom
*/
#ifndef CONFIGCDROM_H
#define CONFIGCDROM_H
#include <vector>
#include <string>
using namespace std;
/** \brief On the success of the A500, Commodore launches in the production of alternative projects,
* that are based on the Amiga. The "CDTV", of 1990, is designed as a household appliance for multimedia entertainment,
* and is basically an A500 with a CD-Rom, in a chassis similar to that of a VCR. \n
* The intention of the Commodore, the CDTV must implement the convergence of television and computers,
* allowing the user to play games, watch movies and listen to music with the same equipment,
* the most advanced user can then expand the purchasing CDTV keyboard, floppy disk drives,
* and mouse and turn it into an actual computer.\n
* AmigaCD32 (1993), is instead a console dedicated to video games, equipped with 68020 processor with 32-bit
* architecture and is based on the use of a CD-Rom integrated. \n \n
* This class is responsible for the Cd-Rom Configuration management. */
/** In this class are defined all the variables for the correct management
 * of CDROM configuration's tab.\n
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
