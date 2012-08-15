#ifndef CONFIGINPUT_H
#define CONFIGINPUT_H
#include <vector>
#include <string>
using namespace std;

class ConfigInput
{
    vector<string> custom_input_mapping_inserted_keys;
    vector<string> custom_input_mapping_inserted_actions;
    //string blablabla;

public:
    ConfigInput();

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();

    bool containsKeyOrAction(string s);
    int getCustomInputMappingSize();
    string getCustomInputMappingAt(int position);
    void eraseCustomInputMappingAt(int position);
};

#endif // CONFIGINPUT_H
