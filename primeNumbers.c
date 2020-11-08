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
static const double upperEnd = 9999999999.0;
static const double lowerEnd = 9990000000.0;
static double currentNumber = lowerEnd;


static double getNextNumber() {
    if (currentNumber > upperEnd) {
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
    while (currentThreadNumber != 0) {
        if (primetester(currentThreadNumber) == 1) {
            //printf("%.0f \n", currentThreadNumber);
            fprintf(fp, "%.0f \n", currentThreadNumber);
        }
        currentThreadNumber = getNextNumber();
    }
    return NULL;
}

int64_t timestamp_now(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int64_t) tv.tv_sec * CLOCKS_PER_SEC + tv.tv_usec;
}

double timestamp_to_seconds(int64_t timestamp) {
    return timestamp / (double) CLOCKS_PER_SEC;
}

int main() {
    double percent;
    double percentLast;
    //timing start
    int64_t start = timestamp_now();


    //open file

    fp = fopen("Primzahlen.txt", "w");


    //multithreading setup
    pthread_t threads[16]; // number of threads besides the main thread

    //thread starter
    for (int i = 0; i < sizeof(threads) / sizeof(threads[0]); i++) {
        //printf("%i \n", i);
        pthread_create(&threads[i], NULL, &testRemainingNumbers, NULL);
    }
    //status
    while (currentNumber <= upperEnd) {
        percentLast = percent;
        percent = (double) (((double) currentNumber - lowerEnd) / ((double) upperEnd - lowerEnd));
        printf("%f %%, %.0f seconds remaining \n", percent, (double) (100.0 - percent) / (percent - percentLast));
        sleep(1);
    }
    //thread stopper
    for (
            int i = 0;
            i < sizeof(threads) / sizeof(threads[0]); i++) {
        pthread_join(threads[i], NULL
        );
    }
}

//end of timing

fprintf(fp,
"took %f seconds\n",

timestamp_to_seconds (timestamp_now()

- start));

//close file
fclose(fp);
return 0;

}
