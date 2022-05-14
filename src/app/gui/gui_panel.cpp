#include "gui_panel.h"

#include <QGraphicsSceneMouseEvent>

GuiPanel::GuiPanel()
  : border_(new QGraphicsRectItem())
{
    setAcceptHoverEvents(true);
    border_->setParentItem(this);
    border_->setVisible(false);

    bg_pixmap_ = QPixmap("./invcellbg.png").scaled(60, 60);
    setPixmap(bg_pixmap_);
    Draw();
}

QGraphicsItem* GuiPanel::GetGraphicsItem()
{
    return this;
}

void GuiPanel::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
}

void GuiPanel::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit SgnClicked(this, event->pos(), event->button());
}

void GuiPanel::Draw()
{
}
