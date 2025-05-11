#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");

        QString dbPath = QCoreApplication::applicationDirPath() + "/history.db";
        db.setDatabaseName(dbPath);

        QFile dbFile(dbPath);
        if (!dbFile.exists()) {
            qDebug() << "Database file does not exist at:" << dbPath;
            return;
        }

        if (!db.open()) {
            qDebug() << "Error opening database:" << db.lastError().text();
            return;
        }

        qDebug() << "Database opened successfully";

        QSqlQuery query;
        if (!query.exec("CREATE TABLE IF NOT EXISTS word_count_history ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "text TEXT, "
                        "word_count INTEGER)")) {
            qDebug() << "Error creating table:" << query.lastError().text();
            return;
        }

        qDebug() << "Table created or already exists";
    }

    ~Database() {
        db.close();
    }

    void addHistoryItem(const QString &text, int wordCount)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO word_count_history (text, word_count) VALUES (?, ?)");
        query.addBindValue(text);
        query.addBindValue(wordCount);
        if (!query.exec()) {
            qDebug() << "Error inserting data:" << query.lastError().text();
        }
    }

    QList<QPair<QString, int>> getHistory()
    {
        QList<QPair<QString, int>> history;

        QSqlQuery query("SELECT text, word_count FROM word_count_history ORDER BY id DESC");
        while (query.next()) {
            QString text = query.value(0).toString();
            int wordCount = query.value(1).toInt();
            history.append(qMakePair(text, wordCount));
        }

        return history;
    }

private:
    QSqlDatabase db;
};

#endif
