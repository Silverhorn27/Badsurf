#include "Logger.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <QDateTime>
#include <QDebug>
#include <QDir>

static const string LOG_LEVELS[] {
    "DEBUG",
    "INFO",
    "DONE",
    "TRACE",
    "WARN",
    "ERROR",
    "FATAL"
};

std::string Logger::_logPath = "log.txt";
bool Logger::_logInFile = false;
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
        _logFile.setFileName(_logPath.c_str());
        if (!_logFile.open(QIODevice::WriteOnly | QIODevice::Text))
            qDebug() << "Error";
    }
}

Logger::~Logger()
{
    _logFile.close();
}

void Logger::setLevel(int level)
{
    qDebug() << "Logger::setLevel";
    _level = static_cast<Logger::Level>(level);
}

void Logger::setLogPath(const std::string logPath)
{
    qDebug() << "Logger::setLogPath";
    _logPath = logPath;
}

QString Logger::logImpl(const QString& line)
{
    std::lock_guard<std::mutex> lock(_mtx);
    QString logStr = QDateTime::currentDateTime().toString("dd-MM-yy hh:mm:ss ") + line;

    if (_logInFile) {
        QTextStream out(&_logFile);
        out << logStr + "\n";
    }

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

void Logger::setLogInFile(bool state)
{
    qDebug() << "Logger::setLogInFile";
    _logInFile = state;
}
