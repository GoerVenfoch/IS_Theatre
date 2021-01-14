#ifndef POSTERS_H
#define POSTERS_H

#include "QDate"
#include "QTime"
#include "QString"
#include "QTextStream"
#include "QDataStream"

class Posters
{
public:
    Posters();
    Posters(QString namePerformance, QDate datePerformance, QTime timePerformance, int countSeats, int countFreeSeats);
    void setData(QString namePerformance, QDate datePerformance, QTime timePerformance, int countSeats, int countFreeSeats);

    QString namePerformance() const;
    void setnamePerformance(const QString namePerformance);

    QDate datePerformance() const;
    void setdatePerformance(const QDate datePerformance);

    QTime timePerformance() const;
    void settimePerformance(const QTime timePerformance);

    int countSeats() const;
    void setCountSeats(int countSeats);

    int countFreeSeats() const;
    void setCountFreeSeats(int countFreeSeats);


    int m_countSeats;
    int m_countFreeSeats;
private:
    QString m_namePerformance;
    QDate m_datePerformance;
    QTime m_timePerformance;
};

inline QDataStream &operator<< (QDataStream &ost, const Posters &poster)
{
    ost << poster.namePerformance() << poster.datePerformance() << poster.timePerformance() << poster.countSeats() << poster.countFreeSeats();
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, Posters &poster)
{
    QString namePerformance;
    QDate datePerformance;
    QTime timePerformance;
    int countSeats;
    int countFreeSeats;

    ist >> namePerformance >> datePerformance >> timePerformance >> countSeats >> countFreeSeats;
    poster.setData(namePerformance, datePerformance, timePerformance, countFreeSeats, countFreeSeats);
    return ist;
}

#endif // POSTERS_H
