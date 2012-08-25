/** \class ConfigRam
*/
#ifndef CONFIGRAM_H
#define CONFIGRAM_H
#include <string>
using namespace std;
///  This class is responsible for the Ram Configuration management.
/** In this class are stored all the variables for RAM configuration.\n
* You can set chip memory, slow memory, fast memory and zorro III memory.\n
* The default value of each type of ram depends on the selected Amiga model. */
class ConfigRam
{
    string chip_memory;                 ///< Chip memory in KB (Must be a multiple of 512)
    string slow_memory;                 ///< Slow memory in KB (Must be a multiple of 256)
    string fast_memory;                 ///< Fast memory in KB (Must be a multiple of 1024)
    string zorro_iii_memory;            ///< Zorro III Fast memory in KB (Must be a multiple of 1024 and Requires a processor with 32­bit address bus (for example the A1200/020 model).


public:
    ConfigRam();///< Creates an empty RAM configuration

    /** \brief Returns the string of chip memory to be written in Config File.
      * \return the string to be written in Config File. If Chip memory has the default value (512), it returns an empty string
      */
    string getChipMemoryConfigString();
    /** \brief Returns the chip memory value.
      * \return the chip memory value.
      */
    string getChipMemoryString();
    /** \brief Returns the string of slow memory to be written in Config File.
      * \return the string to be written in Config File. If Slow memory has the default value (NONE), it returns an empty string
      */
    string getSlowMemoryConfigString();
    /** \brief Returns the slow memory value.
      * \return the slow memory value.
      */
    string getSlowMemoryString();
    /** \brief Returns the string of fast memory to be written in Config File.
      * \return the string to be written in Config File. If Fast memory has the default value (NONE), it returns an empty string
      */
    string getFastMemoryConfigString();
    /** \brief Returns the fast memory value.
      * \return the fast memory value.
      */
    string getFastMemoryString();
    /** \brief Returns the string of zorro III memory to be written in Config File.
      * \return the string to be written in Config File. If Zorro III memory has the default value (NONE), it returns an empty string
      */
    string getZorro3ConfigString();
    /** \brief Returns the zorro III memory value.
      * \return the zorro III memory value.
      */
    string getZorro3String();

    /** \brief Set RAM configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set RAM configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if RAM configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
    bool hasParameter(string parameterName);
};

#endif // CONFIGRAM_H
