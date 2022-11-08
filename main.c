#include <inttypes.h>
#include <stdio.h>
#include <math.h>

/*n^2 + an + n <= 2001000*/
#define UBOUND 2001001 

#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))

uint64_t iscompound[1+((UBOUND+1)>>6)];
int primesList[170];
int numprimes;
void fillprimes(int upperBound);

int main()
{
    fillprimes(UBOUND);
    int maxlen = 0, amax = 0, bmax = 0;
    for(int b = 2; b <= 1000; b++){
        //b has to be prime
        if(baisset(iscompound, b)){
            continue;
        }

        for(int a = -999; a < 1000; a++){               
            int runlen = 1; //n = 0 is valid since b is prime
            int n = 1;
            int num = n*(n + a) + b;
            while(num > 1 && baisclear(iscompound, num)){
                runlen++;
                n++;
                num = n*(n + a) + b;
            }
            if(runlen > maxlen){
                maxlen = runlen;
                amax = a;
                bmax = b;
            }
        }
    }

    printf("len: %d; a: %d; b: %d; result:% d\n", maxlen, amax, bmax, amax*bmax);
}




void fillprimes(int upperBound) {
	int i, j;


	baset(iscompound, 0);
	baset(iscompound, 1);
	int sqrtUb = sqrt(upperBound);
	for (i = 2; i <= sqrtUb; i++) {
		if (baisclear(iscompound, i)) {
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
			}
		}
	}

}
