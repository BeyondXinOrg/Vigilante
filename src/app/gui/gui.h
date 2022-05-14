#ifndef GUI_H
#define GUI_H

#include <QGraphicsItem>
#include <QSet>

class SceneManager;

class Gui : public QObject
{
    Q_OBJECT

    friend class Game;

public:
    Gui();
    virtual ~Gui();

    QPointF GuiPos();

    void SetGuiPos(const QPointF& pos);
    void SetGuiRotation(double degrees);
    void SetParentGui(Gui* gui);

    // 返回包含Gui图形的根 QGraphicsItem
    virtual QGraphicsItem* GetGraphicsItem() = 0;

    // 返回Gui的边界框
    virtual QRectF GetGuiBoundingBox();

    // 设置 manager
    virtual void SetSceneManager(SceneManager* scene_mgr) = 0;

private:
    QList<QRectF> GetBoundingBoxesFor(QGraphicsItem* gi, QGraphicsItem* map_to);

protected:
    SceneManager* scene_mgr_;

    Gui* parent_gui_;
    QSet<Gui*> child_guis_;
};

#endif // GUI_H
