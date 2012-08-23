/**
* \class ConfigChipset
*/
#include <string>
#ifndef CONFIGCHIPSET_H
#define CONFIGCHIPSET_H
using namespace std;
/// This class is responsible for the Chipset Configuration management.
/** In this class are stored all the variables for CHIPSET configuration.\n
 * In this tab, you can choose the type of model you want to emulate FS-UAE (A500, A500+,...,CDTV),
 * the paths for the kickstart and extended kickstart.\n
 * You can also select the emulation accuracy, the video mode (50 Hz PAL or 60 Hz NTSC)
 * and the various types of RAM mountable.\n
 * The extended kickstart path explorer is only permitted if the Amiga model selected si CDTV or CD32.\n
 * In all other cases the Cd-Rom Configuration tabs appears disabled.
*/
class ConfigChipset			  
{
    string amiga_model;          ///< Amiga model you want to emulate.
    string kickstart_file;       ///< Path of kickstart file.
    string kickstart_ext_file;   ///< Path of extended kickstart ROM (for CD32, ...).
    string accuracy;             ///< Sccuracy of the emulation
    string ntsc_mode;            ///< Video mode of the emulation (NTSC/PAL)


public:
    ConfigChipset(); ///< Creates an empty CHIPSET configuration
    /** \brief Returns the string of accuracy to be written in Config File.
          * \return the string to be written in Config File. If Accuracy has the default value (1), it returns an empty string
          */
    string getAccuracyConfigString();
    /** \brief Returns the accuracy value.
          * \return the accuracy value.
          */
    string getAccuracyString();
    /** \brief Returns the string of video mode to be written in Config File.
          * \return the string to be written in Config File. If Video Mode has the default value (0), it returns an empty string
          */
    string getNTSCModeConfigString();
    /** \brief Returns the video mode value.
          * \return the video mode value.
          */
    string getNTSCModeString();
    /** \brief Returns the string of amiga model to be written in Config File.
          * \return the string to be written in Config File. If amiga model has the default value (A500), it returns an empty string
          */
    string getAmigaModelConfigString();
    /** \brief Returns the amiga model value.
          * \return the amiga model value.
          */
    string getAmigaModelString();
    /** \brief Returns the string of kickstart file to be written in Config File.
          * \return the string to be written in Config File.
          */
    string getKickstartFileConfigString();
    /** \brief Returns the kickstart file value.
          * \return the kickstart file value.
          */
    string getKickstartFileString();
    /** \brief Returns the string of extended kickstart file to be written in Config File.
          * \return the string to be written in Config File.
          */
    string getKickstartExtFileConfigString();
    /** \brief Returns the extended kickstart file value.
          * \return the extended kickstart file value.
          */
    string getKickstartExtFileString();

    /** \brief Set Chipset configuration parameter
          *\param parameter is the name of parameter
          *\param value is the value to assign to parameter
          *\return 0 if there aren't error or invalid parameters, -1 otherwise
          */
    int setParameter(string parameter,string value);
    /** \brief Set Chipset configuration parameter to default values
          */
    void setToDefaultConfiguration();
    /** \brief Checks if Chipset configuration has a parameter with that name
          *\param parameterName is the name of parameter to be checked
          *\return true if a parameter with that name exists
          */
    bool hasParameter(string parameterName);
};

#endif // CONFIGCHIPSET_H
