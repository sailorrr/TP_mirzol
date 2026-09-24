#include "VigenereWindow.h"
#include "VigenereCipher.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>

VigenereWindow::VigenereWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Шифр Виженера");
    resize(500, 450);

    QLabel *title = new QLabel("🔐 Шифр Виженера", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    title->setFont(titleFont);

    QLabel *inputLabel = new QLabel("Исходный текст:", this);
    inputText = new QTextEdit(this);
    inputText->setPlaceholderText("Введите текст на латинице (A-Z, a-z, пробел)");
    inputText->setMaximumHeight(80);

    QLabel *keyLabel = new QLabel("Ключ:", this);
    keyEdit = new QLineEdit(this);
    keyEdit->setPlaceholderText("Введите ключ (только латиница)");

    QRegularExpression rx("[a-zA-Z]+");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    keyEdit->setValidator(validator);

    encryptButton = new QPushButton("🔒 Зашифровать", this);
    decryptButton = new QPushButton("🔓 Расшифровать", this);
    clearButton = new QPushButton("🗑 Очистить", this);

    QString btnStyle = "QPushButton { padding: 10px; font-size: 13px; }";
    encryptButton->setStyleSheet(btnStyle);
    decryptButton->setStyleSheet(btnStyle);
    clearButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; background-color: #f0f0f0; }");

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(encryptButton);
    btnLayout->addWidget(decryptButton);

    QLabel *resultLabel = new QLabel("Результат:", this);
    resultText = new QTextEdit(this);
    resultText->setReadOnly(true);
    resultText->setMaximumHeight(80);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addSpacing(10);
    layout->addWidget(inputLabel);
    layout->addWidget(inputText);
    layout->addWidget(keyLabel);
    layout->addWidget(keyEdit);
    layout->addLayout(btnLayout);
    layout->addWidget(resultLabel);
    layout->addWidget(resultText);
    layout->addWidget(clearButton);
    layout->addStretch();

    connect(encryptButton, &QPushButton::clicked, this, &VigenereWindow::onEncrypt);
    connect(decryptButton, &QPushButton::clicked, this, &VigenereWindow::onDecrypt);
    connect(clearButton, &QPushButton::clicked, this, &VigenereWindow::onClear);
}

bool VigenereWindow::validateInput() {
    QString text = inputText->toPlainText().trimmed();
    QString key = keyEdit->text().trimmed();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите исходный текст!");
        return false;
    }
    if (key.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ключ!");
        return false;
    }

    QRegularExpression rx("^[a-zA-Z ]+$");
    if (!rx.match(text).hasMatch()) {
        QMessageBox::warning(this, "Ошибка",
            "Текст должен содержать только латинские буквы и пробелы!");
        return false;
    }
    if (!rx.match(key).hasMatch()) {
        QMessageBox::warning(this, "Ошибка",
            "Ключ должен содержать только латинские буквы!");
        return false;
    }

    return true;
}

void VigenereWindow::onEncrypt() {
    if (!validateInput()) return;
    QString text = inputText->toPlainText();
    QString key = keyEdit->text();
    QString result = VigenereCipher::encrypt(text, key);
    resultText->setPlainText(result);
}

void VigenereWindow::onDecrypt() {
    if (!validateInput()) return;
    QString text = inputText->toPlainText();
    QString key = keyEdit->text();
    QString result = VigenereCipher::decrypt(text, key);
    resultText->setPlainText(result);
}

void VigenereWindow::onClear() {
    inputText->clear();
    keyEdit->clear();
    resultText->clear();
}