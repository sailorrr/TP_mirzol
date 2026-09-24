#include "VigenereWindow.h"
#include <QLabel>
#include <QVBoxLayout>

VigenereWindow::VigenereWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Шифр Виженера");
    resize(400, 300);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("🔐 Шифр Виженера — в разработке", this));
}