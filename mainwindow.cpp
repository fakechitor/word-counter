#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFile>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    textEdit(new QTextEdit(this)),
    calculateButton(new QPushButton("Посчитать слова", this)),
    loadFileButton(new QPushButton("Загрузить файл", this)),
    resultLabel(new QLabel("Количество слов: 0", this)),
    historyWidget(new WordCountHistory(this)),
    dockWidget(new QDockWidget("История запросов", this))
{
    setWindowTitle("Word Counter");
    setGeometry(100, 100, 600, 400);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(loadFileButton);
    layout->addWidget(calculateButton);
    layout->addWidget(resultLabel);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    dockWidget->setWidget(historyWidget);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);

    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateButtonClicked);
    connect(loadFileButton, &QPushButton::clicked, this, &MainWindow::onLoadFileButtonClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onCalculateButtonClicked()
{
    WordCountDTO dto(textEdit->toPlainText());
    int wordCount = wordCountService.countWords(dto);
    resultLabel->setText("Количество слов: " + QString::number(wordCount));
    historyWidget->addHistoryItem(dto.getText(), wordCount);
}

void MainWindow::onLoadFileButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString content = in.readAll();
    textEdit->setText(content);
}
