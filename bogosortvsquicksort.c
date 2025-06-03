#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#define NMAX 100


int compare_ints(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;

    return (int_a > int_b) - (int_a < int_b); // adică: 1, 0 sau -1
    // Sau simplu: return int_a - int_b; (dar poate da overflow la int-uri mari)
}

int is_sorted(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i])
            return 0;
    }
    return 1;
}

void shuffle(int arr[], int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int bogosort(int arr[], int n) {
    int k=0;
    while (!is_sorted(arr, n)) {
        if(k++%4==0) {
            printf("\b\b\b");
            srand(time(NULL));//poate ajuta
        }
        else printf(".");
        shuffle(arr, n);
    }
    for(int i=0; i<k%4; i++) printf("\b");//sa curat punctele ramase
    return k;
}

int isinarr(int el, int n, int arr[n])
{
    for(int i=0; i<n; i++)
    {
        if(arr[i]==el) return 1;
    }
    return 0;
}

void gen_rand_arr(int n, int arr[n], int NMAX, int dist)
{
    int aux=0;
    for(int i=0; i<n; i++)
    {
        if(dist==0) arr[i]=rand()%NMAX;
        else 
        {
            while(isinarr(aux=rand()%NMAX,i,arr))
            {
                continue;
            }
            arr[i]=aux;
        }
    }
}

void afis(int n, int arr[n])
{
    for(int i=0;i<n;i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used, qs;
    int w=0,iter=0, NMAX=0,dist=0;
    printf("Numerele generate vor fi de la 1 la: ");
    while(NMAX<10)
    {
        scanf("%d",&NMAX);
        if(NMAX<10) printf("Minim 10! De la 1 la: ");
    }
    printf("Doriti numere distincte? 0-nu 1-da: ");
    scanf("%d",&dist);
    printf("De la 2 pana la un sir de cate elemente doriti sa mergeti?\nans: ");
    while(w<3||((w>(NMAX-1))&&dist!=0))
    {
        scanf("%d",&w);
        if(w<3) printf("Minim 3!\nans: ");
        if((w>(NMAX-1))&&dist!=0) printf("Maxim %d!\nans: ",NMAX-1);//daca sunt distincte nu vom putea genera de dimensiuni mai mari decat nmax
    }
    printf("\n");
    for(int i=2; i<=w; i++)
    {
        int arr[i],arraux[i];
        gen_rand_arr(i,arr,NMAX,dist);

        for(int j=0; j<i; j++)
        {
            arraux[j]=arr[j];
        }
        printf("Sir de %d elemente amestecat: \n",i);
        afis(i,arr);
        start = clock();
        iter=bogosort(arr,i);
        end = clock();
        printf("Sir de %d elemente ordonat: \n",i);
        afis(i,arr);
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        if(cpu_time_used>1) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f SECUNDE!\n",i,cpu_time_used);
        else if(cpu_time_used>0.001) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f MILISECUNDE!\n",i,1000*(cpu_time_used));
        else if(cpu_time_used>0.000001) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f MICROSECUNDE!\n",i,1000000*(cpu_time_used));
        else if(cpu_time_used>0.000000001) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f NANOOSECUNDE!\n",i,1000000000*(cpu_time_used));
        else if(cpu_time_used!=0) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f PICOSECUNDE!\n",i,1000000000000*(cpu_time_used));
        else printf("PENTRU %d ELEMENTE BOGOSORT A FOST INSTANT!\n",i);

        if (iter>0) {
            printf("A fost nevoie de %d incercari de shuffle\n",iter);
            if(cpu_time_used>0)printf("Asta inseamna %f shuffles/second\n", (double)iter/cpu_time_used);
        }
        else printf("S-a nimerit ca sirul sa fie direct ordonat, n-a fost nevoie de nicio incercare de shuffle!\n");
        start = clock();
        qsort(arraux,i,sizeof(int),compare_ints);
        end = clock();
        qs = ((double) (end - start)) / CLOCKS_PER_SEC;
        if(qs<cpu_time_used)
        {
            if(cpu_time_used-qs>1) printf("Quicksort a fost cu %f secunde mai rapid\n\n",cpu_time_used-qs);
            else if(cpu_time_used-qs>0.001) printf("Quicksort a fost cu %f milisecunde mai rapid\n\n",1000*(cpu_time_used-qs));
            else if(cpu_time_used-qs>0.000001) printf("Quicksort a fost cu %f microsecunde mai rapid\n\n",1000000*(cpu_time_used-qs));
            else if(cpu_time_used-qs>0.000000001) printf("Quicksort a fost cu %f nanosecunde mai rapid\n\n",1000000000*(cpu_time_used-qs));
            else printf("Quicksort a fost cu %f picosecunde mai rapid\n\n",1000000000000*(cpu_time_used-qs));
        }
        else if(cpu_time_used==qs)
        {
            printf("EGALITATE DE TIMP CU QUICKSORT!\n\n");
        }
        else if(cpu_time_used<qs)
        {
            if(qs-cpu_time_used>1) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f SECUNDE!!!\n", qs-cpu_time_used);
            else if(qs-cpu_time_used>0.001) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f MILISECUNDE!!!\n", 1000*(qs-cpu_time_used));
            else if(qs-cpu_time_used>0.000001) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f MICROSECUNDE!!!\n", 1000000*(qs-cpu_time_used));
            else if(qs-cpu_time_used>0.000000001) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f NANOSECUNDE!!!\n", 1000000000*(qs-cpu_time_used));
            else printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f PICOSECUNDE!!!\n", 1000000000000*(qs-cpu_time_used));
        }
    }

    
}
