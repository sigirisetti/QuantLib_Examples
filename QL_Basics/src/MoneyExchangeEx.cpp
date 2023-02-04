//
// Created by appuprakhya on 16/9/22.
//
#include <iostream>
#include <ql/money.hpp>
#include <ql/settings.hpp>
#include <ql/currencies/america.hpp>
#include <ql/currencies/europe.hpp>
#include <ql/currencies/exchangeratemanager.hpp>

using namespace QuantLib;

void moneyExchangeEx() {
    Date todaysDate(1, QuantLib::Sep, 2012);
    Settings::instance().evaluationDate() = todaysDate;

    Currency usd = USDCurrency();
    Currency gbp = GBPCurrency();
    Currency eur = EURCurrency();

    ExchangeRate usdXgbp(usd, gbp, 0.6176);
    ExchangeRate usdXeur(usd, eur, 0.7671);

    ExchangeRateManager::instance().add(usdXgbp);
    ExchangeRateManager::instance().add(usdXeur,
                                        Date(25, August, 2012), Date(3, December, 2012));

    Money m_eur = 100 * eur;
    Money m_gbp = 150 * gbp;

    //Set Evaluation date otherwise below will fail
    std::cout << m_eur << " + " << m_gbp << " = " << m_eur + m_gbp << std::endl;
}