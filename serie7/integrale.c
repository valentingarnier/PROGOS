#include <stdio.h>
#include <math.h>
 
double f(double x) {
  return sin(x);
}

double g(double x) {
	return exp(x);
}

double h(double x) {
	return sqrt(x);
}

typedef double(*Fonction)(double);

Fonction choice[3] ={ f, g, h };
 
int demander_choix(void)
{
  int res = 0;
  printf("Entrez un nombre pour choisir votre fonction [1...3] : ");
  scanf("%d", &res);

  return res;
}

double demander_nombre(void)
{
  double res = 0;
  printf("Entrez un nombre réel : ");
  scanf("%lf", &res);
  return res;
}
 
double integre(Fonction fct, double a, double b)
{
	double res = 0;
	if (fct == f) res = -cos(b) + cos(a);
	else if (fct == g) res = exp(b) - exp(a);
	else if (fct == h) res = (1/(3/2))*(pow(b, 3/2) - pow(a, 3/2));
	else res = 0;
  return res;
}
 
 
int main(void)
{
  double
    a = demander_nombre(),
    b = demander_nombre();
    Fonction fct = NULL;
    fct = choice[demander_choix()];
  printf("Integrale de f entre %f et %f : %.12f\n", a, b, integre(fct, a, b));
  return 0;
}
