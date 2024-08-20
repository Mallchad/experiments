#include <stdio.h>
#include <stdlib.h>
#include <math.h>        
#include <float.h>

#ifdef VAL_DEBUG
    #define d_printf(...) printf(__VA_ARGS__)
#else
    #define d_printf(...)
#endif

double max_double(double a, double b)
{	if (a>b){return a;}
	else {return b;}
}

double min_double(double a, double b)
{	if (a<b){return a;}
	else {return b;}
}

//Find and return largest element of vector V
double max_finder(double *V,int sizeof_V)
{int i; double max=V[0];
for(i=1;i<sizeof_V;i++){if(V[i]>max){max=V[i];}}
return max;}

//Find and return index of largest element of vector V
int max_idx_finder(double *V,int sizeof_V)
{int idx=0,i; 
for(i=1;i<sizeof_V;i++){if(V[i]>V[idx]){idx=i;}}
return idx;}

double f(double x)
{
	return x+log(x)-3.0;
}

//Brent's method of root finding by me - OK, OK, by Wikipedia...
double brent_me(double a, double b){
	
	double max_tolerance=1E-14, s,c,d, f_a, f_b, f_c, f_s,swap,f_swap;
	int flag=1,iteration_number=0,max_iterations=100;

	f_a=f(a);d_printf("x %.26E\n",a);
	f_b=f(b);d_printf("x %.26E\n",b);

	if (f_a*f_b>0){	//Even number of roots in interval
		return 0.0;
	}

	if (fabs(f_b)>fabs(f_a)){ //Swap a and b
		swap=a;
		f_swap=f_a;
		a=b;
		f_a=f_b;
		b=swap;
		f_b=f_swap;
	}

	c=a;
	f_c=f_a;

	while (iteration_number<max_iterations && fabs((b-a)/min_double(a,b))>max_tolerance && f_b!=0.0){
		if (f_a!=f_c && f_b!=f_c){	//Inverse quadratic
			s=a*f_b*f_c/((f_a-f_b)*(f_a-f_c))+b*f_a*f_c/((f_b-f_a)*(f_b-f_c))+c*f_a*f_b/((f_c-f_a)*(f_c-f_b));
			d_printf("%d Q\n",iteration_number);
		}

		else{	//Secant
			s=b-f_b*(b-a)/(f_b-f_a);
			d_printf("%d S\n",iteration_number);
		}

		if ( 	(a>b && s<b && s>(3.0*a+b)/4.0) ||
			(a<b && s>b && s<(3.0*a+b)/4.0) ||
			(flag==1 && fabs(s-b)>=fabs(b-c)/2.0) ||
			(flag==0 && fabs(s-b)>=fabs(c-d)/2.0) ||
			(flag==1 && fabs(b-c)<max_tolerance) ||
			(flag==0 && fabs(c-d)<max_tolerance) ){
			s=(a+b)/2.0;
			flag=1;
			d_printf("%d B\n",iteration_number);
		}
		else{
			flag=0;
		}

		f_s=f(s);d_printf("x %.26E\n",s);
		d=c;
		c=b;
		f_c=f_b;

		if (f_a*f_s<0){
			b=s;
			f_b=f_s;
		}
		else{
			a=s;
			f_a=f_s;
		}

		if (fabs(f_b)>fabs(f_a)){ //Swap a and b
			swap=a;
			f_swap=f_a;
			a=b;
			f_a=f_b;
			b=swap;f_b=f_swap;}
		d_printf("%E %E %E %E\n",a,b,c,s);

		iteration_number++;

	}
	return b;
}


#define MIN(a, b) ((a) < (b) ? (a) : (b))
double brentq(double xa, double xb)
{
    double xpre = xa, xcur = xb;
    double xblk = 0., fpre, fcur, fblk = 0., spre = 0., scur = 0., sbis;
    /* the tolerance is 2*delta */
    double delta;
    double stry, dpre, dblk;
    int i;
    int iter=100;
    double xtol=1E-14, rtol=1E-14;

    fpre = f(xpre);d_printf("x %.26E\n",xpre);
    fcur = f(xcur);d_printf("x %.26E\n",xcur);
    if (fpre == 0) {
        return xpre;
    }
    if (fcur == 0) {
        return xcur;
    }
    if (signbit(fpre)==signbit(fcur)) {
        return 0.;
    }
    for (i = 0; i < iter; i++) {
        if (fpre != 0 && fcur != 0 &&
	    (signbit(fpre) != signbit(fcur))) {
            xblk = xpre;
            fblk = fpre;
            spre = scur = xcur - xpre;
        }
        if (fabs(fblk) < fabs(fcur)) {
            xpre = xcur;
            xcur = xblk;
            xblk = xpre;

            fpre = fcur;
            fcur = fblk;
            fblk = fpre;
        }

        delta = (xtol + rtol*fabs(xcur))/2;
        sbis = (xblk - xcur)/2;
        if (fcur == 0 || fabs(sbis) < delta) {
            return xcur;
        }

        if (fabs(spre) > delta && fabs(fcur) < fabs(fpre)) {
            if (xpre == xblk) {
                /* interpolate */
                stry = -fcur*(xcur - xpre)/(fcur - fpre);
                d_printf("%d S\n",i);
            }
            else {
                /* extrapolate */
                dpre = (fpre - fcur)/(xpre - xcur);
                dblk = (fblk - fcur)/(xblk - xcur);
                stry = -fcur*(fblk*dblk - fpre*dpre)/(dblk*dpre*(fblk - fpre));
                d_printf("%d Q\n",i);
            }

            if (2*fabs(stry) < MIN(fabs(spre), 3*fabs(sbis) - delta)) {
                /* good short step */
                spre = scur;
                scur = stry;
            }
            else {
                /* bisect */
                spre = sbis;
                scur = sbis;
                d_printf("%d B\n",i);
            }
        }
        else {
            /* bisect */
            spre = sbis;
            scur = sbis;
            d_printf("%d B\n",i);
        }

        xpre = xcur;
        fpre = fcur;
        if (fabs(scur) > delta) {
            xcur += scur;
        }
        else {
            xcur += (sbis > 0 ? delta : -delta);
        }

        fcur = f(xcur);d_printf("x %.26E\n",xcur);
    }
    return xcur;
}

double brenth(const double xa, const double xb)
{
    double xpre = xa, xcur = xb;
    double xblk = 0., fpre, fcur, fblk = 0., spre = 0., scur = 0., sbis;
    /* the tolerance is 2*delta */
    double delta;
    double stry, dpre, dblk;
    int i;
    int iter=100;
    double xtol=1E-14, rtol=1E-14;

    fpre = f(xpre);d_printf("x %.26E\n",xpre);
    fcur = f(xcur);d_printf("x %.26E\n",xcur);
    if (fpre == 0) {
        return xpre;
    }
    if (fcur == 0) {
        return xcur;
    }
    if (signbit(fpre)==signbit(fcur)) {
        return 0.;
    }
    for (i = 0; i < iter; i++) {
        if (fpre != 0 && fcur != 0 &&
	    (signbit(fpre) != signbit(fcur))) {
            xblk = xpre;
            fblk = fpre;
            spre = scur = xcur - xpre;
        }
        if (fabs(fblk) < fabs(fcur)) {
            xpre = xcur;
            xcur = xblk;
            xblk = xpre;

            fpre = fcur;
            fcur = fblk;
            fblk = fpre;
        }

        delta = (xtol + rtol*fabs(xcur))/2;
        sbis = (xblk - xcur)/2;
        if (fcur == 0 || fabs(sbis) < delta) {
            return xcur;
        }

        if (fabs(spre) > delta && fabs(fcur) < fabs(fpre)) {
            if (xpre == xblk) {
                /* interpolate */
                stry = -fcur*(xcur - xpre)/(fcur - fpre);
                d_printf("%d S\n",i);
            }
            else {
                /* extrapolate */
                dpre = (fpre - fcur)/(xpre - xcur);
                dblk = (fblk - fcur)/(xblk - xcur);
                stry = -fcur*(fblk - fpre)/(fblk*dpre - fpre*dblk);
                d_printf("%d H\n",i);
            }

            if (2*fabs(stry) < MIN(fabs(spre), 3*fabs(sbis) - delta)) {
                /* good short step */
                spre = scur;
                scur = stry;
            }
            else {
                /* bisect */
                spre = sbis;
                scur = sbis;
                d_printf("%d B\n",i);
            }
        }
        else {
            /* bisect */
            spre = sbis;
            scur = sbis;
            d_printf("%d B\n",i);
        }

        xpre = xcur;
        fpre = fcur;
        if (fabs(scur) > delta) {
            xcur += scur;
        }
        else {
            xcur += (sbis > 0 ? delta : -delta);
        }

        fcur = f(xcur);d_printf("x %.26E\n",xcur);
    }
    return xcur;
}


int main() 
{
	double brent_result=brent_me(1.5,3.0);
  	d_printf("%.26E, %.26E \n",brent_result,f(brent_result));
  	d_printf("\n");
	double brent_result2=brentq(1.5,3.0);
  	d_printf("%.26E, %.26E \n",brent_result2,f(brent_result2));
  	d_printf("\n");
	double brent_result3=brenth(1.5,3.0);
  	d_printf("%.26E, %.26E \n",brent_result3,f(brent_result3));
}

