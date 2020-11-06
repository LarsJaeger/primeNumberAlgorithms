#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


int primetester(double pn) {
    double rechenNummer;

    if (pn == 2) {
        return 1;
    }
    if (remainder(pn, 2) == 0) {
        return 0;
    }
    double highestPossibleFactor = sqrt(pn);
    for (rechenNummer = 3; rechenNummer <= highestPossibleFactor; rechenNummer += 2) {
        if (remainder(pn, rechenNummer) == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    clock_t tv1, tv2;
    double time;
    tv1 = clock();

    double upperEnd = 1500000000000000.0;
    double lowerEnd = 999999999990000.0;
    for(double i = lowerEnd; i <= upperEnd; i++) {
        if (primetester(i) == 1) {
            printf("%f \n", i);
        }
    }


    tv2 = clock();
    time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
    printf("time = %f\n", time);
    return 0;

}