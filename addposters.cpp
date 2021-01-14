#include "addposters.h"
#include "config.h"
#include "posters.h"
#include "ui_AddPoster.h"
#include <QFile>

AddPosters::AddPosters(Posters &poster, const QList<Posters> &listPosters, const QList<Performance> &listperformance, Type type, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::AddPosters),
    m_posters(poster),
    m_listPosters(listPosters),
    m_listPerformance(listperformance),
    m_type(type)
{
    mUi->setupUi(this);

    if (m_type == Edit)
    {
        mUi->mainLabel->setText("Редактирование афиши");
        mUi->namePerformance->setText(m_posters.namePerformance());
        mUi->date->setDate(m_posters.datePerformance());
        mUi->time->setTime(m_posters.timePerformance());
        mUi->countSeats->setValue(m_posters.countSeats());
    }
    else mUi->mainLabel->setText("Добавление афиши");
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

    if (namePerformance.isEmpty() || date.isNull() || time.isNull() || countSeats == 0) mUi->labelError->setText("Ошибка: заполните все поля!");
    else if (m_type == Create && isPosterExists(namePerformance)) mUi->labelError->setText("Ошибка: афиша уже добавлена!");
    else if (isPerformanceExists(namePerformance) == false) mUi->labelError->setText("Нет такого спектакля!");
    else
    {
       m_posters.setData(namePerformance, date, time, countSeats, countFreeSeats);
       if (m_type == Create)
       {
            QFile file(Config::filePosters);
            file.open(QIODevice::Append);
            QDataStream ost(&file);
            ost << m_posters;
            QDialog::accept();
        }
    }
}

bool AddPosters::isPosterExists(const QString namePerformance)
{
    QFile file(Config::filePosters);
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly))
        {
            mUi->labelError->setText("Ошибка: чтение файла невозможно!");
            return false;
        }
        QDataStream ist(&file);

        while (!ist.atEnd())
        {
            Posters buf_poster;
            ist >> buf_poster;
            if (buf_poster.namePerformance() == namePerformance) return true;
        }
        return false;
    }
    else return false;
}

bool AddPosters::isPerformanceExists(const QString namePerformance)
{
    QFile file(Config::filePerformance);
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly))
        {
            mUi->labelError->setText("Ошибка: чтение файла невозможно!");
            return false;
        }
        QDataStream ist(&file);

        while (!ist.atEnd())
        {
            Performance buf_performance;
            ist >> buf_performance;
            if (buf_performance.NamePerformance() == namePerformance) return true;
        }
        return false;
    }
    else return false;
}
