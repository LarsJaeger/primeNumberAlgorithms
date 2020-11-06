#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <pthread.h>


// config
static const double upperEnd = 150.0;
static const double lowerEnd = 99.0;
static double currentNumber = lowerEnd;


static double getNextNumber() {
    if(currentNumber > upperEnd) {
        return 0;
    }
    double nr = currentNumber;
    currentNumber++;
    return nr;
}

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
void *testRemainingNumbers() {
    double currentThreadNumber = getNextNumber();
    while(currentThreadNumber != 0) {
        if (primetester(currentThreadNumber) == 1) {
            printf("%.0f \n", currentThreadNumber);
        }
        currentThreadNumber = getNextNumber();
    }
    return NULL;
}

int main() {
    //timing start
    clock_t tv1, tv2;
    double time;
    tv1 = clock();

    //multithreading setup
    pthread_t threads[4];

    //thread starter
    for(int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        printf("%i \n", i);
        pthread_create(&threads[i], NULL, &testRemainingNumbers, NULL);
    }
    //thread stopper
    for(int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        pthread_join(threads[i], NULL);
    }

    //end of timing
    tv2 = clock();
    time = (tv2 - tv1) / (CLOCKS_PER_SEC / (double) 1000.0);
    printf("time = %f\n", time);
    return 0;

}