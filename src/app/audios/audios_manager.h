#ifndef AUDIOSMANAGER_H
#define AUDIOSMANAGER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>

class AudiosManager : public QObject
{
    Q_OBJECT
public:
    static AudiosManager* Instance();

    void LoadBgMusic(QString key, QString path);
    void PlayBg(QString key);
    void StopBg();

private:
    void InitPlayer();

private:
    // 背景音乐控制（单曲循环）
    QMediaPlayer* bg_player_;
    QMediaPlaylist* bg_list_;
    QHash<QString, int> bg_index_;

private:
    static AudiosManager* instance;
    explicit AudiosManager(QObject* parent = nullptr);
};

#endif // AUDIOSMANAGER_H
