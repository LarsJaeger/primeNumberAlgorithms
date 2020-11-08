#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <pthread.h>


// config
static FILE *fp;
static const double upperEnd = 9999999999.0;
static const double lowerEnd = 9000000000.0;
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
            //printf("%.0f \n", currentThreadNumber);
            fprintf(fp ,"%.0f \n", currentThreadNumber);
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

    //open file
    
    fp = fopen("Primzahlen.txt", "w");
    fprintf(fp ,"Remaininator!!!\n");


    //multithreading setup
    pthread_t threads[16]; // number of threads besides the main thread

    //thread starter
    for(int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        //printf("%i \n", i);
        pthread_create(&threads[i], NULL, &testRemainingNumbers, NULL);
    }
    //thread stopper
    for(int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        pthread_join(threads[i], NULL);
    }

    //end of timing
    tv2 = clock();
    time = (double) (tv2 - tv1) / CLOCKS_PER_SEC;
    fprintf(fp ,"time = %f\n", time);

    //close file
    fclose(fp);
    return 0;

}