#include "addperformance.h"
#include "config.h"
#include "performance.h"
#include "ui_Add_Performance.h"
#include "addperformanceactor.h"
#include "actors.h"

#include <QModelIndex>
#include <QFile>

AddPerformance::AddPerformance(Performance *performance, Type type, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::AddPerformance),
    m_performance(performance),
    m_type(type)
{
    mUi->setupUi(this);

    if (m_type == Edit) {
        setWindowTitle("Редактирование спектакля");
        mUi->mainLabel->setText("РЕДАКТИРОВАНИЕ СПЕКТАКЛЯ");
        mUi->namePerformance->setText(m_performance->NamePerformance());
        mUi->author->setText(m_performance->Author());
        mUi->producer->setText(m_performance->Producer());
        loadActers();
    }
    else {
        setWindowTitle("Добавление спектакля");
        mUi->mainLabel->setText("ДОБАВЛЕНИЕ СПЕКТАКЛЯ");
    }
}

AddPerformance::~AddPerformance()
{
    delete mUi;
}

void AddPerformance::accept()
{
    QString namePerformance = mUi->namePerformance->text();
    QString Author = mUi->author->text();
    QString Produser = mUi->producer->text();

    if (namePerformance == "" || Author == "" || Produser == "") mUi->labelError->setText("Ошибка: заполните все поля!");
    else if (isPerformanceExists(namePerformance))  mUi->labelError->setText("Ошибка: спектакль уже добавлен!");
    else
    {
        m_performance->setData(namePerformance, Author, Produser);
        if (m_type == Create)
        {
            QFile file(Config::filePerformance);
            file.open(QIODevice::Append);
            QDataStream ost(&file);
            ost << m_performance;
        }
        QDialog::accept();
    }
}

void AddPerformance::loadActers()
{
    m_listActors.clear();

    QFile file(Config::fileActor);
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream ist(&file);

        while (!ist.atEnd())
        {
            Actors actor;
            ist >> actor;
            m_listActors.append(actor);
        }
    }

    int row = 0;

    foreach (const Actors &actor, m_listActors)
    {
        int size_arr = actor.performances().size();
        for (int i = 0; i < size_arr; i++)
        {
            if (m_performance->NamePerformance() == actor.performances().at(i))
            {
                QTableWidgetItem *item_firstName = new QTableWidgetItem(actor.firstName());
                QTableWidgetItem *item_secondName = new QTableWidgetItem(actor.secondName());

                mUi->tableActors->insertRow(row);
                mUi->tableActors->setItem(row, 0, item_firstName);
                mUi->tableActors->setItem(row, 1, item_secondName);
                row++;
            }

        }
    }
}

bool AddPerformance::isPerformanceExists(const QString namePerformance)
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
