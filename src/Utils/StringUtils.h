#ifndef STRINGUTILES_H
#define STRINGUTILES_H

#include <sstream>
#include <string>
#include <QString>


using std::string;

class StringUtils
{
public:
    static string toString()
    {
        return string();
    }

    template<typename T>
    static string toString(const T& value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    template<typename T>
    static QString toQString(const T& value)
    {
        return QString::fromStdString(toString(value));
    }


    template<typename T, typename ...Args>
    static string toString(const T& value, const Args&... args)
    {
        return toString(value) + toString(args...);
    }

    template<typename T, typename ...Args>
    static QString toQString(const T& value, const Args&... args)
    {
        return QString::fromStdString(toString(value))
                + QString::fromStdString(toString(args...));
    }

};

#endif // STRINGUTILES_H
