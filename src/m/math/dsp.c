//Free Algos.

//Updated 9/15/16.

//ISC LICENSE INFORMATION
/*
ISC License

Copyright (c) 2016, Mehdy Faik

Permission to use, copy, modify, and/or 
distribute this software for any purpose
with or without fee is hereby granted, 
provided that the above copyright notice 
and this permission notice appear in 
all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND 
THE AUTHOR DISCLAIMS ALL WARRANTIES 
WITH REGARD TO THIS SOFTWARE INCLUDING 
ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS. IN NO EVENT SHALL THE 
AUTHOR BE LIABLE FOR ANY SPECIAL, 
DIRECT, INDIRECT, OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER 
RESULTING FROM LOSS OF USE, DATA OR 
PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
NEGLIGENCE OR OTHER TORTIOUS ACTION, 
ARISING OUT OF OR IN CONNECTION WITH 
THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

//Contact:
/*
Check out my YouTube Channel at:
https://www.youtube.com/channel/UCu_ejE9qAdwHFJxRSUpGNcA

PM me at username hustling_drywall on Reddit.
*/

//Quick note on digital frequency (aka radian frequency)
/*
	//Digital frequency, in radians (w, or lower case omega, equals (2*pi*f) / fs, where:
		//f is the frequency of the tone in Hz, and
		//fs is the rate at which the tone was sampled (sample rate).
	//0.2*M_PI == 2*pi*f / 8000.0 ==> f == 800 Hz.
	//0.3*M_PI == 2*pi*f / 8000.0 ==> f == 1200 Hz.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Objects and constructors.
typedef struct cpx { //Complex number.
	double real;
	double imag;
} cpx_t;
typedef struct vec { //Vector of double values.
	double* arr;
	int len;
} vec_t;
typedef struct vec_list {
	vec_t* arr;
	int len;
} vec_list_t;
typedef struct int_vec {
	int* arr;
	int len;
} int_vec_t;
typedef struct vec_cpx { //Vector of complex numbers.
	cpx_t* arr;
	int len;
} vec_cpx_t;

cpx_t new_cpx_t(double mag, double phase) {
	cpx_t z;
	z.real = mag*cos(phase);
	z.imag = mag*sin(phase);
	return z;
}
vec_t new_vec_t(int length) {
	vec_t xn;
	xn.len = length;
	xn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	return xn;
}
int_vec_t new_int_vec_t(int length) {
	int_vec_t xn;
	xn.len = length;
	xn.arr = (int*)malloc(sizeof(int)*xn.len);
	
	return xn;
}
vec_cpx_t new_vec_cpx_t(int length) {
	vec_cpx_t xn;
	xn.len = length;
	xn.arr = (cpx_t*)malloc(sizeof(cpx_t)*xn.len);
	
	return xn;
}

vec_list_t new_vec_list_t(int num_vecs, int vec_length) {
	
	vec_list_t list;
	list.len = num_vecs;
	list.arr = (vec_t*)malloc(sizeof(vec_t) * list.len);
	
	int n = 0;
	for (n = 0; n < list.len; n++)
		list.arr[n] = new_vec_t(vec_length);
	
	return list;
}

//Complex number operations.
cpx_t cpx_scale(cpx_t a, double c) { //Multiply a complex number by a scalor.
	a.real *= c;
	a.imag *= c;
	return a;
}
vec_cpx_t vec_cpx_scale(vec_cpx_t xn, double c) { //Multiply a vector of complex numbers by a scalor.
	int n = 0;
	for (n = 0; n < xn.len; n++)
		xn.arr[n] = cpx_scale(xn.arr[n], c);
	return xn;
}

cpx_t cpx_add(cpx_t a, cpx_t b) { //Returns a + b.
	cpx_t z;
	z.real = a.real + b.real;
	z.imag = a.imag + b.imag;
	return z;
}
cpx_t cpx_sub(cpx_t a, cpx_t b) { //Returns a - b.
	cpx_t z;
	z.real = a.real - b.real;
	z.imag = a.imag - b.imag;
	return z;
}
cpx_t cpx_mul(cpx_t a, cpx_t b) { //Returns a * b.
	cpx_t z;
	z.real = a.real*b.real - a.imag*b.imag;
	z.imag = b.imag*a.real + a.imag*b.real;
	return z;
}
cpx_t cpx_div(cpx_t a, cpx_t b) { //Returns a / b.
	cpx_t z;
	z.real = a.real * b.real + a.imag * b.imag;
	z.imag = -b.imag * a.real + a.imag * b.real;
	z = cpx_scale(z, 1.0 / (b.real * b.real + b.imag * b.imag));
	return z;
}
cpx_t cpx_recip(cpx_t a) { //Returns 1 / a.
	cpx_t z;
	z.real = a.real / (a.real * a.real + a.imag * a.imag);
	z.imag = -a.imag / (a.real * a.real + a.imag * a.imag);
	return z;
}
cpx_t cpx_conj(cpx_t a) {
	cpx_t z;
	z.real = a.real;
	z.imag = -a.imag;
	return z;
}
double mag_cpx(cpx_t a) { //Find the magnitude of a complex number.
	return sqrt(a.real*a.real + a.imag*a.imag);
}
double mag2_cpx(cpx_t a) {
	return a.real*a.real + a.imag*a.imag;
}
double phase_cpx(cpx_t a) { //Find the phase of a complex number.
	
	//Handle zero exceptions.
	if ((a.real == 0) && (a.imag == 0))
		return 0;
	else if (a.real == 0)
		if (a.imag > 0)
			return M_PI / 2.0;
		else if (a.imag < 0)
			return 3.0 * M_PI / 2.0;
	else if (a.imag == 0)
		if (a.real > 0)
			return 0;
		else if (a.real < 0)
			return M_PI;
	
	//Handles normal numbers for any quadrant.
	if ((a.real > 0) && (a.imag > 0)) { //quadrant 1
		return atan(a.imag / a.real);
	}
	if ((a.real < 0) && (a.imag > 0)) { //quadrant 2
		return atan(a.imag / a.real) + M_PI;
	}
	if ((a.real < 0) && (a.imag < 0)) { //quadrant 3
		return atan(a.imag / a.real) + M_PI;
	}
	if ((a.real > 0) && (a.imag < 0)) { //quadrant 4
		return atan(a.imag / a.real) + 2.0 * M_PI;
	}
}

vec_cpx_t cpx_cast_vec(vec_t xn) { //Store a vector of double values as the real components to a vector of complex numbers.
	vec_cpx_t xn_cpx;
	xn_cpx.len = xn.len;
	xn_cpx.arr = (cpx_t*)malloc(sizeof(cpx_t)*xn_cpx.len);
	
	int n = 0;
	for (n = 0; n < xn_cpx.len; n++) {
		xn_cpx.arr[n].real = xn.arr[n];
		xn_cpx.arr[n].imag = 0;
	}
	return xn_cpx;
}

//Simple vector operations.
void print_vec(vec_t v) { //Print all terms of a vector of doubles.
	int i = 0;
	for (i = 0; i < v.len; i++)
		printf("%lf, ", v.arr[i]);
	//printf("\r\n");
}
void print_int_vec(int_vec_t v) {
	int i = 0;
	for (i = 0; i < v.len; i++)
		printf("%d, ", v.arr[i]);
	//printf("\r\n");
}
void print_cpx_vec(vec_cpx_t xn) { //Print all terms of a vector of complex nums.
	int n = 0;
	for (n = 0; n < xn.len; n++)
		printf("%d, %lf, %lf, %lf, %lf\r\n", n, xn.arr[n].real, xn.arr[n].imag, mag_cpx(xn.arr[n]), phase_cpx(xn.arr[n]));
}

void copy_vec(vec_t src, vec_t dst) { //Copy a vector of double values from src to dst.
	int n = 0;
	for (n = 0; n < src.len; n++)
		dst.arr[n] = src.arr[n];
}
void copy_cpx_vec(vec_cpx_t src, vec_cpx_t dst) { //Copy a vector of complex values from src to dst.
	int n = 0;
	for (n = 0; n < src.len; n++)
		dst.arr[n] = src.arr[n];
}

void clear_vec(vec_t vec) { //Set all double values in a vector to zero.
	int n = 0;
	for (n = 0; n < vec.len; n++)
		vec.arr[n] = 0;
}
void clear_cpx_vec(vec_cpx_t vec) { //Set all complex values in a vector to zero.
	int n = 0;
	for (n = 0; n < vec.len; n++) {
		vec.arr[n].real = 0;
		vec.arr[n].imag = 0;
	}
}

//Indexing vector operations.
int min(vec_t xn, int start_ind, int end_ind) { //Find index of min value in vector of doubles.
	//Searches for n == [start_ind, end_ind].
	//Returns index of minimum.
	
	int n = 0;
	double min = 10000000000000000.0;
	int min_ind = -1;
	for (n = start_ind; n <= end_ind; n++) {
		if (xn.arr[n] < min) {
			min = xn.arr[n];
			min_ind = n;
		}
	}
	return min_ind;
}
int max(vec_t xn, int start_ind, int end_ind) { //Find index of max value in vector of doubles.
	//Searches for n == [start_ind, end_ind].
	//Returns index of maximum.
	
	int n = 0;
	double max = -10000000000000000.0;
	int max_ind = -1;
	for (n = start_ind; n <= end_ind; n++) {
		if (xn.arr[n] > max) {
			max = xn.arr[n];
			max_ind = n;
		}
	}
	return max_ind;
}

void insert_intra_vec(vec_t xn, int src_ind, int dst_ind) { //Pull out xn[src_ind] and shift terms around so you can put it in the place of xn[dst_ind].
	int n = 0;
	int temp = xn.arr[src_ind];
	
	//Shift everything right.
	if (src_ind > dst_ind) {
		for (n = src_ind; n >= dst_ind + 1; n--)
			xn.arr[n] = xn.arr[n - 1];
		xn.arr[dst_ind] = temp;
	}
	//Shift everything left.
	else if (src_ind < dst_ind) {
		for (n = src_ind; n < dst_ind; n++)
			xn.arr[n] = xn.arr[n + 1];
		xn.arr[dst_ind] = temp;
	}
	
	//Test to insert xn[a] into xn[b].
		//xn[a] => temp.
		//From k == a, say that xn[k] = xn[k - 1], k--, until k == b + 1.
		//xn[b] = temp.
	
	//Test to insert xn[a] into xn[b].
		//xn[a] => temp.
		//From k == a, say that xn[k] = xn[k + 1], k++, until k == b.
		//xn[b] = temp.
}
void swap_intra_vec(vec_t xn, int n1, int n2) { //xn[n1] gets the value at xn[n2] and xn[n2] gets the value at xn[n1].
	double temp = xn.arr[n1];
	xn.arr[n1] = xn.arr[n2];
	xn.arr[n2] = temp;
}

int num_equiv(int_vec_t x1, int_vec_t x2) {
	//Return the amount of indices where x1[n] equals x2[n].
	if (x1.len != x2.len)
		return 0;
	
	int n = 0;
	int num_equiv = 0;
	for (n = 0; n < x1.len; n++) {
		if (x1.arr[n] == x2.arr[n])
			num_equiv++;
	}
	return num_equiv;
}

vec_cpx_t zeropad(vec_cpx_t vec, int new_length) {
	int n = 0;
	
	vec_cpx_t cpx_vec_out;
	cpx_vec_out.len = new_length;
	cpx_vec_out.arr = (cpx_t*)malloc(sizeof(cpx_t)*cpx_vec_out.len);
	
	if (new_length < vec.len)
		printf("Error in function pad_to_length: input length must be greater than vec current length");
	else {
		for (n = 0; n < vec.len; n++) {
			cpx_vec_out.arr[n].real = vec.arr[n].real;
			cpx_vec_out.arr[n].imag = vec.arr[n].imag;
		}
		for (n = vec.len; n < cpx_vec_out.len; n++) {
			cpx_vec_out.arr[n].real = 0;
			cpx_vec_out.arr[n].imag = 0;
		}
	}
	
	return cpx_vec_out;
}

//Math vector operations.
void vec_flip_sign(vec_t vec) {
	int n = 0;
	for (n = 0; n < vec.len; n++)
		vec.arr[n] *= -1.0;
}
double norm_vec(vec_t vec) {
	int n = 0;
	double norm = 0;
	for (n = 0; n < vec.len; n++)
		norm += vec.arr[n] * vec.arr[n];
	return sqrt(norm);
}

//Term by term vector operations.
vec_t termbyterm_add(vec_t x1n, vec_t x2n) {
	if (x1n.len != x2n.len) {
		printf("Error in termbyterm_add. Vectors inequal in length.\r\n");
		return;
	}
	
	int n = 0;
	vec_t yn;
	yn.len = x1n.len;
	yn.arr = (double*)malloc(sizeof(double)*yn.len);
	
	for (n = 0; n < yn.len; n++)
		yn.arr[n] = x1n.arr[n] + x2n.arr[n];
	
	return yn;
}
vec_t termbyterm_mul(vec_t x1n, vec_t x2n) {
	if (x1n.len != x2n.len) {
		printf("Error in termbyterm_mul. Vectors inequal in length.\r\n");
		return;
	}
	
	int n = 0;
	vec_t yn;
	yn.len = x1n.len;
	yn.arr = (double*)malloc(sizeof(double)*yn.len);
	
	for (n = 0; n < yn.len; n++)
		yn.arr[n] = x1n.arr[n] * x2n.arr[n];
	
	return yn;
}
vec_t termbyterm_sub(vec_t x1n, vec_t x2n) {
	if (x1n.len != x2n.len) {
		printf("Error in termbyterm_sub. Vectors inequal in length.\r\n");
		return;
	}
	
	int n = 0;
	vec_t yn;
	yn.len = x1n.len;
	yn.arr = (double*)malloc(sizeof(double)*yn.len);
	
	for (n = 0; n < yn.len; n++)
		yn.arr[n] = x1n.arr[n] - x2n.arr[n];
	
	return yn;
}
vec_t termbyterm_div(vec_t x1n, vec_t x2n) {
	if (x1n.len != x2n.len) {
		printf("Error in termbyterm_div. Vectors inequal in length.\r\n");
		return;
	}
	
	int n = 0;
	vec_t yn;
	yn.len = x1n.len;
	yn.arr = (double*)malloc(sizeof(double)*yn.len);
	
	for (n = 0; n < yn.len; n++)
		yn.arr[n] = x1n.arr[n] / x2n.arr[n];
	
	return yn;
}

//DSP operations.
vec_t conv(vec_t xn, vec_t hn) { //Convolve xn with hn. Output is same length as longest of xn and hn.
	int n = 0;
	int m = 0;
	
	vec_t rn;
	rn.len = xn.len;
	rn.arr = (double*)malloc(sizeof(double)*rn.len);
	
	for (n = 0; n < rn.len; n++) {
		for (m = 0; m < hn.len; m++) {
			if (n - m < 0)
				continue;
			rn.arr[n] += xn.arr[n - m] * hn.arr[m];
		}
	}
	return rn;
}
vec_t corr(vec_t xn, vec_t hn) { //Correlate xn with hn. Output is same length as longest of xn and hn.
	int n = 0;
	int m = 0;
	
	vec_t rn;
	rn.len = xn.len;
	rn.arr = (double*)malloc(sizeof(double)*rn.len);
	
	for (n = 0; n < rn.len; n++) {
		for (m = 0; m < hn.len; m++) {
			if ((n + m) >= rn.len)
				break;
			rn.arr[n] += xn.arr[n + m] * hn.arr[m];
		}
	}
	
	return rn;
}
vec_t conv_full_length(vec_t xn, vec_t hn) {
	int n = 0;
	int m = 0;
	
	vec_t rn;
	rn.len = xn.len + hn.len - 1;
	rn.arr = (double*)malloc(sizeof(double)*rn.len);
	
	for (n = 0; n < rn.len; n++) {
		for (m = 0; m < hn.len; m++) {
			if (n - m < 0)
				continue;
			if (n - m > xn.len - 1)
				continue;
			rn.arr[n] += xn.arr[n - m] * hn.arr[m];
		}
	}
	return rn;
}

vec_cpx_t fft(vec_cpx_t xn) { //Computes radix-2 Fast Fourier Transform of complex vector array.
	int n = 0;
	
	vec_cpx_t Xk;
	Xk.len = xn.len;
	Xk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Xk.len);
	
	vec_cpx_t Xkbuf;
	Xkbuf.len = xn.len;
	Xkbuf.arr = (cpx_t*)malloc(sizeof(cpx_t)*Xk.len);
	
	for (n = 0; n < Xk.len; n++) {
		Xk.arr[n].real = 0;
		Xk.arr[n].imag = 0;
		Xkbuf.arr[n].real = 0;
		Xkbuf.arr[n].imag = 0;
	}
	
	for (n = 0; n < (Xk.len >> 1); n++) {
		Xk.arr[n] = cpx_add(xn.arr[n], xn.arr[n + (xn.len >> 1)]);
		Xk.arr[n + (Xk.len >> 1)] = cpx_sub(xn.arr[n], xn.arr[n + (xn.len >> 1)]);
	}
	
	int depth = (int)(log10((double)Xk.len) / log10(2.0)) - 1;
	int y_int = 0;
	int gap = Xk.len >> 1;
	int inst_N = 4;
	int m = 0;
	cpx_t tw; tw.real = 0; tw.imag = 0;
		int tw_m = 0;
		double tw_p = 0;
	
	//printf("%d, %d, %d, %d, %d\r\n", depth, y_int, gap, inst_N, m);
	
	while (depth > 0) {
		//printf("Depth is %d\r\n", depth);
		for (y_int = 0; y_int < (gap >> 1); y_int++) {
			for (m = 0; m < (inst_N >> 1); m++) {
				tw_p = -2.0 * M_PI * (double)(tw_m) / (double)(inst_N);
				tw.real = cos(tw_p);
				tw.imag = sin(tw_p);
				
				Xkbuf.arr[(gap >> 1) * m + y_int] = cpx_add(Xk.arr[gap * m + y_int], cpx_mul(tw, Xk.arr[gap * m + (gap >> 1) + y_int]));
				Xkbuf.arr[(gap >> 1) * m + y_int + (Xk.len >> 1)] = cpx_sub(Xk.arr[gap * m + y_int], cpx_mul(tw, Xk.arr[gap * m + (gap >> 1) + y_int]));
				
				//printf("Storing to: %d, %d\r\n", (gap>>1)*m+y_int, (gap>>1)*m+y_int+(Xk.len>>1));
				//printf("Reading from: %d, %d\r\n", gap*m+y_int, gap*m+(gap>>1)+y_int);
				//printf("%d / %d\r\n", tw_m, inst_N);
				
				tw_m++;
			} //printf("m loop done\r\n");
			tw_m = 0;
		} //printf("y_int loop done\r\n");
		
		copy_cpx_vec(Xkbuf, Xk);
		
		depth--;
		inst_N <<= 1;
		gap >>= 1;
	}
	
	vec_cpx_scale(Xk, 1.0 / (double)(Xk.len));
	return Xk;
}
vec_cpx_t ifft(vec_cpx_t Xk) { //Computes radix-2 Inverse Fast Fourier Transform of complex vector array.
	int n = 0;
	
	vec_cpx_t xn;
	xn.len = Xk.len;
	xn.arr = (cpx_t*)malloc(sizeof(cpx_t)*xn.len);
	
	vec_cpx_t xnbuf;
	xnbuf.len = Xk.len;
	xnbuf.arr = (cpx_t*)malloc(sizeof(cpx_t)*xn.len);
	
	for (n = 0; n < xn.len; n++) {
		xn.arr[n].real = 0;
		xn.arr[n].imag = 0;
		xnbuf.arr[n].real = 0;
		xnbuf.arr[n].imag = 0;
	}
	
	for (n = 0; n < (xn.len >> 1); n++) {
		xn.arr[n] = cpx_add(Xk.arr[n], Xk.arr[n + (Xk.len >> 1)]);
		xn.arr[n + (xn.len >> 1)] = cpx_sub(Xk.arr[n], Xk.arr[n + (Xk.len >> 1)]);
	}
	
	int depth = (int)(log10((double)xn.len) / log10(2.0)) - 1;
	int y_int = 0;
	int gap = xn.len >> 1;
	int inst_N = 4;
	int m = 0;
	cpx_t tw; tw.real = 0; tw.imag = 0;
		int tw_m = 0;
		double tw_p = 0;
	
	//printf("%d, %d, %d, %d, %d\r\n", depth, y_int, gap, inst_N, m);
	
	while (depth > 0) {
		//printf("Depth is %d\r\n", depth);
		for (y_int = 0; y_int < (gap >> 1); y_int++) {
			for (m = 0; m < (inst_N >> 1); m++) {
				tw_p = -2.0 * M_PI * (double)(tw_m) / (double)(inst_N);
				tw.real = cos(tw_p);
				tw.imag = sin(tw_p);
				
				xnbuf.arr[(gap >> 1) * m + y_int] = cpx_add(xn.arr[gap * m + y_int], cpx_mul(tw, xn.arr[gap * m + (gap >> 1) + y_int]));
				xnbuf.arr[(gap >> 1) * m + y_int + (xn.len >> 1)] = cpx_sub(xn.arr[gap * m + y_int], cpx_mul(tw, xn.arr[gap * m + (gap >> 1) + y_int]));
				
				//printf("Storing to: %d, %d\r\n", (gap>>1)*m+y_int, (gap>>1)*m+y_int+(xn.len>>1));
				//printf("Reading from: %d, %d\r\n", gap*m+y_int, gap*m+(gap>>1)+y_int);
				//printf("%d / %d\r\n", tw_m, inst_N);
				
				tw_m++;
			} //printf("m loop done\r\n");
			tw_m = 0;
		} //printf("y_int loop done\r\n");
		
		copy_cpx_vec(xnbuf, xn);
		
		depth--;
		inst_N <<= 1;
		gap >>= 1;
	}
	return xn;
}

//Sort.
void insertion_sort(vec_t xn) { //Insertion sort algorithm for arranging vector of double values in ascending order.
	int n = 0;
	int nc = 0;
	
	for (n = 1; n < xn.len; n++) {
		nc = n - 1;
		while (xn.arr[n] < xn.arr[nc])
			nc--;
		insert_intra_vec(xn, n, nc + 1);
		
		print_vec(xn);
	}
}
void selection_sort(vec_t xn) { //Selection sort algorithm for arranging vector of double values in ascending order.
	int n = 0;
	int sub_min_ind = 0;; //min of unsorted subarray
	for (n = 0; n < xn.len; n++) {
		sub_min_ind = min(xn, n, xn.len - 1);
		swap_intra_vec(xn, n, sub_min_ind);
		
		print_vec(xn);
	}
}

//Misc math.
int int_rand_given_bound(int lo, int hi) {
	
	double lo_d = (double)lo;
	double hi_d = (double)hi;
	
	//[lo, hi], endpoint-inclusive.
	//(rand() / (double)(RAND_MAX)) * (hi_d + 1.0 - lo_d) //-> returns [0, hi_d + 1.0 - lo_d)
	//(rand() / (double)(RAND_MAX)) * (hi_d + 1.0 - lo_d) + lo_d //-> returns [lo_d, hi_d + 1.0)
	return (int)((rand() / (double)(RAND_MAX)) * (hi_d + 1.0 - lo_d) + lo_d); //-> [lo, hi].
}
double rand_given_bound(double lo, double hi) {
	return (rand() / (double)RAND_MAX) * (hi - lo) + lo; //[lo, hi].
}

double sinc(double x) { //Return sin(x) / x; Returns 1 if x == 0. Zeros at integer multiples of pi.
	if (x == 0)
		return 1;
	else
		return sin(x) / x;
}
double sincpi(double x) { //Returns sin(pi * x) / (pi * x). Zeros at integers.
	return sinc(x * M_PI);
}

double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}
double sigmoid_prime(double x) {
	return (sigmoid(x) * (1.0 - sigmoid(x)));
}

int revolve_mod(int cur, int lim) {
	cur++;
	if (cur < lim)
		return cur;
	else
		cur = 0;
	return cur;
}

//Filter.
int pick_window(double stopband_gain) {
	double stopband_gain_dB = 20.0*log10(stopband_gain);
	//printf("stopband gain in dB: %lf\r\n", stopband_gain_dB);
	
	int which_window = -1;
	
	if (stopband_gain_dB > -21.0) //Rectangular.
		which_window = 0;
	else if (stopband_gain_dB > -44.0) //Hanning.
		which_window = 1;
	else if (stopband_gain_dB > -53.0) //Hamming.
		which_window = 2;
	else if (stopband_gain_dB > -74.0) //Blackman.
		which_window = 3;
	else { //Fail.
		printf("LPF generation failed.\r\nYou requested too much stopband attenuation.\r\n");
		printf("To fix this problem, increase the value you have for stopband_gain.\r\n");
		printf("A usual value is 0.01.\r\n");
	}
	return which_window;
}
vec_t generate_window(int which_window, int window_length) {
	int n = 0;
	
	vec_t Wn;
	Wn.len = window_length;
	Wn.arr = (double*)malloc(sizeof(double)*Wn.len);
	
	if (which_window == 0) { //Rectangular.
		for (n = 0; n < Wn.len; n++)
			Wn.arr[n] = 1.0;
	}
	else if (which_window == 1) { //Hanning.
		for (n = 0; n < Wn.len; n++)
			Wn.arr[n] = 0.5 * (1.0 - cos((2.0 * M_PI * (double)(n)) / (Wn.len - 1)));
	}
	else if (which_window == 2) { //Hamming.
		for (n = 0; n < Wn.len; n++)
			Wn.arr[n] = 0.54 - 0.46 * cos((2.0 * M_PI * (double)(n)) / (Wn.len - 1));
	}
	else if (which_window == 3) { //Blackman.
		for (n = 0; n < Wn.len; n++)
			Wn.arr[n] = 0.42 - 0.5 * cos((2.0 * M_PI * (double)(n)) / (Wn.len - 1)) + 0.08 * cos((4.0 * M_PI * (double)(n)) / (Wn.len - 1));
	}
	else
		clear_vec(Wn);
	return Wn;
}

int get_filter_length(double w_1, double w_2, double stopband_gain) { //Based on desired stopband gain, decide on filter length and window function.
	double stopband_gain_dB = 20.0*log10(stopband_gain);
	double dw = fabs(w_1 - w_2);
	int M = 0;
	
	if (stopband_gain_dB > -21.0) //Rectangular.
		M = (int)(4.0*M_PI / dw);
	else if (stopband_gain_dB > -44.0) //Hanning.
		M = (int)(8.0*M_PI / dw);
	else if (stopband_gain_dB > -53.0) //Hamming.
		M = (int)(8.0*M_PI / dw);
	else if (stopband_gain_dB > -74.0) //Blackman.
		M = (int)(12.0*M_PI / dw);
	else { //Fail.
		printf("LPF generation failed.\r\nYou requested too much stopband attenuation.\r\n");
		printf("To fix this problem, increase the value you have for stopband_gain.\r\n");
		printf("A usual value is 0.01.\r\n");
		return 0;
	}
	if ((M % 2) == 0) //Filter length odd.
		M++;
	
	return M;
}
vec_t generate_lowpass_impulse_response(int filter_length, double wc) {
	if ((filter_length % 2) == 0) //Filter length odd.
		filter_length++;
	
	int n = 0;
	double wc_div_pi = wc / M_PI;
	
	vec_t hn;
	hn.len = filter_length;
	hn.arr = (double*)malloc(sizeof(double)*hn.len);
	
	for (n = 0; n < hn.len; n++)
		hn.arr[n] = wc_div_pi * sinc(wc * (double)(n - ((hn.len - 1) / 2)));
	
	return hn;
}
vec_t generate_highpass_impulse_response(int filter_length, double wc) {
	if ((filter_length % 2) == 0)
		filter_length++;
	
	int n = 0;
	double wc_div_pi = wc / M_PI;
	
	vec_t hn;
	hn.len = filter_length;
	hn.arr = (double*)malloc(sizeof(double)*hn.len);
	
	for (n = 0; n < hn.len; n++)
		hn.arr[n] = -wc_div_pi * sinc(wc * (double)(n - ((hn.len - 1) / 2)));
	
	hn.arr[(hn.len - 1) / 2] += 1.0;
	
	return hn;
}

//wL_1: LOW frequency side - Boundary 1 for transition band
//wL_2: LOW frequency side - Boundary 2 for transition band
//wH_1: HIGH frequency side - Boundary 1 for transition band
//wH_2: HIGH frequency side - Boundary 2 for transition band
vec_t generate_lowpass_filter(double wL_1, double wL_2, double stopband_gain) { //Generate impulse response for windowed lowpass filter.
	double wc = (wL_1 + wL_2) / 2.0;
	
	vec_t hn = generate_lowpass_impulse_response(get_filter_length(wL_1, wL_2, stopband_gain), wc);
	vec_t Wn = generate_window(pick_window(stopband_gain), hn.len);
	
	hn = termbyterm_mul(hn, Wn);
	
	return hn;
}
vec_t generate_highpass_filter(double wH_1, double wH_2, double stopband_gain) {
	double wc = (wH_1 + wH_2) / 2.0;
	
	vec_t hn = generate_highpass_impulse_response(get_filter_length(wH_1, wH_2, stopband_gain), wc);
	vec_t Wn = generate_window(pick_window(stopband_gain), hn.len);
	
	hn = termbyterm_mul(hn, Wn);
	
	return hn;
}
vec_t generate_bandstop_filter(double wL_1, double wL_2, double wH_1, double wH_2, double stopband_gain) {
	vec_t hnL = generate_lowpass_filter(wL_1, wL_2, stopband_gain);
	vec_t hnH = generate_highpass_filter(wH_1, wH_2, stopband_gain);
	vec_t hn = termbyterm_add(hnL, hnH);
	
	return hn;
}
vec_t generate_bandpass_filter(double wL_1, double wL_2, double wH_1, double wH_2, double stopband_gain) {
	vec_t hnL = generate_lowpass_filter(wL_1, wL_2, stopband_gain);
	vec_t hnH = generate_highpass_filter(wH_1, wH_2, stopband_gain);
	vec_t hn = termbyterm_add(hnL, hnH);
	
	vec_flip_sign(hn);
	hn.arr[(hn.len - 1) / 2] += 1.0;
	
	return hn;
}

//ANN.
typedef struct node {
	double output;
	
	vec_t weight;
	vec_t prev_dw;
	double bias;
	double prev_db;
	
	double error;
} node_t;
typedef struct layer {
	node_t* arr_nodes;
	int num_nodes;
} layer_t;
typedef struct ann {
	layer_t* arr_layers;
	int num_layers;
	
	double learning_rate;
	double momentum_factor;
} ann_t;

//Create and initialize.
//None of these functions initialize hyperparameters.
//Don't forget to initialize em.
ann_t new_ann_t(int_vec_t nodes_per_layer) {
	ann_t ann;
	
	//Make ANN out of layers.
	ann.num_layers = nodes_per_layer.len;
	ann.arr_layers = (layer_t*)malloc(sizeof(layer_t) * ann.num_layers);
	
	int l = 0;
	int n = 0;
	
	//Make layers out of nodes.
	for (l = 0; l < ann.num_layers; l++) {
		ann.arr_layers[l].num_nodes = nodes_per_layer.arr[l];
		ann.arr_layers[l].arr_nodes = (node_t*)malloc(sizeof(node_t) * ann.arr_layers[l].num_nodes);
	}
	
	//Make nodes out of weight vectors. Ignore input layer, which is passive.
	for (l = 1; l < ann.num_layers; l++) {
		for (n = 0; n < ann.arr_layers[l].num_nodes; n++) {
			ann.arr_layers[l].arr_nodes[n].weight = new_vec_t(nodes_per_layer.arr[l - 1]);
			ann.arr_layers[l].arr_nodes[n].prev_dw = new_vec_t(nodes_per_layer.arr[l - 1]);
		}
	}
	
	return ann;
}
void init_weights_and_biases_ann(ann_t ann) {
	int l = 0;
	int n = 0;
	int w = 0;
	
	for (l = 1; l < ann.num_layers; l++) { //For each layer.
		for (n = 0; n < ann.arr_layers[l].num_nodes; n++) { //For each node.
			for (w = 0; w < ann.arr_layers[l].arr_nodes[n].weight.len; w++) { //For each weight and bias.
				ann.arr_layers[l].arr_nodes[n].weight.arr[w] = rand_given_bound(-0.5, 0.5);
				ann.arr_layers[l].arr_nodes[n].prev_dw.arr[w] = 0;
			}
			ann.arr_layers[l].arr_nodes[n].bias = rand_given_bound(-0.5, 0.5);
			ann.arr_layers[l].arr_nodes[n].prev_db = 0;
		}
	}
}

//Operate.
void feed_forward_ann(ann_t ann) {
	int l = 0;
	int n = 0;
	int w = 0;
	
	for (l = 1; l < ann.num_layers; l++) { //For each layer.
		for (n = 0; n < ann.arr_layers[l].num_nodes; n++) { //For each node in that layer.
			for (w = 0; w < ann.arr_layers[l].arr_nodes[n].weight.len; w++) { //For each weight in that node.
				ann.arr_layers[l].arr_nodes[n].output += ann.arr_layers[l].arr_nodes[n].weight.arr[w] * ann.arr_layers[l - 1].arr_nodes[w].output;
				//printf("Layer %d, Node %d += Weight %d * Output from Layer %d, Node %d.\r\n", l, n, w, l - 1, w);
				//printf("Intermediate output: %lf\r\n\r\n", ann.arr_layers[l].arr_nodes[n].output);
			}
			ann.arr_layers[l].arr_nodes[n].output += ann.arr_layers[l].arr_nodes[n].bias;
			//printf("Add on %lf bias for final output for Layer %d, Node %d: %lf\r\n", ann.arr_layers[l].arr_nodes[n].bias, l, n, ann.arr_layers[l].arr_nodes[n].output);
			//printf("\r\n****Done with Node %d****\r\n\r\n", n);
			ann.arr_layers[l].arr_nodes[n].output = sigmoid(ann.arr_layers[l].arr_nodes[n].output);
		}
		//printf("\r\n\r\n****Done with Layer %d****\r\n\r\n", l);
	}
}
int backpropagate_adjust(ann_t ann, vec_t targets) {
	//Output layer.
	int l = 0; //Iterating over layers of a net.
	
	int n = 0; //Iterating over nodes of a layer
	int w = 0; //Iterating over weights of a node.
	int k = 0; //Iterating over nodes to find a backpropagated error.
	
	int l_output = ann.num_layers - 1; //index of output layer.
	
	double delta = 0; //Final adjustment amount.
	
	//Adjust output nodes.
	if (targets.len != ann.arr_layers[l_output].num_nodes) //# targets == # output nodes.
		return 0;
	for (n = 0; n < ann.arr_layers[l_output].num_nodes; n++) { //For each output node.
	
		ann.arr_layers[l_output].arr_nodes[n].error = targets.arr[n] - ann.arr_layers[l_output].arr_nodes[n].output; //Error is target - output.
		
		for (w = 0; w < ann.arr_layers[l_output].arr_nodes[n].weight.len; w++) { //For each weight of that output node.
			
			delta = ann.learning_rate * ann.arr_layers[l_output].arr_nodes[n].error * ann.arr_layers[l_output - 1].arr_nodes[w].output; //dC/dw is error*activation on this weight.
			delta += ann.momentum_factor * ann.arr_layers[l_output].arr_nodes[n].prev_dw.arr[w]; //Add the momentum factor
			
			ann.arr_layers[l_output].arr_nodes[n].weight.arr[w] += delta; //Adjust weight.
			ann.arr_layers[l_output].arr_nodes[n].prev_dw.arr[w] = delta; //Store weight change.
		}
		
		delta = ann.learning_rate * ann.arr_layers[l_output].arr_nodes[n].error; //dC/db is error.
		delta += ann.momentum_factor * ann.arr_layers[l_output].arr_nodes[n].prev_db; //Add the momentum factor.
		ann.arr_layers[l_output].arr_nodes[n].bias += delta; //Adjust bias.
		ann.arr_layers[l_output].arr_nodes[n].prev_db = delta; //Store bias change.
	}
	
	//Adjust hidden nodes.
	for (l = l_output - 1; l > 0; l--) {
		for (n = 0; n < ann.arr_layers[l].num_nodes; n++) { //For each node in this layer.
			
			//Find the error for that node.
			for (k = 0; k < ann.arr_layers[l + 1].num_nodes; k++) //Take every node in the layer l + 1. Error times weight plus error times weight plus...
				ann.arr_layers[l].arr_nodes[n].error += ann.arr_layers[l + 1].arr_nodes[k].error * ann.arr_layers[l + 1].arr_nodes[k].weight.arr[n];
			ann.arr_layers[l].arr_nodes[n].error *= ann.arr_layers[l].arr_nodes[n].output * (1.0 - ann.arr_layers[l].arr_nodes[n].output);
			
			//Adjust that node's weights.
			for (w = 0; w < ann.arr_layers[l].arr_nodes[n].weight.len; w++) {
				delta = ann.learning_rate * ann.arr_layers[l].arr_nodes[n].error * ann.arr_layers[l - 1].arr_nodes[w].output;
				delta += ann.momentum_factor * ann.arr_layers[l].arr_nodes[n].prev_dw.arr[w];
				ann.arr_layers[l].arr_nodes[n].weight.arr[w] += delta;
				ann.arr_layers[l].arr_nodes[n].prev_dw.arr[w] = delta;
			}
			delta = ann.learning_rate * ann.arr_layers[l].arr_nodes[n].error;
			delta += ann.momentum_factor * ann.arr_layers[l].arr_nodes[n].prev_db;
			ann.arr_layers[l].arr_nodes[n].bias += delta;
			ann.arr_layers[l].arr_nodes[n].prev_db = delta;
		}
	}
	return 1;
}

//Aux operation functions.
int preload_layer_outputs(ann_t ann, vec_t src, int l_dst) {
	if (src.len != ann.arr_layers[l_dst].num_nodes) {
		printf("Load input fail\r\n");
		return 0;
	}
	
	int n = 0;
	for (n = 0; n < ann.arr_layers[l_dst].num_nodes; n++)
		ann.arr_layers[l_dst].arr_nodes[n].output = src.arr[n];
	return 1;
}
vec_list_t create_targets(int num_cases) {
	
	//Simplest setup: Exactly one output node on.
		//In this case, num cases == num output nodes.
		
	int ind_case = 0;
	int ind_node = 0;
	vec_list_t target_vecs = new_vec_list_t(num_cases, num_cases);
	
	for (ind_case = 0; ind_case < num_cases; ind_case++) {
		for (ind_node = 0; ind_node < num_cases; ind_node++) {
			if (ind_case == ind_node)
				target_vecs.arr[ind_case].arr[ind_node] = 1;
			else
				target_vecs.arr[ind_case].arr[ind_node] = 0;
		}
	}
	return target_vecs;
}
int load_weight_to_node(ann_t ann, int l_dst, int n_dst, vec_t weight_src, double bias_src) {
	if (weight_src.len != ann.arr_layers[l_dst].arr_nodes[n_dst].weight.len) {
		printf("Load weight fail\r\n");
		return 0;
	}
	int w = 0;
	for (w = 0; w < weight_src.len; w++)
		ann.arr_layers[l_dst].arr_nodes[n_dst].weight.arr[w] = weight_src.arr[w];
	ann.arr_layers[l_dst].arr_nodes[n_dst].bias = bias_src;
	
	return 1;
}

//Evaluate performance.
int max_output_node_ind(ann_t ann) {
	//Finds the node index, (in the output layer) that holds the max value.
	
	int n = 0;
	int l_output = ann.num_layers - 1;
	double max_output = -1.0;
	int n_max = -1;
	for (n = 0; n < ann.arr_layers[l_output].num_nodes; n++) {
		if (ann.arr_layers[l_output].arr_nodes[n].output > max_output) {
			max_output = ann.arr_layers[l_output].arr_nodes[n].output;
			n_max = n;
		}
	}
	return n_max;
}
int test_and_score(ann_t ann, vec_list_t test_list, int_vec_t answer_key, int_vec_t* answer_ann) {
	
	*answer_ann = new_int_vec_t(test_list.len);
	int ind_vec = 0;
	
	for (ind_vec = 0; ind_vec < test_list.len; ind_vec++) {
		preload_layer_outputs(ann, test_list.arr[ind_vec], 0);
		feed_forward_ann(ann);
		(*answer_ann).arr[ind_vec] = max_output_node_ind(ann);
	}
	
	return num_equiv(answer_key, *answer_ann);
}

//Misc.
void print_ann(ann_t ann) { //Print every weight and bias, of every node, of every layer, of the net.
	int l = 0;
	int n = 0;
	int w = 0;
	
	for (n = 0; n < ann.arr_layers[l].num_nodes; n++) {
		printf("NODE %d.\r\n", n);
		printf("Output %lf\r\n", ann.arr_layers[l].arr_nodes[n].output);
	} printf("\r\n\r\n");
	
	for (l = 1; l < ann.num_layers; l++) {
		printf("LAYER %d.\r\n", l);
		for (n = 0; n < ann.arr_layers[l].num_nodes; n++) {
			printf("NODE %d.\r\n", n);
			for (w = 0; w < ann.arr_layers[l].arr_nodes[n].weight.len; w++)
				printf("%lf\r\n", ann.arr_layers[l].arr_nodes[n].weight.arr[w]);
			printf("Bias: %lf\r\n\r\n", ann.arr_layers[l].arr_nodes[n].bias);
		}
		printf("\r\n\r\n");
	}
}

//Debug.
void init_vec(vec_t vec, int option) { //Dummy function for filling out test vectors.
	int n = 0;
	int f = 0;
		double ff = 0;
		
	if (option == 0) {
		vec.arr[0] = 0;
		vec.arr[1] = 0;
		vec.arr[2] = 1;
		vec.arr[3] = 1;
		vec.arr[4] = 1;
		vec.arr[5] = -1;
		vec.arr[6] = -1;
		vec.arr[7] = 1;
		vec.arr[8] = -1;
		vec.arr[9] = 0;
	}
	else if (option == 1) {
		vec.arr[0] = 1;
		vec.arr[1] = 1;
		vec.arr[2] = 1;
		vec.arr[3] = -1;
		vec.arr[4] = -1;
		vec.arr[5] = 1;
		vec.arr[6] = -1;
	}
	else if (option == 2) {
		vec.arr[0] = 5;
		vec.arr[1] = 4;
		vec.arr[2] = 9;
		vec.arr[3] = 3;
		vec.arr[4] = 7;
		vec.arr[5] = 6;
		vec.arr[6] = 1;
		vec.arr[7] = 0;
		vec.arr[8] = 2;
		vec.arr[9] = 8;
	}
	else if (option == 3) {
		for (n = 0; n < vec.len; n++) {
			for (f = 0; f < 512; f++) {
				ff = (double)(f) * (8000.0 / 512.0);
				vec.arr[n] += cos(2.0 * M_PI * ff * (double)(n) / 8000.0);
			}
		}
	}
}

void main() {
	//Correlation testing.
	/*
	//Initialize.
	vec_t xn;
	xn.len = 10;
	xn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	vec_t hn;
	hn.len = 7;
	hn.arr = (double*)malloc(sizeof(double)*hn.len);
	
	vec_t rn;
	
	init_vec(xn, 0);
	init_vec(hn, 1);
	
	//Execute.
	rn = corr(xn, hn);
	
	//Display.
	printf("\r\nInput signal, xn:\r\n");
	print_vec(xn);
	printf("\r\nImpulse response, hn:\r\n");
	print_vec(hn);
	printf("\r\nOutput vector, rn:\r\n");
	print_vec(rn);
	*/
	
	//Convolve full length testing.
	/*
	//Declare.
	vec_t xn;
	xn.len = 5;
	xn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	vec_t hn;
	hn.len = 3;
	hn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	//Initialize.
	int n = 0;
	for (n = 0; n < xn.len; n++)
		xn.arr[n] = 1;
	for (n = 0; n < hn.len; n++)
		hn.arr[n] = 1.0 / (double)(hn.len);
	
	//Test.
	vec_t yn1 = conv(xn, hn);
	vec_t yn2 = conv_full_length(xn, hn);
	
	//Show.
	print_vec(yn1);
	print_vec(yn2);
	*/

	//FFT testing.
	/*
	//Initialize.
	vec_cpx_t xn;
	xn.len = 16;
	int n = 0;
	for (n = 0; n < xn.len; n++) {
		xn.arr[n].real = 4.7 + 3.2*cos(0.5*M_PI*(double)(n)) + 10.0*cos(0.375*M_PI*(double)(n));
		xn.arr[n].imag = 0;
	}
	
	printf("Start\r\n");
	print_cpx_vec(xn);
	vec_cpx_t Xk;
	
	//Execute.
	Xk = fft(xn);
	xn = ifft(Xk);
	
	//Output.
	printf("FFT output:\r\n");
	print_cpx_vec(Xk);
	
	printf("\r\nIFFT output:\r\n");
	print_cpx_vec(xn);
	*/

	//Insert intra vec testing.
	/*
	int n = 0;
	vec_t xn;
	xn.len = 10;
	for (n = 0; n < xn.len; n++)
		xn.arr[n] = (double)(n);
	
	print_vec(xn);
	insert_intra_vec(xn, 2, 8);
	print_vec(xn);
	*/
	
	//Swap intra vec testing.
	/*
	int n = 0;
	vec_t xn;
	xn.len = 10;
	for (n = 0; n < xn.len; n++)
		xn.arr[n] = (double)(n);
	
	print_vec(xn);
	swap_intra_vec(xn, 2, 8);
	print_vec(xn);
	*/
	
	//Insertion sort testing.
	/*
	int n = 0;
	
	vec_t xn;
	xn.len = 10;
	init_vec(xn, 2);
	//for (n = 0; n < xn.len; n++)
	//	xn.arr[n] = (double)(xn.len - 1 - n);
	
	print_vec(xn);
	printf("\r\n");
	insertion_sort(xn);
	printf("\r\n");
	print_vec(xn);
	*/
	
	//Selection sort testing.
	/*
	int n = 0;
	
	vec_t xn;
	xn.len = 10;
	init_vec(xn, 2);
	
	print_vec(xn);
	printf("\r\n");
	selection_sort(xn);
	printf("\r\n");
	print_vec(xn);
	*/

	//Generate lowpass filter helper functions testing.
		//Pick window testing.
		/*
		printf("%d\r\n\r\n", pick_window(0.1));
		printf("%d\r\n\r\n", pick_window(0.01));
		printf("%d\r\n\r\n", pick_window(0.005));
		printf("%d\r\n\r\n", pick_window(0.001));
		printf("%d\r\n\r\n", pick_window(0.0001));
		*/
	
		//Generate window testing.
		/*
		int n = 0;
		vec_t xn;
		for (n = 0; n < 5; n++) {
			xn = generate_window(n, 100);
			printf("%d:\r\n", n);
			print_vec(xn);
			printf("\r\n\r\n");
		}
		*/

		//Get filter length testing.
		/*
		int M = 0;
		M = get_filter_length(0.2*M_PI, 0.3*M_PI, 0.1);
		printf("Filter length is %d\r\n\r\n", M);
		
		M = get_filter_length(0.2*M_PI, 0.3*M_PI, 0.01);
		printf("Filter length is %d\r\n\r\n", M);
		
		M = get_filter_length(0.2*M_PI, 0.3*M_PI, 0.005);
		printf("Filter length is %d\r\n\r\n", M);
		
		M = get_filter_length(0.2*M_PI, 0.3*M_PI, 0.001);
		printf("Filter length is %d\r\n\r\n", M);
		
		M = get_filter_length(0.2*M_PI, 0.3*M_PI, 0.0001);
		printf("Filter length is %d\r\n\r\n", M);
		*/

		//Generate lowpass impulse response testing.
		/*
		vec_t hn = generate_lowpass_impulse_response(100, 0.5*M_PI);
		print_vec(hn);
		*/

	//Generate lowpass filter testing.
	/*
	//Declare.
	vec_t xn;
	xn.len = 512;
	xn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	vec_cpx_t Xk;
	Xk.len = xn.len;
	Xk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Xk.len);
	
	vec_t hn;
	vec_t yn;
	
	vec_cpx_t xn_cpx;
	vec_cpx_t yn_cpx;
	
	vec_cpx_t Yk;
	Yk.len = xn.len;
	Yk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Yk.len);
	
	double fs = 8000.0;
	
	//Initialize.
	init_vec(xn, 3);
		xn_cpx = cpx_cast_vec(xn);
	
	Xk = fft(xn_cpx);
	
	//Generate and operate lowpass filter.
	hn = generate_lowpass_filter(0.3*M_PI, 0.2*M_PI, 0.1); 
	yn = conv(xn, hn);
		yn_cpx = cpx_cast_vec(yn);
	Yk = fft(yn_cpx);
	
	//Analyze results.
	printf("Used hn with length %d\r\n", hn.len);
	
	printf("Spectrum before lowpass filter:\r\n");
	print_cpx_vec(Xk);
	
	printf("\r\nSpectrum after lowpass filter:\r\n");
	print_cpx_vec(Yk);
	*/

	//Generate highpass filter testing.
	/*
	//Declare.
	vec_t xn;
	xn.len = 512;
	xn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	vec_cpx_t Xk;
	Xk.len = xn.len;
	Xk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Xk.len);
	
	vec_t hn;
	vec_t yn;
	
	vec_cpx_t xn_cpx;
	vec_cpx_t yn_cpx;
	
	vec_cpx_t Yk;
	Yk.len = xn.len;
	Yk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Yk.len);
	
	//Initialize.
	init_vec(xn, 3);
		xn_cpx = cpx_cast_vec(xn);
	
	Xk = fft(xn_cpx);
	
	//Generate and operate filter.
	hn = generate_highpass_filter(0.3*M_PI, 0.2*M_PI, 0.1);
	yn = conv(xn, hn);
		yn_cpx = cpx_cast_vec(yn);
	Yk = fft(yn_cpx);
	
	//Analyze results.
	printf("Used hn with length %d\r\n", hn.len);
	
	printf("Spectrum before filter:\r\n");
	print_cpx_vec(Xk);
	
	printf("\r\nSpectrum after filter:\r\n");
	print_cpx_vec(Yk);
	*/

	//Generate bandstop filter testing.
	/*
	//Declare.
	vec_t xn;
	xn.len = 512;
	xn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	vec_cpx_t Xk;
	Xk.len = xn.len;
	Xk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Xk.len);
	
	vec_t hn;
	vec_t yn;
	
	vec_cpx_t xn_cpx;
	vec_cpx_t yn_cpx;
	
	vec_cpx_t Yk;
	Yk.len = xn.len;
	Yk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Yk.len);
	
	//Initialize.
	init_vec(xn, 3);
		xn_cpx = cpx_cast_vec(xn);
	
	Xk = fft(xn_cpx);
	
	//Generate and operate filter.
	hn = generate_bandstop_filter(0.2*M_PI, 0.3*M_PI, 0.7*M_PI, 0.8*M_PI, 0.1); 
	yn = conv(xn, hn);
		yn_cpx = cpx_cast_vec(yn);
	Yk = fft(yn_cpx);
	
	//Analyze results.
	printf("Used hn with length %d\r\n", hn.len);
	
	printf("Spectrum before filter:\r\n");
	print_cpx_vec(Xk);
	
	printf("\r\nSpectrum after filter:\r\n");
	print_cpx_vec(Yk);
	*/
	
	//Generate bandpass filter testing.
	/*
	//Declare.
	vec_t xn;
	xn.len = 512;
	xn.arr = (double*)malloc(sizeof(double)*xn.len);
	
	vec_cpx_t Xk;
	Xk.len = xn.len;
	Xk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Xk.len);
	
	vec_t hn;
	vec_t yn;
	
	vec_cpx_t xn_cpx;
	vec_cpx_t yn_cpx;
	
	vec_cpx_t Yk;
	Yk.len = xn.len;
	Yk.arr = (cpx_t*)malloc(sizeof(cpx_t)*Yk.len);
	
	//Initialize.
	init_vec(xn, 3);
		xn_cpx = cpx_cast_vec(xn);
	
	Xk = fft(xn_cpx);
	
	//Generate and operate filter.
	hn = generate_bandpass_filter(0.2*M_PI, 0.3*M_PI, 0.7*M_PI, 0.8*M_PI, 0.1); 
	yn = conv(xn, hn);
		yn_cpx = cpx_cast_vec(yn);
	Yk = fft(yn_cpx);
	
	//Analyze results.
	printf("Used hn with length %d\r\n", hn.len);
	
	printf("Spectrum before filter:\r\n");
	print_cpx_vec(Xk);
	
	printf("\r\nSpectrum after filter:\r\n");
	print_cpx_vec(Yk);
	*/
	
	//ANN testing.
		//Create ANN. new_ann_t() test.
		/*
		int_vec_t nodes_per_layer = new_int_vec_t(5);
		nodes_per_layer.arr[0] = 20;
		nodes_per_layer.arr[1] = 4;
		nodes_per_layer.arr[2] = 6;
		nodes_per_layer.arr[3] = 12;
		nodes_per_layer.arr[4] = 15;
		
		ann_t ann = new_ann_t(nodes_per_layer);
		
		printf("ANN has %d layers.\r\n", ann.num_layers);
		
		printf("Their amounts of nodes are:\r\n");
		int l = 0;
		int n = 0;
		for (l = 0; l < ann.num_layers; l++) {
			printf("Layer %d has %d nodes.\r\n", l, ann.arr_layers[l].num_nodes);
			printf("This layer's nodes have the following weight vector lengths: \r\n");
			for (n = 0; n < ann.arr_layers[l].num_nodes; n++)
				printf("Node %d: %d\r\n", n, ann.arr_layers[l].arr_nodes[n].weight.len);
			printf("\r\n\r\n\r\n");
		}
		*/

		//Randomly initialize weights and biases. init_weights_and_biases_ann() test.
		/*
		int_vec_t nodes_per_layer = new_int_vec_t(5);
		nodes_per_layer.arr[0] = 20;
		nodes_per_layer.arr[1] = 4;
		nodes_per_layer.arr[2] = 6;
		nodes_per_layer.arr[3] = 12;
		nodes_per_layer.arr[4] = 15;
		
		ann_t ann = new_ann_t(nodes_per_layer);
		init_weights_and_biases_ann(ann);
		
		int l = 0;
		int n = 0;
		int w = 0;
		for (l = 1; l < ann.num_layers; l++) {
			for (n = 0; n < ann.arr_layers[l].num_nodes; n++) {
				printf("Layer %d, node %d.\r\n", l, n);
				printf("%d weights:\r\n", ann.arr_layers[l].arr_nodes[n].weight.len);
				print_vec(ann.arr_layers[l].arr_nodes[n].weight);
				printf("Bias: %lf\r\n\r\n\r\n", ann.arr_layers[l].arr_nodes[n].bias);
			}
			printf("\r\n\r\n");
		}
		*/

		//Feed forward to ANN output. feed_forward_ann() test.
		/*
		//Declare memory.
		int_vec_t nodes_per_layer = new_int_vec_t(4);
		nodes_per_layer.arr[0] = 3;
		nodes_per_layer.arr[1] = 4;
		nodes_per_layer.arr[2] = 1;
		nodes_per_layer.arr[3] = 2;
		
		ann_t ann = new_ann_t(nodes_per_layer);
		
		//Initialize input layer.
		vec_t input_layer;
			input_layer = new_vec_t(3);
			input_layer.arr[0] = 1; input_layer.arr[1] = 2; input_layer.arr[2] = 3;
		preload_layer_outputs(ann, input_layer, 0);
		
		
		//Initialize weights and biases to presets.
		int l = 0;
		int n = 0;
		int i = 0;
		int q = 0;
		vec_t weight_src;
		for (l = 1; l < ann.num_layers; l++) {
			for (n = 0; n < ann.arr_layers[l].num_nodes; n++) {
				weight_src = new_vec_t(ann.arr_layers[l - 1].num_nodes);
				
				for (i = 0; i < weight_src.len; i++)
					weight_src.arr[i] = (double)(q);
				
				load_weight_to_node(ann, l, n, weight_src, weight_src.arr[0]);
				q++;
			}
		}
		
		//print_ann(ann);
		feed_forward_ann(ann);
		*/
		
		//ANN training test.
		/*
			//Differentiate between three different signals.
			//Case 0: Rect. [0, 1, 1, 1, ... 1, 1, 0].
			//Case 1: Upward line. [0, 0.1, 0.2... 1.0].
			//Case 2: Downward line. [0, -0.1, -0.2 ... -1.0].
			
		//Initialize net.
		int_vec_t npl = new_int_vec_t(3);
			npl.arr[0] = 10;
			npl.arr[1] = 50;
			npl.arr[2] = 3;
		ann_t ann = new_ann_t(npl);
		init_weights_and_biases_ann(ann);
		ann.learning_rate = 0.1;
		ann.momentum_factor = 0.01;
		
		//Generate training examples.
		vec_list_t input_examples = new_vec_list_t(1000, npl.arr[0]);
		int num_cases = npl.arr[npl.len - 1]; int cur_case = 0;
		int ind_vec = 0; int j = 0;
		int r = 0; int r_n = 0; int rn_max = 100;
		for (ind_vec = 0; ind_vec < input_examples.len; ind_vec++) {
			cur_case = ind_vec % num_cases;
			
			//Clear.
			clear_vec(input_examples.arr[ind_vec]);
			
			//Rect, up line or down line.
			if (cur_case == 0) {
				for (j = 1; j < input_examples.arr[ind_vec].len - 1; j++)
					input_examples.arr[ind_vec].arr[j] = 1.0;
			}
			if (cur_case == 1) {
				for (j = 0; j < input_examples.arr[ind_vec].len; j++)
					input_examples.arr[ind_vec].arr[j] = (double)j / (double)(input_examples.arr[ind_vec].len);
			}
			if (cur_case == 2) {
				for (j = 0; j < input_examples.arr[ind_vec].len; j++)
					input_examples.arr[ind_vec].arr[j] = -(double)j / (double)(input_examples.arr[ind_vec].len);
			}
			
			//Randomize.
			for (r_n = 0; r_n < rn_max; r_n++) {
				r = int_rand_given_bound(0, input_examples.arr[ind_vec].len - 1);
				input_examples.arr[ind_vec].arr[r] += rand_given_bound(-0.5, 0.5);
			}
			
		} cur_case = 0;
		
		//Train.
		vec_list_t target_vec_list = create_targets(num_cases);
		for (ind_vec = 0; ind_vec < input_examples.len; ind_vec++) {
			preload_layer_outputs(ann, input_examples.arr[ind_vec], 0);
			
			feed_forward_ann(ann);
			
			backpropagate_adjust(ann, target_vec_list.arr[cur_case]);
			cur_case = revolve_mod(cur_case, num_cases);
			
			//printf("Training trial %d %=> %d:\r\n", ind_vec, cur_case);
			//printf("Output node 0: %lf\r\n", ann.arr_layers[ann.num_layers - 1].arr_nodes[0].output);
			//printf("Output node 1: %lf\r\n", ann.arr_layers[ann.num_layers - 1].arr_nodes[1].output);
			//printf("Output node 2: %lf\r\n\r\n\r\n", ann.arr_layers[ann.num_layers - 1].arr_nodes[2].output);
		}
		
		//Generate test items.
		vec_list_t test_list = new_vec_list_t(1000, npl.arr[0]);
		int_vec_t answer_key = new_int_vec_t(test_list.len);
		for (ind_vec = 0; ind_vec < test_list.len; ind_vec++) {
		
			//Clear.
			clear_vec(test_list.arr[ind_vec]);
			
			//Rect, up line, or down line.
			r = int_rand_given_bound(0,2);
			if (r == 0) {
				for (j = 1; j < test_list.arr[ind_vec].len - 1; j++)
					test_list.arr[ind_vec].arr[j] = 1.0;
				answer_key.arr[ind_vec] = 0;
			}
			if (r == 1) {
				for (j = 0; j < test_list.arr[ind_vec].len; j++)
					test_list.arr[ind_vec].arr[j] = (double)j / (double)(test_list.arr[ind_vec].len);
				answer_key.arr[ind_vec] = 1;
			}
			if (r == 2) {
				for (j = 0; j < test_list.arr[ind_vec].len; j++)
					test_list.arr[ind_vec].arr[j] = -(double)j / (double)(test_list.arr[ind_vec].len);
				answer_key.arr[ind_vec] = 2;
			}
			
			//Randomize.
			for (r_n = 0; r_n < rn_max; r_n++) {
				r = int_rand_given_bound(0, test_list.arr[ind_vec].len - 1);
				test_list.arr[ind_vec].arr[r] += rand_given_bound(-0.5, 0.5);
			}
		}
		
		//Test and score.
		int_vec_t answer_ann = new_int_vec_t(test_list.len);
		int num_correct = test_and_score(ann, test_list, answer_key, &answer_ann);
		
		//Extra output.
		for (ind_vec = 0; ind_vec < test_list.len; ind_vec++)
			printf("%d, %d\r\n", answer_ann.arr[ind_vec], answer_key.arr[ind_vec]);
		printf("%d correct guesses.\r\n", num_correct);
		*/
}
