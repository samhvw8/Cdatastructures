#include <Ginz.h>
#define ERR 0.00000000001
double mex(double x);
double power(double x, double n);
double Factorial(double x);
int main(int argc, char const *argv[]) {
	if (argc != 2)
		printf("%s\nFormat is ./E x", "Wrong format !!");
	else
		printf("%s%.3lf : %.3lf\n", "E^", atof(argv[1]), mex(atof(argv[1])));
	return 0;
}
double Factorial(double x) {
	double i, o;
	o = 1;
	if (x == 0) return 1;
	for (i = 1; i <= x; i += 1) o = o * i;
	return o;
}
double power(double x, double n) {
	double i, o = 1;
	if (n == 0) return 1;
	if (n >= 1) {
		for (i = 1; i <= n; i += 1) o = o * x;
	}
	return o;
}
double mex(double x) {
	double j, a, b;
	b = 1;
	j = 1;
	do {
		a = power(x, j) / Factorial(j);
		b = b + a;
		j += 1;
	} while (a > ERR);
	return b;
}
