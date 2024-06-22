#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){

int i,j,arr_size=100000000;

int *restrict x;
int *restrict y;
int *restrict z;
x=(int*)malloc(arr_size*sizeof(int));
y=(int*)malloc(arr_size*sizeof(int));
z=(int*)malloc(arr_size*sizeof(int));

for(i=0;i<arr_size;++i){
x[i]=3*i;
y[i]=(i % 100)*(i % 100);
z[i]=0;
}

clock_t start = clock();
for(j=1;j<=100;++j){
for(i=0;i<arr_size;++i){
z[i]=x[i]+y[i]+j;
}
}
clock_t stop = clock();
int duration = (stop-start) * 1000000 / CLOCKS_PER_SEC;
printf("Time for separate[mus]: %d\n",duration);


}
