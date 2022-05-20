#ifndef XMLUTIL_H
#define XMLUTIL_H

#include <QFile>
#include <QString>

/**
 * @brief The XmlUtil class
 * xml 文件操作
 */
class XmlUtil : public QObject
{
    Q_OBJECT
public:
    // 构造
    explicit XmlUtil();
    // 析构
    virtual ~XmlUtil() override;
    // 设置xml 路径
    void SetXmlPath(const QString& xml_path);
    // 保存或者更新数据（不删除原来的）
    bool SaveOrUpdateXmlInfo(const QMap<QString, QVariant>& key_list);
    // 保存数据（删除原来的）
    bool SaveXmlInfo(const QMap<QString, QVariant>& key_list);
    // 读取数据
    bool ReadXmlInfo(QMap<QString, QVariant>& key_list);

    // 读取数据
    static bool ReadXmlInfo(const QString& xml_path,
                            QMap<QString, QVariant>& key_list);
    // 保存数据
    static bool SaveXmlInfo(const QString& xml_path,
                            const QMap<QString, QVariant>& key_list);
    // 保存或更新数据
    static bool SaveOrUpdateXmlInfo(const QString& xml_path,
                                    const QMap<QString, QVariant>& key_list);

private:
    QString xml_path_;
};

#endif // XMLUTIL_H
