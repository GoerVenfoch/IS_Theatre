#include "ticket.h"

Ticket::Ticket()
{
    m_performance = "";
    m_firstName = "";
    m_secondName = "";
    m_fatherName = "";
    m_phone = "";
    m_row = 0;
    m_place = 0;
}


Ticket::Ticket(const QString &performance, const QString &firstName, const QString &secondName, const QString &fatherName, const QString &phone, const Combo combobox, int &row, int &place)
{
    setData(performance, firstName, secondName, fatherName, phone, combobox, row, place);
}
void Ticket::setData(const QString &performance, const QString &firstName, const QString &secondName, const QString &fatherName, const QString &phone, const Combo combobox, int &row, int &place)
{
    m_performance = performance;
    m_firstName = firstName;
    m_secondName = secondName;
    m_fatherName = fatherName;
    m_phone = phone;
    m_combobox = combobox;
    m_row = row;
    m_place = place;
}

QString Ticket::performance() const
{
    return m_performance;
}
void Ticket::setperformance(const QString &performance)
{
    m_performance = performance;
}

QString Ticket::firstName() const
{
    return m_firstName;
}
void Ticket::setfirstName(const QString& firstName)
{
    m_firstName = firstName;
}

QString Ticket::secondName() const
{
    return m_secondName;
}
void Ticket::setsecondName(const QString& secondName)
{
    m_secondName = secondName;
}

QString Ticket::fatherName() const
{
    return m_secondName;
}
void Ticket::setfatherName(const QString& fatherName)
{
    m_fatherName = fatherName;
}

QString Ticket::phone() const
{
    return m_phone;
}
void Ticket::setphone(const QString& phone)
{
    m_phone = phone;
}

Ticket::Combo Ticket::combobox() const
{
    return m_combobox;
}
void Ticket::setcombobox(const Combo& combobox)
{
    m_combobox = combobox;
}

int Ticket::row() const
{
    return m_row;
}
void Ticket::setrow(const int& row)
{
    m_row = row;
}

int Ticket::place() const
{
    return m_place;
}
void Ticket::setplace(const int& place)
{
    m_place = place;
}

const QString Ticket::comboString() const
{
    return getListCombo()[m_combobox];
}

QMap<Ticket::Combo, QString> Ticket::getListCombo()
{
    return QMap<Ticket::Combo, QString>({ { Parter, "Партер" },
                                   { Amfiteatr, "Амфитеатр"} ,
                                   { Loga1, "Ложа №1" } ,
                                   { Loga2, "Ложа №2" } ,
                                   { Loga3, "Ложа №3" } ,
                                 });
}
