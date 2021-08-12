#ifndef REVISEVIEW_H
#define REVISEVIEW_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QMapIterator>
#include <QQueue>
#include <QPair>
#include "flashcardset.h"

namespace Ui {
class ReviseView;
}

/*
 * TODO:
 * - Change logic to queue
 */


class ReviseView : public QWidget
{
    Q_OBJECT

public:
    explicit ReviseView(QWidget *parent = nullptr);
    ~ReviseView();

    const FlashcardSet &set() const;
    void setSet(const FlashcardSet &newSet);

    void Begin();

    enum class State {
        CHECK,
        RETYPE
    };

public slots:
    void StartLearning(FlashcardSet& set);


private slots:
    void on_homeButton_clicked();

    void on_checkButton_clicked();

    void on_textInput_returnPressed();

signals:
    void ReturnToSet();

private:
    Ui::ReviseView *ui;

    FlashcardSet mSet;
    QMapIterator<QString, QString> mSetIterator;

    State state;

    QQueue<QPair<QString, QString>> mTermsQueue;
    QPair<QString, QString> mCurrentTerm;

    void SetNextTerm();

    int terms_done = 0;
};

#endif // REVISEVIEW_H
