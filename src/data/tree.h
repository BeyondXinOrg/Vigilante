#ifndef TREE_H
#define TREE_H

#include "graph.h"

// 最短路径树
class SPTree
{
public:
    SPTree(const Cell& root);
    SPTree(const Graph& graph, const Cell& root);

    QSet<Cell> nodes() const;
    QSet<Edge> edges() const;

    QList<Cell> PathTo(const Cell& node) const;
    void AddChild(const Cell& to, const Cell& child, int weight);

    // private:
    Graph graph_;
    Cell root_;

private: // DFS
    QList<Cell> DFS(const Cell& src_node, const Cell& target_node, QList<Cell> path) const;
    void DFS_Visit(const Cell& node) const;
    bool DFS_IsVisited(const Cell& node) const;
    bool DFS_HasUnvisitedChild(const Cell& parent_node) const;
    Cell DFS_FirstUnvisitedChild(const Cell& parent_node) const;
    mutable QSet<Cell> dfs_visited_nodes_; // 访问过的节点
};

#endif // TREE_H
