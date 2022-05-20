#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QFile>
#include <QString>

/**
 * @brief The FileUtil class
 * 文件操作
 */
class FileUtil : public QFile
{
public:
    // 继承QFile，可以绑定 软件操作的文件和数据库
    // 暂时没空搞，防止数据篡改，后续软件生成的所有文件都需要FileUtil过一遍，把文件大小和
    // 文件最后修改时间存到数据库里，启动软件时校验文件篡改。
    explicit FileUtil(const QString& name);
    virtual ~FileUtil() override;

public:
    // 通用文件操作

    // 复制文件
    static bool FileCopy(const QString& src, const QString& dst, const bool cover = false);
    // 复制路径
    static bool DirCopy(const QString& src, const QString& dst);
    // 路径是否存在
    static bool DirExist(const QString& path);
    // 文件是否存在
    static bool FileExist(const QString& path);
    // 创建路径
    static bool DirMake(const QString& path);
    // 删除路径
    static bool DirRemove(const QString& path);
    // 清空路径（保留文件）
    static bool DirClear(const QString& path);
    // 获取全局路径
    static QString GetFullPath(const QString& path);
    // 删除文件或路径
    static bool DeleteFileOrFolder(const QString& strPath);
    // 文件是否存在
    static bool FileIsExist(const QString& strFile);
    // 弹窗获取选择文件
    static QString GetFolderName();

public:
    // 软件级别文件操作
    static bool DirInitial(const QString& app_path);
};

#endif // FILEUTIL_H
