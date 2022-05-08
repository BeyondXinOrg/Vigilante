#include "layout_instructions.h"

#include "hero/hero.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QPainter>
#include <QRectF>

LayoutInstructions::LayoutInstructions(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    scene_mgr_ = nullptr;

    brush_move_range_.setColor(QColor(80, 105, 210, 80));
    brush_move_range_.setStyle(Qt::SolidPattern);

    brush_select_.setColor(QColor(80, 105, 210, 110));
    brush_select_.setStyle(Qt::SolidPattern);
}

QRectF LayoutInstructions::boundingRect() const
{
    return rect_;
}

void LayoutInstructions::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
    Resize(scene_mgr_->GetPathGrid()->Width(),
           scene_mgr_->GetPathGrid()->Height());
}

void LayoutInstructions::ChangeSelectHero(Hero* hero)
{
    // 无场景
    if (!scene_mgr_) {
        return;
    }

    // 清空之前可移动范围
    move_range_rects_.clear();

    // 获取当前英雄
    if (hero == nullptr) {
        hero = scene_mgr_->GetCurMouseHero();
    }
    if (!hero) {
        UpdataTerrainBg();
        return;
    }

    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();
    auto move_range_cells = hero->GetMovingRange();
    foreach (auto var, move_range_cells) {
        move_range_rects_
          << QRect(var.x * cell_size, var.y * cell_size,
                   cell_size, cell_size);
    }

    Cell cell = hero->GetCell();
    select_rect_ = QRect(cell.x * cell_size, cell.y * cell_size, cell_size, cell_size);

    // 更新背景图片
    UpdataTerrainBg();
}

// 切换当前选择的格子，刷新层
void LayoutInstructions::ChangeSelectCell(const Cell& cell)
{
    // 无场景
    if (!scene_mgr_) {
        return;
    }

    // 清空之前可移动范围
    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();
    select_rect_ = QRect(cell.x * cell_size, cell.y * cell_size, cell_size, cell_size);
    move_range_rects_.clear();

    // 更新背景图片
    UpdataTerrainBg();
}

void LayoutInstructions::Resize(int width, int heigh)
{
    rect_ = QRectF(0, 0, width, heigh);
    UpdataTerrainBg();
}

void LayoutInstructions::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::white, 2));
    painter->drawPixmap(0, 0, bg_pix_);
}

void LayoutInstructions::UpdataTerrainBg()
{
    if (!scene_mgr_) {
        return;
    }

    bg_pix_ = QPixmap(rect_.width(), rect_.height());
    bg_pix_.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&bg_pix_);

    // 当前选择格子
    painter.setPen(QPen(brush_select_.color(), 4));
    painter.setBrush(brush_select_);
    painter.drawRect(select_rect_);

    // 可移动范围
    painter.setPen(QPen(brush_move_range_.color(), 4));
    painter.setBrush(brush_move_range_);
    painter.drawRects(move_range_rects_);

    painter.end();

    update();
}
