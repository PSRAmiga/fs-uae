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

void ConfigHardDisks::setParameter(string parameter, string value)
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
        hard_drive_read_only[0]=value;
    } else if(parameter.compare("hard_drive_1_read_only")==0){
        hard_drive_read_only[1]=value;
    } else if(parameter.compare("hard_drive_2_read_only")==0){
        hard_drive_read_only[2]=value;
    } else if(parameter.compare("hard_drive_3_read_only")==0){
        hard_drive_read_only[3]=value;
    } else if(parameter.compare("hard_drive_4_read_only")==0){
        hard_drive_read_only[4]=value;
    } else if(parameter.compare("hard_drive_5_read_only")==0){
        hard_drive_read_only[5]=value;
    } else if(parameter.compare("hard_drive_6_read_only")==0){
        hard_drive_read_only[6]=value;
    } else if(parameter.compare("hard_drive_7_read_only")==0){
        hard_drive_read_only[7]=value;
    } else if(parameter.compare("hard_drive_8_read_only")==0){
        hard_drive_read_only[8]=value;
    } else if(parameter.compare("hard_drive_9_read_only")==0){
        hard_drive_read_only[9]=value;
    }
}

void ConfigHardDisks::setToDefaultConfiguration()
{
    for(int i=0;i<10;i++){
        hard_drive[i]=DEFAULTHARDDISKDRIVE;
        hard_drive_label[i]=DEFAULTHARDDISKDRIVELABEL;
        hard_drive_read_only[i]=DEFAULTHARDDISKDRIVEREADONLY;
    }

}
