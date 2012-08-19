/*! \file configharddisks.cpp
 configharddisks.cpp

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
#include "configharddisks.h"
#include <sstream>

const string DEFAULTHARDDISKDRIVE = "";
const string DEFAULTHARDDISKDRIVELABEL = "";
const string DEFAULTHARDDISKDRIVEREADONLY = "0";

ConfigHardDisks::ConfigHardDisks()
{
    setToDefaultConfiguration();
}

string static intToStr(int n){
    return static_cast<ostringstream*>( &(ostringstream() << n) )->str();
}

string ConfigHardDisks::getHardDriveConfigStringAt(int i)
{
    string iString=intToStr(i);
    if (i<0 || i>10){return "";}
    if (hard_drive[i].compare(DEFAULTHARDDISKDRIVE)==0){return "";}
    else {return "hard_drive_" + iString + " = " + hard_drive[i];}
}

string ConfigHardDisks::getHardDriveStringAt(int i)
{
    if (i<0 || i>10){return "";}
    return hard_drive[i];
}

string ConfigHardDisks::getHardDriveLabelConfigStringAt(int i)
{
    string iString=intToStr(i);
    if (i<0 || i>10){return "";}
    if (hard_drive_label[i].compare(DEFAULTHARDDISKDRIVELABEL)==0){return "";}
    else {return "hard_drive_" + iString + "_label = " + hard_drive_label[i];}
}

string ConfigHardDisks::getHardDriveLabelStringAt(int i)
{
    if (i<0 || i>10){return "";}
    return hard_drive_label[i];
}

string ConfigHardDisks::getHardDriveReadOnlyConfigStringAt(int i)
{
    string iString=intToStr(i);
    if (i<0 || i>10){return "";}
    if (hard_drive_read_only[i].compare(DEFAULTHARDDISKDRIVEREADONLY)==0){return "";}
    else {return "hard_drive_" + iString + "_read_only = " + hard_drive_read_only[i];}
}

string ConfigHardDisks::getHardDriveReadOnlyStringAt(int i)
{
    if (i<0 || i>10){return "";}
    return hard_drive_read_only[i];
}

int ConfigHardDisks::setParameter(string parameter, string value)
{
    if(parameter.compare("hard_drive_0")==0){
        hard_drive[0]=value;
    } else if(parameter.compare("hard_drive_1")==0){
        hard_drive[1]=value;
    } else if(parameter.compare("hard_drive_2")==0){
        hard_drive[2]=value;
    } else if(parameter.compare("hard_drive_3")==0){
        hard_drive[3]=value;
    } else if(parameter.compare("hard_drive_4")==0){
        hard_drive[4]=value;
    } else if(parameter.compare("hard_drive_5")==0){
        hard_drive[5]=value;
    } else if(parameter.compare("hard_drive_6")==0){
        hard_drive[6]=value;
    } else if(parameter.compare("hard_drive_7")==0){
        hard_drive[7]=value;
    } else if(parameter.compare("hard_drive_8")==0){
        hard_drive[8]=value;
    } else if(parameter.compare("hard_drive_9")==0){
        hard_drive[9]=value;
    } else if(parameter.compare("hard_drive_0_label")==0){
        hard_drive_label[0]=value;
    } else if(parameter.compare("hard_drive_1_label")==0){
        hard_drive_label[1]=value;
    } else if(parameter.compare("hard_drive_2_label")==0){
        hard_drive_label[2]=value;
    } else if(parameter.compare("hard_drive_3_label")==0){
        hard_drive_label[3]=value;
    } else if(parameter.compare("hard_drive_4_label")==0){
        hard_drive_label[4]=value;
    } else if(parameter.compare("hard_drive_5_label")==0){
        hard_drive_label[5]=value;
    } else if(parameter.compare("hard_drive_6_label")==0){
        hard_drive_label[6]=value;
    } else if(parameter.compare("hard_drive_7_label")==0){
        hard_drive_label[7]=value;
    } else if(parameter.compare("hard_drive_8_label")==0){
        hard_drive_label[8]=value;
    } else if(parameter.compare("hard_drive_9_label")==0){
        hard_drive_label[9]=value;
    } else if(parameter.compare("hard_drive_0_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[0]=value;}
        else{
            hard_drive_read_only[0]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_1_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[1]=value;}
        else{
            hard_drive_read_only[1]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_2_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[2]=value;}
        else{
            hard_drive_read_only[2]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_3_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[3]=value;}
        else{
            hard_drive_read_only[3]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_4_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[4]=value;}
        else{
            hard_drive_read_only[4]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_5_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[5]=value;}
        else{
            hard_drive_read_only[5]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_6_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[6]=value;}
        else{
            hard_drive_read_only[6]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_7_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[7]=value;}
        else{
            hard_drive_read_only[7]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_8_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[8]=value;}
        else{
            hard_drive_read_only[8]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    } else if(parameter.compare("hard_drive_9_read_only")==0){
        if ((value.compare("0")==0)||(value.compare("1")==0)){
            hard_drive_read_only[9]=value;}
        else{
            hard_drive_read_only[9]=DEFAULTHARDDISKDRIVEREADONLY;
            return -1;
        }
    }
    return 0;
}

void ConfigHardDisks::setToDefaultConfiguration()
{
    for(int i=0;i<10;i++){
        hard_drive[i]=DEFAULTHARDDISKDRIVE;
        hard_drive_label[i]=DEFAULTHARDDISKDRIVELABEL;
        hard_drive_read_only[i]=DEFAULTHARDDISKDRIVEREADONLY;
    }

}

bool ConfigHardDisks::hasParameter(string parameterName)
{
    return (parameterName.substr(0,parameterName.length()-1).compare("hard_drive_")==0)||
            ((parameterName.substr(0,string("hard_drive_").length()).compare("hard_drive_")==0)&&(parameterName.substr(string("hard_drive_").length()+1,parameterName.length()).compare("_label")==0))||
            ((parameterName.substr(0,string("hard_drive_").length()).compare("hard_drive_")==0)&&(parameterName.substr(string("hard_drive_").length()+1,parameterName.length()).compare("_read_only")==0));
}
