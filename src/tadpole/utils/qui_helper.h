
#ifndef QUIHELPER_H
#define QUIHELPER_H

#include <QFile>
#include <QPushButton>
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <QtWidgets>

/**
 * @brief The QUIHelper class
 * ui相关全局操作
 */
class QUIHelper : public QObject
{
    Q_OBJECT
public:
    // 设置全局样式表
    static void SetStyle(QWidget* wid = nullptr, const QString& qssFile = ":/style.qss"); // 设置全局样式
    // 获取本机ip
    static QStringList GetLocalIP();
    // 是否是IP
    static bool IsIP(const QString& ip);

    // TaskBar 状态
    static void ActiveTaskBarButton(QPushButton* button);
    static void DisableTaskBarButton(QPushButton* button);
    static void CurrentTaskBarButton(QPushButton* button);

    // 按钮样式
    static void SetCircularButtonStatus(QPushButton* button, const QString& image_name);
    static void SetInteractionButtonStatus(QPushButton* button, const QString& image_name);
    static void SetTransparentButtonStatus(QPushButton* button, const QString& image_path);

    // 用于字符串转换
    static QString ByteArrayToAsciiStr(const QByteArray& data);
    static QString ByteArrayToHexStr(const QByteArray& data);
    static QByteArray HexStrToByteArray(const QString& str);
    static QByteArray AsciiStrToByteArray(const QString& str);
    static QString DecimalToStrHex(int decimal);
    static int StrHexToDecimal(const QString& strHex);
    static char ConvertHexChar(char ch);
};

#endif // QUIHELPER_H
