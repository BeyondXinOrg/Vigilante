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

    brush_move_range_.setColor(QColor(80, 105, 210, 180));
    brush_move_range_.setStyle(Qt::SolidPattern);
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

    if (!move_range_rects_.empty()) {
        QPainter painter;
        painter.begin(&bg_pix_);

        // 可移动范围
        painter.setPen(QPen(brush_move_range_.color(), 4));
        painter.setBrush(brush_move_range_);
        painter.drawRects(move_range_rects_);

        painter.end();
    }
    update();
}
