#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include "wordcountdto.h"
#include "wordcountservice.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCalculateButtonClicked();
    void onLoadFileButtonClicked();

private:
    QTextEdit *textEdit;
    QPushButton *calculateButton;
    QPushButton *loadFileButton;
    QLabel *resultLabel;
    WordCountService wordCountService;
};

#endif
