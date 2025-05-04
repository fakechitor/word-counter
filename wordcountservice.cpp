#ifndef WORDCOUNTSERVICE_H
#define WORDCOUNTSERVICE_H

#include "wordcountdto.h"


class WordCountService
{
public:
    int countWords(const WordCountDTO &dto)
    {
        QString text = dto.getText();
        text = text.simplified();
        return text.split(QRegExp("\\s+"), QString::kipEmptyParts).count();
    }
};

#endif
