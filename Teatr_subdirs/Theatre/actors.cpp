#include "actors.h"

Actors::Actors()
{
    m_firstName = "";
    m_secondName = "";
}

Actors::Actors(QString firstName, QString secondName, QDate born, QList<QString> performances)
{
   setData(firstName, secondName, born, performances);
}
void Actors::setData(QString firstName, QString secondName, QDate born, QList<QString> performances)
{
    m_firstName = firstName;
    m_secondName = secondName;
    m_born = born;
    m_performances = performances;
}

QString Actors::firstName() const
{
    return m_firstName;
}
void Actors::setfirstName(const QString& firstName)
{
    m_firstName = firstName;
}

QString Actors::secondName() const
{
    return m_secondName;
}
void Actors::setsecondName(const QString& secondName)
{
    m_secondName = secondName;
}

QDate Actors::born() const
{
    return m_born;
}
void Actors::setBorn(const QDate& born)
{
    m_born = born;
}

QList<QString> Actors::performances() const
{
    return m_performances;
}
void Actors::setPerformances(const QList<QString>& performances)
{
    m_performances = performances;
}
