#include "UserWindow.h"
#include "VigenereWindow.h"
#include "MD5Window.h"
#include "SecantWindow.h"
#include "GraphWindow.h"
#include "HistoryWindow.h"
#include "LoginWindow.h"
#include "Client.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>

UserWindow::UserWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Главное меню — Лабораторная работа");
    resize(500, 500);

    QString username = Client::instance().currentUser();

    QLabel *title = new QLabel("Главное меню", this);
    title->setAlignment(Qt::AlignCenter);
    QFont f = title->font();
    f.setPointSize(18);
    f.setBold(true);
    title->setFont(f);

    QLabel *userLabel = new QLabel(
        QString("👤 Пользователь: <b>%1</b>").arg(username.isEmpty() ? "—" : username), this);
    userLabel->setAlignment(Qt::AlignCenter);
    userLabel->setStyleSheet("QLabel { color: #2e7d32; font-size: 13px; padding: 5px; }");

    QLabel *subtitle = new QLabel("Выберите модуль:", this);
    subtitle->setAlignment(Qt::AlignCenter);

    QPushButton *btnVigenere = new QPushButton("🔐 Шифр Виженера", this);
    QPushButton *btnMD5 = new QPushButton("🔑 md5-хэш", this);
    QPushButton *btnSecant = new QPushButton("📐 Метод секущих", this);
    QPushButton *btnGraph = new QPushButton("🔀 Проверка цикла графа", this);
    QPushButton *btnHistory = new QPushButton("📊 История операций", this);
    QPushButton *btnLogout = new QPushButton("🚪 Выйти", this);

    QString style = "QPushButton { padding: 12px; font-size: 14px; }";
    btnVigenere->setStyleSheet(style);
    btnMD5->setStyleSheet(style);
    btnSecant->setStyleSheet(style);
    btnGraph->setStyleSheet(style);
    btnHistory->setStyleSheet("QPushButton { padding: 12px; font-size: 14px; background-color: #2196f3; color: white; }");
    btnLogout->setStyleSheet("QPushButton { padding: 12px; font-size: 14px; background-color: #f44336; color: white; }");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(userLabel);
    layout->addWidget(subtitle);
    layout->addSpacing(15);
    layout->addWidget(btnVigenere);
    layout->addWidget(btnMD5);
    layout->addWidget(btnSecant);
    layout->addWidget(btnGraph);
    layout->addSpacing(10);
    layout->addWidget(btnHistory);
    layout->addSpacing(10);
    layout->addWidget(btnLogout);
    layout->addStretch();

    connect(btnVigenere, &QPushButton::clicked, this, &UserWindow::openVigenere);
    connect(btnMD5, &QPushButton::clicked, this, &UserWindow::openMD5);
    connect(btnSecant, &QPushButton::clicked, this, &UserWindow::openSecant);
    connect(btnGraph, &QPushButton::clicked, this, &UserWindow::openGraph);
    connect(btnHistory, &QPushButton::clicked, this, &UserWindow::openHistory);
    connect(btnLogout, &QPushButton::clicked, this, &UserWindow::logout);
}

void UserWindow::openVigenere() {
    Client::instance().logOperation("Открыт модуль: Шифр Виженера");
    VigenereWindow *w = new VigenereWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void UserWindow::openMD5() {
    Client::instance().logOperation("Открыт модуль: md5-хэш");
    MD5Window *w = new MD5Window();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void UserWindow::openSecant() {
    Client::instance().logOperation("Открыт модуль: Метод секущих");
    SecantWindow *w = new SecantWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void UserWindow::openGraph() {
    Client::instance().logOperation("Открыт модуль: Проверка цикла графа");
    GraphWindow *w = new GraphWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void UserWindow::openHistory() {
    HistoryWindow *w = new HistoryWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

void UserWindow::logout() {
    Client::instance().setLoggedIn(false);
    Client::instance().setCurrentUser("");

    LoginWindow *login = new LoginWindow();
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    this->close();
}