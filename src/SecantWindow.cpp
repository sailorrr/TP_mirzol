#include "SecantWindow.h"
#include "SecantMethod.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <cmath>

SecantWindow::SecantWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Метод секущих");
    resize(500, 550);

    // Заголовок
    QLabel *title = new QLabel("📐 Метод секущих", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    title->setFont(titleFont);

    // Описание функции
    QLabel *funcLabel = new QLabel("Решается уравнение:  f(x) = x³ - 2x - 5 = 0", this);
    funcLabel->setAlignment(Qt::AlignCenter);
    funcLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: 8px; border-radius: 4px; font-family: monospace; }");

    // Валидатор для чисел
    QRegularExpression numRx("-?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
    QRegularExpressionValidator *numValidator = new QRegularExpressionValidator(numRx, this);

    // x0
    QLabel *x0Label = new QLabel("x₀ (первое приближение):", this);
    x0Edit = new QLineEdit(this);
    x0Edit->setText("2");
    x0Edit->setValidator(numValidator);

    // x1
    QLabel *x1Label = new QLabel("x₁ (второе приближение):", this);
    x1Edit = new QLineEdit(this);
    x1Edit->setText("3");
    x1Edit->setValidator(numValidator);

    // eps
    QLabel *epsLabel = new QLabel("ε (точность):", this);
    epsEdit = new QLineEdit(this);
    epsEdit->setText("0.000001");
    epsEdit->setValidator(numValidator);

    // Кнопки
    solveButton = new QPushButton("🔍 Найти корень", this);
    solveButton->setStyleSheet("QPushButton { padding: 12px; font-size: 14px; }");

    clearButton = new QPushButton("🗑 Очистить", this);
    clearButton->setStyleSheet("QPushButton { padding: 10px; font-size: 13px; background-color: #f0f0f0; }");

    // Результат
    QLabel *resultLabel = new QLabel("Результат:", this);
    resultText = new QTextEdit(this);
    resultText->setReadOnly(true);
    resultText->setStyleSheet("QTextEdit { font-family: monospace; font-size: 12px; }");

    // Компоновка
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(funcLabel);
    layout->addSpacing(10);
    layout->addWidget(x0Label);
    layout->addWidget(x0Edit);
    layout->addWidget(x1Label);
    layout->addWidget(x1Edit);
    layout->addWidget(epsLabel);
    layout->addWidget(epsEdit);
    layout->addWidget(solveButton);
    layout->addSpacing(10);
    layout->addWidget(resultLabel);
    layout->addWidget(resultText);
    layout->addWidget(clearButton);
    layout->addStretch();

    // Сигналы
    connect(solveButton, &QPushButton::clicked, this, &SecantWindow::onSolve);
    connect(clearButton, &QPushButton::clicked, this, &SecantWindow::onClear);
}

void SecantWindow::onSolve() {
    bool ok1, ok2, ok3;
    double x0 = x0Edit->text().toDouble(&ok1);
    double x1 = x1Edit->text().toDouble(&ok2);
    double eps = epsEdit->text().toDouble(&ok3);

    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Проверьте введённые числа!");
        return;
    }
    if (eps <= 0) {
        QMessageBox::warning(this, "Ошибка", "Точность ε должна быть > 0!");
        return;
    }
    if (x0 == x1) {
        QMessageBox::warning(this, "Ошибка", "x₀ и x₁ должны быть разными!");
        return;
    }

    double root = SecantMethod::solve(SecantMethod::defaultFunction, x0, x1, eps, 100);

    if (std::isnan(root)) {
        resultText->setPlainText("❌ Метод не сошёлся.\n\nПопробуйте другие начальные приближения.");
        return;
    }

    double fRoot = SecantMethod::defaultFunction(root);

    QString result;
    result += "✅ Корень найден!\n";
    result += "───────────────────────\n";
    result += QString("x  ≈ %1\n").arg(root, 0, 'g', 12);
    result += QString("f(x) = %1\n").arg(fRoot, 0, 'e', 3);
    result += QString("ε = %1\n").arg(eps);
    result += QString("Начальные приближения: x₀=%1, x₁=%2\n").arg(x0).arg(x1);

    resultText->setPlainText(result);
}

void SecantWindow::onClear() {
    x0Edit->clear();
    x1Edit->clear();
    epsEdit->clear();
    resultText->clear();
}