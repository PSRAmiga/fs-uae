/** \class ConfigFloppy
* This class is responsible for the Floppy Configuration.\n
*/
#ifndef CONFIGFLOPPY_H
#define CONFIGFLOPPY_H
#include <vector>
#include <string>
using namespace std;
/// This class is responsible for the Floppy Configuration management.
/** In this class are stored all the variables for FLOPPY configuration.\n
 * You can load up to a maximum of 4 physical floppy disk,
 * and create a list with up to 20 floppy images to enable floppy-swapping during emulation without having to manually change the configuration file.\n
 * You can also set he output volume of the floppy disk drive and floppy drive speed.
*/
class ConfigFloppy
{
    string floppy_drive[4];         ///< Floppy drive image 0-3 list
    vector<string> floppy_image;    ///< List of floppy images
    string floppy_drive_volume;     ///< Floppy drive sounds. Max volume is 100. The default value is 20.
    string floppy_drive_speed;      ///< Floppy drive speed, in percent. The default is 100. You can specify 800 to get an 8x increase in speed. Use 0 to specify turbo mode.*/

public:
    ConfigFloppy();     ///< Creates an empty FLOPPY configuration

    /** \brief Returns the floppy image string at position i to be written in Config File.
      *\param i is the position of floppy image to be returned.
      * \return the string to be written in Config File.
      */
    string getFloppyDriveConfigStringAt(int i);
    /** \brief Returns the floppy image string at position i
      * \return the floppy image string at position i
      */
    string getFloppyDriveStringAt(int i);

    /** \brief Returns the floppy drive volume to be written in Config File.
      * \return the string to be written in Config File. If floppy_drive_volume has the default value (20), it returns an empty string
      */
    string getFloppyDriveVolumeConfigString();
    /** \brief Returns the floppy drive volume value.
      * \return the floppy drive volume value.
      */
    string getFloppyDriveVolumeString();
    /** If floppy_drive_speed is the default value [100], it returns an empty string.\n floppy_drive_speed = 100 */
    /** \brief Returns the floppy drive speed to be written in Config File.
      * \return the string to be written in Config File. If floppy_drive_speed has the default value (100), it returns an empty string
      */
    string getFloppyDriveSpeedConfigString();
    /** \brief Returns the floppy drive speed value.
      * \return the floppy drive speed value.
      */
    string getFloppyDriveSpeedString();
    /** \brief Returns the size of List of Floppy images.
      * \return the size of List of Floppy images.
      */
    int getFloppyImageSize();
    /** \brief Returns the floppy image at position
      *\param position of image to be returned
      * \return the floppy image at position.
      */
    string getFloppyImageAt(int position);
    /** \brief Add a floppy image at the end of the list
      *\param s is the floppy image to be added
      */
    void pushBackFloppyImage(string s);
    /** \brief Delete the floppy image path at position
      *\param position of the image to be removed
      */
    void eraseFloppyImageAt(int position);

    /** \brief Set Floppy configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set Floppy configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if Chipset configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
    bool hasParameter(string parameterName);
};

#endif // CONFIGFLOPPY_H
