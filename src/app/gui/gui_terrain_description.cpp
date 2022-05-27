#pragma execution_character_set("utf-8")

#include "gui_terrain_description.h"
#include "gui_terrain_description_item.h"

#include <QDebug>
#include <QPainter>

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

    center_item_->SetVisable(true);
    center_item_->UpdataInfo(title, content);
    center_item_->update();
}

void GuiTerrainDescription::ClearDescribe()
{
    center_item_->SetVisable(false);
    center_item_->update();
}
