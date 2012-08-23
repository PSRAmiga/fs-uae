/*! \file configcdrom.cpp
 configcdrom.cpp

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 Written by Riva Alessandro Mario, alessandromario.riva@gmail.com
 and Sanvito Davide, dsanvito90@gmail.com. */
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
    if (position>=(int)cdrom_image.size()){return "";}
    return cdrom_image.at(position);
}

void ConfigCDRom::pushBackCDRomImage(string s)
{
    cdrom_image.push_back(s);
}

void ConfigCDRom::eraseCDRomImageAt(int position)
{
    if (position>=(int)cdrom_image.size()){return;}
    cdrom_image.erase(cdrom_image.begin()+ position);
}

int ConfigCDRom::setParameter(string parameter, string value)
{
    if(parameter.compare("cdrom_drive_0")==0){
        cdrom_drive_0=value;
    } else if((parameter.substr(0,parameter.length()-1).compare("cdrom_image")==0 || parameter.substr(0,parameter.length()-2).compare("cdrom_image")==0)&& cdrom_image.size()<20){
        cdrom_image.push_back(value);
    }
    return 0;
}

void ConfigCDRom::setToDefaultConfiguration()
{
    cdrom_drive_0=DEFAULTCDROMEDRIVE0;
    cdrom_image.clear();
}

bool ConfigCDRom::hasParameter(string parameterName)
{
    return (parameterName.substr(0,parameterName.length()-1).compare("cdrom_drive_")==0)||(parameterName.substr(0,parameterName.length()-1).compare("cdrom_image_")==0)||(parameterName.substr(0,parameterName.length()-2).compare("cdrom_image_")==0);
}
