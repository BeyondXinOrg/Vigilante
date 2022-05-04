#include "colourful_map_block.h"

#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QPen>
#include <QTimer>

ColourfulMapBlock::ColourfulMapBlock()
  : center_item_(new QGraphicsRectItem())
{
    QPen pen(Qt::yellow, 5);
    blocks_brush_[KHoverBlockType] = pen;
    blocks_[KHoverBlockType] << new QGraphicsRectItem(center_item_);
    blocks_[KHoverBlockType][0]->setPen(blocks_brush_[KHoverBlockType]);

    pen.setBrush(Qt::green);
    blocks_brush_[KPlayerCampType] = pen;

    pen.setBrush(Qt::red);
    blocks_brush_[KEnemyCampType] = pen;

    pen.setBrush(Qt::white);
    blocks_brush_[KCurHeroBolockType] = pen;
    blocks_[KCurHeroBolockType] << new QGraphicsRectItem(center_item_);
    blocks_[KCurHeroBolockType][0]->setPen(blocks_brush_[KCurHeroBolockType]);
    blocks_[KCurHeroBolockType][0]->setVisible(false);

    follow_timer_ = new QTimer(this);
    connect(follow_timer_, &QTimer::timeout, this, &ColourfulMapBlock::FollowMouse);
}

QGraphicsItem* ColourfulMapBlock::GetGraphicsItem()
{
    return center_item_;
}

// 将ui增加到scene中
void ColourfulMapBlock::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;

    center_item_->setParentItem(scene_mgr_->GetGuiLayer());
    center_item_->setVisible(true);

    const int cell_size = scene_mgr->GetPathGrid()->CellSize();
    blocks_[KHoverBlockType][0]->setRect(0, 0, cell_size, cell_size);
    follow_timer_->start(20);

    const int space = 5;
    cell_rect_ = QRectF(space, space, cell_size - space * 2, cell_size - space * 2);
}

// 更新当前人物格子
void ColourfulMapBlock::ShowCurHeroBlock(const Cell& cur_cell)
{
    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();
    blocks_[KCurHeroBolockType][0]->setVisible(true);
    blocks_[KCurHeroBolockType][0]->setPos(cur_cell.x * cell_size, cur_cell.y * cell_size);
}

// 隐藏当前人物格子，操作结束等待下一个人物
void ColourfulMapBlock::HideCurHeroBlock()
{
    blocks_[KCurHeroBolockType][0]->setVisible(false);
}

// 更新阵营格子
void ColourfulMapBlock::UpdataCampBlock(
  const QList<Cell>& player_cell, const QList<Cell>& enemy_cell)
{
    qDeleteAll(blocks_[KPlayerCampType]);
    blocks_[KPlayerCampType].clear();
    qDeleteAll(blocks_[KEnemyCampType]);
    blocks_[KEnemyCampType].clear();

    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();

    foreach (auto cell, player_cell) {
        QGraphicsRectItem* item = new QGraphicsRectItem(center_item_);
        item->setPen(blocks_brush_[KPlayerCampType]);
        item->setOpacity(0.9);
        item->setRect(cell_rect_);
        item->setPos(cell.x * cell_size, cell.y * cell_size);
        blocks_[KPlayerCampType] << item;
    }

    foreach (auto cell, enemy_cell) {
        QGraphicsRectItem* item = new QGraphicsRectItem(center_item_);
        item->setPen(blocks_brush_[KEnemyCampType]);
        item->setOpacity(0.9);
        item->setRect(cell_rect_);
        item->setPos(cell.x * cell_size, cell.y * cell_size);
        blocks_[KEnemyCampType] << item;
    }
}

// 更新鼠标移动格子
void ColourfulMapBlock::FollowMouse()
{
    if (!scene_mgr_) {
        return;
    }
    Cell cell = scene_mgr_->GetCurMouseCell();
    blocks_[KHoverBlockType][0]->setPos(scene_mgr_->GetPathGrid()->CellToTopLeftPoint(cell));
}
