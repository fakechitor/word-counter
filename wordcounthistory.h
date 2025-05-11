#ifndef WORDCOUNTHISTORY_H
#define WORDCOUNTHISTORY_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QLabel>
#include <QClipboard>
#include <QApplication>
#include "database.h"

class WordCountHistory : public QWidget
{
    Q_OBJECT

public:
    explicit WordCountHistory(Database *db, QWidget *parent = nullptr) : QWidget(parent), database(db)
    {
        historyLayout = new QVBoxLayout(this);
        historyLayout->setAlignment(Qt::AlignTop);
        setLayout(historyLayout);

        loadHistory();
    }

    void addHistoryItem(const QString &text, int wordCount)
    {
        QString truncatedText = text.left(80);
        if (text.length() > 80) {
            truncatedText += "...";
        }

        QWidget *itemWidget = new QWidget(this);
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

        QPushButton *textButton = new QPushButton(truncatedText, itemWidget);
        textButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QLabel *wordCountLabel = new QLabel("Кол-во слов: " + QString::number(wordCount), itemWidget);

        itemLayout->addWidget(textButton);
        itemLayout->addWidget(wordCountLabel);

        historyLayout->insertWidget(0, itemWidget);

        connect(textButton, &QPushButton::clicked, this, [this, text](){ copyToClipboard(text); });

        database->addHistoryItem(text, wordCount);
    }
    void loadHistory()
    {
        QList<QPair<QString, int>> history = database->getHistory();

        for (const auto &item : history) {
            addHistoryItem(item.first, item.second);
        }
    }


private:
    void copyToClipboard(const QString &text)
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(text);
    }


    QVBoxLayout *historyLayout;
    Database *database;
};

#endif // WORDCOUNTHISTORY_H
