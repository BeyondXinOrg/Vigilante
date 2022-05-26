#ifndef GUIPANEL_H
#define GUIPANEL_H

#include "gui.h"

class GuiButon : public Gui, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GuiButon();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

Q_SIGNALS:
    void SgnClicked(GuiButon* panel, QPointF pos, int button);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    void Draw();

private:
    QGraphicsRectItem* border_;

    QPixmap bg_pixmap_;
};

#endif // GUIPANEL_H
