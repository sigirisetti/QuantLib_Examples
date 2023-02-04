//
// Created by appuprakhya on 3/2/23.
//
#include<iostream>
#include<boost/foreach.hpp>
#include<ql/time/date.hpp>
#include<ql/time/calendar.hpp>
#include<ql/time/calendars/japan.hpp>
#include<ql/time/dategenerationrule.hpp>
#include<ql/time/schedule.hpp>

using namespace QuantLib;

void dateScheduleGen() {
    Date begin(30, September, 2009), end(15, Jun, 2012);
    Calendar myCal = Japan();
    BusinessDayConvention bdC = BusinessDayConvention(Following);
    Period myTenor(6, Months);
    DateGeneration::Rule myRule = DateGeneration::Forward;
    Schedule mySched(begin, end, myTenor, myCal, bdC, bdC, myRule, true);
    std::vector<Date> finalSched = mySched.dates();
    BOOST_FOREACH(Date d, finalSched) std::cout << d << std::endl;
}

void dateScheduleGen_NextAndPrevious() {
    Date begin(30, September, 2009), end(15, Jun, 2012);
    Calendar myCal = Japan();
    BusinessDayConvention bdC = BusinessDayConvention(Following);
    Period myTenor(6, Months);
    DateGeneration::Rule myRule = DateGeneration::Forward;
    Schedule mySched(begin, end, myTenor, myCal, bdC, bdC, myRule, true);
    Date myDate(3, Aug, 2010);
    std::cout << " Date :" << myDate << std::endl;
    std::cout << " Next Date :" << mySched.nextDate(myDate) << std::endl;
    std::cout << " Prev Date :" << mySched.previousDate(myDate) << std::endl;
}

void makeScheduleFlowApiHelper() {
    Date begin(30, September, 2009), end(15, Jun, 2012);
    Calendar myCal = Japan();
    auto bdC = BusinessDayConvention(Following);
    Period myTenor(6, Months);
    Schedule myScheduleMade = MakeSchedule()
            .from(begin)
            .to(end)
            .withTenor(myTenor)
            .withCalendar(myCal)
            .withConvention(bdC)
            .backwards()
            .endOfMonth(false)
            .withNextToLastDate(Date(24, Aug, 2011));
    std::vector<Date> finalSched = myScheduleMade.dates();
    BOOST_FOREACH (Date d, finalSched) std::cout << d << std::endl;
}