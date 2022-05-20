#include "string_util.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QTime>
#include <QVector3D>

// map 转 json
bool StringUtil::MapToJson(const QMap<QString, QVariant>& list, QString& msg)
{
    QJsonArray json_array;
    QJsonObject jsonObj;
    for (auto ite = list.begin(); ite != list.end(); ++ite) {
        jsonObj.insert(ite.key(), ite.value().toString());
    }
    json_array.append(jsonObj);
    QJsonDocument parse_doucment(json_array);
    msg = parse_doucment.toJson(QJsonDocument::Compact);
    return true;
}

// json 转 map
bool StringUtil::JsonToMap(const QString& msg, QMap<QString, QVariant>& list)
{
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(msg.toUtf8(), &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (parse_doucment.isArray()) {
            QJsonArray json_array = parse_doucment.array();
            QMap<QString, QVariant> temp_map;
            QJsonObject json_obj = json_array.at(0).toObject();
            for (qint32 j = 0; j < json_obj.size(); j++) {
                QString tmp = json_obj.keys().at(j);
                QVariant tp = json_obj.value(tmp).toVariant();
                list.insert(tmp, tp);
            }
            return true;
        } else {
            qWarning() << "the json is not array error! "
                          "jsonError:"
                       << json_error.error;
            return false;
        }
    } else {
        qWarning() << "the json analysisError! "
                      "jsonError:"
                   << json_error.error;
        return false;
    }
}

// list 转 json
bool StringUtil::ListDoubleToJson(const QList<QList<double>>& list, QString& msg)
{
    QJsonArray json_array;
    for (qint32 i = 0; i < list.size(); ++i) {
        QList<double> temp_list = list.at(i);
        QJsonArray temp_array;
        for (qint32 j = 0; j < temp_list.size(); ++j) {
            temp_array.append(temp_list.at(j));
        }
        json_array.append(temp_array);
    }
    QJsonDocument parse_doucment(json_array);
    msg = parse_doucment.toJson(QJsonDocument::Compact);
    return true;
}

// json 转 list
bool StringUtil::JsonToListDouble(const QString& msg, QList<QList<double>>& list)
{
    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(msg.toUtf8(), &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (parse_document.isArray()) {
            QJsonArray json_array1 = parse_document.array();
            qint32 size = json_array1.size();
            for (qint32 i = 0; i < size; ++i) {
                QList<double> temp_list;
                QJsonArray json_array2 = json_array1.at(i).toArray();
                for (qint32 j = 0; j < json_array2.size(); ++j) {
                    temp_list.append(json_array2.at(j).toDouble());
                }
                list.append(temp_list);
            }
            return true;
        } else {
            qWarning() << "the json is not array error! "
                          "jsonError:"
                       << json_error.error;
            return false;
        }
    } else {
        qWarning() << "the json analysisError! "
                      "jsonError:"
                   << json_error.error;
        return false;
    }
}

// json 转 list map
bool StringUtil::JsonToListMap(
  const QString& msg, QList<QMap<QString, QVariant>>& list)
{
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(msg.toUtf8(), &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (parse_doucment.isArray()) {
            QJsonArray json_array = parse_doucment.array();
            qint32 size = json_array.size();
            for (qint32 i = 0; i < size; i++) {
                QMap<QString, QVariant> temp_map;
                QJsonObject json_obj = json_array.at(i).toObject();
                for (qint32 j = 0; j < json_obj.size(); j++) {
                    QString tmp = json_obj.keys().at(j);
                    QVariant tp = json_obj.value(tmp).toVariant();
                    temp_map.insert(tmp, tp);
                }
                list.append(temp_map);
            }
            return true;
        } else {
            qWarning() << "the json is not array error! "
                          "jsonError:"
                       << json_error.error;
            return false;
        }
    } else {
        qWarning() << "the json analysisError! "
                      "jsonError:"
                   << json_error.error;
        return false;
    }
}

// list map 转 json
bool StringUtil::ListMapToJson(
  const QList<QMap<QString, QVariant>>& list, QString& msg)
{
    QJsonArray json_array;
    for (qint32 i = 0; i < list.size(); ++i) {
        QMap<QString, QVariant> temp_map = list.at(i);
        QJsonObject jsonObj;
        for (auto ite = temp_map.begin(); ite != temp_map.end(); ++ite) {
            jsonObj.insert(ite.key(), ite.value().toString());
        }
        json_array.append(jsonObj);
    }
    QJsonDocument parse_doucment(json_array);
    msg = parse_doucment.toJson(QJsonDocument::Compact);
    return true;
}

// QVector3D 转 str
QString StringUtil::QVector3DToQStr(const QVector3D& data)
{
    return QString("%1||%2||%3")
      .arg(QString::number(static_cast<double>(data.x())),
           QString::number(static_cast<double>(data.y())),
           QString::number(static_cast<double>(data.z())));
}

// str 转 QVector3D
QVector3D StringUtil::QStrToQVector3D(const QString& data)
{
    const auto list = data.split("||");
    return QVector3D(list.at(0).toFloat(), list.at(1).toFloat(), list.at(2).toFloat());
}

// 数组 转 str
QString StringUtil::Double3DToQStr(double pos[])
{
    return QString("%1||%2||%3")
      .arg(QString::number(pos[0]),
           QString::number(pos[1]),
           QString::number(pos[2]));
}

// str 转 数组
void StringUtil::QStrToDouble3D(const QString& data, QList<double>& list)
{
    list.clear();
    const auto datalist = data.split("||");
    list << datalist.at(0).toDouble();
    list << datalist.at(1).toDouble();
    list << datalist.at(2).toDouble();
}

// 获取随机字符串
QString StringUtil::GetRandString(
  const quint32 len, const QString& char_set)
{
    QString result("");
    QTime t = QTime::currentTime();
    qsrand(static_cast<quint32>(t.msec() + t.second() * 1000));
    for (quint32 i = 0; i < len; i++) {
        qint32 ir = qrand() % char_set.length();
        result[i] = char_set.at(ir);
    }
    return result;
}

// md5加密
QString StringUtil::StrToMd5(const QString& str)
{
    QByteArray hash = QCryptographicHash::hash(str.toLatin1(), QCryptographicHash::Md5);
    return hash.toHex();
}
