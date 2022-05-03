#include "tree.h"

SPTree::SPTree(const Cell& root)
  : graph_()
  , root_(root)
{
    graph_.AddCell(root);
}

// 请确保图形实际上是一棵树（即没有循环）
SPTree::SPTree(const Graph& graph, const Cell& root)
  : graph_(graph)
  , root_(root)
{
}

QSet<Cell> SPTree::nodes() const
{
    return graph_.Cells();
}

QSet<Edge> SPTree::edges() const
{
    return graph_.Edges();
}

// 返回从根节点到指定节点的节点向量
QList<Cell> SPTree::PathTo(const Cell& node) const
{
    dfs_visited_nodes_.clear();
    QList<Cell> empty;
    return DFS(root_, node, empty);
}

// 将子节点添加到指定节点
void SPTree::AddChild(
  const Cell& to, const Cell& child, int weight)
{
    graph_.AddCell(child);
    graph_.AddEdge(to, child, weight);
}

QList<Cell> SPTree::DFS(
  const Cell& cur_node, const Cell& target_node, QList<Cell> path) const
{
    // 标记已访问过的向量
    DFS_Visit(cur_node);

    // 当前位置 == 目标，返回当前路径
    if (cur_node == target_node) {
        path.push_back(cur_node);
        return path;
    }

    // 如果节点没有任何未访问的子节点
    // 将其删除，在路径中的前一个节点上运行dfs
    if (!DFS_HasUnvisitedChild(cur_node)) {
        Cell last_node = path.back();
        path.pop_back();
        return DFS(last_node, target_node, path);
    } else {
        path.push_back(cur_node);
        Cell unvisited = DFS_FirstUnvisitedChild(cur_node);
        return DFS(unvisited, target_node, path);
    }
}

// 将节点标记为已访问
void SPTree::DFS_Visit(const Cell& node) const
{
    dfs_visited_nodes_ << node;
}

// 节点是否被访问过
bool SPTree::DFS_IsVisited(const Cell& node) const
{
    return dfs_visited_nodes_.contains(node);
}

// 节点是否有子节点
bool SPTree::DFS_HasUnvisitedChild(const Cell& parent_node) const
{
    QList<Cell> children = graph_.OutgoingCells(parent_node);
    foreach (Cell child, children) {
        if (DFS_IsVisited(child)) {
            return false;
        }
    }
    return true;
}

// 返回第一个未访问过的节点
Cell SPTree::DFS_FirstUnvisitedChild(const Cell& parent_node) const
{
    QList<Cell> children = graph_.OutgoingCells(parent_node);

    foreach (Cell child, children) {
        if (!DFS_IsVisited(child)) {
            return child;
        }
    }
    return Cell(parent_node);
}
