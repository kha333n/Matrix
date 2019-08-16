// Matrix<T>.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
template <class T>
class Matrix
{
private:
	int numRows, numCols;
	T **elements;
public:
	Matrix<T> (int = 0, int = 0); //Default constructor
	Matrix<T> (const Matrix<T> &);	//Copy constructor
	~Matrix<T> ();		//Destructor

	//Utility functions
	int getRows (void) const;
	int getCols (void) const;

	//Input functions
	const Matrix<T> & input (istream &is = cin);
	const Matrix<T> & input (ifstream &is);
	
	//Output functions
	void output (ostream &os = cout) const;
	void output (ofstream &os) const;

	//Plus operatpr
	Matrix<T> operator + (Matrix<T> &m) const;
	const Matrix<T> & operator += (Matrix<T> &m);
	Matrix<T> operator + (T d) const;
	friend Matrix<T> operator+(T, Matrix<T> &);

	//Minus operator
	Matrix<T> operator - (Matrix<T> &m) const;
	const Matrix<T> & operator -= (Matrix<T> &m);
	Matrix<T> operator - (T d) const;
	friend Matrix<T> operator - (T d, Matrix<T> &m);

	//Multiplication operator
	Matrix<T> operator * ( const Matrix<T> & m);
	Matrix<T> operator * (T d) const;
	friend Matrix<T> operator * (const T d, const Matrix<T> &m);

	//Division operator
	Matrix<T> operator / (const T d);

	//Stream insertion operator
	friend istream & operator >> (istream &os, Matrix<T> &);
	friend ifstream & operator >> (ifstream &os, Matrix<T> &);

	//Stream Extraction operator
	friend ostream & operator << (ostream &is, Matrix<T> &);
	friend  ofstream & operator << (ofstream &is, Matrix<T> &);

	//Assignment operator
	const Matrix<T> & operator = (const Matrix<T> &m);

	//Transpose
	const Matrix<T> & transpose (void);
};

template <class T>
Matrix<T>::Matrix(int row, int cols)
{
	numRows = row;
	numCols = cols;
	elements = new T * [numRows];
	for (int i = 0; i < numRows; i++)
	{
		elements[i] = new T [numCols];
		for (int j = 0; j < numCols; j++)
			elements[i][j] = 0;
	}
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &m)
{
	numRows = m.numRows;
	numCols = m.numCols;
	elements = new T * [numRows];
	for (int i = 0; i < numRows; i++)
	{
		elements[i] = new T [numCols];
		for (int j = 0; j < numCols; j++)
			elements[i][j] = m.elements[i][j];
	}
}

template <class T>
Matrix<T>::~Matrix<T>()
{
	delete [] elements;
}

template <class T>
int Matrix<T>::getRows(void) const
{
	return numRows;
}

template <class T>
int Matrix<T>::getCols(void) const
{
	return numCols;
}

template <class T>
const Matrix<T>& Matrix<T>::input(istream& is)
{
	cout << "Input Matrix<T> size: " << numRows << " rows by " << numCols << " columns\n";
	for (int i = 0; i<numRows; i++)
	{
		cout << "Please enter " << numCols << " value seprated by spaces for row no. " << i+1 << ": ";
		for (int j = 0; j<numCols; j++)
		{
			cin >> elements[i][j];
		}
	}
	return *this;
	// TODO: insert return statement here
}

template <class T>
const Matrix<T>& Matrix<T>::input(ifstream& is)
{
	int Rows, Cols;
	is >> Rows;
	is	>> Cols;
	if (Rows>0 && Cols>0)
	{
		Matrix<T> temp (Rows,Cols);
		*this = temp;
		for (int i = 0; i<numRows; i++)
		{
			for (int j = 0; j<numCols; j++)
			{
				is >> elements[i][j];
			}
		}
	}
	return *this;
	// TODO: insert return statement here
}

template <class T>
void Matrix<T>::output(ostream& os) const
{
	//Print first row with special chracters
	os.setf(ios::showpoint);
	os.setf(ios::fixed,ios::floatfield);
	os << (char) 218;
	for (int j = 0; j<numCols; j++)
		os << setw(10) << " ";
	os << (char) 191 << "\n";
	//Print remaning rows with vertical bars only
	for (int i = 0; i<numRows; i++)
	{
		os << (char) 179;
		for (int j = 0; j<numCols; j++)
			os << setw(10) << setprecision(2) << elements[i][j];
		os << (char) 179 << "\n";
	}
	//Print last row with special chracter
	os << (char) 192;
	for (int j = 0; j<numCols; j++)
		os << setw(10) << " ";
	os << (char) 217 << "\n";
}

template <class T>
void Matrix<T>::output(ofstream& os) const
{
	os.setf(ios::showpoint);
	os.setf(ios::fixed,ios::floatfield);
	os << numRows << " " << numCols << "\n";
	for (int i = 0; i<numRows; i++)
	{
		for (int j = 0; j<numCols; j++)
			os << setw(10) << setprecision(2) << elements[i][j];
		os << "\n";
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& m) const
{
	if (numRows == m.numRows && numCols == m.numCols)
	{
		Matrix<T> temp(*this);
		for (int i = 0; i<numRows; i++)
		{
			for (int j = 0; j<numCols; j++)
			{
				temp.elements[i][j] += m.elements[i][j];
			}
		}
		return temp;
	}
	Matrix<T> temp (*this);
	return temp;
}

template <class T>
const Matrix<T>& Matrix<T>::operator+=(Matrix<T>& m)
{
	*this = *this + m;
	return *this;
	// TODO: insert return statement here
}

template <class T>
Matrix<T> Matrix<T>::operator+(T d) const
{
	Matrix<T> temp(*this);
	for (int i = 0; i<numRows; i++)
	{
		for (int j = 0; j<numCols; j++)
		{
			temp.elements[i][j] += d;
		}
	}
	return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& m) const
{
	if (numRows == m.numRows && numCols == m.numCols)
	{
		Matrix<T> temp(*this);
		for (int i = 0; i<numRows; i++)
		{
			for (int j = 0; j<numCols; j++)
			{
				temp.elements[i][j] -= m.elements[i][j];
			}
		}
		return temp;
	}
	Matrix<T> temp (*this);
	return temp;
}

template <class T>
const Matrix<T>& Matrix<T>::operator-=(Matrix<T>& m)
{
	*this = *this - m;
	return *this;
	// TODO: insert return statement here
}

template <class T>
Matrix<T> Matrix<T>::operator-(T d) const
{
	Matrix<T> temp(*this);
	for (int i = 0; i<numRows; i++)
	{
		for (int j = 0; j<numCols; j++)
		{
			temp.elements[i][j] -= d;
		}
	}
	return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m)
{
	Matrix<T> temp(numRows, m.numCols);
	if (numCols == m.numRows)
	{
		for (int i = 0; i<numRows; i++)
		{
			for (int j = 0; j<m.numCols; j++)
			{
				temp.elements[i][j] = 0;
				for (int k = 0; k<numCols; k++)
				{
					temp.elements[i][j] += elements[i][k] * m.elements[k][j];
				}
			}
		}
	}
	return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator*(T d) const
{
	Matrix<T> temp (*this);
	for (int i = 0; i<numRows; i++)
	{
		for (int j = 0; j<numCols; j++)
		{
			temp.elements[i][j] *= d;
		}
	}
	return temp;
}

template <class T>
Matrix<T> Matrix<T>::operator/(const T d)
{
	if (d != 0)
	{
	Matrix<T> temp (*this);
	for (int i = 0; i<numRows; i++)
	{
		for (int j = 0; j<numCols; j++)
		{
			temp.elements[i][j] /= d;
		}
		return temp;
	}
	}
	return (*this);
}

template <class T>
const Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
	if ( &m != this)
	{
		if (numRows != m.numRows || numCols != m.numCols)
		{
			delete [] elements;
			elements = new T *[m.numRows];
			for (int i = 0; i<m.numRows; i++)
			{
				elements[i] = new T [m.numCols];
			}
			numRows = m.numRows;
			numCols = m.numCols;
			for (int i = 0; i<numRows; i++)
			{
				for (int j = 0; j<numCols; j++)
				{
					elements[i][j] = m.elements[i][j];
				}
			}
		}
		return *this;
	}
	// TODO: insert return statement here
}

template <class T>
const Matrix<T>& Matrix<T>::transpose(void)
{
	if (numRows == numCols)
	{
		T temp;
		for (int i = 0; i<numRows; i++)
		{
			for (int j = i+1; j<numCols; j++)
			{
				temp = elements[i][j];
				elements[i][j] = elements[j][i];
				elements[j][i] = temp;
			}
		}
	}
	else
	{
		Matrix<T> temp(numCols, numRows);
		for (int i = 0; i<numRows; i++)
		{
			for (int j = 0; j<numCols; j++)
			{
				temp.elements[j][j] = elements[i][j];
			}
		}
		*this = temp;
	}
	return *this;
	// TODO: insert return statement here
}

template <class T>
Matrix<T> operator+(T d, Matrix<T> &m)
{
	Matrix<T> temp(m);
	for (int i = 0; i<temp.numRows; i++)
	{
		for (int j = 0; j<temp.numCols; j++)
		{
			temp.elements[i][j] += d;
		}
	}
	return temp;
}

template <class T>
Matrix<T> operator-(T d, Matrix<T>& m)
{
	Matrix<T> temp(m);
	for (int i = 0; i<temp.numRows; i++)
	{
		for (int j = 0; j<temp.numCols; j++)
		{
			temp.elements[i][j] += d;
		}
	}
	return temp;
}

template <class T>
Matrix<T> operator*(const T d, const Matrix<T> &m)
{
	Matrix<T> temp (m);
	for (int i = 0; i<temp.numRows; i++)
	{
		for (int j = 0; j<temp.numCols; j++)
		{
			temp.elements[i][j] *= d;
		}
	}
	return temp;
}

template <class T>
istream& operator>>(istream &is, Matrix<T> &m)
{
	m.input(is);
	return is;
	// TODO: insert return statement here
}

template <class T>
ifstream& operator>>(ifstream &is, Matrix<T> &m)
{
	m.input(is);
	return is;
	// TODO: insert return statement here
}

template <class T>
ostream& operator<<(ostream &os, Matrix<T> &m)
{
	m.output();
	return os;
	// TODO: insert return statement here
}

template <class T>
ofstream& operator<<(ofstream &os, Matrix<T> &m)
{
	m.output(os);
	return os;
	// TODO: insert return statement here
}

int main()
{
	Matrix<int> a(3,3), b(3,3) ,c(3,3);
	cin >> a;
	a.input();
	b.input();
	system("pause");
	a.output();
	c = a+b;
	c.output();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

