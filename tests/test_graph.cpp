#include <QtTest>
#include <QVector>
#include "../src/GraphCycle.h"

class TestGraph : public QObject {
    Q_OBJECT

private:
    QVector<QVector<int>> makeExampleGraph() {
        // Граф:
        //   1-2, 1-3, 2-4, 3-4, 3-5
        return {
            {0, 1, 1, 0, 0},  // 1
            {1, 0, 0, 1, 0},  // 2
            {1, 0, 0, 1, 1},  // 3
            {0, 1, 1, 0, 0},  // 4
            {0, 0, 1, 0, 0}   // 5
        };
    }

private slots:
    void test_valid_cycle() {
        auto adj = makeExampleGraph();
        QVector<int> path = {0, 2, 3, 1, 0};  // 1-3-4-2-1
        QVERIFY(GraphCycle::isCycle(adj, path));
    }

    void test_not_closed() {
        auto adj = makeExampleGraph();
        QVector<int> path = {0, 1, 2};  // 1-2-3 (не замкнут)
        QVERIFY(!GraphCycle::isCycle(adj, path));
    }

    void test_missing_edge() {
        auto adj = makeExampleGraph();
        QVector<int> path = {0, 4, 2, 0};  // 1-5-3-1 (нет ребра 1-5)
        QVERIFY(!GraphCycle::isCycle(adj, path));
    }

    void test_too_short() {
        auto adj = makeExampleGraph();
        QVector<int> path = {0, 1};  // только 2 вершины, не цикл
        QVERIFY(!GraphCycle::isCycle(adj, path));
    }

    void test_triangle_cycle() {
        auto adj = makeExampleGraph();
        QVector<int> path = {0, 2, 3, 1, 0};  // валидный цикл 1-3-4-2-1
        QVERIFY(GraphCycle::isCycle(adj, path));
    }
};

QTEST_MAIN(TestGraph)
#include "test_graph.moc"