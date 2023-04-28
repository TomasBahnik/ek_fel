/*** PPC - HW03 ***/
/* Tento soubor se odevzdava. Zde implementujte vsechny potrebne funkce */

#include "matrix.hpp"

using namespace std;

/*** CONSTRUCTORS & DESTRUCTOR ***/
Matrix::Matrix(int nrow, int ncol)
{

}

Matrix::Matrix(int rowscols)
{

}

Matrix::Matrix(const Matrix &m)
{

}

Matrix::Matrix(const std::vector<value> &v)
{

}

Matrix::~Matrix()
{

}

/*** L1 Matrix:: FUNCTIONS ***/
void Matrix::zeros()
{

}

void Matrix::uniform(value element)
{

}

void Matrix::eye()
{

}

void Matrix::bias(value b)
{

}

/*** L2 Matrix:: FUNCTIONS ***/
void Matrix::scale(value s)
{

}

void Matrix::transpose()
{

}

/*** L3 Matrix:: FUNCTIONS ***/
void Matrix::changedim(int rows, int cols)
{

}

/*** L1 Matrix:: Operators ***/
value Matrix::operator () (int row, int col) const
{
 
}

value & Matrix::operator () (int row, int col)
{

}

bool Matrix::operator==(const Matrix &m)
{
 
}

Matrix & Matrix::operator=(const Matrix &m)
{

}

/*** L3 Matrix:: Operators ***/
std::vector<value> Matrix::operator () (void) const
{
 
}


/*** L1 NON-MEMBER FUNCTIONS/OPERATORS ***/
std::ostream & operator<<(std::ostream &os, const Matrix &m)
{

}

void loadMatrixFile(Matrix & m, string fname)
{

}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{

}

Matrix operator+(const value & lhs, const Matrix &rhs)
{

}

Matrix operator+(const Matrix &lhs, const value & rhs) 
{

}

Matrix operator-(const Matrix &lhs, const Matrix &rhs)
{
 
}

Matrix operator-(const value & lhs, const Matrix &rhs)
{

}

Matrix operator-(const Matrix &lhs, const value & rhs) 
{

}

/*** L2 NON-MEMBER FUNCTIONS/OPERATORS ***/

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{

}

Matrix operator*(const value & lhs, const Matrix &rhs)
{

}

Matrix operator*(const Matrix &lhs, const value & rhs) 
{

}

Matrix hadamard(const Matrix &lhs, const Matrix &rhs)
{

}

Matrix power(const Matrix &m, unsigned int pow)
{

}

/*** L3 NON-MEMBER FUNCTIONS/OPERATORS ***/
Matrix horzcat(const Matrix &lhs, const Matrix &rhs)
{

}

Matrix vertcat(const Matrix &top, const Matrix &bot)
{
 
}

Matrix blkdiag (const Matrix & lhs, const Matrix & rhs)
{

}

Matrix blkdiag (const value & lhs, const Matrix & rhs) 
{

}

Matrix blkdiag (const Matrix & lhs, const value & rhs) 
{

}

Matrix blkdiag (const value & lhs, const value & rhs) 
{

}

Matrix kronecker(const Matrix &lhs, const Matrix &rhs)
{

}



