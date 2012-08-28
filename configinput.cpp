#include "configinput.h"
#include <algorithm>
using namespace std;

// ABBIAMO IPOTIZZATO UN'ASSOCIAZIONE 1 a 1 TRA TASTO E AZIONE -> NON POSSO ASSOCIARE 1 AZIONE A 2 TASTI o 1 TASTO A 2 AZIONI

const string DEFAULTJOYSTICKPORT0 = "mouse";
const string DEFAULTJOYSTICKPORT1 = "keyboard";
const string DEFAULTJOYSTICKPORT = "none";
const string DEFAULTJOYSTICKPORTMODE = "";

ConfigInput::ConfigInput()
{
    setToDefaultConfiguration();
}

/** \brief Returns the string to be appended to joystick name so that, if user has 2 joystick with the same name, fs-uae can distinguish them
  *\param portNumber is the port number of Joystick
  *\return the string to be appended to joystick name
  */
string ConfigInput::joystickNumberString(int portNumber){
    if (portNumber==0){
        return "";
    } else if (portNumber==1){
        if (joystick_port_1.compare(joystick_port_0)==0){
            return " #2";
        } else {
            return "";
        }
    } else if (portNumber==2){
        if (joystick_port_2.compare(joystick_port_0)==0){
            if (joystick_port_2.compare(joystick_port_1)==0){
                return " #3";
            } else {
                return " #2";
            }
        } else {
            if (joystick_port_2.compare(joystick_port_1)==0){
                return " #2";
            } else {
                return "";
            }
        }

    } else if (portNumber==3){
        if (joystick_port_3.compare(joystick_port_0)==0){
            if (joystick_port_3.compare(joystick_port_1)==0){
                if (joystick_port_3.compare(joystick_port_2)==0){
                    return " #4";
                } else {
                    return " #3";
                }
            } else {
                if (joystick_port_3.compare(joystick_port_2)==0){
                    return " #3";
                } else {
                    return " #2";
                }
            }
        } else {
            if (joystick_port_3.compare(joystick_port_1)==0){
                if (joystick_port_3.compare(joystick_port_2)==0){
                    return " #3";
                } else {
                    return " #2";
                }
            } else {
                if (joystick_port_3.compare(joystick_port_2)==0){
                    return " #2";
                } else {
                    return "";
                }
            }
        }
    }
    return "";
}

string ConfigInput::getJoystickPort0ConfigString()
{
    if (joystick_port_0.compare(DEFAULTJOYSTICKPORT0)==0){return "";}
    else {return "joystick_port_0 = " + joystick_port_0+joystickNumberString(0);}
}

string ConfigInput::getJoystickPort0String()
{
    return joystick_port_0;
}

string ConfigInput::getJoystickPort1ConfigString()
{
    if (joystick_port_1.compare(DEFAULTJOYSTICKPORT1)==0){return "";}
    else {return "joystick_port_1 = " + joystick_port_1+joystickNumberString(1);}
}

string ConfigInput::getJoystickPort1String()
{
    return joystick_port_1;
}

string ConfigInput::getJoystickPort2ConfigString()
{
    if (joystick_port_2.compare(DEFAULTJOYSTICKPORT)==0){return "";}
    else {return "joystick_port_2 = " + joystick_port_2+joystickNumberString(2);}
}

string ConfigInput::getJoystickPort2String()
{
    return joystick_port_2;
}

string ConfigInput::getJoystickPort3ConfigString()
{
    if (joystick_port_3.compare(DEFAULTJOYSTICKPORT)==0){return "";}
    else {return "joystick_port_3 = " + joystick_port_3+joystickNumberString(3);}
}

string ConfigInput::getJoystickPort3String()
{
    return joystick_port_3;
}

string ConfigInput::getJoystickPort0ModeConfigString()
{
    if (joystick_port_0_mode.compare(DEFAULTJOYSTICKPORTMODE)==0){return "";}
    else {return "joystick_port_0_mode = " + joystick_port_0_mode;}
}

string ConfigInput::getJoystickPort0ModeString()
{
    return joystick_port_0_mode;
}

string ConfigInput::getJoystickPort1ModeConfigString()
{
    if (joystick_port_1_mode.compare(DEFAULTJOYSTICKPORTMODE)==0){return "";}
    else {return "joystick_port_1_mode = " + joystick_port_1_mode;}
}

string ConfigInput::getJoystickPort1ModeString()
{
    return joystick_port_1_mode;
}

string ConfigInput::getJoystickPort2ModeConfigString()
{
    if (joystick_port_2_mode.compare(DEFAULTJOYSTICKPORTMODE)==0){return "";}
    else {return "joystick_port_2_mode = " + joystick_port_2_mode;}
}

string ConfigInput::getJoystickPort2ModeString()
{
    return joystick_port_2_mode;
}

string ConfigInput::getJoystickPort3ModeConfigString()
{
    if (joystick_port_3_mode.compare(DEFAULTJOYSTICKPORTMODE)==0){return "";}
    else {return "joystick_port_3_mode = " + joystick_port_3_mode;}
}

string ConfigInput::getJoystickPort3ModeString()
{
    return joystick_port_3_mode;
}

string static joystickNameWithoutNumber(string joystickName){
    int separatorPosition=joystickName.find(" #");
    if(separatorPosition==(int) string::npos){
        return joystickName;
    }
    return joystickName.substr(0,separatorPosition);
}

int ConfigInput::setParameter(string parameter, string value)
{
    if(parameter.substr(0,13).compare("keyboard_key_")==0){
        if(!containsKeyOrAction(parameter) && !containsKeyOrAction(value)){
            custom_input_mapping_inserted_keys.push_back(parameter);
            custom_input_mapping_inserted_actions.push_back(value);
        }
    } else if(parameter.compare("joystick_port_0")==0){
        //accepts everything because I don't know the name of every joystick
        if (value.compare("")!=0){
            joystick_port_0=joystickNameWithoutNumber(value);
        }else{
            joystick_port_0=DEFAULTJOYSTICKPORT0;}
    } else if(parameter.compare("joystick_port_1")==0){
        if (value.compare("")!=0){
            joystick_port_1=joystickNameWithoutNumber(value);
        }else{
            joystick_port_1=DEFAULTJOYSTICKPORT0;}
    } else if(parameter.compare("joystick_port_2")==0){
        if (value.compare("")!=0){
            joystick_port_2=joystickNameWithoutNumber(value);
        }else{
            joystick_port_2=DEFAULTJOYSTICKPORT0;}
    } else if(parameter.compare("joystick_port_3")==0){
        if (value.compare("")!=0){
            joystick_port_3=joystickNameWithoutNumber(value);
        }else{
            joystick_port_3=DEFAULTJOYSTICKPORT0;}
    } else if(parameter.compare("joystick_port_0_mode")==0){
        /* if ((value.compare("joystick")==0)||(value.compare("mouse")==0)||(value.compare("cd32 gamepad")==0)||(value.compare("none")==0)){
            joystick_port_0_mode=value;
        }else{
            joystick_port_0_mode=DEFAULTJOYSTICKPORTMODE;
            return -1;
        }*/
        joystick_port_0_mode=DEFAULTJOYSTICKPORTMODE;
    } else if(parameter.compare("joystick_port_1_mode")==0){
        /*if ((value.compare("joystick")==0)||(value.compare("mouse")==0)||(value.compare("cd32 gamepad")==0)||(value.compare("none")==0)){
            joystick_port_1_mode=value;
        }else{
            joystick_port_1_mode=DEFAULTJOYSTICKPORTMODE;
            return -1;
        }*/
        joystick_port_1_mode=DEFAULTJOYSTICKPORTMODE;
    } else if(parameter.compare("joystick_port_2_mode")==0){
        /*if ((value.compare("joystick")==0)||(value.compare("mouse")==0)||(value.compare("cd32 gamepad")==0)||(value.compare("none")==0)){
            joystick_port_2_mode=value;
        }else{
            joystick_port_2_mode=DEFAULTJOYSTICKPORTMODE;
            return -1;
        }*/
        joystick_port_2_mode=DEFAULTJOYSTICKPORTMODE;
    } else if(parameter.compare("joystick_port_3_mode")==0){
        /*if ((value.compare("joystick")==0)||(value.compare("mouse")==0)||(value.compare("cd32 gamepad")==0)||(value.compare("none")==0)){
            joystick_port_3_mode=value;
        }else{
            joystick_port_3_mode=DEFAULTJOYSTICKPORTMODE;
            return -1;
        }*/
        joystick_port_3_mode=DEFAULTJOYSTICKPORTMODE;
    }
    return 0;
}

void ConfigInput::setToDefaultConfiguration()
{
    custom_input_mapping_inserted_actions.clear();
    custom_input_mapping_inserted_keys.clear();
    joystick_port_0=DEFAULTJOYSTICKPORT0;
    joystick_port_1=DEFAULTJOYSTICKPORT1;
    joystick_port_2=DEFAULTJOYSTICKPORT;
    joystick_port_3=DEFAULTJOYSTICKPORT;
    joystick_port_0_mode=DEFAULTJOYSTICKPORTMODE;
    joystick_port_1_mode=DEFAULTJOYSTICKPORTMODE;
    joystick_port_2_mode=DEFAULTJOYSTICKPORTMODE;
    joystick_port_3_mode=DEFAULTJOYSTICKPORTMODE;

}

bool ConfigInput::containsKeyOrAction(string s)
{
    if(std::find(custom_input_mapping_inserted_actions.begin(), custom_input_mapping_inserted_actions.end(), s) != custom_input_mapping_inserted_actions.end()) {
        return true;
    }
    if(std::find(custom_input_mapping_inserted_keys.begin(), custom_input_mapping_inserted_keys.end(), s) != custom_input_mapping_inserted_keys.end()) {
        return true;
    }
    return false;
}

int ConfigInput::getCustomInputMappingSize()
{
    return custom_input_mapping_inserted_keys.size();
}

string ConfigInput::getCustomInputMappingConfigStringAt(int position)
{
    if (position>=(int)custom_input_mapping_inserted_keys.size()){return "";}
    return custom_input_mapping_inserted_keys.at(position)+" = "+custom_input_mapping_inserted_actions.at(position);
}

void ConfigInput::eraseCustomInputMappingAt(int position)
{
    if (position>=(int)custom_input_mapping_inserted_keys.size()){return;}
    custom_input_mapping_inserted_keys.erase(custom_input_mapping_inserted_keys.begin()+ position);
    custom_input_mapping_inserted_actions.erase(custom_input_mapping_inserted_actions.begin()+ position);
}

bool ConfigInput::hasParameter(string parameterName)
{
    return ((parameterName.substr(0,13).compare("keyboard_key_")==0)||(parameterName.compare("joystick_port_0")==0)||
            (parameterName.compare("joystick_port_1")==0)||(parameterName.compare("joystick_port_2")==0)||
            (parameterName.compare("joystick_port_3")==0)||(parameterName.compare("joystick_port_0_mode")==0)||
            (parameterName.compare("joystick_port_1_mode")==0)||(parameterName.compare("joystick_port_2_mode")==0)||
            (parameterName.compare("joystick_port_3_mode")==0));
}
