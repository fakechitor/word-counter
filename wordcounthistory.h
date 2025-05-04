#ifndef WORDCOUNTHISTORY_H
#define WORDCOUNTHISTORY_H

#include <QWidget>
#include <QListWidget>
#include <QStringList>

class WordCountHistory : public QWidget
{
    Q_OBJECT

public:
    explicit WordCountHistory(QWidget *parent = nullptr) : QWidget(parent)
    {
        historyList = new QListWidget(this);
    }

    void addHistoryItem(const QString &text, int wordCount)
    {
        historyList->addItem(text + " - " + QString::number(wordCount) + " слов");
    }

private:
    QListWidget *historyList;
};

#endif
