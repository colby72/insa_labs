#include <stdio.h>
#define ZERO 1e-100
#define EPSILON 1e-10
#include <math.h>

int proche(double a, double b) {
	//if (fabs(a-b)<EPSILON | (fabs(a)<=ZERO & fabs(b)<=ZERO)) return 1;
	if (fabs(a)<ZERO ? fabs(b)<ZERO:fabs(a-b)<EPSILON*fabs(a)) return 1;
	else return 0;
}
double moyenne(double t[], int n) {
	int i;
	double s=0;
	for (i=0; i<n; i++) {
		s = s+t[i];
	}
	return s/n;
}
double moyenne_positifs(double t[]) {
	if (t[0]<0) return -1.0;
	else {
		int i=0;
		double s=0;
		do {
			s = s + t[i];
			i++;
		} while (t[i]>=0);
	return s/(i+1);
	}
}
double test_moyenne() {
	double v[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, -1.0};
	double d, attendu;
	attendu = 1;
	if (!proche((d=moyenne(v,1)), attendu)) {
		printf("Pb moyenne. Attendu: %f Obtenu: %f\n", attendu, d);
	}
	attendu = 2.0;
	if (!proche((d=moyenne(v,3)), attendu)) {
		printf("Pb moyenne. Attendu: %f Obtenu: %f\n", attendu, d);
	}
	attendu = 3.5;
	if (!proche((d=moyenne(v,6)), attendu)) {
		printf("Pb moyenne. Attendu: %f Obtenu: %f\n", attendu, d);
	}
	attendu = 3.5;
	if (!proche((d=moyenne_positifs(v)), attendu)) {
		printf("Pb moyenne_positifs. Attendu: %f Obtenu: %f\n", attendu, d);
	}
	attendu = 5.0;
	if (!proche((d=moyenne_positifs(v+3)), attendu)) {
		printf("Pb moyenne_positifs. Attendu: %f Obtenu: %f\n", attendu, d);
	}
	attendu = -1.0;
	if (!proche((d=moyenne_positifs(v+3)), attendu)) {
		printf("Pb moyenne_positifs. Attendu: %f Obtenu: %f\n", attendu, d);
	}
}

int main(void) {
	/*
	double a, b;
	printf("Enter a : ");
	scanf("%lf", &a);
	printf("Enter b : ");
	scanf("%lf", &b);
	printf("%d\n", proche(a, b));
	*/
	test_moyenne();
	//test1
	//double t[] = {1.0, 2.0, 3.0};
	//printf("%f\n", moyenne_positifs(t));
	return 0;
}
