#ifndef ACTORS_H
#define ACTORS_H

#include "QString"
#include "QTextStream"
#include "QDataStream"
#include "QList"
#include "QDate"

class Actors
{
public:
    Actors();

    Actors(QString firstName, QString secondName, QDate born, QList<QString> performances);
    void setData(QString firstName, QString secondName, QDate born, QList<QString> performances);

    QString firstName() const;
    void setfirstName(const QString& firstName);

    QString secondName() const;
    void setsecondName(const QString& secondName);

    QDate born() const;
    void setBorn(const QDate& born);

    QList<QString> performances() const;
    void setPerformances(const QList<QString>& performances);

private:
    QString m_firstName;
    QString m_secondName;
    QDate m_born;
    QList<QString> m_performances;
};

inline QDataStream &operator<< (QDataStream &ost, const Actors &actor)
{
    ost << actor.firstName() << actor.secondName() << actor.born() << actor.performances();
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, Actors &actor)
{
    QString firstName, secondName;
    QList<QString> performance;
    QDate born;
    ist >> firstName >> secondName >> born >> performance;
    actor.setData(firstName, secondName, born, performance);
    return ist;
}

inline QTextStream &operator<< (QTextStream &ost, const Actors &actor)
{
    ost << QString("_____________АКТЕР____________")
        << QString("Имя: ") << actor.firstName()
        << QString("Фамилия: ") << actor.secondName()
        << QString("Дата рождения: ") << actor.born().toString("d-MMMM-yyyy")
        << QString("Спектакли, в которых играл актер: ");

    int sizePerformance = actor.performances().size();
    for (int i = 0; i < sizePerformance; i++)
    {
        ost << actor.performances().at(i) << endl;
    }

    ost << QString("_________КОНЕЦ АКТЕРА_________");

    return ost;
}

#endif // ACTORS_H
