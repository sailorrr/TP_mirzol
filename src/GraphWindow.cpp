#include "GraphWindow.h"
#include "GraphCycle.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>
#include <QVector>

GraphWindow::GraphWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Проверка цикла в графе");
    resize(600, 650);

    // Заголовок
    QLabel *title = new QLabel("🔀 Проверка цикла в графе", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    title->setFont(titleFont);

    // Подсказка
    QLabel *hintLabel = new QLabel(
        "Задайте матрицу смежности (0 — нет ребра, 1 — есть ребро).\n"
        "Затем введите последовательность вершин и нажмите «Проверить».", this);
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setStyleSheet("QLabel { color: #555; font-size: 11px; }");

    // Матрица смежности 5x5
    QLabel *matrixLabel = new QLabel("Матрица смежности (5×5):", this);
    matrixTable = new QTableWidget(5, 5, this);
    matrixTable->setHorizontalHeaderLabels({"1", "2", "3", "4", "5"});
    matrixTable->setVerticalHeaderLabels({"1", "2", "3", "4", "5"});
    matrixTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixTable->setMaximumHeight(200);

    setupMatrix();
    loadExampleMatrix();

    // Ввод пути
    QLabel *pathLabel = new QLabel("Последовательность вершин (например: 1 2 3 1):", this);
    pathEdit = new QLineEdit(this);
    pathEdit->setPlaceholderText("Введите вершины через пробел");
    pathEdit->setText("1 3 4 2 1");

    // Кнопки
    checkButton = new QPushButton("✅ Проверить", this);
    checkButton->setStyleSheet("QPushButton { padding: 12px; font-size: 14px; }");

    resetButton = new QPushButton("🔄 Сбросить матрицу", this);
    resetButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; background-color: #f0f0f0; }");

    // Результат
    QLabel *resultTitle = new QLabel("Результат:", this);
    resultLabel = new QLabel("—", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: 15px; border-radius: 6px; font-size: 16px; font-weight: bold; }");

    // Компоновка
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(hintLabel);
    layout->addSpacing(10);
    layout->addWidget(matrixLabel);
    layout->addWidget(matrixTable);
    layout->addWidget(pathLabel);
    layout->addWidget(pathEdit);
    layout->addWidget(checkButton);
    layout->addSpacing(10);
    layout->addWidget(resultTitle);
    layout->addWidget(resultLabel);
    layout->addWidget(resetButton);
    layout->addStretch();

    // Сигналы
    connect(checkButton, &QPushButton::clicked, this, &GraphWindow::onCheck);
    connect(resetButton, &QPushButton::clicked, this, &GraphWindow::onReset);
}

void GraphWindow::setupMatrix() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem("0");
            item->setTextAlignment(Qt::AlignCenter);
            matrixTable->setItem(i, j, item);
        }
    }
}

void GraphWindow::loadExampleMatrix() {
    // Пример графа:
    //   1-2, 1-3, 2-4, 3-4, 3-5
    int example[5][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            matrixTable->item(i, j)->setText(QString::number(example[i][j]));
        }
    }
}

void GraphWindow::onCheck() {
    // 1. Считываем матрицу смежности
    QVector<QVector<int>> adj(5, QVector<int>(5, 0));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            QTableWidgetItem *item = matrixTable->item(i, j);
            if (!item) {
                QMessageBox::warning(this, "Ошибка", "Пустая ячейка матрицы!");
                return;
            }
            QString val = item->text().trimmed();
            if (val != "0" && val != "1") {
                QMessageBox::warning(this, "Ошибка",
                    QString("Ячейка [%1,%2] должна быть 0 или 1!").arg(i+1).arg(j+1));
                return;
            }
            adj[i][j] = val.toInt();
        }
    }

    // 2. Считываем путь
    QString pathStr = pathEdit->text().trimmed();
    if (pathStr.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите последовательность вершин!");
        return;
    }

    QStringList parts = pathStr.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (parts.size() < 3) {
        resultLabel->setText("❌ НЕ ЦИКЛ\n\n(нужно минимум 3 вершины)");
        resultLabel->setStyleSheet("QLabel { background-color: #ffebee; color: #c62828; padding: 15px; border-radius: 6px; font-size: 16px; font-weight: bold; }");
        return;
    }

    QVector<int> path;
    for (const QString& part : parts) {
        bool ok;
        int v = part.toInt(&ok);
        if (!ok || v < 1 || v > 5) {
            QMessageBox::warning(this, "Ошибка",
                QString("Некорректная вершина: %1 (должна быть 1-5)").arg(part));
            return;
        }
        path.append(v - 1);  // Convert to 0-based
    }

    // 3. Проверяем
    bool isCycle = GraphCycle::isCycle(adj, path);

    if (isCycle) {
        resultLabel->setText("✅ ЦИКЛ!");
        resultLabel->setStyleSheet("QLabel { background-color: #e8f5e9; color: #2e7d32; padding: 15px; border-radius: 6px; font-size: 18px; font-weight: bold; }");
    } else {
        // Проверим почему
        QString reason;
        if (path.first() != path.last()) {
            reason = "первая и последняя вершины не совпадают";
        } else if (!GraphCycle::allEdgesExist(adj, path)) {
            reason = "не все рёбра существуют в графе";
        } else {
            reason = "не выполнены условия цикла";
        }

        resultLabel->setText(QString("❌ НЕ ЦИКЛ\n\n(%1)").arg(reason));
        resultLabel->setStyleSheet("QLabel { background-color: #ffebee; color: #c62828; padding: 15px; border-radius: 6px; font-size: 14px; font-weight: bold; }");
    }
}

void GraphWindow::onReset() {
    loadExampleMatrix();
    pathEdit->setText("1 3 4 2 1");
    resultLabel->setText("—");
    resultLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: 15px; border-radius: 6px; font-size: 16px; font-weight: bold; }");
}