#include <QtTest>
#include "wordcountservice.h"
#include "wordcountdto.h"

class TestWordCountService : public QObject
{
    Q_OBJECT

private slots:
    void testSingleWord();
    void testMultipleWords();
    void testEmptyString();
    void testWhitespace();
};

void TestWordCountService::testSingleWord()
{
    WordCountService service;
    WordCountDTO dto("hello");
    int wordCount = service.countWords(dto);
    QCOMPARE(wordCount, 1);
}

void TestWordCountService::testMultipleWords()
{
    WordCountService service;
    WordCountDTO dto("hello world");
    int wordCount = service.countWords(dto);
    QCOMPARE(wordCount, 2);
}

void TestWordCountService::testEmptyString()
{
    WordCountService service;
    WordCountDTO dto("");
    int wordCount = service.countWords(dto);
    QCOMPARE(wordCount, 0);
}

void TestWordCountService::testWhitespace()
{
    WordCountService service;
    WordCountDTO dto("   ");
    int wordCount = service.countWords(dto);
    QCOMPARE(wordCount, 0);
}

QTEST_MAIN(TestWordCountService)
#include "test_wordcountservice.moc"
