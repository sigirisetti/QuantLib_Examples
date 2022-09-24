//
// Created by appuprakhya on 16/9/22.
//
#include <iostream>
#include <ql/money.hpp>
#include <ql/currencies/all.hpp>

using namespace QuantLib;

void moneyExchangeEx() {
    Money::conversionType = Money::AutomatedConversion;
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

    std::cout << m_eur << " + " << m_gbp << " = " << m_eur + m_gbp << std::endl;
}