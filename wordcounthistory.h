#ifndef WORDCOUNTHISTORY_H
#define WORDCOUNTHISTORY_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QLabel>

class WordCountHistory : public QWidget
{
    Q_OBJECT

public:
    explicit WordCountHistory(QWidget *parent = nullptr) : QWidget(parent)
    {
        historyLayout = new QVBoxLayout(this);
        historyLayout->setAlignment(Qt::AlignTop);
        setLayout(historyLayout);
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
    }

private:
    QVBoxLayout *historyLayout;
};

#endif
