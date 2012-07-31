/** \class ConfigFloppy
* This class is responsible for the Floppy Configuration.\n
*/
#ifndef CONFIGFLOPPY_H
#define CONFIGFLOPPY_H
#include <vector>
#include <string>
using namespace std;
/// Create the Floppy Configuration Class
class ConfigFloppy
{

    //FARE UN VETTORE DA 4 ELEMENTI (anche nel CD)
    /*
    string floppy_drive_0;      ///< You specify paths for floppy images in floppy_drive_0.
    string floppy_drive_1;      ///< You specify paths for floppy images in floppy_drive_1 [opt].
    string floppy_drive_2;      ///< You specify paths for floppy images in floppy_drive_2 [opt].
    string floppy_drive_3;      ///< You specify paths for floppy images in floppy_drive_3 [opt].
    */
    string floppy_drive[4];
    vector<string> floppy_image;///< In order to enable floppy­swapping, you must list all floppy images which is to appear in the floppy list.\nYou can use floppy_image_0, floppy_image_1, floppy_image_2, and so on.
    string floppy_drive_volume; ///< Set volume to 0 to disable floppy drive sounds. Max volume is 100. The default value is 20.
    string floppy_drive_speed;  ///< Set the speed of the emulated floppy drives, in percent. The default is 100.\nFor example, you can specify 800 to get an 8x increase in speed. Use 0 to specify turbo mode.


public:
    ConfigFloppy();

    /*
    string getFloppyDrive0ConfigString();       ///< Represents the string of floppy_drive_0 to be written in Config File.\n floppy_drive_0 = path/to/adt_or_ipf
    string getFloppyDrive0String();             ///< Represent the effective value of floppy_drive_0.
    string getFloppyDrive1ConfigString();       ///< Represents the string of floppy_drive_1 to be written in Config File.\n floppy_drive_1 = path/to/adt_or_ipf
    string getFloppyDrive1String();             ///< Represent the effective value of floppy_drive_1.
    string getFloppyDrive2ConfigString();       ///< Represents the string of floppy_drive_2 to be written in Config File.\n floppy_drive_2 = path/to/adt_or_ipf
    string getFloppyDrive2String();             ///< Represent the effective value of floppy_drive_2.
    string getFloppyDrive3ConfigString();       ///< Represents the string of floppy_drive_3 to be written in Config File.\n floppy_drive_3 = path/to/adt_or_ipf
    string getFloppyDrive3String();             ///< Represent the effective value of floppy_drive_3.
    */

    string getFloppyDriveConfigStringAt(int i);
    string getFloppyDriveStringAt(int i);
    string getFloppyDriveVolumeConfigString();  ///< Represents the string of floppy_drive_volume to be written in Config File. If floppy_drive_volume is the default value, it returns an empty string.\n floppy_drive_volume = 20
    string getFloppyDriveVolumeString();        ///< Represent the effective value of floppy_drive_volume.
    string getFloppyDriveSpeedConfigString();   ///< Represents the string of floppy_drive_speed to be written in Config File. If floppy_drive_speed is the default value [100], it returns an empty string.\n floppy_drive_speed = 100
    string getFloppyDriveSpeedString();

    int getFloppyImageSize();
    string getFloppyImageAt(int position);
    void pushBackFloppyImage(string s);
    void eraseFloppyImageAt(int position);


    void setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGFLOPPY_H
