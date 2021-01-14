#include "posters.h"

Posters::Posters()
{
    m_namePerformance = "";
    m_countSeats = 0;
    m_countFreeSeats = 0;
}

Posters::Posters(QString namePerformance, QDate datePerformance, QTime timePerformance, int countSeats, int countFreeSeats)
{
    setData(namePerformance, datePerformance, timePerformance, countSeats, countFreeSeats);
}
void Posters::setData(QString namePerformance, QDate datePerformance, QTime timePerformance, int countSeats, int countFreeSeats)
{
    m_namePerformance = namePerformance;
    m_datePerformance = datePerformance;
    m_timePerformance = timePerformance;
    m_countSeats = countSeats;
    m_countFreeSeats = countFreeSeats;
}

QString Posters::namePerformance() const
{
    return m_namePerformance;
}
void Posters::setnamePerformance(const QString namePerformance)
{
    m_namePerformance = namePerformance;
}

QDate Posters::datePerformance() const
{
    return m_datePerformance;
}
void Posters::setdatePerformance(const QDate datePerformance)
{
    m_datePerformance = datePerformance;
}

QTime Posters::timePerformance() const
{
    return m_timePerformance;
}
void Posters::settimePerformance(const QTime timePerformance)
{
    m_timePerformance = timePerformance;
}

int Posters::countSeats() const
{
    return m_countSeats;
}
void Posters::setCountSeats(int countSeats)
{
    m_countSeats = countSeats;
}

int Posters::countFreeSeats() const
{
    return m_countFreeSeats;
}
void Posters::setCountFreeSeats(int countFreeSeats)
{
    m_countFreeSeats = countFreeSeats;
}
