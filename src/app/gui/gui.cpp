#include "gui.h"

Gui::Gui()
  : parent_gui_(nullptr)
{
    scene_mgr_ = nullptr;
}

Gui::~Gui()
{
    for (Gui* gui : child_guis_) {
        delete gui;
    }
}

QPointF Gui::GuiPos()
{
    return GetGraphicsItem()->pos();
}

void Gui::SetGuiPos(const QPointF& pos)
{
    GetGraphicsItem()->setPos(pos);
}

void Gui::SetGuiRotation(double degrees)
{
    GetGraphicsItem()->setRotation(degrees);
}

void Gui::SetParentGui(Gui* gui)
{
    // gui为空，但父级已经为空
    if (gui == nullptr && parent_gui_ == nullptr)
        return;

    // gui为空，但它有父级
    if (gui == nullptr && parent_gui_ != nullptr) {
        parent_gui_->child_guis_.remove(this);
        GetGraphicsItem()->setParentItem(nullptr);
        GetGraphicsItem()->setVisible(false);
        parent_gui_ = nullptr;
        return;
    }

    // gui不为空
    GetGraphicsItem()->setParentItem(gui->GetGraphicsItem());
    GetGraphicsItem()->setVisible(true);
    gui->child_guis_ << this;
    parent_gui_ = gui;
}

QRectF Gui::GetGuiBoundingBox()
{
    QList<QRectF> bboxes =
      GetBoundingBoxesFor(GetGraphicsItem(), GetGraphicsItem());

    QRectF initialRect = bboxes[0];
    double lowestY = initialRect.top();
    double highestY = initialRect.bottom();
    double lowestX = initialRect.left();
    double highestX = initialRect.right();

    for (QRectF rect : bboxes) {
        if (rect.top() < lowestY)
            lowestY = rect.top();
        if (rect.bottom() > highestY)
            highestY = rect.bottom();
        if (rect.left() < lowestX)
            lowestX = rect.left();
        if (rect.right() > highestX)
            highestX = rect.right();
    }

    QRectF total_box(
      QPointF(lowestX, lowestY), QPointF(highestX, highestY));
    total_box.moveTopLeft(QPointF(0, 0));

    return total_box;
}

QList<QRectF> Gui::GetBoundingBoxesFor(
  QGraphicsItem* gi, QGraphicsItem* map_to)
{
    QList<QRectF> boxes;
    QRectF bbox = gi->boundingRect();
    bbox.moveTopLeft(gi->mapToItem(map_to, QPointF(0, 0)));
    boxes.push_back(bbox);

    for (QGraphicsItem* child : gi->childItems()) {
        QList<QRectF> childBBoxes = GetBoundingBoxesFor(child, map_to);
        for (QRectF rect : childBBoxes) {
            boxes.push_back(rect);
        }
    }

    return boxes;
}
