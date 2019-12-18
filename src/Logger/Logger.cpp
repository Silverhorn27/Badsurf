#include "Logger.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <QDateTime>
#include <QDebug>
#include <QDir>

static const char* LOG_FILE_NAME = "log.txt";

static const string LOG_LEVELS[] {
    "DEBUG",
    "INFO",
    "DONE",
    "TRACE",
    "WARN",
    "ERROR",
    "FATAL"
};

QFile Logger::_logFile;
std::mutex Logger::_mtx;
std::atomic<Logger::Level> Logger::_level(Logger::Level::INFO);

Logger::Logger(const string &name)
    : _name(name)
{
    init();
}

void Logger::init()
{
    std::lock_guard<std::mutex> lock(_mtx);
    if (!_logFile.isOpen()) {
        _logFile.setFileName(LOG_FILE_NAME);
        if (!_logFile.open(QIODevice::WriteOnly))
            qDebug() << "Error";
    }
}

Logger::~Logger()
{
    _logFile.close();
}

void Logger::setLevel(Logger::Level level)
{
    _level = level;
}

QString Logger::logImpl(const QString& line)
{
    std::lock_guard<std::mutex> lock(_mtx);
    QString logStr = QDateTime::currentDateTime().toString("dd-MM-yy hh:mm:ss ") + line;

    QTextStream out(&_logFile);
    out << logStr + "\n";

    return logStr;
}

string Logger::describeLevel(Logger::Level level)
{
    return LOG_LEVELS[level];
}

const QStringList Logger::getAllLevels()
{
    QStringList levels;
    for(auto &i : LOG_LEVELS)
        levels.append(QString::fromStdString(i));
    return levels;
}
