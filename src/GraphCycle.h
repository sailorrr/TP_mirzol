#ifndef GRAPHCYCLE_H
#define GRAPHCYCLE_H

#include <QVector>

class GraphCycle {
public:
    // Проверка, что последовательность вершин образует цикл
    // adj — матрица смежности (adj[i][j] = 1, если есть ребро i-j)
    // path — последовательность вершин (нумерация с 0)
    static bool isCycle(const QVector<QVector<int>>& adj,
                        const QVector<int>& path);

    // Проверка, что каждое ребро в path существует в графе
    static bool allEdgesExist(const QVector<QVector<int>>& adj,
                              const QVector<int>& path);
};

#endif // GRAPHCYCLE_H