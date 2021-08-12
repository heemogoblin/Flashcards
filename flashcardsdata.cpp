#include "flashcardsdata.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <algorithm>

QList<FlashcardSet> FlashCardsData::flashcards = QList<FlashcardSet>();

/*

        {
            "Name": "test set 1",
            "Terms": [
                {
                    "Key": "hallo",
                    "Value": "hello"
                }
                {
                    "Key": "Hund",
                    "Value": "dog"
                }
            ]
        },
        {
            "Name": "test set 2",
            "Terms": [
                {
                    "Key": "hallo",
                    "Value": "hello"
                }
            ]
        },
        {
            "Name": "test set 3",
            "Terms": [
                {
                    "Key": "hallo",
                    "Value": "hello"
                }
            ]
        }
        */

bool FlashCardsData::LoadSets(QString sLoadFilePath){
    QFile loadFile(sLoadFilePath);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("Failed to open file\n");
        return false;
    }
    QByteArray bytes = loadFile.readAll();
    qDebug() << bytes.count();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);
    qDebug() << error.errorString();
    QJsonObject json = doc.object();

    for (auto set : json["Sets"].toArray()) {
        qDebug("Adding flashcard");
        flashcards.push_back(FlashcardSet(set.toObject()));
    }
    loadFile.close();
    return true;
}
/*
 *
            {
            "Key": "hallo",
            "Value": "hello"
}
*/

bool FlashCardsData::SaveSets(QString sSaveFilePath) {
    QFile loadFile(sSaveFilePath);
    if (!loadFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Unable to open file for writing " << loadFile.errorString() << "\n";
        return false;
    }
    QJsonObject json;
    QJsonArray setsArray;
    for (auto set : flashcards) {
        QJsonObject setObject;
        set.generateJson(setObject);
        //qDebug() << setObject["Terms"].toArray()[0].toObject()["Key"].toString();
        setsArray.append(setObject);
    }
    json["Sets"] = setsArray;
    loadFile.write(QJsonDocument(json).toJson());
    loadFile.close();
    return true;
}

void FlashCardsData::setFlashcards(const QList<FlashcardSet> &newFlashcards)
{
    flashcards = newFlashcards;
}

const QList<FlashcardSet> &FlashCardsData::getFlashcards()
{
    return flashcards;
}

void FlashCardsData::addFlashcard(const FlashcardSet set)
{
    flashcards.append(set);
}

void FlashCardsData::DeleteFlashcard(FlashcardSet set)
{
    for (int i = 0; i < flashcards.size(); i++) {
        if (flashcards[i].getName() == set.getName()) {
            flashcards.removeAt(i);
            break;
        }
    }
}
