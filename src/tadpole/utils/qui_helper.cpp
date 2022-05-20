#include "qui_helper.h"

#include <QApplication>
#include <QDebug>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QPalette>
#include <QWidget>

// 设置全局样式表
void QUIHelper::SetStyle(QWidget* wid, const QString& qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss;
        QStringList list;
        QTextStream in(&file);
        //        in.setCodec("utf-8");
        //        while (!in.atEnd()) {
        //            QString line;
        //            in >> line;
        //            list << line;
        //        }
        //        qss = list.join("\n");
        qss = in.readAll();
        QString paletteColor = qss.mid(15, 7);
        if (wid) {
            wid->setPalette(QPalette(QColor(paletteColor)));
            wid->setStyleSheet(qss);
            wid->setAutoFillBackground(true);
        } else {
            qApp->setPalette(QPalette(QColor(paletteColor)));
            qApp->setStyleSheet(qss);
        }

        file.close();
    }
}

// 获取本机ip
QStringList QUIHelper::GetLocalIP()
{
    QStringList ips;
    QList<QHostAddress> addrs = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, addrs) {
        QString ip = addr.toString();
        if (QUIHelper::IsIP(ip)) {
            ips << ip;
        }
    }
    //    //优先取192开头的IP,如果获取不到IP则取127.0.0.1
    //    QString ip = "127.0.0.1";
    //    foreach (QString str, ips) {
    //        if (str.startsWith("192.168.1") || str.startsWith("192")) {
    //            ip = str;
    //            break;
    //        }
    //    }
    return ips;
}

// 是否是IP
bool QUIHelper::IsIP(const QString& ip)
{
    QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.)"
                   "{3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    return RegExp.exactMatch(ip);
}

// TaskBar 状态
void QUIHelper::ActiveTaskBarButton(QPushButton* button)
{
    button->setStyleSheet(QLatin1String("QPushButton {background-color: #002A38; color: #DDDBDB; border-style: none; \
                                     border-left: 1px solid #4F686B; border-right: 1px solid #4F686B;}"));
}

void QUIHelper::DisableTaskBarButton(QPushButton* button)
{
    button->setStyleSheet(QLatin1String("QPushButton {background-color:#002A38; color: #828282; border-style: none; \
                                      border-left: 1px solid #001A1E; border-right: 1px solid #4F686B;}"));
}

void QUIHelper::CurrentTaskBarButton(QPushButton* button)
{
    button->setStyleSheet(QLatin1String("QPushButton {background-color: #323333; color: #6BD6FC; border-style: none; \
                                      border-left: 1px solid #323333; border-right: 1px solid #323333; border-bottom: 8px solid #6BD6FC;}"));
}

// 按钮样式
void QUIHelper::SetCircularButtonStatus(QPushButton* button, const QString& image_name)
{
    QString sytle;
    sytle = QString("\
                     QPushButton{\
                         border:none;\
                         border-radius:25px;\
                         width:50px;\
                         height:50px;\
                         background-image: url(:/btn/%1.png);\
                         background-repeat: no-repeat;\
                         background-position: center center;\
                     }\
                     ")
              .arg(image_name);
    button->setStyleSheet(sytle);
}

void QUIHelper::SetInteractionButtonStatus(QPushButton* button, const QString& image_name)
{
    QString sytle;
    sytle = QString("\
                    QPushButton{background-color:transparent;\
                    border-image: url(:/interaction/%1.png);}\
                    QPushButton:hover{border-image:url(:/interaction/%1_hover.png);}\
                    QPushButton:pressed{border-image:url(:/interaction/%1_pressed.png);}\
                    ")
              .arg(image_name);
    button->setStyleSheet(sytle);
}

void QUIHelper::SetTransparentButtonStatus(QPushButton* button, const QString& image_name)
{
    QString sytle;
    sytle = QString("\
                    QPushButton{background-color:transparent;\
                    border-image: url(:/btn/%1.png);}\
                    QPushButton:hover{border-image:url(:/btn/%1_hover.png);}\
                    QPushButton:pressed{border-image:url(:/btn/%1_pressed.png);}\
                    ")
              .arg(image_name);
    button->setStyleSheet(sytle);
}

// 用于字符串转换
QString QUIHelper::DecimalToStrHex(int decimal)
{
    QString temp = QString::number(decimal, 16);
    if (temp.length() == 1) {
        temp = "0" + temp;
    }
    return temp;
}

int QUIHelper::StrHexToDecimal(const QString& strHex)
{
    bool ok;
    return strHex.toInt(&ok, 16);
}

QString QUIHelper::ByteArrayToAsciiStr(const QByteArray& data)
{
    QString temp;
    int len = data.size();
    for (int i = 0; i < len; i++) {
        // 0x20为空格,空格以下都是不可见字符
        char b = data.at(i);
        if (0x00 == b) {
            temp += QString("\\NUL");
        } else if (0x01 == b) {
            temp += QString("\\SOH");
        } else if (0x02 == b) {
            temp += QString("\\STX");
        } else if (0x03 == b) {
            temp += QString("\\ETX");
        } else if (0x04 == b) {
            temp += QString("\\EOT");
        } else if (0x05 == b) {
            temp += QString("\\ENQ");
        } else if (0x06 == b) {
            temp += QString("\\ACK");
        } else if (0x07 == b) {
            temp += QString("\\BEL");
        } else if (0x08 == b) {
            temp += QString("\\BS");
        } else if (0x09 == b) {
            temp += QString("\\HT");
        } else if (0x0A == b) {
            temp += QString("\\LF");
        } else if (0x0B == b) {
            temp += QString("\\VT");
        } else if (0x0C == b) {
            temp += QString("\\FF");
        } else if (0x0D == b) {
            temp += QString("\\CR");
        } else if (0x0E == b) {
            temp += QString("\\SO");
        } else if (0x0F == b) {
            temp += QString("\\SI");
        } else if (0x10 == b) {
            temp += QString("\\DLE");
        } else if (0x11 == b) {
            temp += QString("\\DC1");
        } else if (0x12 == b) {
            temp += QString("\\DC2");
        } else if (0x13 == b) {
            temp += QString("\\DC3");
        } else if (0x14 == b) {
            temp += QString("\\DC4");
        } else if (0x15 == b) {
            temp += QString("\\NAK");
        } else if (0x16 == b) {
            temp += QString("\\SYN");
        } else if (0x17 == b) {
            temp += QString("\\ETB");
        } else if (0x18 == b) {
            temp += QString("\\CAN");
        } else if (0x19 == b) {
            temp += QString("\\EM");
        } else if (0x1A == b) {
            temp += QString("\\SUB");
        } else if (0x1B == b) {
            temp += QString("\\ESC");
        } else if (0x1C == b) {
            temp += QString("\\FS");
        } else if (0x1D == b) {
            temp += QString("\\GS");
        } else if (0x1E == b) {
            temp += QString("\\RS");
        } else if (0x1F == b) {
            temp += QString("\\US");
        } else if (0x7F == b) {
            temp += QString("\\x7F");
        } else if (0x5C == b) {
            temp += QString("\\x5C");
        } else if (0x20 >= b) {
            temp += QString("\\x%1").arg(DecimalToStrHex(static_cast<quint8>(b)));
        } else {
            temp += QString("%1").arg(b);
        }
    }
    return temp.trimmed();
}

char QUIHelper::ConvertHexChar(char ch)
{
    if ((ch >= '0') && (ch <= '9')) {
        return ch - 0x30;
    } else if ((ch >= 'A') && (ch <= 'F')) {
        return ch - 'A' + 10;
    } else if ((ch >= 'a') && (ch <= 'f')) {
        return ch - 'a' + 10;
    } else {
        return (-1);
    }
}

QByteArray QUIHelper::HexStrToByteArray(const QString& str)
{
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len / 2);
    char lstr, hstr;
    for (int i = 0; i < len;) {
        hstr = str.at(i).toLatin1();
        if (hstr == ' ') {
            i++;
            continue;
        }
        i++;
        if (i >= len) {
            break;
        }
        lstr = str.at(i).toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if ((hexdata == 16) || (lowhexdata == 16)) {
            break;
        } else {
            hexdata = hexdata * 16 + lowhexdata;
        }
        i++;
        senddata[hexdatalen] = static_cast<char>(hexdata);
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

QByteArray QUIHelper::AsciiStrToByteArray(const QString& str)
{
    QByteArray buffer;
    int len = str.length();
    QString letter;
    QString hex;
    for (int i = 0; i < len; i++) {
        letter = str.at(i);
        if (letter == "\\") {
            i++;
            letter = str.mid(i, 1);
            if (letter == "x") {
                i++;
                hex = str.mid(i, 2);
                buffer.append(static_cast<char>(StrHexToDecimal(hex)));
                i++;
                continue;
            } else if (letter == "N") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "L") { // NUL=0x00
                        buffer.append(static_cast<char>(0x00));
                        continue;
                    }
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "K") { // NAK=0x15
                        buffer.append(0x15);
                        continue;
                    }
                }
            } else if (letter == "S") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "H") { // SOH=0x01
                        buffer.append(0x01);
                        continue;
                    } else { // SO=0x0E
                        buffer.append(0x0E);
                        i--;
                        continue;
                    }
                } else if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "X") { // STX=0x02
                        buffer.append(0x02);
                        continue;
                    }
                } else if (hex == "I") { // SI=0x0F
                    buffer.append(0x0F);
                    continue;
                } else if (hex == "Y") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "N") { // SYN=0x16
                        buffer.append(0x16);
                        continue;
                    }
                } else if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "B") { // SUB=0x1A
                        buffer.append(0x1A);
                        continue;
                    }
                }
            } else if (letter == "E") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "X") { // ETX=0x03
                        buffer.append(0x03);
                        continue;
                    } else if (hex == "B") { // ETB=0x17
                        buffer.append(0x17);
                        continue;
                    }
                } else if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "T") { // EOT=0x04
                        buffer.append(0x04);
                        continue;
                    }
                } else if (hex == "N") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "Q") { // ENQ=0x05
                        buffer.append(0x05);
                        continue;
                    }
                } else if (hex == "M") { // EM=0x19
                    buffer.append(0x19);
                    continue;
                } else if (hex == "S") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "C") { // ESC=0x1B
                        buffer.append(0x1B);
                        continue;
                    }
                }
            } else if (letter == "A") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "K") { // ACK=0x06
                        buffer.append(0x06);
                        continue;
                    }
                }
            } else if (letter == "B") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "E") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "L") { // BEL=0x07
                        buffer.append(0x07);
                        continue;
                    }
                } else if (hex == "S") { // BS=0x08
                    buffer.append(0x08);
                    continue;
                }
            } else if (letter == "C") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "R") { // CR=0x0D
                    buffer.append(0x0D);
                    continue;
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "N") { // CAN=0x18
                        buffer.append(0x18);
                        continue;
                    }
                }
            } else if (letter == "D") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "L") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "E") { // DLE=0x10
                        buffer.append(0x10);
                        continue;
                    }
                } else if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);
                    if (hex == "1") { // DC1=0x11
                        buffer.append(0x11);
                        continue;
                    } else if (hex == "2") { // DC2=0x12
                        buffer.append(0x12);
                        continue;
                    } else if (hex == "3") { // DC3=0x13
                        buffer.append(0x13);
                        continue;
                    } else if (hex == "4") { // DC2=0x14
                        buffer.append(0x14);
                        continue;
                    }
                }
            } else if (letter == "F") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "F") { // FF=0x0C
                    buffer.append(0x0C);
                    continue;
                } else if (hex == "S") { // FS=0x1C
                    buffer.append(0x1C);
                    continue;
                }
            } else if (letter == "H") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "T") { // HT=0x09
                    buffer.append(0x09);
                    continue;
                }
            } else if (letter == "L") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "F") { // LF=0x0A
                    buffer.append(0x0A);
                    continue;
                }
            } else if (letter == "G") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "S") { // GS=0x1D
                    buffer.append(0x1D);
                    continue;
                }
            } else if (letter == "R") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "S") { // RS=0x1E
                    buffer.append(0x1E);
                    continue;
                }
            } else if (letter == "U") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "S") { // US=0x1F
                    buffer.append(0x1F);
                    continue;
                }
            } else if (letter == "V") {
                i++;
                hex = str.mid(i, 1);
                if (hex == "T") { // VT=0x0B
                    buffer.append(0x0B);
                    continue;
                }
            } else if (letter == "\\") {
                //如果连着的是多个\\则对应添加\对应的16进制0x5C
                buffer.append(0x5C);
                continue;
            } else {
                //将对应的\[前面的\\也要加入
                buffer.append(0x5C);
                buffer.append(letter.toLatin1());
                continue;
            }
        }
        buffer.append(str.mid(i, 1).toLatin1());
    }
    return buffer;
}

QString QUIHelper::ByteArrayToHexStr(const QByteArray& data)
{
    QString temp = "";
    QString hex = data.toHex();
    for (int i = 0; i < hex.length(); i = i + 2) {
        temp += hex.mid(i, 2) + " ";
    }
    return temp.trimmed().toUpper();
}
