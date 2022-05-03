#include "battle_view.h"

BattleView::BattleView(QWidget* parent)
  : QGraphicsView(parent)
{
    // 禁用QGraphicsView的滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 追踪鼠标
    setMouseTracking(true);
}

BattleView::~BattleView()
{
}
