#include "graph.h"

#include "data/tree.h"

Graph::Graph()
{
}

Graph::Graph(const QSet<Cell>& Cells,
             const QSet<Edge>& edges)
  : Cells_(Cells)
  , edges_(edges)
{
}

QSet<Cell> Graph::Cells() const
{
    return Cells_;
}

QSet<Edge> Graph::Edges() const
{
    return edges_;
}

bool Graph::Contains(const Cell& Cell) const
{
    return Cells_.contains(Cell);
}

bool Graph::Contains(const Edge& edge) const
{
    return edges_.contains(edge);
}

// 给定节点为起点的所有边
QList<Edge> Graph::OutgoingEdges(const Cell& from) const
{
    Q_ASSERT(Contains(from));
    QList<Edge> edges;

    foreach (auto edge, edges_) {
        if (edge.from == from) {
            edges << edge;
        }
    }

    return edges;
}

// 给定节点为终点的所有边
QList<Edge> Graph::IncomingEdges(const Cell& to) const
{
    Q_ASSERT(Contains(to));
    QList<Edge> edges;

    foreach (auto edge, edges_) {
        if (edge.to == to) {
            edges << edge;
        }
    }

    return edges;
}

// 给定点为起点能到达的所有节点
QList<Cell> Graph::OutgoingCells(const Cell& from) const
{
    Q_ASSERT(Contains(from));
    QList<Cell> Cells;
    QList<Edge> outgoint_edges = OutgoingEdges(from);

    foreach (auto edge, outgoint_edges) {
        Cells << edge.to;
    }

    return Cells;
}

// 能到达给点给为终点的所有节点
QList<Cell> Graph::IncomingCells(const Cell& to) const
{
    Q_ASSERT(Contains(to));
    QList<Cell> Cells;
    QList<Edge> outgoint_edges = IncomingEdges(to);

    foreach (auto edge, outgoint_edges) {
        Cells << edge.from;
    }

    return Cells;
}

void Graph::AddCell(const Cell& Cell)
{
    Cells_ << Cell;
}

void Graph::AddEdge(const Cell& from, const Cell& to, int weight)
{
    edges_ << Edge(from, to, weight);
}

// 最短路径 A*
QList<Cell> Graph::ShortesPath(const Cell& from, const Cell& to) const
{
    return GetSPTree(from).PathTo(to);
    //    return QList<Cell> {};
}

// 最短路径树
SPTree Graph::GetSPTree(const Cell& source) const
{
    // 需要记住第一个拾取的节点作为根节点
    Cell root_Cell(0, 0);
    DijInit(source);

    bool first = true;
    while (!unpicked_Cells_.isEmpty()) {

        Cell lightest = DijLightestUnpickedCell();

        // 拾取点
        picked_Cells_ << lightest;
        unpicked_Cells_.remove(lightest);

        // 更新其邻居的权重
        DijUpdateNeighborWeights(lightest);
        if (first) {
            first = false;
            root_Cell = lightest;
            continue;
        }

        // 拾取边
        Edge edge = updated_edge_[lightest];
        picked_edges_ << edge;
    }
    Graph graph(picked_Cells_, picked_edges_);
    return SPTree(graph, root_Cell);
}

// 路径节点 BFS
QList<Cell> Graph::GetPTCells(const Cell& source, const int& power) const
{
    BFSInit(source);
    for (int i = 0; i <= power; i++) {
        foreach (auto new_Cell, bfs_new_Cells_) {
            bfs_new_Cells_.remove(new_Cell);
            bfs_close_Cells_ << new_Cell;

            QList<Cell> neighbors = OutgoingCells(new_Cell);
            foreach (auto neighbor, neighbors) {
                if (bfs_close_Cells_.contains(neighbor)) {

                } else {
                    bfs_new_Cells_ << neighbor;
                }
            }
        }
    }

    bfs_close_Cells_.remove(source);
    return bfs_close_Cells_.values();
}

bool Graph::DijPicked(const Cell& Cell) const
{
    return picked_Cells_.contains(Cell);
}

Edge Graph::DijGetEdge(const Cell& from, const Cell& to) const
{
    for (Edge edge : edges_) {
        if (edge.from == from && edge.to == to) {
            return edge;
        }
    }
    return Edge();
}

void Graph::DijInit(const Cell& source) const
{
    picked_Cells_.clear();
    unpicked_Cells_.clear();
    picked_edges_.clear();
    Cell_weight_.clear();
    updated_edge_.clear();

    unpicked_Cells_.unite(Cells_);

    for (Cell Cell : Cells_) {
        Cell_weight_[Cell] = 1000;
    }
    Cell_weight_[source] = 0;
}

// 最轻的未选择节点
Cell Graph::DijLightestUnpickedCell() const
{
    Cell lightest = *unpicked_Cells_.begin();
    foreach (auto Cell, unpicked_Cells_) {
        if (Cell_weight_[Cell] < Cell_weight_[lightest]) {
            lightest = Cell;
        }
    }
    return lightest;
}

// 指定节点周围未选中的点
QList<Cell> Graph::DijUnpickedNeighbors(const Cell& of) const
{
    QList<Cell> neighbors = OutgoingCells(of);
    QList<Cell> unpicked;
    foreach (auto neighbor, neighbors) {
        if (!DijPicked(neighbor)) {
            unpicked << neighbor;
        }
    }

    return unpicked;
}

// 更新节点
void Graph::DijUpdateNeighborWeights(const Cell& of) const
{
    foreach (auto neighbor, DijUnpickedNeighbors(of)) {
        Edge edge_to_neighbor = DijGetEdge(of, neighbor);
        int edge_weight = edge_to_neighbor.weight;

        // 找到邻居的新权重和旧权重
        int new_to_tal_weight = Cell_weight_[of] + edge_weight;
        int old_weight = Cell_weight_[neighbor];

        if (new_to_tal_weight < old_weight) {
            Cell_weight_[neighbor] = new_to_tal_weight;
            updated_edge_[neighbor] = edge_to_neighbor;
        }
    }
}

void Graph::BFSInit(const Cell& source) const
{
    bfs_now_Cells_.clear();
    bfs_close_Cells_.clear();
    bfs_new_Cells_.clear();

    bfs_new_Cells_ << source;
}
