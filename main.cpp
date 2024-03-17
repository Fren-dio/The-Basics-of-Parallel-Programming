#include <iostream>

#define N 3

double* multColumnByValue(double* column, double value);
double* mult(double* A, double* B);
double* multMatrByCol(double* A, double* B);
double* subMatrix(double* reduced, double* subtracted);
double* calculatedXMatrix(double countValueTau, double* A, double* X, double* B);
bool conditionIsCompleted(double epsilon, double* A, double* X, double* B);
double norma(double* column);
double* subColumn(double* reduced, double* subtracted);


int main()
{
	double epsilon = 0.00001;
	double countValueTau = 0.01;
	double* A = new double[N * N];
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (i == j)
				A[i * N + j] = 2.0;
			else
				A[i * N + j] = 1.0;
	double* X = new double[N];
	for (i = 0; i < N; i++)
		X[i] = 0;
	double* B = new double[N];
	for (i = 0; i < N; i++)
		B[i] = N + 1;

	double* result = new double[N];
	for (i = 0; i < N; i++)
		result[i] = 0.0;
	int cnt = 0;
	while (true)
	{
		//std::cout << cnt << " step\n";
		result = calculatedXMatrix(countValueTau, A, X, B);
		X = subColumn(X, result);
		cnt++;
		if ((norma(subColumn(multMatrByCol(A, X), B)) / norma(B)) < epsilon)
			break;
	}
	std::cout << "\nX vector:\n";
	for (i = 0; i < N; i++)
		std::cout << X[i] << " ";
	std::cout << "program was completed";
	
	return 0;

}

//X = X - tau * (A*X - B)


//is a correct
double norma(double* column)
{
	double result = 0.0;
	int i;
	for (i = 0; i < N; i++)
		result += pow(column[i], 2);
	result = sqrt(result);

	return result;
}

double* subColumn(double* reduced, double* subtracted)
{
	int i, j;
	for (i = 0; i < N; i++)
			reduced[i] -= subtracted[i];
	return reduced;
}


//is a correct
double* calculatedXMatrix(double countValueTau, double* A, double* X, double* B)
{
	// countValueTau * (A*X - B)
	double* result = new double[N];
	int i, j, k;
	for (i = 0; i < N; i++)
		result[i] = 0.0;

	result = multMatrByCol(A, X);
	result = subColumn(result, B);
	result = multColumnByValue(result, countValueTau);

	return result;
}


double* multColumnByValue(double* column, double value)
{
	int i;
	for (i = 0; i < N; i++)
		column[i] = column[i] * value;
	return column;
}


double* multMatrByCol(double* matrix, double* column)
{
	double* result = new double[N];
	int i, j;
	for (i = 0; i < N; i++)
		result[i] = 0.0;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
				result[i] += matrix[i*N+j] * column[j];
	return result;

}