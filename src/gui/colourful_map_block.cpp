#include "colourful_map_block.h"

#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QPen>
#include <QTimer>

ColourfulMapBlock::ColourfulMapBlock()
  : center_item_(new QGraphicsRectItem())
{
    QPen pen(Qt::yellow, 5);
    blocks_brush_[KHover_Block_Type] = pen;
    blocks_[KHover_Block_Type] << new QGraphicsRectItem(center_item_);
    blocks_[KHover_Block_Type][0]->setPen(blocks_brush_[KHover_Block_Type]);
    blocks_[KHover_Block_Type][0]->setZValue(50);

    pen.setBrush(Qt::green);
    blocks_brush_[KPlayer_Camp_Type] = pen;

    pen.setBrush(Qt::red);
    blocks_brush_[KEnemy_Camp_Type] = pen;

    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    pen.setBrush(brush);
    blocks_brush_[KCurHero_Range_Type] = pen;

    pen.setBrush(Qt::white);
    blocks_brush_[KCurHero_Bolock_Type] = pen;
    blocks_[KCurHero_Bolock_Type] << new QGraphicsRectItem(center_item_);
    blocks_[KCurHero_Bolock_Type][0]->setPen(blocks_brush_[KCurHero_Bolock_Type]);
    blocks_[KCurHero_Bolock_Type][0]->setZValue(30);
    blocks_[KCurHero_Bolock_Type][0]->setVisible(false);

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
    blocks_[KHover_Block_Type][0]->setRect(0, 0, cell_size, cell_size);
    blocks_[KCurHero_Bolock_Type][0]->setRect(0, 0, cell_size, cell_size);
    follow_timer_->start(20);

    const int space = 5;
    cell_rect_ = QRectF(space, space, cell_size - space * 2, cell_size - space * 2);
}

// 更新当前人物格子
void ColourfulMapBlock::ShowCurHeroBlock(const Cell& cur_cell)
{
    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();
    blocks_[KCurHero_Bolock_Type][0]->setVisible(true);
    blocks_[KCurHero_Bolock_Type][0]->setPos(cur_cell.x * cell_size, cur_cell.y * cell_size);
}

// 隐藏当前人物格子，操作结束等待下一个人物
void ColourfulMapBlock::HideCurHeroBlock()
{
    blocks_[KCurHero_Bolock_Type][0]->setVisible(false);
}

// 设置可移动范围
void ColourfulMapBlock::ShowMovingRangeBlock(const QList<Cell>& cells)
{
    qDeleteAll(blocks_[KCurHero_Range_Type]);
    blocks_[KCurHero_Range_Type].clear();

    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();

    foreach (auto cell, cells) {
        QGraphicsRectItem* item = new QGraphicsRectItem(center_item_);
        item->setPen(blocks_brush_[KCurHero_Range_Type]);
        item->setOpacity(0.9);
        item->setRect(cell_rect_);
        item->setPos(cell.x * cell_size, cell.y * cell_size);
        blocks_[KCurHero_Range_Type] << item;
    }
}

// 更新阵营格子
void ColourfulMapBlock::UpdataCampBlock(
  const QList<Cell>& player_cell, const QList<Cell>& enemy_cell)
{
    qDeleteAll(blocks_[KPlayer_Camp_Type]);
    blocks_[KPlayer_Camp_Type].clear();
    qDeleteAll(blocks_[KEnemy_Camp_Type]);
    blocks_[KEnemy_Camp_Type].clear();

    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();

    foreach (auto cell, player_cell) {
        QGraphicsRectItem* item = new QGraphicsRectItem(center_item_);
        item->setPen(blocks_brush_[KPlayer_Camp_Type]);
        item->setOpacity(0.9);
        item->setRect(cell_rect_);
        item->setPos(cell.x * cell_size, cell.y * cell_size);
        blocks_[KPlayer_Camp_Type] << item;
    }

    foreach (auto cell, enemy_cell) {
        QGraphicsRectItem* item = new QGraphicsRectItem(center_item_);
        item->setPen(blocks_brush_[KEnemy_Camp_Type]);
        item->setOpacity(0.9);
        item->setRect(cell_rect_);
        item->setPos(cell.x * cell_size, cell.y * cell_size);
        blocks_[KEnemy_Camp_Type] << item;
    }
}

// 更新鼠标移动格子
void ColourfulMapBlock::FollowMouse()
{
    if (!scene_mgr_) {
        return;
    }
    Cell cell = scene_mgr_->GetCurMouseCell();
    blocks_[KHover_Block_Type][0]->setPos(scene_mgr_->GetPathGrid()->CellToTopLeftPoint(cell));
}
