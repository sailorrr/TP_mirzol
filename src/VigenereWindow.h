#ifndef VIGENEREWINDOW_H
#define VIGENEREWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class VigenereWindow : public QWidget {
    Q_OBJECT

public:
    VigenereWindow(QWidget *parent = nullptr);

private slots:
    void onEncrypt();
    void onDecrypt();
    void onClear();

private:
    QTextEdit *inputText;
    QLineEdit *keyEdit;
    QTextEdit *resultText;
    QPushButton *encryptButton;
    QPushButton *decryptButton;
    QPushButton *clearButton;

    bool validateInput();
};

#endif