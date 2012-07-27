#ifndef CONFIGRAM_H
#define CONFIGRAM_H
#include <string>
using namespace std;

class ConfigRam
{
    string chip_memory;
    string slow_memory;
    string fast_memory;
    string zorro_iii_memory;

public:
    ConfigRam();

    string getChipMemoryConfigString();
    string getChipMemoryString();
    string getSlowMemoryConfigString();
    string getSlowMemoryString();
    string getFastMemoryConfigString();
    string getFastMemoryString();
    string getZorro3ConfigString();
    string getZorro3String();

    void setParameter(string parameter,string value);
    void setToDefaultConfiguration();
};

#endif // CONFIGRAM_H
