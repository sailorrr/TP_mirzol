#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class HistoryWindow : public QWidget {
    Q_OBJECT

public:
    HistoryWindow(QWidget *parent = nullptr);

private slots:
    void onRefresh();
    void onClear();

private:
    QTableWidget *historyTable;
    QPushButton *refreshButton;
    QPushButton *clearButton;
    QPushButton *closeButton;

    void loadHistory();
};

#endif