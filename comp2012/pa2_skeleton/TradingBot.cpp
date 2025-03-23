#include "TradingBot.h"
#include <limits>
// Task 2.1 done
TradingBot::TradingBot(Market *market, int initialCapacity):market(market), strategyCapacity(initialCapacity),strategyCount(0)
{
    this->availableStrategies = new Strategy*[this->strategyCapacity]{nullptr};
}
// Task 2.2 done
TradingBot::~TradingBot()
{
    delete [] availableStrategies;
}
// Task 2.3 done
void TradingBot::addStrategy(Strategy *strategy)
{
    // if the capacity is reached
    if(this->strategyCapacity <= this->strategyCount){
        Strategy ** temp = new Strategy*[strategyCapacity+1];
        for(int i=0;i<this->strategyCapacity;i++){
            temp[i] = this->availableStrategies[i];
        }
        temp[strategyCapacity] = strategy;
        delete [] this->availableStrategies;
        availableStrategies = temp;
        strategyCapacity++;
    }
    else{
        this->availableStrategies[this->strategyCount-1] = strategy;
    }
    strategyCount++;
}
// Task 2.4
SimulationResult TradingBot::runSimulation()
{
    double profit = 0;
    for(int i=101;i>0;i--){
        int trading_day = this->market->getNumTradingDays()-i;
        // if no stock

    }


}
