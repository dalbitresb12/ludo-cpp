#include <iostream>
#include <conio.h>
using namespace std;
int valida_n(int& n) {
	do {
		cout << "Digite numero de terminos: "; cin >> n;
	} while (n < 0);
	return n;
}
float valida_x(float* x) {
	do {
		cout << "Digite x: "; cin >> *x;
	} while (*x < 2 || *x > 4);
	return *x;
}
float valida_y(float* y) {
	do {
		cout << "Digite y: "; cin >> *y;
	} while (*y < 2 || *y > 4);
	return *y;
}
int valida_nfilas(int& nf) {
	do {
		cout << "Digite numero de filas: "; cin >> nf;
	} while (nf < 0 || nf > 10);
	return nf;
}
void menu() {
	cout << "\t\nMENU DE OPCIONES" << endl;
	cout << "A. Hallar la suma de la serie." << endl;
	cout << "B. Graficar." << endl;
	cout << "C. Fin." << endl;
	cout << "Opcion: ";
}
float factorial(int k) {
	float fact = 1;
	for (int i = 1; i <= k; i++) {
		fact *= i;
	}
	return fact;
}
double SumaSerie(int &n, float *x, float*y) {
	double suma = 0;
	int signo = 1;
	for (int i = 1; i <= n; i++) {
		suma += signo * pow(*x, i * *y) / factorial(pow(2, i));
		signo = signo * -1;
	}
	return suma;
}
void Graficar(int& nfilas) {
	for (int i = 1; i <= 2 * nfilas - 1; i++) {
		for (int j = 1; j <= 2 * nfilas - 1; j++) {
			if (i == j || i + j == 2 * nfilas || i == 1 || i == 2 * nfilas - 1)
				cout << j;
			else
				cout << " ";
		}
		cout << endl;
	}
}
int main() {
	char* opc = new char;
	float* x = new float;
	float* y = new float;
	int n;
	int nf;
	while (1) {
		menu();
		cin >> *opc;
		*opc = toupper(*opc);
		switch (*opc) {
		case 'A':
			cout << "SUMA SERIE" << endl;
			n = valida_n(n);
			*x = valida_x(x);
			*y = valida_y(y);
			cout << "La sumatoria es: " << SumaSerie(n, x, y) << endl;
			break;
		case 'B':
			cout << "GRAFICA" << endl;
			nf = valida_nfilas(nf);
			Graficar(nf);
			break;
		case 'C':
			exit(0);
			break;
		}
	}
	_getch();
	return 0;
}