#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "QString"
#include "QTextStream"
#include "QDataStream"
#include "QList"

#include "actors.h"

class Performance
{
public:
    Performance();

    Performance(const QString NamePerformance, QString Author, const QString Producer);
    void setData(const QString NamePerformance, QString Author, const QString Producer);

    QString Author() const;
    void setAuthor (const QString& Author);

    QString NamePerformance () const;
    void setNamePerformance (const QString& NamePerformance);

    QString Producer() const;
    void setProduser (const QString& Produser);

private:
    QString m_NamePerformance;
    QString m_Author;
    QString m_Producer;
};

inline QDataStream &operator<< (QDataStream &ost, const Performance &performance)
{
    ost << performance.NamePerformance() <<  performance.Author() << performance.Producer();

    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, Performance &performance)
{
    QString Author;
    QString NamePerformance;
    QString Producer;

    ist >> NamePerformance >> Author >> Producer;

    performance.setData(NamePerformance, Author, Producer);
    return ist;
}

#endif // PERFORMANCE_H
