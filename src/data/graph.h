#ifndef GRAPH_H
#define GRAPH_H

#include "data/edge.h"

class SPTree;

// ͼ
class Graph
{
public:
    Graph();
    Graph(const QSet<Cell>& Cells, const QSet<Edge>& Edges);

    QSet<Cell> Cells() const;
    QSet<Edge> Edges() const;

    bool Contains(const Cell& Cell) const;
    bool Contains(const Edge& edge) const;

    QList<Edge> OutgoingEdges(const Cell& from) const;
    QList<Edge> IncomingEdges(const Cell& to) const;
    QList<Cell> OutgoingCells(const Cell& from) const;
    QList<Cell> IncomingCells(const Cell& to) const;

    void AddCell(const Cell& Cell);
    void AddEdge(const Cell& from, const Cell& to, int weight);

    QList<Cell> ShortesPath(const Cell& from, const Cell& to) const;

    SPTree GetSPTree(const Cell& source) const;
    QList<Cell> GetPTCells(const Cell& source, const int& power) const;

private:
    QSet<Cell> Cells_;
    QSet<Edge> edges_;

private: // A*
private: // dijkstras
    mutable QSet<Cell> picked_Cells_;
    mutable QSet<Cell> unpicked_Cells_;
    mutable QSet<Edge> picked_edges_;
    mutable QHash<Cell, int> Cell_weight_;
    mutable QHash<Cell, Edge> updated_edge_;

    bool DijPicked(const Cell& Cell) const;
    Edge DijGetEdge(const Cell& from, const Cell& to) const;
    void DijInit(const Cell& source) const;
    Cell DijLightestUnpickedCell() const;
    QList<Cell> DijUnpickedNeighbors(const Cell& of) const;
    void DijUpdateNeighborWeights(const Cell& of) const;

private: // BFS
    mutable QSet<Cell> bfs_now_Cells_;
    mutable QSet<Cell> bfs_close_Cells_;
    mutable QSet<Cell> bfs_new_Cells_;

    void BFSInit(const Cell& source) const;
};

#endif // GRAPH_H
