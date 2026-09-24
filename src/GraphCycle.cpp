#include "GraphCycle.h"

bool GraphCycle::isCycle(const QVector<QVector<int>>& adj,
                         const QVector<int>& path) {
    if (path.size() < 3) return false;
    if (path.first() != path.last()) return false;
    return allEdgesExist(adj, path);
}

bool GraphCycle::allEdgesExist(const QVector<QVector<int>>& adj,
                               const QVector<int>& path) {
    for (int i = 0; i + 1 < path.size(); ++i) {
        int from = path[i];
        int to = path[i + 1];

        if (from < 0 || from >= adj.size()) return false;
        if (to < 0 || to >= adj.size()) return false;

        if (adj[from][to] == 0) return false;
    }
    return true;
}