#ifndef FLASHCARDSDATA_H
#define FLASHCARDSDATA_H

#include <QString>
#include <QList>
#include "flashcardset.h"

class FlashCardsData
{
public:
    static bool LoadSets(QString setPath);
    static bool SaveSets(QString setPath);


    static void setFlashcards(const QList<FlashcardSet> &newFlashcards);
    static const QList<FlashcardSet> &getFlashcards();

    static void addFlashcard(const FlashcardSet set);
    static void DeleteFlashcard(FlashcardSet set);

private:

    static QList<FlashcardSet> flashcards;

};

#endif // FLASHCARDSDATA_H
