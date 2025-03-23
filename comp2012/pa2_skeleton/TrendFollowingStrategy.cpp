#include "TrendFollowingStrategy.h"
#include "Utils.h"
#include <iostream>
// Task 5.1 done!
TrendFollowingStrategy::TrendFollowingStrategy():Strategy(),shortMovingAverageWindow(0),longMovingAverageWindow(0)
{
}
// Task 5.2 done!
TrendFollowingStrategy::TrendFollowingStrategy(const std::string &name, int shortWindow, int longWindow): Strategy(name),shortMovingAverageWindow(shortWindow),longMovingAverageWindow(longWindow)
{
}
// Task 5.3 done!
Action TrendFollowingStrategy::decideAction(Market *market, int index, double currentHolding) const
{
    double short_ma = calculateMovingAverage(market,index,this->shortMovingAverageWindow);
    double long_ma = calculateMovingAverage(market,index,this->longMovingAverageWindow);
    if(short_ma > long_ma && currentHolding == 0){
        return BUY;
    }
    else if(long_ma > short_ma && currentHolding == 1){
        return SELL;
    }
    else{
        return HOLD;
    }
}
// Task 5.4
TrendFollowingStrategy **TrendFollowingStrategy::generateStrategySet(const string &baseName, int minShortWindow, int maxShortWindow, int stepShortWindow, int minLongWindow, int maxLongWindow, int stepLongWindow)
{
    int num_of_combination = 0;
    int count = 0;
    for (int i=minShortWindow;i<=maxShortWindow;i+=stepShortWindow){
        for (int j=minLongWindow;j<=maxLongWindow;j+=stepLongWindow){
            num_of_combination++;
        }
    }
    TrendFollowingStrategy ** strategies = new TrendFollowingStrategy*[num_of_combination];
    for (int i=minShortWindow;i<=maxShortWindow;i+=stepShortWindow){
        for (int j=minLongWindow;j<=maxLongWindow;j+=stepLongWindow){
            strategies[count] = new TrendFollowingStrategy(baseName + "_" + to_string(i) + "_" + to_string(j),i,j);
            count ++;
        }
    }
}
