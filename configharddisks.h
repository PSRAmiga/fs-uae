/**
* \class ConfigHardDisks
*/
#ifndef CONFIGHARDDISKS_H
#define CONFIGHARDDISKS_H
#include <string>
using namespace std;
/// This class is responsible for the Hard Disks Configuration management.
/** In this class are stored all the variables for HARD DISK configuration.\n
  * You can set 10 hard disk drive selecting a hdf file or using a directory \n
  * as a drvie. For each hard disk you can set a Label and set it as Read only.\n
  */
class ConfigHardDisks
{
    string hard_drive[10];              ///< Hard drive image 0-9 list
    string hard_drive_label[10];        ///< Hard drive label 0-9 list
    string hard_drive_read_only[10];    ///< Hard drive read only attribute 0-9 list

public:
    ConfigHardDisks();               ///< Creates an empty HARD DRIVE configuration

    /** \brief Returns the hard drive image string at position i to be written in Config File.
      *\param i is the position of hard drive image to be returned.
      * \return the string to be written in Config File.
      */
    string getHardDriveConfigStringAt(int i);
    /** \brief Returns the hard drive image string at position i
      * \return the hard drive image string at position i
      */
    string getHardDriveStringAt(int i);
    /** \brief Returns the hard drive label string at position i to be written in Config File.
      *\param i is the position of hard drive label to be returned.
      * \return the string to be written in Config File.
      */
    string getHardDriveLabelConfigStringAt(int i);
    /** \brief Returns the hard drive label string at position i
      * \return the hard drive label string at position i
      */
    string getHardDriveLabelStringAt(int i);
    /** \brief Returns the hard drive read only string at position i to be written in Config File.
      *\param i is the position of hard drive read only to be returned.
      * \return the string to be written in Config File.
      */
    string getHardDriveReadOnlyConfigStringAt(int i);
    /** \brief Returns the hard drive read only string at position i
      * \return the hard drive read only string at position i. If Read Only attribute has the default value (0), it returns an empty string
      */
    string getHardDriveReadOnlyStringAt(int i);

    /** \brief Set HARD DRIVE configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set HARD DRIVE configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if HARD DRIVE configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
    bool hasParameter(string parameterName);
};

#endif // CONFIGHARDDISKS_H
