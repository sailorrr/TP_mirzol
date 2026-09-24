#include "MD5Window.h"
#include "MD5.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

MD5Window::MD5Window(QWidget *parent) : QWidget(parent) {
    setWindowTitle("md5-хэш");
    resize(500, 500);

    // Заголовок
    QLabel *title = new QLabel("🔑 md5-хэш", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    title->setFont(titleFont);

    // Ввод текста
    QLabel *inputLabel = new QLabel("Текст для хэширования:", this);
    inputText = new QTextEdit(this);
    inputText->setPlaceholderText("Введите любой текст (кириллица, латиница, цифры)");
    inputText->setMaximumHeight(80);

    hashButton = new QPushButton("🔑 Хэшировать", this);
    hashButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; }");

    // Результат хэша
    QLabel *hashLabel = new QLabel("Хэш (32 символа hex):", this);
    hashResult = new QLineEdit(this);
    hashResult->setReadOnly(true);
    hashResult->setPlaceholderText("Здесь появится md5-хэш");
    hashResult->setStyleSheet("QLineEdit { padding: 8px; font-family: monospace; font-size: 12px; }");

    copyButton = new QPushButton("📋 Копировать хэш", this);
    copyButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; }");

    // Сравнение
    QLabel *compareLabel = new QLabel("Сравнение с эталоном:", this);
    compareEdit = new QLineEdit(this);
    compareEdit->setPlaceholderText("Вставьте эталонный хэш (32 символа)");
    compareEdit->setStyleSheet("QLineEdit { padding: 8px; font-family: monospace; font-size: 12px; }");

    compareButton = new QPushButton("✅ Проверить соответствие", this);
    compareButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; }");

    statusLabel = new QLabel("", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 14px; font-weight: bold;");

    // Компоновка
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addSpacing(10);
    layout->addWidget(inputLabel);
    layout->addWidget(inputText);
    layout->addWidget(hashButton);
    layout->addSpacing(5);
    layout->addWidget(hashLabel);
    layout->addWidget(hashResult);
    layout->addWidget(copyButton);
    layout->addSpacing(10);
    layout->addWidget(compareLabel);
    layout->addWidget(compareEdit);
    layout->addWidget(compareButton);
    layout->addWidget(statusLabel);
    layout->addStretch();

    // Сигналы
    connect(hashButton, &QPushButton::clicked, this, &MD5Window::onHash);
    connect(copyButton, &QPushButton::clicked, this, &MD5Window::onCopy);
    connect(compareButton, &QPushButton::clicked, this, &MD5Window::onCompare);
}

void MD5Window::onHash() {
    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите текст для хэширования!");
        return;
    }
    QString hash = MD5::hash(text);
    hashResult->setText(hash);
    statusLabel->clear();
}

void MD5Window::onCopy() {
    QString hash = hashResult->text();
    if (hash.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала хэшируйте текст!");
        return;
    }
    QApplication::clipboard()->setText(hash);
    statusLabel->setText("📋 Хэш скопирован в буфер обмена");
    statusLabel->setStyleSheet("color: blue; font-size: 13px;");
}

void MD5Window::onCompare() {
    QString hash = hashResult->text();
    QString expected = compareEdit->text().trimmed().toLower();

    if (hash.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала хэшируйте текст!");
        return;
    }
    if (expected.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите эталонный хэш!");
        return;
    }

    if (hash.toLower() == expected) {
        statusLabel->setText("✅ СОВПАДЕНИЕ!");
        statusLabel->setStyleSheet("color: green; font-size: 16px; font-weight: bold;");
    } else {
        statusLabel->setText("❌ НЕ СОВПАДАЕТ");
        statusLabel->setStyleSheet("color: red; font-size: 16px; font-weight: bold;");
    }
}