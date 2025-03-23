#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include "Market.h"

using namespace std;

const int EVALUATION_WINDOW = 100;
    enum Action
{
    BUY,
    SELL,
    HOLD
};

class Strategy
{
private:
    string name;
    // TODO: fill out this part if needed
protected:
    // TODO: fill out this part if needed

    virtual Action decideAction(Market *market, int index, double currentHolding) const = 0;
    // not sure
    virtual double calculateMovingAverage(Market *market, int index, int window) const;
public:
    // TODO: fill out this part if needed
    Strategy();
    Strategy(const string& name);
    ~Strategy();
    string getName() const;
};

#endif