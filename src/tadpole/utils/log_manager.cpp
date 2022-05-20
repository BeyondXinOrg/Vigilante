#include "log_manager.h"

#include <QDateTime>
#include <QReadWriteLock>
#include <QTextStream>
#include <QThread>

Logger<TextDecorator> LogManager::sanTa;

// 初始化
bool LogManager::InitLogger(const QString& path)
{
    sanTa.InitLogger(static_cast<const char*>(path.toLocal8Bit()), "SantaTec 3D Log!", false, false);
    qInstallMessageHandler(LogMessageOutput);
    return true;
}

// 增加日志
void LogManager::AppendLog(const QString& str)
{
    sanTa.AppendLog(str);
}

// 增加日志
void LogManager::Log(const std::string& p_entry)
{
    sanTa.Log(p_entry);
}

// 打印重定向
void LogManager::LogMessageOutput(QtMsgType type,
                                  const QMessageLogContext& context,
                                  const QString& msg)
{
    static QReadWriteLock lock;
    QWriteLocker locker(&lock);
    static QTextStream cout(stdout, QIODevice::WriteOnly);
    QString text;
    bool appden_log = true;
    switch (type) {
    case QtDebugMsg: {
        text = QString("DEBUG:");
        appden_log = false;
        break;
    }
    case QtInfoMsg: {
        text = QString("INFO:");
        break;
    }
    case QtWarningMsg: {
        text = QString("WARNING:");
        break;
    }
    case QtCriticalMsg: {
        text = QString("CRITICAL:");
        break;
    }
    case QtFatalMsg: {
        text = QString("FATAL:");
        break;
    }
    }
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString currentThreadName = QThread::currentThread()->objectName();

    QString message = QString("%1 [%2] %3 - (%4) %5 ")
                        .arg(currentDateTime)
                        .arg(currentThreadName)
                        .arg(text)
                        .arg(QString(context.function).remove(QRegExp("\\((.*)\\)")))
                        .arg(msg);

    cout << message << endl;
    cout.flush();

    if (appden_log) {
        AppendLog(message);
    }
}
