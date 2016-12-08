#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned uint;
#define swap(a,b) { tmp=(a); (a)=(b); (b)=tmp; }
#define each(i,x) for (i=0; i<x; ++i)

/* unsigned int sort */
static void u_radsort(uint *from, uint *to, uint bit)
{
	if (!bit || to<from+1)
		return;

	uint *ll = from,
		*rr = to-1,
		tmp;

	while (1) {
		/* find left most w/ bit, and right most w/o bit, swap */
		while (ll<rr && !(*ll & bit))
			ll++;	
		while (ll<rr && (*rr & bit))
			rr--;	
		if (ll >= rr)
			break;
		swap(*ll, *rr);
	}

	if (!(bit & *ll) && ll<to)
		ll++;
	bit >>= 1;

	u_radsort(from, ll, bit); 
	u_radsort(ll, to, bit); 
}

/* signed int sort: flip highest bit, sort as unsigned, flip back */
static void radixsort(int *a, const size_t len)
{
	size_t i;
	uint *x = (uint *)a;

	each(i, len)
		x[i] ^= INT_MIN;
	u_radsort(x, x+len, INT_MIN);
	each(i, len)
		x[i] ^= INT_MIN;
}

static inline void uradixsort(int *a, const size_t len)
{
	u_radsort(a, a+len, (uint)INT_MIN);
}

int main(void)
{
	int len = 16, x[16], i;
	//size_t len = 16, i;
	each(i, len)
		x[i] = rand() % 512 - 256;

	radixsort(x, len);

	each(i, len)
		printf("%d%c", x[i], i+1<len ? ' ' : '\n');

	return 0;
}

