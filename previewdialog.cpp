#include "previewdialog.h"
#include "ui_previewdialog.h"
#include <QLabel>

PreviewDialog::PreviewDialog(QMap<QString, QString> setToPreview, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);

    QMapIterator<QString, QString> it(setToPreview);
    while (it.hasNext()) {
        it.next();
        QLabel* label = new QLabel(it.key() + " " + it.value());
        ui->mainLayout->addWidget(label);
    }
}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}
