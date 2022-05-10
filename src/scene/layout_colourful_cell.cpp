#include "layout_colourful_cell.h"

#include "hero/hero.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QPainter>
#include <QRectF>

LayoutColourfulCell::LayoutColourfulCell(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    scene_mgr_ = nullptr;

    brush_move_range_.setColor(QColor(80, 105, 210, 80));
    brush_move_range_.setStyle(Qt::SolidPattern);

    brush_select_.setColor(QColor(80, 105, 210, 110));
    brush_select_.setStyle(Qt::SolidPattern);

    show_move_track_ = false;
}

void LayoutColourfulCell::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
    rect_ = QRectF(0, 0,
                   scene_mgr_->GetPathGrid()->Width(),
                   scene_mgr_->GetPathGrid()->Height());
    UpdataTerrainBg();
}

QRectF LayoutColourfulCell::boundingRect() const
{
    return rect_;
}

void LayoutColourfulCell::SetSelectHero(Hero* hero)
{

    if (!scene_mgr_) { // 无场景
        return;
    }

    // 清空之前可移动范围
    move_range_rects_.clear();

    // 获取当前英雄
    if (!hero) { // 无场景
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

void LayoutColourfulCell::SetSelectCell(const Cell& cell)
{

    if (!scene_mgr_) { // 无场景
        return;
    }

    // 清空之前可移动范围
    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();
    select_rect_ = QRect(cell.x * cell_size, cell.y * cell_size, cell_size, cell_size);
    move_range_rects_.clear();

    UpdataTerrainBg(); // 更新背景图片
}

void LayoutColourfulCell::SetMovingTrack(QList<Cell> cells)
{
    show_move_track_ = true;
    move_track_pos_.clear();

    foreach (auto cell, cells) {
        move_track_pos_ << scene_mgr_->GetPathGrid()->CellToPoint(cell);
    }

    UpdataTerrainBg(); // 更新背景图片
}

void LayoutColourfulCell::HideMovingTrack()
{
    show_move_track_ = false;
    move_track_pos_.clear();

    UpdataTerrainBg(); // 更新背景图片
}

void LayoutColourfulCell::ClearSelect()
{
    move_range_rects_.clear();
    select_rect_ = QRect();
    UpdataTerrainBg();
}

void LayoutColourfulCell::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::white, 2));
    painter->drawPixmap(0, 0, bg_pix_);
}

void LayoutColourfulCell::UpdataTerrainBg()
{
    if (!scene_mgr_) {
        return;
    }

    bg_pix_ = QPixmap(rect_.width(), rect_.height());
    bg_pix_.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&bg_pix_);

    // 当前选择格子
    painter.setPen(QPen(brush_select_.color().toRgb(), 4));
    painter.setBrush(brush_select_);
    painter.drawRect(select_rect_);

    // 可移动范围
    painter.setPen(QPen(brush_move_range_.color().toRgb(), 4));
    painter.setBrush(brush_move_range_);
    painter.drawRects(move_range_rects_);

    if (show_move_track_) {
        QPainterPath path(move_track_pos_.at(0));
        for (int i = 0; i < move_track_pos_.size() - 1; ++i) {
            // 控制点的 x 坐标为 sp 与 ep 的 x 坐标和的一半
            // 第一个控制点 c1 的 y 坐标为起始点 sp 的 y 坐标
            // 第二个控制点 c2 的 y 坐标为结束点 ep 的 y 坐标
            QPointF sp = move_track_pos_[i];
            QPointF ep = move_track_pos_[i + 1];
            QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
            QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());

            path.cubicTo(c1, c2, ep);
        }
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 5));
        painter.setBrush(Qt::NoBrush);
        painter.drawPath(path);
    }

    painter.end();

    update();
}
