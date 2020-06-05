#include <iostream>
#include <cmath>
#include <map>
#include <iomanip>
#include <random>
using namespace std;

/// With this you can play and see different results
const double dev = 0.7;
const double a = 0.8;

/// Main variables
int number_of_data;
map <double, int> hist;
double meanError = 0.0;
double memory[10] = {0.0}, mean = 0.0, data, forecast, error = 0.0;

/// Data initialization
double input()
{
    random_device rd;
    normal_distribution <double> dist(mean, dev);
    return floor(100.0 * dist(rd)) / 100.0;
}

/// Logistic function of weighted sum
double sigmoid()
{
    double sum = 0;

    for (unsigned i = 0; i < 10; ++i)
        sum += memory[i] * pow(a, i);
    sum = data / (1 + exp(-sum)) - error;

    return floor(100.0 * sum) / 100.0;
}

/// Show result for current forecast
void stage_result()
{
    cout << "Forecast: " << forecast << endl;
    cout << "Actual data: " << data << endl;
    cout << "Algorithm error, abs: " << abs(error) << endl;
    system("pause");
}

/// Main process of program
void data_analysis()
{
    /// Memory and mean updating
    mean = data;
    for (unsigned i = 9; i > 0; --i)
        memory[i] = memory[i - 1];
    memory[0] = data;

    /// Making forecast
    forecast = sigmoid();

    /// Taking another data
    data = input();

    /// Checking for error forecast
    error = forecast - data;
    ++hist[floor(20 * abs(error))];
    meanError += abs(error);

    /// Some info
    /// stage_result();
    /// system("cls");
}

int main()
{
    cout << setprecision(2) << fixed;
    cout << "Enter number of data: " << endl;
    cin >> number_of_data;
    system("cls");

    /// Data analysis seed (no actual data)
    data = input();

    /// Actual data analysis
    for (unsigned i = 0; i < number_of_data; ++i)
        data_analysis();
    meanError /= number_of_data;

    /// Data analysis log
    cout << "Algorithm log: " << endl;
    cout << "Mean error, abs: " << meanError << endl;
    for (auto i : hist)
    {
        cout << i.first / 20 << " - " << i.first / 20 + 0.05 << ": ";
        cout << (float) i.second * 100 / number_of_data << '%' << endl;
    }
    system("pause");

    return 0;
}
