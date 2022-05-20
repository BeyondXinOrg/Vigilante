#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <QFile>
#include <QString>

/**
 * @brief The StringUtil class
 * 一些常用的字符串操作
 */
class StringUtil
{
public:
    // map 转 json
    static bool MapToJson(const QMap<QString, QVariant>& list, QString& msg);
    // json 转 map
    static bool JsonToMap(const QString& msg, QMap<QString, QVariant>& list);

    // list 转 json
    static bool ListDoubleToJson(const QList<QList<double>>& list, QString& msg);
    // json 转 list
    static bool JsonToListDouble(const QString& msg, QList<QList<double>>& list);

    // json 转 list map
    static bool JsonToListMap(const QString& msg, QList<QMap<QString, QVariant>>& list);
    // list map 转 json
    static bool ListMapToJson(const QList<QMap<QString, QVariant>>& list, QString& msg);

    // QVector3D 转 str
    static QString QVector3DToQStr(const QVector3D& data);
    // str 转 QVector3D
    static QVector3D QStrToQVector3D(const QString& data);

    // 数组 转 str
    static QString Double3DToQStr(double pos[3]);
    // str 转 数组
    static void QStrToDouble3D(const QString& data, QList<double>& list);

    // 获取随机字符串
    static QString GetRandString(const quint32 len,
                                 const QString& char_set =
                                   QString("0123456789"
                                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                           "abcdefghijklmnopqrstuvwxyz"));

    // md5加密
    static QString StrToMd5(const QString& str);
};
#endif // STRINGUTIL_H
