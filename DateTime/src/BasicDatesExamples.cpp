#include<iostream>
#include<ql/time/all.hpp>

using namespace QuantLib;

void basicDatesExamples()
{
    Date d1(34524);
    Date d2(6, September, 2012);

    std::cout << d1 << std::endl;
    std::cout << d2 << std::endl;

    Date d(6, Sep, 2012);

    std::cout << "Date is " << d << std::endl;
    std::cout << "Weekday is " << d.weekday() << std::endl;
    std::cout << "Day of the month is " << d.dayOfMonth() << std::endl;
    std::cout << "Day of the year is " << d.dayOfYear() << std::endl;
    std::cout << "Month is " << d.month() << std::endl;
    std::cout << "Year is " << d.year() << std::endl;
    std::cout << "Serial number is " << d.serialNumber() << std::endl;

}

