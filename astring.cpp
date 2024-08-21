/**
 * @file astring.cpp
 * @brief aso own string utils,
 * 	C++ body file
 *
 * @date Created on: 6 янв. 2024 г.
 *
 * @author:  aso (Solomatov A.A.)
 *
 * @version: 0.1
 */

#include <cstring>
#include <string>

#include <esp_log.h>

#include "astring.h"

/// @brief match the confirmation string
/// pure C version
bool yes_str(const char str[])
{
    return astr::confirm(str);
}; /* yes_str() */

/// @brief match negation string
/// pure C version
bool no_str(const char str[])
{
    return astr::decline(str);
}; /* no_str() */



namespace astr
{

    /// @brief matching confirmation string value
    bool confirm(const std::string& bst)
    {
	    std::string buf = tolower(bst);

	return ((!is_zero(buf) && is_digitex(buf)) || buf == "on" || buf == "ok" || buf == "y" || buf == "yes");
    }; /* astr::yes_str */

    /// @brief match negation string value
    bool decline(const std::string& bst)
    {
	    std::string buf = tolower(bst);

	return (is_space(buf) || is_zero(buf) || buf == "n" || buf == "no" || buf == "cancel");
    }; /* astr::no_str */


    /// String manipulation utility ---------------------------


    /// @brief trim leading & trailing spaces from the string
    std::string trim(std::string str)
    {
	    size_t head, tail;

	for (head = 0; head < str.length(); head++)
	    if (!std::isspace(str[head]))
		break;

	for (tail = str.length(); tail > head; tail--)
	    if (!std::isspace(str[tail - 1]))
		break;

	return str.substr(head, tail - head);
    }; /* astr::trim(std::string) */

    /// @brief trim leading & trailing spaces from the string
    std::string new_trim(std::string str)
    {
	    std::string::const_iterator head/* = str.cbegin()*/;
	    std::string::const_iterator tail /*= str.cend()*/;

	for (head = str.cbegin(); head < str.cend(); head++)
	{
	    ESP_LOGI("new_trim", "head_iter is: [%c]", *head);
	    if (!std::isspace(*head))
		break;
	};

	for (tail = --str.cend(); tail > str.cbegin(); tail--)
	{
	    ESP_LOGI("new_trim", "tail_iter is: [%c]", *tail);
	    if (!std::isspace(*tail))
		break;
	};

	return std::move(std::string(head, tail));
    }; /* astr::new_trim(std::string) */

#if 0
    /// @brief trim leading & trailong spacec from the string
    std::string_view trim(std::string_view vw)
    {
	    size_t head, tail;


	for (head = 0; head < str.length(); head++)
	    if (!std::isspace(str[head]))
		break;

	for (tail = str.length(); tail > head; tail--)
	    if (!std::isspace(str[tail - 1]))
		break;

	return str.substr(head, tail - head);
    }; /* astr::trim(std::string_view) */
#endif


    /// string to lower case
    std::string tolower(std::string str)
    {
	for (char& c: str)
	    c = ::tolower(static_cast<unsigned char>(c));
	return str;
    }; /* astr::tolower */

    /// string with only space chars or empty?
    bool is_space(const std::string& str)
    {
	    bool resf = true;

	ESP_LOGD(__PRETTY_FUNCTION__, "Input string is: [%s]", str.c_str());

	if (str == "")
	    return true;

	for (unsigned char c: str)
	    if (!std::isspace(c))
		resf = false;

	return resf;
    }; /* astr::is_space */


    /// string with digit & optionsl spaces and/or underline
    bool is_digitex(const std::string& str)
    {
	    bool withdigit = false;	///< detected digit in string
	    bool spdigit = true;	///< detected non_digit && non_space && no underline chars

	for (unsigned char c: str)
	{
	    if (std::isdigit(c))
		withdigit = true;
	    else if (c != '_' || !std::isspace(c))
		spdigit = false;
	}; /* for unsigned char c: str */
	return (withdigit && spdigit);
    }; /* astr::is_digitex */


    /// string is zero only?
    bool is_zero(const std::string& str)
    {
	    bool accept = false;
	    bool decline = false;

	if (!is_digitex(str))
	    return false;

	for (unsigned char c: str)
	    if (c == '0')
		accept = true;
	    else if (!(std::isspace(c) || c == '.' || (std::tolower(static_cast<unsigned char>(c) == 'x'))))
		decline = true;

	return accept && !decline;

    }; /* astr::is_zero */


}; /* namespace astr */


//--[ astring.cpp ]----------------------------------------------------------------------------------------------------


