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
#include <QScrollArea>
#include "database.h"

class WordCountHistory : public QWidget
{
    Q_OBJECT

public:
    explicit WordCountHistory(Database *db, QWidget *parent = nullptr) : QWidget(parent), database(db)
    {
        historyLayout = new QVBoxLayout(this);
        historyLayout->setAlignment(Qt::AlignTop);

        historyWidget = new QWidget(this);
        QVBoxLayout *scrollLayout = new QVBoxLayout(historyWidget);
        historyWidget->setLayout(scrollLayout);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidget(historyWidget);
        scrollArea->setWidgetResizable(true);
        historyLayout->addWidget(scrollArea);

        setLayout(historyLayout);

        setFixedSize(400, 600);

        loadHistory();
    }

    void addHistoryItem(const QString &text, int wordCount)
    {
        QString truncatedText = text.left(80);
        if (text.length() > 80) {
            truncatedText += "...";
        }

        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM word_count_history WHERE text = :text AND word_count = :word_count");
        query.bindValue(":text", text);
        query.bindValue(":word_count", wordCount);
        query.exec();
        query.next();

        int count = query.value(0).toInt();
        if (count == 0) {
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO word_count_history (text, word_count) VALUES (?, ?)");
            insertQuery.addBindValue(text);
            insertQuery.addBindValue(wordCount);
            if (!insertQuery.exec()) {
                qDebug() << "Error inserting data:" << insertQuery.lastError().text();
            }
        }

        QWidget *itemWidget = new QWidget(this);
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

        QPushButton *textButton = new QPushButton(truncatedText, itemWidget);
        textButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QLabel *wordCountLabel = new QLabel("Кол-во слов: " + QString::number(wordCount), itemWidget);

        itemLayout->addWidget(textButton);
        itemLayout->addWidget(wordCountLabel);

        historyWidget->layout()->addWidget(itemWidget);

        connect(textButton, &QPushButton::clicked, this, [this, text](){ copyToClipboard(text); });
    }

    void loadHistory()
    {
        QList<QPair<QString, int>> history = database->getHistory();
        for (const auto &item : history) {
            addHistoryItem(item.first, item.second);
        }
    }

private slots:
    void copyToClipboard(const QString &text)
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(text);
    }

private:
    QVBoxLayout *historyLayout;
    Database *database;
    QWidget *historyWidget;
};

#endif // WORDCOUNTHISTORY_H
