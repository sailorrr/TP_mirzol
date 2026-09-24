#ifndef MD5WINDOW_H
#define MD5WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

class MD5Window : public QWidget {
    Q_OBJECT

public:
    MD5Window(QWidget *parent = nullptr);

private slots:
    void onHash();
    void onCopy();
    void onCompare();

private:
    QTextEdit *inputText;
    QLineEdit *hashResult;
    QLineEdit *compareEdit;
    QPushButton *hashButton;
    QPushButton *copyButton;
    QPushButton *compareButton;
    QLabel *statusLabel;
};

#endif