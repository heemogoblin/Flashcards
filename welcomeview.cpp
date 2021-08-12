
#include "welcomeview.h"
#include "ui_welcomeview.h"
#include "flashcardsdata.h"
#include "mainwindow.h"
#include "importsetdialog.h"
#include <QGroupBox>

WelcomeView::WelcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeView)
{
    ui->setupUi(this);
    scrollLayout = new QVBoxLayout;
    mainBox = new QGroupBox;
    mainBox->setLayout(scrollLayout);
    ui->setView->setWidget(mainBox);

    setupLayout();

}

WelcomeView::~WelcomeView()
{
    delete ui;
}

void WelcomeView::Refresh()
{
    for (auto button: setButtons) {
        scrollLayout->removeWidget(button);
    }
    setupLayout();

}

void WelcomeView::on_importButton_clicked()
{
    ImportSetDialog* importDialog = new ImportSetDialog(this);
    importDialog->show();
    QObject::connect(importDialog, &ImportSetDialog::finished, this, &WelcomeView::on_importDialog_close);
}


void WelcomeView::on_createButton_clicked()
{

}

void WelcomeView::on_importDialog_close()
{
    qDebug() << "Closed";
    Refresh();
}



void WelcomeView::setupLayout()
{

    for (auto set : FlashCardsData::getFlashcards()) {

        QPushButton* setButton = new QPushButton(set.getName());
        QObject::connect(setButton, &QPushButton::clicked, this, [=]() {
            emit GotoSet(set);
        });
        scrollLayout->addWidget(setButton);
        setButtons.append(setButton);
    }
}

