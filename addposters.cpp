#include "addposters.h"
#include "config.h"
#include "posters.h"
#include "ui_AddPoster.h"

AddPosters::AddPosters(Posters *poster, const QList<Posters> &listPosters, Type type, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::AddPosters),
    m_posters(poster),
    m_listPosters(listPosters)
{
    mUi->setupUi(this);

    if (type == Edit) {
        mUi->mainLabel->setText("Редактирование афиши");
        mUi->namePerformance->setText(m_posters->namePerformance());
        mUi->date->setDate(m_posters->datePerformance());
        mUi->time->setTime(m_posters->timePerformance());
        mUi->countSeats->setValue(m_posters->countSeats());
    }
    else {
        mUi->mainLabel->setText("Добавление афиши");
    }
}

AddPosters::~AddPosters()
{
    delete mUi;
}

void AddPosters::accept()
{
    mUi->labelError->clear();

    QString namePerformance = mUi->namePerformance->text();
    QDate date = mUi->date->date();
    QTime time = mUi->time->time();
    int countSeats = mUi->countSeats->value();
    int countFreeSeats = countSeats;
    if (namePerformance.isEmpty() ||
        date.isNull() ||
        time.isNull() ||
        countSeats == 0) {
        mUi->labelError->setText("Ошибка: заполните все поля!");
    } else {
        m_posters->setData(namePerformance, date, time, countSeats, countFreeSeats);
        QDialog::accept();
    }
}
