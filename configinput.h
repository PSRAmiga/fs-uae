/**
* \class ConfigInput
*/
#ifndef CONFIGINPUT_H
#define CONFIGINPUT_H
#include <vector>
#include <string>
using namespace std;
/// This class is responsible for the Input Configuration management
/** In this class are stored all the variables for INPUT configuration.\n
  * You can set the host devices mapped to the Amiga Joysticks and you \n
  * can re-map all the keyboard and joystick events to any Amiga keyboard\n
  * and joystick action, overriding default settings.
  */
class ConfigInput
{
    vector<string> custom_input_mapping_inserted_keys;          ///< List of Custom Input Mapping Inserted Keys
    vector<string> custom_input_mapping_inserted_actions;       ///< List of Custom Input Mapping Inserted Keys
    string joystick_port_0;                                     ///< Joystick Port 0 Host Device
    string joystick_port_1;                                     ///< Joystick Port 1 Host Device
    string joystick_port_2;                                     ///< Joystick Port 2 Host Device
    string joystick_port_3;                                     ///< Joystick Port 3 Host Device
    string joystick_port_0_mode;                                ///< Joystick Port 0 Mode
    string joystick_port_1_mode;                                ///< Joystick Port 1 Mode
    string joystick_port_2_mode;                                ///< Joystick Port 2 Mode
    string joystick_port_3_mode;                                ///< Joystick Port 3 Mode

public:
    ConfigInput();               ///< Creates an empty INPUT configuration

    /** \brief Returns the Joystick Port 0 Host Device setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 0 Host Device has the default value (Mouse), it returns an empty string
     */
    string getJoystickPort0ConfigString();
    /** \brief Returns the Joystick Port 0 Host Device value.
     * \return the Joystick Port 0 Host Device value.
     */
    string getJoystickPort0String();
    /** \brief Returns the Joystick Port 1 Host Device setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 1 Host Device has the default value (Keyboard), it returns an empty string
     */
    string getJoystickPort1ConfigString();
    /** \brief Returns the Joystick Port 1 Host Device value.
     * \return the Joystick Port 1 Host Device value.
     */
    string getJoystickPort1String();
    /** \brief Returns the Joystick Port 2 Host Device setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 2 Host Device has the default value (NONE), it returns an empty string
     */
    string getJoystickPort2ConfigString();
    /** \brief Returns the Joystick Port 2 Host Device value.
     * \return the Joystick Port 2 Host Device value.
     */
    string getJoystickPort2String();
    /** \brief Returns the Joystick Port 3 Host Device setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 3 Host Device has the default value (NONE), it returns an empty string
     */
    string getJoystickPort3ConfigString();
    /** \brief Returns the Joystick Port 3 Host Device value.
     * \return the Joystick Port 3 Host Device value.
     */
    string getJoystickPort3String();

    /** \brief Returns the Joystick Port 0 Mode setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 0 Mode has the default value (AUTO), it returns an empty string
     */
    string getJoystickPort0ModeConfigString();
    /** \brief Returns the Joystick Port 0 Mode value.
     * \return the Joystick Port 0 Mode value.
     */
    string getJoystickPort0ModeString();
    /** \brief Returns the Joystick Port 1 Mode setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 1 Mode has the default value (AUTO), it returns an empty string
     */
    string getJoystickPort1ModeConfigString();
    /** \brief Returns the Joystick Port 1 Mode value.
     * \return the Joystick Port 1 Mode value.
     */
    string getJoystickPort1ModeString();
    /** \brief Returns the Joystick Port 2 Mode setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 2 Mode has the default value (AUTO), it returns an empty string
     */
    string getJoystickPort2ModeConfigString();
    /** \brief Returns the Joystick Port 2 Mode value.
     * \return the Joystick Port 2 Mode value.
     */
    string getJoystickPort2ModeString();
    /** \brief Returns the Joystick Port 3 Mode setting to be written in Config File.
     * \return the string to be written in Config File. If Joystick Port 3 Mode has the default value (AUTO), it returns an empty string
     */
    string getJoystickPort3ModeConfigString();
    /** \brief Returns the Joystick Port 3 Mode value.
     * \return the Joystick Port 3 Mode value.
     */
    string getJoystickPort3ModeString();

    /** \brief Checks if you have already remapped a key or an action.
     * \return true if you have already remapped s key/action
     * \param s is the key/action to be checked
     */
    bool containsKeyOrAction(string s);
    /** \brief Returns the size of List of remapped items.
      * \return the size of List of remapped items.
      */
    int getCustomInputMappingSize();
    /** \brief Returns the Custom Input Mapping string at the specified position to be written in Config File.
      *\param position of Custom Input Mapping string to be returned
      * \return the Custom Input Mapping string at the specified position to be written in Config File.
      */
    string getCustomInputMappingConfigStringAt(int position);
    /** \brief Delete the Custom Input Mapping at the specified position
      *\param position of the Custom Input Mapping to be removed
      */
    void eraseCustomInputMappingAt(int position);

    /** \brief Set INPUT configuration parameter
      *\param parameter is the name of parameter
      *\param value is the value to assign to parameter
      *\return 0 if there aren't error or invalid parameters, -1 otherwise
      */
    int setParameter(string parameter,string value);
    /** \brief Set INPUT configuration parameter to default values
      */
    void setToDefaultConfiguration();
    /** \brief Checks if INPUT configuration has a parameter with that name
      *\param parameterName is the name of parameter to be checked
      *\return true if a parameter with that name exists
      */
    bool hasParameter(string parameterName);

private:
    string joystickNumberString(int portNumber);
};

#endif // CONFIGINPUT_H
