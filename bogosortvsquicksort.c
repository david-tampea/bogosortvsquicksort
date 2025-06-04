#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#define NMAX 100


int compare_ints(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;

    return (int_a > int_b) - (int_a < int_b); 
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

int bogosortpetimp(int arr[], int n, double qs, clock_t start) {//returneaza 1 la succes si 0 la esec
    int k=0;
    clock_t inter;
    double timp;
    while (!is_sorted(arr, n)) {
        if(k++%4==0)srand(time(NULL));//poate ajuta
        shuffle(arr, n);
        inter=clock();
        timp= ((double) (inter - start)) / CLOCKS_PER_SEC;
        if(timp>qs) return 0;
    }
    return 1;
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
    int w=0,iter=0, NMAX=0,dist=-1;
    printf("Ati dori sa incercati bogosort pe:\n1.Un singur array generat aleator\n2.Incepand de la 2 elemente pana la un numar decis de dvs\n3.Pe un array generat aleator, la infinit, pana scoate timp mai bun decat quicksort\noptiune: ");
    int opt=0;
    while(opt!=1&&opt!=2&&opt!=3)
    {
        scanf("%d",&opt);
        if(opt!=1&&opt!=2&&opt!=3) printf("1, 2 sau 3!\noptiune: ");
    }
    printf("Numerele generate vor fi de la 0 la: ");
    while(NMAX<4)
    {
        scanf("%d",&NMAX);
        if(NMAX<4) printf("Minim 4! De la 0 la: ");
    }
    NMAX++;//ca ia pana la NMAX exclusiv si noi am spus utilizatorului inclusiv
    printf("Doriti numere distincte? 0-nu 1-da: ");
    while(dist!=0&&dist!=1)
    {
        scanf("%d",&dist);
        if(dist!=0&&dist!=1) printf("0 sau 1!\noptiune: ");
    }
    if(opt==1||opt==3)printf("Un sir de cate elemente aleatoare doriti sa ordonati?\nans: ");
    if(opt==2)printf("De la 2 pana la un sir de cate elemente aleatoare doriti sa mergeti?\nans: ");
    while(w<3||((w>(NMAX-1))&&dist!=0))
    {
        scanf("%d",&w);
        if(w<3) printf("Minim 3!\nans: ");
        if((w>(NMAX-1))&&dist!=0) printf("Maxim %d!\nans: ",NMAX-1);//daca sunt distincte nu vom putea genera de dimensiuni mai mari decat nmax
    }
    printf("\n");
    if(opt==1||opt==2)
    {
    for(int i=2; i<=w; i++)
    {
        if(opt==1) i=w;//practic asa dam si skip la for
        unsigned long long fact = 1;
        for (int t = 2; t <= i; t++) fact*=t;
        int arr[i],arraux[i],arrauxaux[i];
        gen_rand_arr(i,arr,NMAX,dist);

        for(int j=0; j<i; j++)
        {
            arraux[j]=arr[j];//pt qsort
            arrauxaux[j]=arr[j];//pt estimated time
        }
        printf("Sir de %d elemente amestecat: \n",i);
        afis(i,arr);

        start = clock();
        for(int j=0; j<100000; j++) {shuffle(arrauxaux,i); is_sorted(arrauxaux,i);}//am luat 100000 ca mi se pare suficient. chiar daca ignoram return value-ul de la issorted  tot e mai bine sa il punem ca face parte din bogosort si ne da o estimare mai buna
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        double sps=100000/cpu_time_used;//shuffles/second
        double est=fact/sps;//estimated time = estimated iterations over iterations per second
        printf("Timp estimat: ");//Doar aici ma duc mai sus de ani, deoarece nu cred ca ruleaza cineva programul asta mai mult de 10 ani, dar macar sa stie un estimated time
        
        if(est>=(60*60*24*365.25*1000)) printf("%f milenii.\n",est/(60*60*24*365.25*1000));
        else if(est>=(60*60*24*365.25*100)) printf("%f secole.\n",est/(60*60*24*365.25*100));
        else if(est>=(60*60*24*365.25*10)) printf("%f decenii.\n",est/(60*60*24*365.25*10));
        else if(est>=(60*60*24*365.25)) printf("%f ani.\n",est/(60*60*24*365.25));
        else if(est>=(60*60*24*30)) printf("%f luni.\n",est/(60*60*24*30));
        else if(est>=(60*60*24*7)) printf("%f saptamani.\n",est/(60*60*24*7));
        else if(est>=(60*60*24)) printf("%f zile.\n",est/(60*60*24));
        else if(est>=(60*60)) printf("%f ore.\n",est/(60*60));
        else if(est>=60) printf("%f minute.\n",est/60);
        else if(est>1) printf("%f secunde.\n",est);
        else if(est>0.001) printf("%f milisecunde.\n",1000*(est));
        else if(est>0.000001) printf("%f microsecunde.\n",1000000*(est));
        else if(est>0.000000001) printf("%f nanosecunde.\n",1000000000*(est));
        else if(est!=0) printf("%f picosecunde.\n",1000000000000*(est));
        else if(est==0)printf("instant.\n");
        
        start = clock();
        iter=bogosort(arr,i);
        end = clock();
        printf("Sir de %d elemente ordonat: \n",i);
        afis(i,arr);
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        if (cpu_time_used >= 60*60*24*365.25) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f ANI!\n", i, cpu_time_used/(60*60*24*365.25));
        else if (cpu_time_used >= 60*60*24*30) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f LUNI!\n", i, cpu_time_used/(60*60*24*30));
        else if (cpu_time_used >= 60*60*24*7) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f SAPTAMANI!\n", i, cpu_time_used/(60*60*24*7));
        else if (cpu_time_used >= 60*60*24) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f ZILE!\n", i, cpu_time_used/(60*60*24));
        else if (cpu_time_used >= 60*60) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f ORE!\n", i, cpu_time_used/(60*60));
        else if (cpu_time_used >= 60) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f MINUTE!\n", i, cpu_time_used/60);
        else if (cpu_time_used >= 1) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f SECUNDE!\n", i, cpu_time_used);
        else if (cpu_time_used >= 0.001) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f MILISECUNDE!\n", i, 1000 * cpu_time_used);
        else if (cpu_time_used >= 0.000001) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f MICROSECUNDE!\n", i, 1000000 * cpu_time_used);
        else if (cpu_time_used >= 0.000000001) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f NANOOSECUNDE!\n", i, 1000000000 * cpu_time_used);
        else if (cpu_time_used != 0) printf("PENTRU %d ELEMENTE BOGOSORT A DURAT %f PICOSECUNDE!\n", i, 1000000000000 * cpu_time_used);
        else printf("PENTRU %d ELEMENTE BOGOSORT A FOST INSTANT!\n", i);
        if (iter>0) {
            printf("A fost nevoie de %d incercari de shuffle\n",iter);
            if(cpu_time_used>0)printf("Asta inseamna %f shuffles/second\n", (double)iter/cpu_time_used);
            

            if ((unsigned long long)iter < fact) {
                printf("Esti norocos! Ai avut %d iteratii, dar media e %llu. Mai norocos cu %d%% decat media!\n", iter, fact, (int)((fact/iter)*100));
            } else if ((unsigned long long)iter > fact) {
                printf("Esti ghinionist! Ai avut %d iteratii, dar media e %llu. Mai ghinionist cu %d%% decat media!\n", iter, fact,(int)((iter/fact)*100));
            } else {
                printf("Wow, ai nimerit exact sansa matematica! Ai avut %d iteratii, adica %llu in medie.\n", iter, fact);
            }
        }
        else printf("S-a nimerit ca sirul sa fie direct ordonat, n-a fost nevoie de nicio incercare de shuffle!\n");
        start = clock();
        qsort(arraux,i,sizeof(int),compare_ints);
        end = clock();
        qs = ((double) (end - start)) / CLOCKS_PER_SEC;
        if(qs<cpu_time_used)
        {
            double diff_qs = cpu_time_used - qs;
            if (diff_qs >= 60*60*24*365.25) printf("Quicksort a fost cu %f ANI mai rapid\n\n", diff_qs/(60*60*24*365.25));
            else if (diff_qs >= 60*60*24*30) printf("Quicksort a fost cu %f LUNI mai rapid\n\n", diff_qs/(60*60*24*30));
            else if (diff_qs >= 60*60*24*7) printf("Quicksort a fost cu %f SAPTAMANI mai rapid\n\n", diff_qs/(60*60*24*7));
            else if (diff_qs >= 60*60*24) printf("Quicksort a fost cu %f ZILE mai rapid\n\n", diff_qs/(60*60*24));
            else if (diff_qs >= 60*60) printf("Quicksort a fost cu %f ORE mai rapid\n\n", diff_qs/(60*60));
            else if (diff_qs >= 60) printf("Quicksort a fost cu %f MINUTE mai rapid\n\n", diff_qs/60);
            else if (diff_qs >= 1) printf("Quicksort a fost cu %f SECUNDE mai rapid\n\n", diff_qs);
            else if (diff_qs >= 0.001) printf("Quicksort a fost cu %f MILISECUNDE mai rapid\n\n", 1000 * diff_qs);
            else if (diff_qs >= 0.000001) printf("Quicksort a fost cu %f MICROSECUNDE mai rapid\n\n", 1000000 * diff_qs);
            else if (diff_qs >= 0.000000001) printf("Quicksort a fost cu %f NANOOSECUNDE mai rapid\n\n", 1000000000 * diff_qs);
            else if (diff_qs != 0) printf("Quicksort a fost cu %f PICOSECUNDE mai rapid\n\n", 1000000000000 * diff_qs);
            else printf("EGALITATE DE TIMP CU QUICKSORT!\n\n");

        }
        else if(cpu_time_used==qs)
        {
            printf("EGALITATE DE TIMP CU QUICKSORT!\n\n");
        }
        else if(cpu_time_used<qs)
        {//aici sincer e foarte unlikely sa fie nevoie vreodata de supraunitati ale secundei, dar le-am pus sa fie
            double diff_bo = qs - cpu_time_used;
            if (diff_bo >= 60*60*24*365.25) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f ANI!!!\n", diff_bo/(60*60*24*365.25));
            else if (diff_bo >= 60*60*24*30) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f LUNI!!!\n", diff_bo/(60*60*24*30));
            else if (diff_bo >= 60*60*24*7) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f SAPTAMANI!!!\n", diff_bo/(60*60*24*7));
            else if (diff_bo >= 60*60*24) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f ZILE!!!\n", diff_bo/(60*60*24));
            else if (diff_bo >= 60*60) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f ORE!!!\n", diff_bo/(60*60));
            else if (diff_bo >= 60) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f MINUTE!!!\n", diff_bo/60);
            else if (diff_bo >= 1) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f SECUNDE!!!\n", diff_bo);
            else if (diff_bo >= 0.001) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f MILISECUNDE!!!\n", 1000 * diff_bo);
            else if (diff_bo >= 0.000001) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f MICROSECUNDE!!!\n", 1000000 * diff_bo);
            else if (diff_bo >= 0.000000001) printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f NANOSECUNDE!!!\n", 1000000000 * diff_bo);
            else printf("SUNTETI EXTREM DE NOROCOS! BOGOSORT A ARANJAT ARRAY-UL MAI REPEDE DECAT QUICKSORT CU %f PICOSECUNDE!!!\n", 1000000000000 * diff_bo);

        }
    }

}
else if (opt==3)
{
    int i=w, win=0, k=0;
    long long int incercare=0;
    int arr[i],arraux[i],auxi[i];
    double bg=0;
    printf("Se incearca   ");
    do{
        if(k++%4==0) {
            printf("\b\b\b");
            srand(time(NULL));//poate ajuta
        }
        else printf(".");
        gen_rand_arr(i,arr,NMAX,dist);
        for(int j=0; j<i; j++)
        {
            arraux[j]=arr[j];//pt qsort
            auxi[j]=arr[j];//pt a tine minte initial
        }
        //printf("Sir de %d elemente amestecat: \n",i);
        //afis(i,arr);
        //am renuntat la print-uri ca erau prea multe, am inlocuit cu animatia de "..."
        start = clock();
        qsort(arraux,i,sizeof(int),compare_ints);
        end = clock();
        qs = ((double) (end - start)) / CLOCKS_PER_SEC;//time to beat
        start = clock();
        win = bogosortpetimp(arr,i,qs,start);
        end = clock();
        bg = ((double) (end - start)) / CLOCKS_PER_SEC;
        incercare++;
    }while(win==0);
for(int i=0; i<k%4; i++) printf("\b");//sa curat punctele ramase sper
printf("\nSir initial de %d elemente amestecat: \n",i);
afis(i,auxi);
printf("Sir de %d elemente sortat prin bogosort:\n",i);
afis(i,arr);
if(is_sorted(auxi,i)) printf("Ati avut noroc, sirul s-a generat direct sortat, totusi ");
if(win) {printf("FELICITARI, ATI ");
    if(bg>qs) printf("BATUT");
    else if(bg==qs) printf("EGALAT");
    else printf("WTF");//N-AR TREBUI SA AJUNGA AIVI DIN MOMENT CE A IESIT DIN WHILE
 printf(" QUICKSORT-UL DIN INCERCAREA A %lld-A!\n",incercare);//nu mai am chef sa scriu cu cate mili micro nano secunde
}
}
}
