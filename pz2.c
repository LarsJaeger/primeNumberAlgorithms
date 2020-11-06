#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


int primetester (double pn){
    double rechennummer;
    
    if (pn == 2)
    {
        return 1;
    }
    if (remainder(pn , 2) == 0)
    {
        return 0;
    }
    double halbenummer = sqrt(pn);
    for(rechennummer = 3;rechennummer <= halbenummer;rechennummer += 2)
    {
        if(remainder(pn , rechennummer) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main(){
    clock_t tv1, tv2;
    double time;
    tv1 = clock();

    double limiti = 1500000000000000.0;
    double nummer = 999999999990000.0;
    while (nummer <= limiti)
    {
        
        if(primetester(nummer)==1){
            printf("%f \n",nummer);
        }
        nummer++;
    }



    tv2 = clock();
    time = (tv2 - tv1)/(CLOCKS_PER_SEC / (double) 1000.0); 
    printf("time = %f\n",time );
    return 0;

}