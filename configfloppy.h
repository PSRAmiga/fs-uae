#ifndef CONFIGFLOPPY_H
#define CONFIGFLOPPY_H
#include <vector>
#include <string>
using namespace std;

class ConfigFloppy
{
    string floppy_drive_0;
    string floppy_drive_1;
    string floppy_drive_2;
    string floppy_drive_3;
    vector<string> floppy_image;
    string floppy_drive_volume;
    string floppy_drive_speed;

public:
    ConfigFloppy();

    string getFloppyDrive0ConfigString();
    string getFloppyDrive0String();
    string getFloppyDrive1ConfigString();
    string getFloppyDrive1String();
    string getFloppyDrive2ConfigString();
    string getFloppyDrive2String();
    string getFloppyDrive3ConfigString();
    string getFloppyDrive3String();
    string getFloppyDriveVolumeConfigString();
    string getFloppyDriveVolumeString();
    string getFloppyDriveSpeedConfigString();
    string getFloppyDriveSpeedString();

    int getFloppyImageSize();
    string getFloppyImageAt(int position);
    void pushBackFloppyImage(string s);
    void eraseFloppyImageAt(int position);


    void setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGFLOPPY_H
