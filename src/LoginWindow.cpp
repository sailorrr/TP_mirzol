#include "LoginWindow.h"
#include "UserWindow.h"
#include "ServerStub.h"
#include "VigenereCipher.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Авторизация — Лабораторная работа");
    resize(400, 250);

    QLabel *titleLabel = new QLabel("Вход в систему", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("Логин");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Войти", this);

    statusLabel = new QLabel("", this);
    statusLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addSpacing(10);
    layout->addWidget(loginEdit);
    layout->addWidget(passwordEdit);
    layout->addSpacing(10);
    layout->addWidget(loginButton);
    layout->addWidget(statusLabel);
    layout->addStretch();

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);

    // Подсказка для теста
    statusLabel->setText("Подсказка: admin / 12345");
    statusLabel->setStyleSheet("color: gray; font-size: 11px;");
}

void LoginWindow::onLoginClicked() {
    QString login = loginEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
        return;
    }

    // Формируем запрос к серверу: auth&login&password
    QString request = "auth&" + login + "&" + password;
    QString response = ServerStub::processRequest(request);

    if (response == "auth&ok") {
        // Успех — открываем главное окно
        UserWindow *userWindow = new UserWindow();
        userWindow->setAttribute(Qt::WA_DeleteOnClose);
        userWindow->show();
        this->close();
    } else {
        statusLabel->setText("❌ Неверный логин или пароль");
        statusLabel->setStyleSheet("color: red; font-size: 12px;");
    }
}