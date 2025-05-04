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

        // Используем QRegularExpression для разделения текста
        QRegularExpression re("\\s+");
        QStringList words = text.split(re);

        // Отфильтровываем пустые строки
        words.removeAll("");

        return words.count();
    }
};

#endif // WORDCOUNTSERVICE_H
