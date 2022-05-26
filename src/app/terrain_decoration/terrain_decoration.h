#ifndef TERRAINDECORATION_H
#define TERRAINDECORATION_H

#include <QGraphicsItem>
#include <QSet>

class SceneManager;

class TerrainDecoration : public QObject
{
    Q_OBJECT
public:
    TerrainDecoration();
    virtual ~TerrainDecoration();

    // 返回包含Gui图形的根 QGraphicsItem
    virtual QGraphicsItem* GetGraphicsItem() = 0;

    // 设置 manager
    virtual void SetSceneManager(SceneManager* scene_mgr) = 0;

    // 是否隐藏
    virtual void SetVisable(const bool& show);

protected:
    SceneManager* scene_mgr_;
};

#endif // TERRAINDECORATION_H
