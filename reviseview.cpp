#include "reviseview.h"
#include "ui_reviseview.h"

ReviseView::ReviseView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReviseView),
    mSetIterator(mSet.getTermIterator())
{
    ui->setupUi(this);
}

ReviseView::~ReviseView()
{
    delete ui;
}

const FlashcardSet &ReviseView::set() const
{
    return mSet;
}

void ReviseView::setSet(const FlashcardSet &newSet)
{
    mSet = newSet;

    QMapIterator<QString, QString> termsIterator = mSet.getTermIterator();
    mTermsQueue.clear();
    while (termsIterator.hasNext()) {
        termsIterator.next();
        mTermsQueue.append( qMakePair(termsIterator.key(), termsIterator.value()));
    }
}

void ReviseView::Begin()
{
    state = State::CHECK;
    terms_done = 0;
    ui->progressBar->setRange(0, mTermsQueue.size());
    ui->textInput->setPlaceholderText("");
    ui->progressBar->setValue(0);
    if (mTermsQueue.size() == 0) {
        qErrnoWarning("No terms in set");
        emit ReturnToSet();
    }
    mCurrentTerm = mTermsQueue.dequeue();
    ui->keyLabel->setText(mCurrentTerm.first);
    /*
    mSetIterator.next();
    ui->keyLabel->setText(mSetIterator.key());
    */
}

void ReviseView::StartLearning(FlashcardSet &set)
{
    qDebug() << "Learning " << set.getName();
    /*
    setSet(set);
    mSetIterator = mSet.getTermIterator();

    ui->progressBar->setRange(0, mSet.getTerms().size());
    ui->progressBar->setValue(0);
    */
}

void ReviseView::on_homeButton_clicked()
{
    emit ReturnToSet();
}


void ReviseView::on_checkButton_clicked()
{

    QString key = mCurrentTerm.first;
    QString value = mCurrentTerm.second;

    QString input = ui->textInput->text();

    if (state == State::CHECK) {
        if (input != value) {
            // Wrong - go to check
            state = State::RETYPE;
            ui->statusLabel->setText( "Incorrect - please retype!");

            ui->textInput->clear();
            ui->textInput->setPlaceholderText(value);
            mTermsQueue.enqueue(mCurrentTerm);

        } else {
            terms_done++;
            SetNextTerm();
        }

    } else {
        if (input != value) {
            // Wrong
            ui->statusLabel->setText("Incorrect - please type in the correct word!");
        } else {
            SetNextTerm();
        }
    }
}

void ReviseView::SetNextTerm()
{
    state = State::CHECK;
    ui->statusLabel->setText("Correct!");
    if (mTermsQueue.size() > 0)
    {
        mCurrentTerm = mTermsQueue.dequeue();
        ui->progressBar->setValue(terms_done);
        ui->textInput->clear();
        ui->textInput->setPlaceholderText("");
        ui->keyLabel->setText(mCurrentTerm.first);
    } else {
        emit ReturnToSet();
    }

}


void ReviseView::on_textInput_returnPressed()
{
    on_checkButton_clicked();
}

