#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class GraphWindow : public QWidget {
    Q_OBJECT

public:
    GraphWindow(QWidget *parent = nullptr);

private slots:
    void onCheck();
    void onReset();

private:
    QTableWidget *matrixTable;
    QLineEdit *pathEdit;
    QPushButton *checkButton;
    QPushButton *resetButton;
    QLabel *resultLabel;

    void setupMatrix();
    void loadExampleMatrix();
};

#endif