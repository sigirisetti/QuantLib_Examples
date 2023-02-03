#include<iostream>
#include<ql/time/all.hpp>
#include<boost/foreach.hpp>

using namespace QuantLib;

void printDateInformation(Date d, const Calendar &cal) {
    if (cal.isBusinessDay(d))
        std::cout << d << " is a business day" << std::endl;

    if (cal.isHoliday(d))
        std::cout << d << " is a holiday" << std::endl;

    if (cal.isWeekend(d.weekday()))
        std::cout << d << " falls on a weekend" << std::endl;

    if (cal.isEndOfMonth(d))
        std::cout << d << " is the last business day of the month" << std::endl;

    std::cout << "The last business day of " << d.month() << " " << d.year() << " is " << cal.endOfMonth(d)
              << std::endl;
}

void test_printDateInformation() {
    Calendar uk = UnitedKingdom();

    std::cout << "Using calendar " << uk.name() << std::endl;

    printDateInformation(Date(25, Dec, 2012), uk);
    printDateInformation(Date(28, Feb, 2013), uk);
    printDateInformation(Date(26, Jan, 2013), uk);
}

void calendarTesting() {
    Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);
    Calendar saudiArabCal = SaudiArabia();
    Date nyEve(31, Dec, 2009);
    std::cout << "Is BD:" << frankfCal.isBusinessDay(nyEve) << std::endl;
    std::cout << "Is Holiday :" << frankfCal.isHoliday(nyEve) << std::endl;
    std::cout << "Is Weekend :" << saudiArabCal.isWeekend(Saturday) << std::endl;
    std::cout << "Is Last BD :" << frankfCal.isEndOfMonth(Date(30, Dec, 2009)) << std::endl;
    std::cout << " Last BD:" << frankfCal.endOfMonth(nyEve) << std::endl;
}

void holidaySetup() {
    Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);
    Date d1(24, Dec, 2009), d2(30, Dec, 2009), d3(31, Dec, 2009);
    frankfCal.addHoliday(d2);
    frankfCal.removeHoliday(d3);
    std::cout << "Is Business Day :" << frankfCal.isBusinessDay(d2) << std::endl;
    std::cout << "Is Business Day :" << frankfCal.isBusinessDay(d3) << std::endl;
    std::vector<Date> holidayVec = frankfCal.holidayList(d1, d2, false);
    std::cout << " - - - - - - - - - -" << std::endl;
    BOOST_FOREACH(Date d, holidayVec) std::cout << d << std::endl;
}

void businessDayAdjustment() {
    Calendar frankfCal = Germany(Germany::FrankfurtStockExchange);
    Date firstDate(31, Oct, 2009);
    Date secondDate(1, Jan, 2010);
    std::cout << " Date 2 Adv :" << frankfCal.adjust(secondDate,
                                                     BusinessDayConvention(Preceding)) << std::endl;
    std::cout << " Date 2 Adv :" << frankfCal.adjust(secondDate,
                                                     BusinessDayConvention(ModifiedPreceding)) << std::endl;
    Period mat(2, Months);
    std::cout << " Date 1 Month Adv :" << frankfCal.advance(firstDate, mat,
                                                            BusinessDayConvention(Following), false) << std::endl;
    std::cout << " Date 1 Month Adv :" << frankfCal.advance(firstDate, mat,
                                                            BusinessDayConvention(ModifiedFollowing), false)
              << std::endl;
    std::cout << " Business Days Between :" << frankfCal.businessDaysBetween(
            firstDate, secondDate, false, false) << std::endl;
}