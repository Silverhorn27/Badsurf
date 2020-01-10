#include "Logger.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <array>

static const std::array<string, 7> LOG_LEVELS {
    "DEBUG",
    "INFO",
    "DONE",
    "TRACE",
    "WARN",
    "ERROR",
    "FATAL"
};

std::string Logger::_logPath = "log.txt";
bool Logger::_logInFile = true;
QFile Logger::_logFile;
std::mutex Logger::_mtx;
std::atomic<Logger::Level> Logger::_level(Logger::Level::INFO);

Logger::Logger(string name)
    : _name(std::move(name))
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
    _level = static_cast<Logger::Level>(level);
}

void Logger::setLogPath(const std::string &logPath)
{
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

    return QDateTime::currentDateTime().toString("hh:mm:ss ") + line;
}

string Logger::describeLevel(Logger::Level level)
{
    return LOG_LEVELS.at(static_cast<size_t>(level));
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
    _logInFile = state;
}
