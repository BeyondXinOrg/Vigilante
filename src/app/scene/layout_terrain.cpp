#include "layout_terrain.h"

#include "data/cell_grid.h"
#include "hero/hero.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QPainter>
#include <QRandomGenerator>
#include <QRect>

LayoutTerrain::LayoutTerrain(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
}

QRectF LayoutTerrain::boundingRect() const
{
    return rect_;
}

void LayoutTerrain::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::white, 2));
    painter->drawPixmap(0, 0, bg_pix_);
}

void LayoutTerrain::Resize(int width, int heigh)
{
    rect_ = QRectF(0, 0, width, heigh);
    update();
}

void LayoutTerrain::SetSceneMap(const QString& pix_path)
{
    bg_pix_ = QPixmap(pix_path).scaled(rect_.size().toSize());
}

TerrainType LayoutTerrain::GetTerrainType(const Cell& cell)
{
    return cells_type_.value(cell);
}
