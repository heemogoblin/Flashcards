#include "setview.h"
#include "ui_setview.h"
#include <QMessageBox>
// TODO: edit set
SetView::SetView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetView)
{
    ui->setupUi(this);
}

SetView::~SetView()
{
    delete ui;
}

void SetView::on_homeButton_clicked()
{
    emit RequestGoBack();
}

const FlashcardSet &SetView::set() const
{
    return mSet;
}

void SetView::setSet(const FlashcardSet &newSet)
{
    mSet = newSet;
    ui->setName->setText(mSet.getName());
/*
    for (auto label : setLabels) {
        label->hide();
        ui->mainLayout->removeWidget(label);
    }
    setLabels.clear();


    QMapIterator<QString, QString> setIterator(mSet.getTerms());
    while (setIterator.hasNext()) {
        setIterator.next();
        QLabel* termLabel = new QLabel(setIterator.key() + " = " + setIterator.value());
        ui->mainLayout->addWidget(termLabel);
        setLabels.push_back(termLabel);
    }*/

}


void SetView::on_editButton_clicked()
{

}


void SetView::on_reviseButton_clicked()
{
    qDebug() << "Revising set " << mSet.getName();
    emit ReviseSet(mSet);
}


void SetView::on_learnButton_clicked()
{

}


void SetView::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Delete set?");
    msgBox.setInformativeText("Confirm");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Cancel)  {
        return;
    }
    FlashCardsData::DeleteFlashcard(mSet);

}

