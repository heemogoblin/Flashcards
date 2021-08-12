#ifndef FLASHCARDSET_H
#define FLASHCARDSET_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>


class FlashcardSet
{
public:
    FlashcardSet();
    FlashcardSet(QString name, QMap<QString, QString> terms);
    explicit FlashcardSet(QJsonObject json);

    QString getName();
    void setName(QString newName);
    QJsonObject generateJson(QJsonObject& json);
    const QMap<QString, QString> &getTerms() const;
    void setTerms(const QMap<QString, QString> &newTerms);

    QMapIterator<QString, QString> getTermIterator();

private:
    QString name;
    QMap<QString, QString> terms;
};

bool operator==( FlashcardSet& s1,  FlashcardSet& s2);

#endif // FLASHCARDSET_H
