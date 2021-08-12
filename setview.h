#ifndef SETVIEW_H
#define SETVIEW_H

#include <QWidget>
#include "flashcardset.h"
#include "flashcardsdata.h"

namespace Ui {
class SetView;
}

class SetView : public QWidget
{
    Q_OBJECT

public:
    explicit SetView(QWidget *parent = nullptr);
    ~SetView();

    const FlashcardSet &set() const;
    void setSet(const FlashcardSet &newSet);

signals:
    void RequestGoBack();
    void ReviseSet(FlashcardSet& set);
    void LearnSet(FlashcardSet& set);

public slots:
    void on_homeButton_clicked();

    void on_editButton_clicked();

    void on_reviseButton_clicked();

    void on_learnButton_clicked();

private slots:
    void on_deleteButton_clicked();

private:
    Ui::SetView *ui;
    FlashcardSet mSet;

    QList<QWidget*> setLabels;
};

#endif // SETVIEW_H
