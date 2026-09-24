#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <QPushButton>

class UserWindow : public QWidget {
    Q_OBJECT

public:
    UserWindow(QWidget *parent = nullptr);

private slots:
    void openVigenere();
    void openMD5();
    void openSecant();
    void openGraph();
    void openHistory();
    void logout();
};

#endif