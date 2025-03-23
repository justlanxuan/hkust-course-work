#include "Strategy.h"
#include <iostream>
// Task 3.1 done
Strategy::Strategy():name("")
{
}
// Task 3.2 done
Strategy::Strategy(const string &name):name(name)
{
}
// Task 3.4 done
double Strategy::calculateMovingAverage(Market *market, int index, int window) const
{
    // if the window is falling beyond the array bound
    if(window > index){
        double cumulated_price = 0;
        for(int i=0;i<=index;i++){
            cumulated_price += market->getPrice(i);
        }
        return cumulated_price/(index+1);
    }   
    else{
        double cumulated_price = 0;
        for(int i=index;i>index-window;i--){
            cumulated_price += market->getPrice(i);
        }
        return cumulated_price/window;
    }
}
// Task 3.3 done
string Strategy::getName() const
{
    return this->name;
}
