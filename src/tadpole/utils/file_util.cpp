#include "file_util.h"

#include <QDebug>
#include <QFileDialog>

FileUtil::FileUtil(const QString& name)
  : QFile(name)
{
}

FileUtil::~FileUtil()
{
}

// 复制文件
bool FileUtil::FileCopy(const QString& src, const QString& dst, const bool cover)
{
    if (!QFile::exists(src)) {
        return false;
    }
    if (cover && QFile::exists(dst)) {
        QFile::remove(dst);
    }
    return QFile::copy(src, dst);
}

// 复制路径
bool FileUtil::DirCopy(const QString& src, const QString& dst)
{
    bool result = true;
    QDir dir(src);
    if (!dir.exists()) {
        return false;
    }
    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        FileUtil::DirMake(dst_path);
        result = result && FileUtil::DirCopy(src + QDir::separator() + d, dst_path);
    }
    foreach (QString f, dir.entryList(QDir::Files)) {
        result = result && QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
    return result;
}

// 路径是否存在
bool FileUtil::DirExist(const QString& path)
{
    QDir dir(path);
    return dir.exists();
}

// 文件是否存在
bool FileUtil::FileExist(const QString& path)
{
    QFileInfo dir(path);
    return dir.exists();
}

// 创建路径
bool FileUtil::DirMake(const QString& path)
{
    QString full_path = GetFullPath(path);
    QDir dir(full_path);
    if (dir.exists()) {
        return true;
    } else {
        return dir.mkpath(full_path);
    }
}

// 删除路径
bool FileUtil::DirRemove(const QString& path)
{
    if (path.isEmpty()) {
        qWarning() << "the path is empty error! ";
        return false;
    }
    QDir dir(path);
    return dir.removeRecursively();
}

// 清空路径（保留文件）
bool FileUtil::DirClear(const QString& path)
{
    return DeleteFileOrFolder(path) && DirMake(path);
}

// 获取全局路径
QString FileUtil::GetFullPath(const QString& path)
{
    QFileInfo file_info(path);
    return file_info.absoluteFilePath();
}

// 删除文件或路径
bool FileUtil::DeleteFileOrFolder(const QString& strPath)
{
    if (strPath.isEmpty() || !QDir().exists(strPath)) { //是否传入了空的路径||路径是否存在
        return false;
    }
    QFileInfo FileInfo(strPath);
    if (FileInfo.isFile()) { //如果是文件
        QFile::remove(strPath);
    } else if (FileInfo.isDir()) { //如果是文件夹
        QDir qDir(strPath);
        qDir.removeRecursively();
    }
    return true;
}

// 文件是否存在
bool FileUtil::FileIsExist(const QString& strFile)
{
    QFile tempFile(strFile);
    return tempFile.exists();
}

// 弹窗获取选择文件
QString FileUtil::GetFolderName()
{
    return QFileDialog::getExistingDirectory();
}

// 软件级别文件操作
bool FileUtil::DirInitial(const QString& app_path)
{
    bool result = true;
    FileUtil::DeleteFileOrFolder(app_path + "/cache/"); // 软件启动清空本地临时文件
    FileUtil::DeleteFileOrFolder(app_path + "/image/"); // 软件启动清空本地临时文件
    FileUtil::DirMake(app_path + "/image/");
    FileUtil::DirMake(app_path + "/etc/");
    FileUtil::DirMake(app_path + "/cache/");
    return result;
}
