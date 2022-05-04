#include "colourful_map_block.h"

#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QPen>
#include <QTimer>

ColourfulMapBlock::ColourfulMapBlock()
  : center_item_(new QGraphicsRectItem())
{

    follow_pen_.setWidth(5);
    follow_pen_.setBrush(Qt::yellow);
    follow_item_ = new QGraphicsRectItem(center_item_);
    follow_item_->setPen(follow_pen_);
    //    follow_item_->setOpacity(0.15);

    follow_timer_ = new QTimer(this);
    connect(follow_timer_, &QTimer::timeout, this, &ColourfulMapBlock::FollowMouse);
}

QGraphicsItem* ColourfulMapBlock::GetGraphicsItem()
{
    return center_item_;
}

void ColourfulMapBlock::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;

    center_item_->setParentItem(scene_mgr_->GetGuiLayer());
    center_item_->setVisible(true);

    const int cell_size = scene_mgr->GetPathGrid()->CellSize();
    follow_item_->setRect(0, 0, cell_size, cell_size);
    follow_timer_->start(20);
}

void ColourfulMapBlock::FollowMouse()
{
    if (!scene_mgr_) {
        return;
    }
    Cell cell = scene_mgr_->GetCurMouseCell();
    follow_item_->setPos(scene_mgr_->GetPathGrid()->CellToTopLeftPoint(cell));
}
