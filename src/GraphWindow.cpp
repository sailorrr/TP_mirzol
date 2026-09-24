#include "GraphWindow.h"
#include <QLabel>
#include <QVBoxLayout>

GraphWindow::GraphWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Проверка цикла графа");
    resize(400, 300);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("🔀 Проверка цикла — в разработке", this));
}