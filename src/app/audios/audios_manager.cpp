#include "audios_manager.h"

#include <QMutex>

AudiosManager* AudiosManager::instance = nullptr;
AudiosManager* AudiosManager::Instance()
{
    if (!instance) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (!instance) {
            instance = new AudiosManager;
        }
    }
    return instance;
}

void AudiosManager::LoadBgMusic(QString key, QString path)
{
    bg_list_->addMedia(QMediaContent(QUrl(path)));
    bg_index_[key] = bg_list_->mediaCount() - 1;
}

void AudiosManager::PlayBg(QString key)
{
    StopBg();
    if (bg_index_.contains(key)) {
        bg_list_->setCurrentIndex(bg_index_.value(key));
        bg_player_->play();
    }
}

void AudiosManager::StopBg()
{
    bg_player_->stop();
}

void AudiosManager::InitPlayer()
{
    bg_player_ = new QMediaPlayer(this);
    bg_list_ = new QMediaPlaylist(this);
    bg_list_->setPlaybackMode(QMediaPlaylist::Loop);
    bg_player_->setPlaylist(bg_list_);
    bg_player_->setVolume(100);
}

AudiosManager::AudiosManager(QObject* parent)
  : QObject(parent)
{
    InitPlayer();
}
