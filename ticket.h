#ifndef TICKET_H
#define TICKET_H

#include "QString"
#include "QTextStream"
#include "QDataStream"

class Ticket
{
public:
    enum Combo { Parter, Amfiteatr, Loga1, Loga2, Loga3 };

    Ticket();

    Ticket(const QString &performance, const QString &firstName, const QString &secondName, const QString &fatherName, const QString &phone, const Combo combobox, int &row, int &place);
    void setData(const QString &performance, const QString &firstName, const QString &secondName, const QString &fatherName, const QString &phone, const Combo combobox, int &row, int &place);

    QString performance() const;
    void setperformance(const QString& performance);

    QString firstName() const;
    void setfirstName(const QString& firstName);

    QString secondName() const;
    void setsecondName(const QString& secondName);

    QString fatherName() const;
    void setfatherName(const QString& fatherName);

    QString phone() const;
    void setphone(const QString& phone);

    Combo combobox() const;
    void setcombobox(const Combo& combobox);

    int row() const;
    void setrow(const int& row);

    int place() const;
    void setplace(const int& place);

    const QString comboString() const;
    static QMap<Combo, QString> getListCombo();

private:
    Combo m_combobox;
    int m_row;
    int m_place;
    QString m_firstName;
    QString m_secondName;
    QString m_fatherName;
    QString m_phone;
    QString m_performance;
};

inline QDataStream &operator<< (QDataStream &ost, const Ticket &ticket)
{
    ost << ticket.performance() << ticket.firstName() << ticket.secondName() << ticket.fatherName() << ticket.phone() << ticket.combobox() << ticket.row() << ticket.place();
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, Ticket &ticket)
{
    QString performance, firstName, secondName, fatherName, phone;
    int combobox, row, place;
    ist >> performance >> firstName >> secondName >> fatherName >> phone >> combobox >> row >> place;
    ticket.setData(performance, firstName, secondName, fatherName, phone, Ticket::Combo(combobox), row, place);
    return ist;
}

inline QTextStream &operator<< (QTextStream &ost, const Ticket &ticket)
{
    ost << QString("_____________БИЛЕТ____________")
        << QString("Название спектакля: ") << ticket.performance()
        << QString("Имя: ") << ticket.firstName()
        << QString("Фамилия: ") << ticket.secondName()
        << QString("Отчество: ") << ticket.fatherName()
        << QString("Телефон: ") << ticket.phone()
        << QString("Группа зала: ") << Ticket::Combo(ticket.combobox())
        << QString("Ряд: ") << ticket.row()
        << QString("Место: ") << ticket.place()
        << QString("_________КОНЕЦ АКТЕРА_________");

    return ost;
}

#endif // TICKET_H
