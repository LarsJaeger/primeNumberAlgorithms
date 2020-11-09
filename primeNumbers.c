#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <pthread.h>


// config
static FILE *fp;
static double upperLimit = 99.0;
static double lowerLimit = 0.0;
static double currentNumber;


static double getNextNumber() {
    if(currentNumber > upperLimit) {
        return 0;
    }
    double nr = currentNumber;
    currentNumber += 2;
    return nr;
}

int primetester(double pn) {
    double rechenNummer;
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

int64_t timestamp_now (void)
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return (int64_t) tv.tv_sec * CLOCKS_PER_SEC + tv.tv_usec;
}

double timestamp_to_seconds (int64_t timestamp)
{
    return timestamp / (double) CLOCKS_PER_SEC;
}

int main() {
    //input thread number and limits
    int threadNumber;
    printf("please enter the number of threads you want to run: ");
    scanf("%d", &threadNumber);
    printf("please set the lower limit: ");
    scanf("%lf", &lowerLimit);
    printf("please set the upper limit: ");
    scanf("%lf", &upperLimit);
    double percent = 0;
    double percentLast = 0;
    //timing start
    int64_t start = timestamp_now ();
    

    //open file
    
    fp = fopen("Primzahlen.txt", "w");
    
    //prepare limits and current number
    if(lowerLimit < 0) {
        printf("please choose a positive number or zero as the lower limit");
        return 0;
    }
    currentNumber = lowerLimit;
    if(currentNumber == 1) {
        fprintf(fp ,"%.0f \n", 1.0);
    }
    if(remainder(currentNumber, 2) == 0) {
        currentNumber++;
    }

    //multithreading setup
    pthread_t threads[threadNumber]; // number of threads besides the main thread
    
    //thread starter
    for(int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        //printf("%i \n", i);
        pthread_create(&threads[i], NULL, &testRemainingNumbers, NULL);
    }
    //status
    
    while(currentNumber <= upperLimit) {
        percentLast = percent;
        percent = (double) (((double) currentNumber - lowerLimit )/ ((double) upperLimit - lowerLimit)) * 100;
        printf("%f %%, %.0f seconds remaining \n", percent, (double) (100.0 - percent) / (double) (percent - percentLast));
        sleep(1);
    }
    //thread stopper
    for(int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        pthread_join(threads[i], NULL);
    }

    //end of timing
    
    fprintf(fp ,"took %f seconds\n", 
            timestamp_to_seconds (timestamp_now () - start));

    //close file
    fclose(fp);
    return 1;

}
