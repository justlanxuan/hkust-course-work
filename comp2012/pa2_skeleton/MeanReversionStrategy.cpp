#include "MeanReversionStrategy.h"
#include "Utils.h"
#include <cmath>
#include <iostream>
// Task 4.1 done
MeanReversionStrategy::MeanReversionStrategy():Strategy(),window(0),threshold(0)
{
}
// Task 4.2 done
MeanReversionStrategy::MeanReversionStrategy(const string &name, int window, int threshold):Strategy(name),window(window),threshold(threshold)
{
}
// Task 4.3 done
Action MeanReversionStrategy::decideAction(Market *market, int index, double currentHolding) const
{
    double moving_average = calculateMovingAverage(market,index,this->window);
    // if the price is above ma by the threshold amout, then sell
    if(market->getLastPrice()>moving_average*(1+this->threshold) && currentHolding==1){
        // sell
        return SELL;
    }
    else if (market->getLastPrice()<moving_average*(1-this->threshold) && currentHolding ==0){
        // buy
        return BUY;
    }
    else{
        return HOLD;
    }
}
// Task 4.4 done
MeanReversionStrategy **MeanReversionStrategy::generateStrategySet(const string &baseName, int minWindow, int maxWindow, int windowStep, int minThreshold, int maxThreshold, int thresholdStep)
{
    int num_of_combination = 0;
    int count = 0;
    for (int i=minWindow;i<=maxWindow;i+=windowStep){
        for (int j=minThreshold;j<=maxThreshold;j+=thresholdStep){
            num_of_combination++;
        }
    }
    MeanReversionStrategy ** strategies = new MeanReversionStrategy*[num_of_combination];
    for (int i=minWindow;i<=maxWindow;i+=windowStep){
        for (int j=minThreshold;j<=maxThreshold;j+=thresholdStep){
            strategies[count] = new MeanReversionStrategy(baseName + "_" + to_string(i) + "_" + to_string(j),i,j);
            count ++;
        }
    }

}