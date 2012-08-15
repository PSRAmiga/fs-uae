#include "configinput.h"
#include <algorithm>

// ABBIAMO IPOTIZZATO UN'ASSOCIAZIONE 1 a 1 TRA TASTO E AZIONE -> NON POSSO ASSOCIARE 1 AZIONE A 2 TASTI o 1 TASTO A 2 AZIONI

ConfigInput::ConfigInput()
{
     setToDefaultConfiguration();
}

int ConfigInput::setParameter(string parameter, string value)
{
    if(parameter.substr(0,13).compare("keyboard_key_")==0){
        if(!containsKeyOrAction(parameter) && !containsKeyOrAction(value)){
        custom_input_mapping_inserted_keys.push_back(parameter);
        custom_input_mapping_inserted_actions.push_back(value);
        }
    }
    return 0;
}

void ConfigInput::setToDefaultConfiguration()
{
    custom_input_mapping_inserted_actions.clear();
    custom_input_mapping_inserted_keys.clear();

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

string ConfigInput::getCustomInputMappingAt(int position)
{
    if (position>=custom_input_mapping_inserted_keys.size()){return "";}
    return custom_input_mapping_inserted_keys.at(position)+" = "+custom_input_mapping_inserted_actions.at(position);
}

void ConfigInput::eraseCustomInputMappingAt(int position)
{
    if (position>=custom_input_mapping_inserted_keys.size()){return;}
    custom_input_mapping_inserted_keys.erase(custom_input_mapping_inserted_keys.begin()+ position);
    custom_input_mapping_inserted_actions.erase(custom_input_mapping_inserted_actions.begin()+ position);
}
