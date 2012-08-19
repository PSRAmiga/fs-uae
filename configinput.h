/**
* \class ConfigInput
*/
#ifndef CONFIGINPUT_H
#define CONFIGINPUT_H
#include <vector>
#include <string>
using namespace std;
/// This class is responsible for the Graphics Configuration
class ConfigInput
{
    vector<string> custom_input_mapping_inserted_keys;
    vector<string> custom_input_mapping_inserted_actions;
    string joystick_port_0;
    string joystick_port_1;
    string joystick_port_2;
    string joystick_port_3;
    string joystick_port_0_mode;
    string joystick_port_1_mode;
    string joystick_port_2_mode;
    string joystick_port_3_mode;

public:
    ConfigInput();

    string getJoystickPort0ConfigString();
    string getJoystickPort0String();
    string getJoystickPort1ConfigString();
    string getJoystickPort1String();
    string getJoystickPort2ConfigString();
    string getJoystickPort2String();
    string getJoystickPort3ConfigString();
    string getJoystickPort3String();
    string getJoystickPort0ModeConfigString();
    string getJoystickPort0ModeString();
    string getJoystickPort1ModeConfigString();
    string getJoystickPort1ModeString();
    string getJoystickPort2ModeConfigString();
    string getJoystickPort2ModeString();
    string getJoystickPort3ModeConfigString();
    string getJoystickPort3ModeString();

    bool containsKeyOrAction(string s);
    int getCustomInputMappingSize();
    string getCustomInputMappingAt(int position);
    void eraseCustomInputMappingAt(int position);

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
    bool hasParameter(string parameterName);

private:
    string joystickNumberString(int portNumber);
};

#endif // CONFIGINPUT_H
