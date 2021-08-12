#include "importsetdialog.h"
#include "ui_importsetdialog.h"
#include <stdexcept>
#include <QException>
#include <QtAlgorithms>
#include "previewdialog.h"
#include <QMessageBox>

ImportSetDialog::ImportSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportSetDialog)
{
    ui->setupUi(this);
}

ImportSetDialog::~ImportSetDialog()
{
    delete ui;
}

void ImportSetDialog::on_chooseFileButton_clicked()
{
    mFileName = QFileDialog::getOpenFileName(this, "Choose file with set");
    QFile loadFile(mFileName);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
    }
    else ui->setInput->setText(loadFile.readAll());
}

bool ImportSetDialog::LoadSet()
{

    QString name = ui->nameEdit->text();
    if (name == "") {
        QMessageBox::warning(this, "Name is empty", "Please enter a name for your set");
        return false;
    }
    QString delim = ui->delimEdit->text();
    QString setData = ui->setInput->toPlainText();
    QTextStream textStream(&setData);
    QString line;
    bool definitionFirst = ui->defFirstButton->isChecked();
    while (textStream.readLineInto(&line, 200)) {
        try {
            QList<QString> parts = line.split(delim, Qt::SkipEmptyParts);
            QString key, value;
            if (parts.size() != 2){ return false; }
            if (definitionFirst){
                key = parts[1];
                value = parts[0];
            } else{
                key = parts[0];
                value = parts[1];
            }
            qDebug() << key.simplified() << value.simplified();
            mTerms.insert(key.simplified(), value.simplified());
            //qDebug() << key << value;

        }  catch (QException& e) {
            return false;
        }
    }
    mTempSet.setTerms(mTerms);
    mTempSet.setName(name);
    return true;
}

void ImportSetDialog::LoadSetError()
{
    QMessageBox::critical(this, "Error loading set", "Error when loading set. Check you have entered the set correctly");
}


void ImportSetDialog::on_previewButton_clicked()
{
    if (!LoadSet()){ LoadSetError(); return; }
    PreviewDialog* dialog = new PreviewDialog(mTerms);
    dialog->show();
}


void ImportSetDialog::on_importButton_clicked()
{
    if (!LoadSet()) { LoadSetError(); return; }
    FlashCardsData::addFlashcard(mTempSet);
    close();
}

