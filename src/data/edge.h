#ifndef EDGE_H
#define EDGE_H

#include "data/cell.h"

struct Edge
{
    Edge();
    Edge(const Cell& tmp_from, const Cell& tmp_to, int tmp_weight);

    Cell from;
    Cell to;
    int weight;
};

// 支持 std::hash
namespace std {
template<>
struct hash<Edge>
{
    size_t operator()(const Edge& edge) const
    {
        return hash<Cell>()(edge.from) ^ hash<Cell>()(edge.to);
    }
};
} // namespace std

// 支持 qHash
inline uint qHash(const Edge& key, uint seed)
{
    return qHash(key.from, seed) << 16 | qHash(key.to, seed);
}

inline bool operator==(const Edge& lhs, const Edge& rhs)
{
    return (lhs.from == rhs.from) && (lhs.to == rhs.to);
}

inline bool operator!=(const Edge& lhs, const Edge& rhs)
{
    return !(operator==(lhs, rhs));
}

#endif // EDGE_H
