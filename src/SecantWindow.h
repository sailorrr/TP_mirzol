#ifndef SECANTWINDOW_H
#define SECANTWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

class SecantWindow : public QWidget {
    Q_OBJECT

public:
    SecantWindow(QWidget *parent = nullptr);

private slots:
    void onSolve();
    void onClear();

private:
    QLineEdit *x0Edit;
    QLineEdit *x1Edit;
    QLineEdit *epsEdit;
    QPushButton *solveButton;
    QPushButton *clearButton;
    QTextEdit *resultText;
};

#endif