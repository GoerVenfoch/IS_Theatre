#include "performance.h"

Performance::Performance()
{
    m_Author = "";
    m_NamePerformance = "";
    m_Producer = "";
}

Performance::Performance(const QString NamePerformance, QString Author, const QString Producer)
{
    setData(Author, NamePerformance, Producer);
}
void Performance::setData(const QString NamePerformance, QString Author, const QString Producer)
{
    m_Author = Author;
    m_NamePerformance = NamePerformance;
    m_Producer = Producer;
}

QString Performance::Author() const
{
    return m_Author;
}
void Performance::setAuthor (const QString& Author)
{
    m_Author = Author;
}

QString Performance::NamePerformance () const
{
    return m_NamePerformance;
}
void Performance::setNamePerformance (const QString& NamePerformance)
{
    m_NamePerformance = NamePerformance;
}

QString Performance::Producer() const
{
    return m_Producer;
}
void Performance::setProduser (const QString& Produser)
{
    m_Producer = Produser;
}
