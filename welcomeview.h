#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include <QList>
#include <QPushButton>
#include "flashcardset.h"
#include <QVBoxLayout>
#include <QGroupBox>

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();
    void Refresh();

signals:
    void GotoSet(FlashcardSet set);
private slots:
    void on_importButton_clicked();

    void on_createButton_clicked();

    void on_importDialog_close();

private:
    Ui::WelcomeView *ui;

    void     setupLayout();
    QList<QPushButton*> setButtons;

    QVBoxLayout* scrollLayout;
    QGroupBox* mainBox;
};

#endif // WELCOMEVIEW_H
