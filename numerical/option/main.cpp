#include <cmath>
#include <stdio.h>
#include <ctime>
#include <random>
#include <iostream>
using namespace std;

int TRIALS;

bool callOption;

int Tdays;
double strike;
double vol;
double r;
double S0;
double T;
double sqT;
double rmvol2t;

std::default_random_engine generator(time(0));
std::normal_distribution<double> distribution(0.0, 1.0);

double normalCFD(double value) {
   return 0.5 * erfc(-value * M_SQRT1_2);
}

double simulateMonteCarlo() {
    
    double bt = distribution(generator)*sqT;

    double St = S0*exp(rmvol2t + bt*vol);

    double payoff = St - strike;

    if (!callOption) {
        payoff = -payoff;
    }

    if (payoff < 0) {
        payoff = 0;
    }

    double optionPrice = payoff*exp(-r*T);

    return optionPrice;
}

double black_scholes() {
    double d1, d2;
    d1 = log(S0 / strike) + T*(r + vol*vol / 2.0);
    d1 /= vol*sqT;

    d2 = log(S0 / strike) + T*(r - vol*vol / 2.0);
    d2 /= vol*sqT;

    return S0*normalCFD(d1) - strike*exp(-r*T)*normalCFD(d2);
}

int main() {
    srand(time(0));

    printf("Current stock price: ");
    scanf("%lf", &S0);

    printf("Risk-free interest rate in percents: ");
    scanf("%lf", &r);
    r /= 100.0;

    int temp;
    printf("Insert 1 if the option is a call option, 0 otherwise: ");
    scanf("%d", &temp);
    callOption = temp;

    printf("Strike price of the option: ");
    scanf("%lf", &strike);

    printf("Number of days until expiration of the option: ");
    scanf("%d", &Tdays);

    printf("Implied volatility in percents: ");
    scanf("%lf", &vol);
    vol /= 100.0;

    printf("Specify the number of trials for Monte Carlo (e.g. 1000000): ");
    scanf("%d", &TRIALS);

    T = (double)Tdays / 365.0;
    sqT = sqrt(T);
    rmvol2t = (r - vol*vol / 2.0) * T;

    double sum = 0;
    for (int i = 0; i < TRIALS; ++i) {
        double price = simulateMonteCarlo();
        sum += price;
    }

    double optionPrice = sum / TRIALS;

    printf("Option price according to Monte Carlo simulation: %.6f\n", optionPrice);
    printf("Option price according to Black-Scholes equation: %.6f\n", black_scholes());

    return 0;
}