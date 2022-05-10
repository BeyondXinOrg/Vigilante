#include "edge.h"

// 边缘放在地图上
Edge::Edge()
{
}

Edge::Edge(const Cell& tmp_from, const Cell& tmp_to, int tmp_weight)
  : from(tmp_from)
  , to(tmp_to)
  , weight(tmp_weight)
{
    Q_ASSERT(from != to); // 确保 from 和 to 不一样
}
