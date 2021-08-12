#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
#include <QMap>
#include <QString>

namespace Ui {
class PreviewDialog;
}

class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewDialog(QMap<QString, QString> setToPreview, QWidget *parent = nullptr);
    ~PreviewDialog();

private:
    Ui::PreviewDialog *ui;
};

#endif // PREVIEWDIALOG_H
