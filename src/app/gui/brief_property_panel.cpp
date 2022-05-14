#include "brief_property_panel.h"

#include "gui/brief_property_item.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QSize>

BriefPropertyPanel::BriefPropertyPanel()
  : center_item_(new BriefPropertyItem())
{
    // center_item_->setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

QGraphicsItem* BriefPropertyPanel::GetGraphicsItem()
{
    return center_item_;
}

void BriefPropertyPanel::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
    center_item_->setVisible(false);
    center_item_->setPos(QPointF(1920 - 750, 1080 - 150 - 20));
    center_item_->update();
}

void BriefPropertyPanel::Describe(TerrainType& type, Hero* hero)
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

    if (hero) {
        content = hero->BasePropertiesStr();
    }

    center_item_->setVisible(true);
    center_item_->UpdataInfo(title, content);
    center_item_->update();
}

void BriefPropertyPanel::ClearDescribe()
{
    center_item_->setVisible(false);
    center_item_->update();
}
