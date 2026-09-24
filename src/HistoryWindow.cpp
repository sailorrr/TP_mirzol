#include "HistoryWindow.h"
#include "Client.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>

HistoryWindow::HistoryWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("История операций");
    resize(700, 500);

    // Заголовок
    QLabel *title = new QLabel("📊 История операций", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    title->setFont(titleFont);

    // Подсказка
    QLabel *hint = new QLabel(
        QString("👤 Текущий пользователь: <b>%1</b>")
            .arg(Client::instance().currentUser().isEmpty()
                 ? "—" : Client::instance().currentUser()), this);
    hint->setAlignment(Qt::AlignCenter);
    hint->setStyleSheet("QLabel { color: #2e7d32; font-size: 12px; }");

    // Таблица
    historyTable = new QTableWidget(this);
    historyTable->setColumnCount(3);
    historyTable->setHorizontalHeaderLabels({"№", "Время", "Операция"});
    historyTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    historyTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    historyTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    historyTable->setAlternatingRowColors(true);

    // Кнопки
    refreshButton = new QPushButton("🔄 Обновить", this);
    clearButton = new QPushButton("🗑 Очистить историю", this);
    closeButton = new QPushButton("✖ Закрыть", this);

    QString btnStyle = "QPushButton { padding: 10px; font-size: 13px; }";
    refreshButton->setStyleSheet(btnStyle);
    clearButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; background-color: #ff9800; color: white; }");
    closeButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; background-color: #f0f0f0; }");

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(refreshButton);
    btnLayout->addWidget(clearButton);

    // Компоновка
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(hint);
    layout->addSpacing(10);
    layout->addWidget(historyTable);
    layout->addLayout(btnLayout);
    layout->addWidget(closeButton);

    // Сигналы
    connect(refreshButton, &QPushButton::clicked, this, &HistoryWindow::onRefresh);
    connect(clearButton, &QPushButton::clicked, this, &HistoryWindow::onClear);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    // Загружаем историю при открытии
    loadHistory();
}

void HistoryWindow::loadHistory() {
    QVector<QString> history = Client::instance().getHistory();

    historyTable->setRowCount(history.size());

    for (int i = 0; i < history.size(); ++i) {
        QString entry = history[i];

        // Парсим: "[timestamp] operation"
        QString timestamp;
        QString operation;

        int closeBracket = entry.indexOf(']');
        if (closeBracket > 0 && entry.startsWith('[')) {
            timestamp = entry.mid(1, closeBracket - 1);
            operation = entry.mid(closeBracket + 1).trimmed();
        } else {
            timestamp = "—";
            operation = entry;
        }

        QTableWidgetItem *numItem = new QTableWidgetItem(QString::number(i + 1));
        numItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *timeItem = new QTableWidgetItem(timestamp);
        timeItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *opItem = new QTableWidgetItem(operation);

        historyTable->setItem(i, 0, numItem);
        historyTable->setItem(i, 1, timeItem);
        historyTable->setItem(i, 2, opItem);
    }

    // Прокрутить к последней записи
    if (history.size() > 0) {
        historyTable->scrollToBottom();
    }
}

void HistoryWindow::onRefresh() {
    loadHistory();
}

void HistoryWindow::onClear() {
    int result = QMessageBox::question(this, "Подтверждение",
        "Очистить всю историю операций?",
        QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::Yes) {
        Client::instance().clearHistory();
        Client::instance().logOperation("История очищена");
        loadHistory();
    }
}