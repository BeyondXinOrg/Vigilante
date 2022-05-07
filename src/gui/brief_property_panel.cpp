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
    center_item_->setVisible(true);
    center_item_->setPos(QPointF(1920 - 750,
                                 1080 - 150 - 20));
}

void BriefPropertyPanel::DescribeHero(Hero* hero)
{
    center_item_->setVisible(true);
}

void BriefPropertyPanel::DescribeTerrain(Hero* hero)
{
    center_item_->setVisible(true);
}

void BriefPropertyPanel::DescribeNone()
{
    center_item_->setVisible(false);
}
