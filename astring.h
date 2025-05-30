/**
 * @file: astring.h
 * @brief aso own string utils
 * Include file
 *
 * @author  aso (Solomatov A.A.)
 *
 * @date Created 17.11.2022
 *	Updated  29.05.2025
 *
 * @version v.0.99.1
 */


#ifndef __ASTRING__
#define __ASTRING__


#ifdef __cplusplus

/// Convert an identificator to a string (by enclosing the identifier in quotation marks)
#define __INN_STR__(str) #str
#define STRING(str) __INN_STR__(str)

/// Create a std::string literal from an ANSI C string
#define STRLIT(str)	__inner_strliteral__(str)
#define __inner_strliteral__(str) str##s

/// Create a std::string_view literal from an ANSI C string
#define STRVIEWLIT(str)	__inner_strviewlit__(str)
#define __inner_strviewlit__(str) str##sv


/// C++ specialization

/// @brief String 'str' is empty [""] or NULL?
constexpr bool empty(const char* const str)
{
    return str == NULL || str[0] == '\0';
}; /*  empty */


/// @brief is the path terminated a slash
/// as a directory name
constexpr bool is_dirname(const char path[])
{
    return !empty(path) && std::string_view(path).back() == '/';
}; /* is_dirname */


extern "C"
{
#endif

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
//    inline bool empty(const std::string& str)
    inline bool empty(const std::string_view str)
    {
        return str.empty();
    }; /*  empty */

    /// @brief matching the confirmation string
    /// Is the string math the "Yes" string
//    bool confirm(const std::string&);
    bool confirm(const std::string_view);

    /// matching the negation string
    ///Is the string math the "No" string
//    bool decline(const std::string&);
    bool decline(const std::string_view);

    /// @brief Return the "Yes" string
    constexpr const char* yes() { return "y";};

    /// @brief Return the "No" string
    constexpr const char* no() { return "n"; };

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


    /// @brief trim leading & trailong spaces from the string_view
    /// @return  new trimmed string
    std::string_view& trim(std::string_view& strv);

    /// @brief return trimmed string w/o modifing sources string from the string_view
    /// @param[in,out]  str - string for trailing spaces
    /// @return         trimmed passed string
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

#else	// not defined __cplusplus
/// Pure C specialization

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

#endif	// __cplusplus



#endif	// __ASTRING__

//--[ astring.h ]----------------------------------------------------------------------------------
