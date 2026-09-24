#include "SecantWindow.h"
#include <QLabel>
#include <QVBoxLayout>

SecantWindow::SecantWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Метод секущих");
    resize(400, 300);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("📐 Метод секущих — в разработке", this));
}