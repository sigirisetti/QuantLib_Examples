#include<iostream>
#include <ql/qldefines.hpp>
#include <ql/patterns/observable.hpp>
#include "ObserverObservableEx.h"

using namespace QuantLib;

class MyObservable : public Observable {
  private:
    Real amount;
    Natural year;
  public:
    void calculateInterest(Real amount, Real rate, Natural years) {
      this->amount = amount;
      this->year = 0;
      notifyObservers();
      for (this->year=1; this->year<=years; ++this->year) {
        this->amount = this->amount*(1.0 + rate);
        notifyObservers();
      }
    }
    Real getAmount() {
      return this->amount;
    }
};

typedef boost::shared_ptr<MyObservable> pMyObservable;

class MyObserver : public Observer {
  private:
    pMyObservable observable;
    std::string name;
  public:
    MyObserver(pMyObservable obs, std::string n)
        : observable(obs), name(n)
    {
      this->registerWith(observable);
    }
    MyObserver(const MyObserver &observer)
      : Observer(observer),
        observable(observer.observable),
        name("Copy of "+observer.name)
    {}
    void update() {
      std::cout << name << " "
                << observable->getAmount() << std::endl;
    }
};

void observer_test() {
  pMyObservable calc(new MyObservable);
  MyObserver observerA(calc, "observer a");
  MyObserver observerB(calc, "observer b");

  std::cout << "First calculation" << std::endl;
  calc->calculateInterest(100.0, 0.03, 5);

  observerB.unregisterWith(calc);

  std::cout << "Second calculation" << std::endl;
  calc->calculateInterest(100.0, 0.04, 5);

}
