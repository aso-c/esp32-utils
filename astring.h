/**
 * @file: astring.h
 * @brief aso own string utils
 * Include file
 *
 * @author  aso (Solomatov A.A.)
 *
 * @date Created 17.11.2022
 *	Updated  16.09.2024
 *
 * @version v.0.98
 */


#ifndef __ASTRING__
#define __ASTRING__


#ifdef __cplusplus
extern "C"
{
#endif


/// @brief String 'str' is empty [""] or NULL?
inline bool empty(const char* const str)
{
    return str == NULL || str[0] == '\0';
}; /*  empty */


/// @brief is the path terminated a slash
/// as a directory name
inline bool is_dirname(const char path[])
{
    return !empty(path) && path[strlen(path)] == '/';
}; /* is_dirname */


/// @brief match confirmation string
/// pure C version
bool yes_str(const char[]);

/// @brief match negation string
/// pure C version
bool no_str(const char[]);



#ifdef __cplusplus
}; /* extern "C" */


/// class freewrapper - dispose memory by the "free()" procedure,
/// that was allocated by the malloc()
template <typename T>
class freewrapper
{
public:
    freewrapper(T* ptr) {data = ptr;};
    ~freewrapper() {free(data);};

    operator T*() {return data;}
    operator const T*() {return data;}

    T* data;
}; /* freewrapper */


namespace astr
{


    //--[ system procedures ]--------------------------------------------------------------------------

    //! Make container, stored data from the pure C array, passed as parameter (e.g. std::list or std::vector)
    // from the passed pure C array of the TData
    // @param[in]  argc - counter of the strings in array
    // @param[in]  argv - array of pointer to the asciiz strings
    // @return          - created container, initialized with values of the passed array
    template <template <typename> class Holder, typename TData>
    Holder<TData> makestorx(int argc, TData argv[])
    {
    	    Holder<TData> holder(argc);

	for (int i = 0; i < argc; i++)
	   holder[i] = argv[i];

        return holder;
    }; /* makestor() */
    //! Make container, stored data from the pure C array, passed as parameter (intended stdlib classes,
    //  e.g. std::list or std::vector)
    template <typename Holder>
    Holder makestor(int argc, typename Holder::value_type argv[])
    {
	    Holder holder;

	holder.insert(std::end(holder), argv, argv + argc);
	return holder;
    }; /* makestor() */


    //! Make container with pointer to containers (e.g. list of the pointers to std::string)
    // from the array of the pointer to asciiz string char*[]
    // @param[in]  argc - counter of the strings in array
    // @param[in]  argv - array of pointer to the asciiz strings
    // @return          - created list of std::string with passed strings
    template <template <typename> class OutHolder, template <typename> class HoldStor, typename TData>
    OutHolder<HoldStor<TData> > mk_containerholder(int argc, TData *argv[])
    {
//    	    OutHolder<HoldStor<TData> > holder(argc);
////    	    int i = 0;
////
////        for (HoldStor<TData>& curr : holder)
////            curr = argv[i++];
//	for (int i = 0; i < argc; i++)
//	    holder[i] = argv[i];

	OutHolder<HoldStor<TData> > holder;
	holder.insert(holder.end(), argv, argv + argc);

        return holder;
    }; /* mk_containerholder() */

    /// @brief String 'str' is empty [""] or NULL?, C++ definition
    inline bool empty(const std::string& str)
    {
        return str.empty();
    }; /*  empty */

    /// @brief matching the confirmation string
    /// Is the string math the "Yes" string
    bool confirm(const std::string&);

    /// matching the negation string
    ///Is the string math the "No" string
    bool decline(const std::string&);

    /// @brief Return the "Yes" string
    inline const char* yes() { return "y";};

    /// @brief Return the "No" string
    inline const char* no() { return "n"; };

    ///------- String manipulation utility

    /// @brief return trimmed string - w/o leading & trailing spaces of the string
    /// @return  new trimmed string
    std::string trimmed(const std::string& str);
    /// @brief trim leading & trailшng spacec from the string "in place"
    /// @param[in,out]  str - string for trailing spaces
    /// @return         trimmed passed string
    inline std::string& trim(std::string& str) {
	str = trimmed(str);
	return str;
    };


    /// @brief trim leading & trailong spacec from the string_view
    std::string_view& trim(std::string_view& strv);

    /// @brief return trimmed string w/o modifing sources string from the string_view
    inline std::string_view trimmed(std::string_view strv) { return trim(strv); };


    /// @brief string to lower case
    std::string tolower(std::string);

    /// @brief string with only space chars or empty?
    bool is_space(const std::string&);

    /// @brief string with digit & optionsl spaces and/or underline
    bool is_digitex(const std::string&);

    /// @brief string is zero only?
    bool is_zero(const std::string&);

}; /* astr */

/// @brief String 'str' is empty [""] - alias of the the astr::empty(const std::string&)
using astr::empty;

#endif	// __cplusplus



#endif	// __ASTRING__

//--[ astring.h ]----------------------------------------------------------------------------------
