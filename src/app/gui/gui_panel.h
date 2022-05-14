#ifndef GUIPANEL_H
#define GUIPANEL_H

#include "gui.h"

class GuiPanel : public Gui, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GuiPanel();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

Q_SIGNALS:
    void SgnClicked(GuiPanel* panel, QPointF pos, int button);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    void Draw();

private:
    QGraphicsRectItem* border_;

    QPixmap bg_pixmap_;
};

#endif // GUIPANEL_H
