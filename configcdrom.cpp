#include "configcdrom.h"

const string DEFAULTCDROMEDRIVE0 = "";

ConfigCDRom::ConfigCDRom()
{
    setToDefaultConfiguration();
}

string ConfigCDRom::getCDRomDrive0ConfigString()
{
    if (cdrom_drive_0.compare(DEFAULTCDROMEDRIVE0)==0){return "";}
    else {return "cdrom_drive_0 = " + cdrom_drive_0;}
}

string ConfigCDRom::getCDRomDrive0String()
{
    return cdrom_drive_0;
}

int ConfigCDRom::getCDRomImageSize()
{
    return cdrom_image.size();
}

string ConfigCDRom::getCDRomImageAt(int position)
{
    if (position>=cdrom_image.size()){return "";}
    return cdrom_image.at(position);
}

void ConfigCDRom::pushBackCDRomImage(string s)
{
    cdrom_image.push_back(s);
}

void ConfigCDRom::erasCDRomImageAt(int position)
{
    if (position>=cdrom_image.size()){return;}
    cdrom_image.erase(cdrom_image.begin()+ position);
}

void ConfigCDRom::setParameter(string parameter, string value)
{
    if(parameter.compare("cdrom_drive_0")==0){
        cdrom_drive_0=value;
    } else if((parameter.substr(0,parameter.length()-1).compare("cdrom_image")==0 || parameter.substr(0,parameter.length()-2).compare("cdrom_image")==0)&& cdrom_image.size()<20){
        cdrom_image.push_back(value);
    }
}

void ConfigCDRom::setToDefaultConfiguration()
{
    cdrom_drive_0=DEFAULTCDROMEDRIVE0;
    cdrom_image.clear();
}
