/*
 
[factorial] v. 1 (2016) for Pd written by Ricky Graham <ricky@rickygraham.net>

*/


#include "m_pd.h"
#include <stdlib.h>

static char *version = "[factorial] v. 1 (2016) for Pd written by Ricky Graham <ricky@rickygraham.net>";

static t_class *factorial_class;

typedef struct _factorial {
    
    t_object fctrl;

    double long factor;
    
    t_outlet  *factorial;

    t_clock *x_clock;
    
} t_factorial;




long double factfun(long double n) 
{
  int c;
  long double x = n;
  long double result = 1;
 
  for (c = 1; c <= x; c++)
  result = result * c;
  return result;
}



void factorial_wait(t_factorial *x)
{

float test = x->factor;	
outlet_float(x->factorial, test);

}
void factorial_free(t_factorial *x)
{
	clock_free(x->x_clock);
}



void factorial_loadbang(t_factorial *x)
{
clock_delay(x->x_clock, 0); //delay of zero
}



/* Constructor - Creation of Inlets and Outlets */
void *factorial_new(t_floatarg f) 
{
    t_factorial *x = (t_factorial *)pd_new(factorial_class);

    x->x_clock = clock_new(x,(t_method)factorial_wait); 

   

  	 int a = (int)f;
  	 
  	 long double b = f;

  	 
  	 post("%d! = %Lf\n", a, factfun(b));
  	
  	 x->factor = factfun(b); 

  	 x->factorial = outlet_new(&x->fctrl, gensym("int")); 
    
     return (void *)x;

}




void factorial_float(t_factorial *x, t_floatarg a) { //takes float input

    
  	int b = (int)a;
  	int c = 1;
  	long double fact = 1;
  	
  	  for (c = 1; c <= b; c++) {
	  fact = fact * c;
 
  	  outlet_float(x->factorial, fact);
 
	}
 
}



/* Setup */
void factorial_setup(void)
{
    factorial_class = class_new(gensym("factorial"),
                              (t_newmethod)factorial_new,
                              0, sizeof(t_factorial),
                              CLASS_DEFAULT,
                              A_DEFFLOAT, 0);

    class_addmethod(factorial_class, (t_method)factorial_loadbang, gensym("loadbang"), 0);

    class_addfloat(factorial_class, factorial_float);
    
    class_addcreator((t_newmethod)factorial_new, gensym("n!"), A_DEFFLOAT, 0);
   
    class_sethelpsymbol(factorial_class, gensym("factorial-help.pd"));
    post(version);
    
}

