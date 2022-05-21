#pragma execution_character_set("utf-8")

#include "gui_terrain_description.h"

#include <QDebug>
#include <QPainter>

TerrainDescriptionItem::TerrainDescriptionItem(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    rect_.setRect(0, 0, 750, 150);

    title_ = " ";
    content_ = " ";
    show_ = false;
}

void TerrainDescriptionItem::UpdataInfo(const QString& title, const QString& content)
{
    title_ = title;
    content_ = content;
    update();
}

QRectF TerrainDescriptionItem::boundingRect() const
{
    return rect_;
}

void TerrainDescriptionItem::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->save();

    if (show_) {
        painter->setPen(QColor(86, 74, 61));
        painter->setBrush(QColor(235, 209, 173, 125));
        painter->drawRect(rect_);
    }

    QFont font;
    font.setPointSize(25);
    painter->setPen(Qt::black);
    painter->setFont(font);
    painter->drawText(60, -15, title_);
    font.setPointSize(20);
    painter->setFont(font);
    painter->drawText(rect_.adjusted(10, 10, -10, -10), Qt::TextWordWrap | Qt::AlignLeft, content_);

    painter->restore();
}

void TerrainDescriptionItem::SetVisible(const bool& show)
{
    // 首次绘制 drawText 会造成卡顿，不使用自带的setVisable

    if (!show) {
        title_ = " ";
        content_ = " ";
    }
    show_ = show;
}

GuiTerrainDescription::GuiTerrainDescription()
  : center_item_(new TerrainDescriptionItem())
{
}

QGraphicsItem* GuiTerrainDescription::GetGraphicsItem()
{
    return center_item_;
}

void GuiTerrainDescription::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
    center_item_->setPos(QPointF(1920 - 750, 1080 - 150 - 20));
    center_item_->update();
}

void GuiTerrainDescription::Describe(TerrainType& type)
{

    QString title, content;

    switch (type) {
    case KNormal_Cell: {
        title = u8"平原";
        content = u8"平原的描述";
        break;
    }
    case KTree_Cell: {
        title = u8"树林";
        content = u8"树林的描述";
        break;
    }
    case KWall_Cell: {
        title = u8"石头";
        content = u8"石头的描述";
        break;
    }
    default:
        break;
    }

    center_item_->SetVisible(true);
    center_item_->UpdataInfo(title, content);
    center_item_->update();
}

void GuiTerrainDescription::ClearDescribe()
{
    center_item_->SetVisible(false);
    center_item_->update();
}
