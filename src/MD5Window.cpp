#include "MD5Window.h"
#include <QLabel>
#include <QVBoxLayout>

MD5Window::MD5Window(QWidget *parent) : QWidget(parent) {
    setWindowTitle("md5");
    resize(400, 300);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("🔑 md5-хэш — в разработке", this));
}