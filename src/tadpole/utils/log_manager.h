#ifndef LOGMANAGER_H
#define LOGMANAGER_H

// 易于使用的日志类，称为minilogger

#include <QDataStream>
#include <QFile>
#include <QObject>
#include <QPointer>
#include <QString>

#include <fstream>
#include <string>

#include <time.h>

// 以24小时为单位的时间hh:mm:ss格式
static std::string TimeStamp()
{
    char str[9];

    // get the time, and convert it to struct tm format
    time_t a = time(0);
    // struct tm* b = localtime_s(&a);
    struct tm now_time;
    localtime_s(&now_time, &a);

    // print the time to the string
    strftime(str, 9, "%H:%M:%S", &now_time);

    return str;
}

// 日期YYY:MM:DD格式
static std::string DateStamp()
{
    char str[11];

    // get the time, and convert it to struct tm format
    time_t a = time(0);
    // struct tm* b = localtime_s(&a);
    struct tm now_time;
    localtime_s(&now_time, &a);

    // print the time to the string
    strftime(str, 11, "%Y.%m.%d", &now_time);

    return str;
}

// 下面是一个简单的日志装饰器示例，您可以定义自己的装饰器
class TextDecorator
{
public:
    static std::string FileHeader(const std::string& p_title)
    {
        return "==================================================\n" + p_title + "\n" + "==================================================\n";
    }

    static std::string SessionOpen()
    {
        return "\n";
    }

    static std::string SessionClose()
    {
        return "\n";
    }

    static std::string Decorate(const std::string& p_string)
    {
        return p_string + "\n";
    }
};

// 具有新日志文件和新日志标题的新记录器
template<class decorator>
class Logger
{
public:
    Logger();
    void InitLogger(const std::string& p_filename,
                    const std::string& p_logtitle,
                    bool p_timestamp = false,
                    bool p_datestamp = false);

    ~Logger();
    void Log(const std::string& p_entry);
    void AppendLog(const QString& p_entry)
    {
        Log(p_entry.toStdString());
    }

protected:
    std::fstream m_logfile;
    bool m_timestamp;
    bool m_datestamp;
};

typedef Logger<TextDecorator> TextLog;

template<class decorator>
Logger<decorator>::Logger()
{
}

template<class decorator>
void Logger<decorator>::InitLogger(const std::string& p_filename,
                                   const std::string& p_logtitle,
                                   bool p_timestamp,
                                   bool p_datestamp)
{
    // 现在棘手的部分。。。测试文件是否打开。愚蠢的C++。
    // 你需要以读取模式打开一个文件，如果它没有正确打开，你就知道它不存在。文件是否打开。
    std::fstream filetester(p_filename.c_str(), std::ios::in);

    if (filetester.is_open()) {
        // 文件存在，所以只需关闭测试文件
        filetester.close();

        // 打开真实文件并设置应用程序模式
        m_logfile.open(p_filename.c_str(), std::ios::out | std::ios::app);
    } else {
        // 文件不存在。
        m_logfile.open(p_filename.c_str(), std::ios::out);

        // 将文件头打印到文件中
        m_logfile << decorator::FileHeader(p_logtitle);
    }

    // 打印一份开场白。确保它有时间和日期戳
    m_timestamp = true;
    m_datestamp = true;
    m_logfile << decorator::SessionOpen();
    Log("Session opened.");
    m_timestamp = p_timestamp;
    m_datestamp = p_datestamp;
}

template<class decorator>
Logger<decorator>::~Logger()
{
    m_timestamp = true;
    m_datestamp = true;
    Log("Session closed.");
    m_logfile << decorator::SessionClose();
}

template<class decorator>
void Logger<decorator>::Log(const std::string& p_entry)
{
    std::string message;

    if (m_datestamp) {
        message += "[" + DateStamp() + "] ";
    }
    if (m_timestamp) {
        message += "[" + TimeStamp() + "] ";
    }

    message += p_entry;
    m_logfile << decorator::Decorate(message);
    m_logfile.flush();
}

/**
 * @brief The LogManager class
 * 日志管理
 */
class LogManager : public QObject
{
    Q_OBJECT
public:
    // 初始化
    static bool InitLogger(const QString& path);
    // 增加日志
    static void AppendLog(const QString& str);
    // 增加日志
    static void Log(const std::string& p_entry);

private:
    // 打印重定向
    static void LogMessageOutput(QtMsgType type,
                                 const QMessageLogContext& context,
                                 const QString& msg);

private:
    static Logger<TextDecorator> sanTa;
};

#endif // LOGMANAGER_H
