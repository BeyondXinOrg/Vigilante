#include "xml_util.h"

#include <QDebug>
#include <QMap>
#include <QXmlStreamReader>

// 构造
XmlUtil::XmlUtil()
{
}

// 析构
XmlUtil::~XmlUtil()
{
}

// 设置xml 路径
void XmlUtil::SetXmlPath(const QString& xml_path)
{
    xml_path_ = xml_path;
}

// 保存或者更新数据（不删除原来的）
bool XmlUtil::SaveOrUpdateXmlInfo(const QMap<QString, QVariant>& key_list)
{
    QMap<QString, QVariant> xml_list;
    if (QFile::exists(xml_path_)) {
        bool result = this->ReadXmlInfo(xml_list);
        if (!result) {
            return false;
        }
    }
    for (auto ite = key_list.constBegin(); ite != key_list.constEnd(); ++ite) {
        xml_list.insert(ite.key(), ite.value());
    }
    return this->SaveXmlInfo(xml_list);
}

// 保存数据（删除原来的）
bool XmlUtil::SaveXmlInfo(const QMap<QString, QVariant>& key_list)
{
    QFile file(xml_path_);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning() << "xml file open error";
        return false;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument("1.0", true);
    writer.writeStartElement("meta");
    for (auto ite = key_list.begin(); ite != key_list.end(); ite++) {
        writer.writeStartElement("data");
        writer.writeTextElement("key", ite.key());
        writer.writeTextElement("value", ite.value().toString());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
    return true;
}

// 读取数据
bool XmlUtil::ReadXmlInfo(QMap<QString, QVariant>& key_list)
{
    QFile file(xml_path_);
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << "xml file open error";
        return false;
    }
    if (file.size() == 0) {
        return true;
    }
    QXmlStreamReader reader(&file);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            static QString key, value;
            if (reader.name() == "key") {
                key = reader.readElementText();
            } else if (reader.name() == "value") {
                value = reader.readElementText();
                key_list.insert(key, value);
            }
        }
    }
    if (reader.hasError()) {
        qWarning() << "xml file open error" << reader.errorString();
        file.close();
        return false;
    }
    file.close();
    return true;
}

// 读取数据
bool XmlUtil::ReadXmlInfo(
  const QString& xml_path,
  QMap<QString, QVariant>& key_list)
{
    QFile file(xml_path);
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << "xml file open error";
        return false;
    }
    if (file.size() == 0) {
        return true;
    }
    QXmlStreamReader reader(&file);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            static QString key, value;
            if (reader.name() == "key") {
                key = reader.readElementText();
            } else if (reader.name() == "value") {
                value = reader.readElementText();
                key_list.insert(key, value);
            }
        }
    }
    if (reader.hasError()) {
        qWarning() << "xml file open error" << reader.errorString();
        file.close();
        return false;
    }
    file.close();
    return true;
}

// 保存数据
bool XmlUtil::SaveXmlInfo(
  const QString& xml_path,
  const QMap<QString, QVariant>& key_list)
{
    QFile file(xml_path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning() << "xml file open error";
        return false;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument("1.0", true);
    writer.writeStartElement("meta");
    for (auto ite = key_list.begin(); ite != key_list.end(); ite++) {
        writer.writeStartElement("data");
        writer.writeTextElement("key", ite.key());
        writer.writeTextElement("value", ite.value().toString());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();

    return true;
}

// 保存或更新数据
bool XmlUtil::SaveOrUpdateXmlInfo(
  const QString& xml_path,
  const QMap<QString, QVariant>& key_list)
{
    QMap<QString, QVariant> xml_list;
    if (QFile::exists(xml_path)) {
        bool result = ReadXmlInfo(xml_path, xml_list);
        if (!result) {
            return false;
        }
    }
    for (auto ite = key_list.constBegin(); ite != key_list.constEnd(); ++ite) {
        xml_list.insert(ite.key(), ite.value());
    }
    return SaveXmlInfo(xml_path, xml_list);
}
