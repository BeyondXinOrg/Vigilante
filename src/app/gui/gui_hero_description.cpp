#pragma execution_character_set("utf-8")

#include "gui_hero_description.h"

#include "gui/gui_buton.h"
#include "gui/gui_hero_description_item.h"
#include "hero/hero.h"
#include "hero/hero_state.h"

#include <QDebug>
#include <QPainter>

GuiHeroDescription::GuiHeroDescription()
  : center_item_(new HeroDescriptionItem())
{
    for (int i = 0; i < 7; i++) {
        auto location_btn = new GuiButon();
        location_btn->setParentItem(center_item_);
        location_btn->setPos(40 + 100 * i, 80);
        location_btn->SetParentGui(center_item_);
        location_btn->setObjectName(QString("skill%1").arg(i));
        location_btns_ << location_btn;

        connect(location_btn, &GuiButon::SgnClicked,
                this, &GuiHeroDescription::OnClickSkill);
    }
    center_item_->SetParentGui(this);

    ClearDescribe();
}

QGraphicsItem* GuiHeroDescription::GetGraphicsItem()
{
    return center_item_;
}

void GuiHeroDescription::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
    center_item_->setPos(QPointF(20, 1080 - 150 - 20));
    center_item_->update();
}

void GuiHeroDescription::Describe(Hero* hero)
{
    SetVisable(true);

    QString title, content;
    title = hero->State()->name_;
    content = hero->State()->GetBattleState();

    center_item_->UpdataInfo(title, content);
}

void GuiHeroDescription::ClearDescribe()
{
    SetVisable(false);
}

void GuiHeroDescription::OnClickSkill(
  GuiButon* panel, QPointF pos, int button)
{
    const int id = panel->objectName().remove("skill").toInt();
    emit SgnClickedSkill(id);
}
