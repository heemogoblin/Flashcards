#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QMap>
#include "flashcardset.h"
#include <QVBoxLayout>
#include <setview.h>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QGroupBox>
#include "welcomeview.h"
#include "reviseview.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void OnSetButtonClicked(FlashcardSet set);
    void OnGoBackRequest();
    void OnReviseSet(FlashcardSet& set);
    void OnGoBackToSet();

signals:
    void GotoWidget(QWidget*);

private:

    QList<FlashcardSet> sets;

    QString setPath = "/home/artyom/Documents/src/C++/Flashcards/sets.json";
    WelcomeView* welcomeView;
    SetView* setView;
    ReviseView* reviseView;


    QStackedLayout* mainStack;
    QVBoxLayout* mainLayout;
    QGroupBox* mainBox;

    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
