#include<iostream>
#include<ql/time/all.hpp>

using namespace QuantLib;

void printDateInformation(Date d, const Calendar& cal) {
  if (cal.isBusinessDay(d))
    std::cout << d << " is a business day" << std::endl;

  if (cal.isHoliday(d))
    std::cout << d << " is a holiday" << std::endl;

  if (cal.isWeekend(d.weekday()))
    std::cout << d << " falls on a weekend" << std::endl;

  if (cal.isEndOfMonth(d))
    std::cout << d << " is the last business day of the month" << std::endl;

  std::cout << "The last business day of " << d.month() << " " << d.year() << " is " << cal.endOfMonth(d) << std::endl;
}

void test_printDateInformation() {
    Calendar uk=UnitedKingdom();

    std:: cout << "Using calendar " << uk. name() << std:: endl;

    printDateInformation(Date(25, Dec, 2012), uk);
    printDateInformation(Date(28, Feb, 2013), uk);
    printDateInformation(Date(26, Jan, 2013), uk);
}
