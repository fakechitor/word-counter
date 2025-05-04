#ifndef WORDCOUNTDTO_H
#define WORDCOUNTDTO_H

#include <QString>

class WordCountDTO
{
public:
    WordCountDTO(const QString &text = "") : text(text) {}

    QString getText() const { return text; }
    void setText(const QString &value) { text = value; }

private:
    QString text;
};

#endif
