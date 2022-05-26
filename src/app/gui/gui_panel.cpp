#include "gui_panel.h"

#include <QGraphicsSceneMouseEvent>

GuiButon::GuiButon()
  : border_(new QGraphicsRectItem())
{
    setAcceptHoverEvents(true);
    border_->setParentItem(this);
    border_->setVisible(false);

    bg_pixmap_ = QPixmap("./invcellbg.png").scaled(60, 60);
    setPixmap(bg_pixmap_);
    Draw();
}

QGraphicsItem* GuiButon::GetGraphicsItem()
{
    return this;
}

void GuiButon::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
}

void GuiButon::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit SgnClicked(this, event->pos(), event->button());
}

void GuiButon::Draw()
{
}
