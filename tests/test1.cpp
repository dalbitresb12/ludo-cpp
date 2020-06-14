#include<iostream>
#include<conio.h>
#include<time.h>
using namespace std;
//recorrido por filas
void LecturaDatos(int &n, int&c,int **matriz) { //2  3

	//lecctura e datos por filas
	for (int i = 0; i < n; i++) {

		for (int j = 0; j < c; j++) {
			matriz[i][j] = 3 * i * 10 + (j + 1) * 10;

		}
	}

}
//recorrido por columnas
//void LecturaDatos_columna(int& n, int& c, int** matriz) { //2  3
//	//2  3
//	//lecctura e datos por filas
//	for (int j = 0; j < c; j++) {
//
//		for (int i = 0; i < n; i++) {
//
//			matriz[i][j] = 3 * i * 10 + (j + 1) * 10;
//
//			cout << endl;
//		}
//		
//	}
//
//}
//generando datos aleatorios para la matriz

void generarDatos(int& n, int& c, int** matriz) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c; j++) {
			matriz[i][j] = rand() % 21;
		}
	}
}
void MostrarDatos(int& n, int& c, int** matriz) {
	for (int i = 0; i < n; i++) {//recorre todas las filas
		for (int j = 0; j < c; j++) {//recorre todas columnas
			cout << matriz[i][j] << "  ";
		}
		cout << endl;
	}
}
void buscarValor(int& n, int& c, int** matriz, int& valor) {
	int posf, posc;
	posf = posc = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c; j++) {
			if (matriz[i][j] == valor) {
				posf = i;
				posc = j;
			}
		}
	}
	if (posc == -1 || posf == -1)
		cout << "no se encontro el dato";
	else
		cout << " Si se encontro el dato";
}

void mayorElemento(int& n, int& c, int** matriz) {
	int mayor = matriz[0][0];
	int posf=0, posc=0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c; j++) {
			if (mayor < matriz[i][j]) {
				mayor = matriz[i][j];
				posf = i;
				posc = j;
			}

		}
	}
	cout << " el mayor valor es: " << mayor << endl;
	cout << "En la posicion: " << posf<<" " << posc;
}
int main() {
	srand(time(NULL));
	int filas = 100;
	int columnas = 100;
	int** matriz = new int*[filas];
	for (int i = 0; i < filas; i++)
		matriz[i] = new int[columnas];
	//LecturaDatos(filas, columnas, matriz);
	generarDatos(filas, columnas, matriz);
	MostrarDatos(filas, columnas, matriz);
	int valor;
	cout << "Ingrese el valor: "; cin >> valor;
	buscarValor(filas,columnas, matriz,valor);
	cout << endl;
	mayorElemento(filas, columnas, matriz);
	//mostramos los datos de la matriz
	






	//liberando el espacio de memoria
	for (int i = 0; i < filas; i++)
		delete[]matriz[i];//se leibera cada vector de enteros
	delete[]matriz;//cada vector de punteros


	_getch();
}