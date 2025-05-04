#ifndef WORDCOUNTSERVICE_H
#define WORDCOUNTSERVICE_H

#include "wordcountdto.h"
#include <QString>
#include <QRegularExpression>
#include <QStringList>

class WordCountService
{
public:
    int countWords(const WordCountDTO &dto)
    {
        QString text = dto.getText();
        text = text.simplified();

        QRegularExpression re("\\s+");
        QStringList words = text.split(re);

        words.removeAll("");

        return words.count();
    }
};

#endif
