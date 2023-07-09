#include "EventLogger.h"
#include "../Paths.h"

namespace utils
{
    EventLogger::EventLogger(const std::string &programData) :
        _thread{&EventLogger::logEvents, this}
    {
        CreateDirectoryA(programData.c_str(), NULL);
        CreateDirectoryA(LOG_DIR, NULL);
    }

    EventLogger::~EventLogger()
    {
        _destruct = true;
        _thread.join();
    }

    std::string EventLogger::getPath()
    {
        std::string path(LOG_DIR);
        path += "\\";
        path += getCurrentDate();
        path += ".txt";
        return path;
    }

    std::string EventLogger::getCurrentDateTime()
    {
        auto currentTime = std::time(0);
        struct tm localTime {};
        char strCurrentTime[64] = "";
        localtime_s(&localTime, &currentTime);
        asctime_s(strCurrentTime, sizeof(strCurrentTime), &localTime);
        return std::string(strCurrentTime);
    }

    std::string EventLogger::getCurrentDate()
    {
        auto currentTime = std::time(0);
        struct tm localTime {};
        localtime_s(&localTime, &currentTime);
        return std::to_string(localTime.tm_year + 1900) + "-" +
            (localTime.tm_mon <= 10 ? "0" : "" ) +
            std::to_string(localTime.tm_mon + 1) + "-" +
            (localTime.tm_mday < 10 ? "0" : "") +
            std::to_string(localTime.tm_mday);
    }

    void EventLogger::addLogEvent(const std::string& log)
    {
        if (!_condition || _condition())
        {
            std::string str(getCurrentDateTime().substr() + log + "\n");
            _mtx.lock();
            _logs.push(str);
            _mtx.unlock();
            _lastLog = str;
        }
    }

    const std::string &EventLogger::getLastLog()
    {
        return _lastLog;
    }

    void EventLogger::logEvents()
    {
        std::ofstream os(getPath(), std::ios_base::app);
        while (!_destruct)
        {
            _mtx.lock();
            if (!_logs.empty())
            {
                os << _logs.front();
                _logs.pop();
            }
            _mtx.unlock();
        }
        os.close();
    }
}
