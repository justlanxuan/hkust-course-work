#include "Market.h"
#include "Utils.h"

// Task 1.1 done! (price每一天里面是数组？)
Market::Market(double initialPrice, double volatility, double expectedYearlyReturn, int numTradingDays, int seed):initialPrice(initialPrice),volatility(volatility),expectedYearlyReturn(expectedYearlyReturn),numTradingDays(numTradingDays),seed(seed)
{
    prices = new double*[numTradingDays];
    for(int i=0;i<numTradingDays;i++){
        prices[i] = new double{0};
    }
}
// Task 1.2 done!
Market::Market(const string &filename)
{
    this->loadFromFile(filename);
}
// Task 1.10 done!(price每一天里面是数组？)
Market::~Market()
{
    for (int i = 0; i < this->numTradingDays; i++) {
        delete prices[i]; 
    }
    delete[] prices;      
}

// ===== Don't modify below this line =====
// Helper function to generate a random number from a normal distribution
double Market::generateZ(int seed)
{
    static std::mt19937 gen(seed == -1 ? std::random_device{}() : seed);
    static std::normal_distribution<> d(0, 1);
    return d(gen);
}
// ===== Don't modify above this line =====

// Task 1.5 done!
void Market::simulate() 
{
    double price_today = roundToDecimals(this->initialPrice,3);
    for(int i=0; i<this->numTradingDays;i++){
        *prices[i] = price_today;
        price_today = roundToDecimals(price_today*exp((this->expectedYearlyReturn-0.5*this->volatility*this->volatility)/TRADING_DAYS_PER_YEAR+this->volatility*sqrt(1/TRADING_DAYS_PER_YEAR)*generateZ(this->seed)),3);
    }
}
// Task 1.3 done!
double Market::getVolatility() const
{
    return this->volatility;
}
// Task 1.4 done!
double Market::getExpectedYearlyReturn() const
{
    return this->expectedYearlyReturn;
}
// Task 1.6 done!
double **Market::getPrices() const
{
    return this->prices;
}
// Task 1.7 done!
double Market::getPrice(int index) const
{
    return *this->prices[index];
}
// Task 1.8 done!
double Market::getLastPrice() const
{
    return *this->prices[this->numTradingDays-1];
}
// Task 1.9 
int Market::getNumTradingDays() const
{
    return this->numTradingDays;
}

// ===== Don't modify below this line =====
void Market::createDirectory(const string &folder)
{
#ifdef _WIN32
    _mkdir(folder.c_str());
#else
    mkdir(folder.c_str(), 0777);
#endif
}

void Market::writeToFile(const string &filename)
{
    string folder = "data";
    string filePath = folder + "/" + filename;

    createDirectory(folder);

    ofstream outFile(filePath);
    if (!outFile)
    {
        cerr << "Error opening file for writing: " << filePath << endl;
        return;
    }

    outFile << initialPrice << " " << volatility << " "
            << expectedYearlyReturn << " " << numTradingDays << " " << seed << endl;

    for (int i = 0; i < numTradingDays; ++i)
    {
        outFile << *prices[i] << endl;
    }

    outFile.close();
    cout << "Market parameters and prices written to file: " << filePath << endl;
}

void Market::loadFromFile(const string &filename)
{
    string filePath = "data/" + filename;
    ifstream inFile(filePath);
    if (!inFile)
    {
        cerr << "Error opening file for reading: " << filePath << endl;
        return;
    }

    inFile >> initialPrice >> volatility >> expectedYearlyReturn >> numTradingDays >> seed;

    // Clear existing prices
    if (prices)
    {
        for (int i = 0; i < numTradingDays; i++)
        {
            delete prices[i];
        }
        delete[] prices;
    }

    // Count number of prices first
    ifstream countFile(filePath);
    string line;
    int count = 0;
    double dummy;
    countFile >> dummy >> dummy >> dummy >> dummy >> dummy; // Skip parameters
    while (countFile >> dummy)
        count++;
    countFile.close();

    // Allocate new array
    prices = new double *[count];
    for (int i = 0; i < count; i++)
    {
        prices[i] = new double(0.0);
    }

    // Read prices
    int pricesSize = 0;
    double price;
    while (inFile >> price)
    {
        *prices[pricesSize++] = price;
    }

    inFile.close();
    cout << "Loaded parameters from file: " << filePath << endl;
    cout << "Initial Price: " << initialPrice << ", Volatility: " << volatility
         << ", Expected Yearly Return: " << expectedYearlyReturn
         << ", Num of Trading Days: " << numTradingDays << ", Seed: " << seed << endl;
    cout << "Loaded " << pricesSize << " price entries." << endl;
}
// ===== Don't modify above this line =====

// TODO: Implement the member functions of the Market class
