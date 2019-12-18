#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include "Utils/StringUtils.h"
#include <string>
#include <mutex>
#include <atomic>
#include <QFile>

class Logger;

#define LOG_TRACE(logger) { logger.log(Logger::TRACE, __func__, "() in ", __FILE__, ":", __LINE__); }

using std::string;

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger(const string& name);
    ~Logger();

    enum Level : int {
        DEBUG,
        INFO,
        DONE,
        TRACE,
        WARN,
        ERROR,
        FATAL,
    };

    template<typename ...Args>
    void log(Level level, const Args&... args)
    {
        QString log = logImpl(StringUtils::toQString('[', describeLevel(level), "] ",
                                                      _name, ": ", args...));
        if (level <= _level)
            emit logging(log);
    }

    void setShowThreadId(bool b);
    static void setLevel(Level level);
    static string describeLevel(Level level);
    static const QStringList getAllLevels();

signals:
    void logging(const QString&);

private:
    static void init();
    string _name;
    static QFile _logFile;
    static std::atomic<Level> _level;
    static std::mutex _mtx;
    static QString logImpl(const QString& line);
}; 

#endif // LOGGER_H
