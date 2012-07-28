/** \class ConfigRam
* This class is responsible for the Ram Configuration.\n
* The default value of each type of ram depends on the selected Amiga model.
*/
#ifndef CONFIGRAM_H
#define CONFIGRAM_H
#include <string>
using namespace std;
/// Create the RAM Configuration Class
class ConfigRam
{
    string chip_memory;                 ///< Override amount of chip memory, specified in KB. Must be a multiple of 512.
    string slow_memory;                 ///< Override the amount of “slow” memory, specified in KB. Must be a multiple of 256.
    string fast_memory;                 ///< Override the amount of Zorro II Fast memory, specified in KB. Must be a multiple of 1024.
    string zorro_iii_memory;            ///< Override the amount of Zorro III Fast memory, specified in KB. Must be a multiple of 1024.\nRequires a processor with 32­bit address bus, (use for example the A1200/020 model).


public:
    ConfigRam();

    string getChipMemoryConfigString(); ///< Represents the string of Chip memory to be written in Config File. If Chip memory is the default value, it returns an empty string.\n chip_memory = 1024
    string getChipMemoryString();       ///< Represent the effective value of Chip memory
    string getSlowMemoryConfigString(); ///< Represents the string of Slow memory to be written in Config File. If Slow memory is the default value, it returns an empty string.\n slow_memory = 512
    string getSlowMemoryString();       ///< Represent the effective value of Slow memory
    string getFastMemoryConfigString(); ///< Represents the string of Zorro II Fast memory to be written in Config File. If Fast memory is the default value, it returns an empty string.\n fast_memory = 4096
    string getFastMemoryString();       ///< Represent the effective value of Zorro II Fast memory
    string getZorro3ConfigString();     ///< Represents the string of Zorro III Fast memory to be written in Config File. If Zorro III memory is the default value, it returns an empty string.\n zorro_iii_memory = 65536
    string getZorro3String();           ///< Represent the effective value of Zorro III Fast memory

    void setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGRAM_H
