#include "WeightedTrendFollowingStrategy.h"
#include "Utils.h"
#include <cmath>
// Task 6.1 done
WeightedTrendFollowingStrategy::WeightedTrendFollowingStrategy():TrendFollowingStrategy()
{
}
// Task 6.2 done
WeightedTrendFollowingStrategy::WeightedTrendFollowingStrategy(const string &name, int shortWindow, int longWindow):TrendFollowingStrategy(name,shortWindow,longWindow)
{
}
// Task 6.3
double WeightedTrendFollowingStrategy::calculateExponentialWeight(int index) const
{
}
// Task 6.4 
double WeightedTrendFollowingStrategy::calculateMovingAverage(Market *market, int index, int window) const
{
}

WeightedTrendFollowingStrategy **WeightedTrendFollowingStrategy::generateStrategySet(const string &baseName, int minShortWindow, int maxShortWindow, int stepShortWindow, int minLongWindow, int maxLongWindow, int stepLongWindow)
{
}
