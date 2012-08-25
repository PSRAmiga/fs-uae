/**
* \class ConfigCDRom
*/
#ifndef CONFIGCDROM_H
#define CONFIGCDROM_H
#include <vector>
#include <string>
using namespace std;

/// This class is responsible for the Cd-Rom Configuration management.
/** In this class are stored all the variables for CDROM configuration.\n
  * You can specify the path to the CD-ROM image and a list of other CD-ROM images to enable CD-ROM swapping.
  */
class ConfigCDRom
{
    string cdrom_drive_0;           ///< CD-ROM drive 0 image path
    vector<string> cdrom_image;     ///< List of CD-ROM images
public:
    ConfigCDRom(); ///< Creates an empty CD-ROM configuration

    /** \brief Returns the string of cdrom_drive_0 to be written in Config File.
      * \return the string to be written in Config File.
      */
    string getCDRomDrive0ConfigString();
    /** \brief Returns the CD-ROM drive 0 image path.
      * \return the CD-ROM drive 0 image path.
      */
    string getCDRomDrive0String();

    /** \brief Returns the size of List of CD-ROM images.
      * \return the size of List of CD-ROM images.
      */
    int getCDRomImageSize();
    /** \brief Returns the CD-ROM image path at position
      *\param position of image to be returned
      * \return the CD-ROM image path at position.
      */
    string getCDRomImageAt(int position);
    /** \brief Add a CD-ROM image at the end of the list
      *\param s is the CD-ROM image to be added
      */
    void pushBackCDRomImage(string s);
    /** \brief Delete the CD-ROM image path at position
      *\param position of the image to be removed
      */
    void eraseCDRomImageAt(int position);


    /** \brief Set CD-ROM configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set CD-ROM configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if CD-ROM configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
    bool hasParameter(string parameterName);
};

#endif // CONFIGCDROM_H
