/** \class ConfigRam
*/
#ifndef CONFIGRAM_H
#define CONFIGRAM_H
#include <string>
using namespace std;
///  This class is responsible for the Ram Configuration.
/** The default value of each type of ram depends on the selected Amiga model. */
class ConfigRam
{
    string chip_memory;                 ///< Override amount of chip memory, specified in KB. Must be a multiple of 512.
    string slow_memory;                 ///< Override the amount of “slow” memory, specified in KB. Must be a multiple of 256.
    string fast_memory;                 ///< Override the amount of Zorro II Fast memory, specified in KB. Must be a multiple of 1024.
    string zorro_iii_memory;            ///< Override the amount of Zorro III Fast memory, specified in KB. Must be a multiple of 1024.\n Requires a processor with 32­bit address bus, (use for example the A1200/020 model).


public:
    ConfigRam();

    /** If Chip memory is the default value, it returns an empty string.\n chip_memory = 1024 */
    string getChipMemoryConfigString(); ///< Represents the string of Chip memory to be written in Config File.
    string getChipMemoryString();       ///< Represent the effective value of Chip memory
    /** If Slow memory is the default value, it returns an empty string.\n slow_memory = 512 */
    string getSlowMemoryConfigString(); ///< Represents the string of Slow memory to be written in Config File.
    string getSlowMemoryString();       ///< Represent the effective value of Slow memory
    /** If Fast memory is the default value, it returns an empty string.\n fast_memory = 4096*/
    string getFastMemoryConfigString(); ///< Represents the string of Zorro II Fast memory to be written in Config File.
    string getFastMemoryString();       ///< Represent the effective value of Zorro II Fast memory
    /** If Zorro III memory is the default value, it returns an empty string.\n zorro_iii_memory = 65536 */
    string getZorro3ConfigString();     ///< Represents the string of Zorro III Fast memory to be written in Config File.
    string getZorro3String();           ///< Represent the effective value of Zorro III Fast memory

    int setParameter(string parameter,string value);
    void setToDefaultConfiguration();
    bool hasParameter(string parameterName);
};

#endif // CONFIGRAM_H
