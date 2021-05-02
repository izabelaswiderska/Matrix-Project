#pragma once
#include <iostream>
#include <vector>
#include "CMatrix.h"
using namespace std;

CMatrix<int> ciMatrix1(3, 4);
CMatrix<int> ciMatrix2(3, 4);
CMatrix<int> ciMatrix3(4, 2);
CMatrix<int> ciMatrix4(1, 3);
CMatrix<int> ciMatrix5(1, 3);

CMatrix<double> cdMatrix1(3, 4);
CMatrix<double> cdMatrix2(3, 4);
CMatrix<double> cdMatrix3(4, 2);
CMatrix<double> cdVector1(1, 3);
CMatrix<double> cdVector2(1, 3);

CErrorMatrix* errorCode = new CErrorMatrix;

void printErrorCode() {
	if (errorCode->iGetErrorCode() != NO_ERROR)
		cout << "Error Code: " << errorCode->iGetErrorCode() << endl;;
}

void CreateMatrix() {
	cout << "--CONSTRUCTOR TEST--" << endl;
	CMatrix<int> newCiMatrix1;
	CMatrix<int> newCiMatrix2(-1, -5);
	CMatrix<double> newCdMatrix1;
	CMatrix<double> newCdMatrix2(-1, -5);

	cout << "Default Constructor for int" << endl;
	newCiMatrix1.vPrintMatrix();
	cout << endl;

	cout << "Matrix int -1 x -5" << endl;
	newCiMatrix2.vPrintMatrix();
	cout << endl;

	cout << "Default Constructor for double" << endl;
	newCdMatrix1.vPrintMatrix();
	cout << endl;

	cout << "Matrix double -1 x -5" << endl;
	newCdMatrix2.vPrintMatrix();
	cout << endl;

	cout << "Matrix created from default Matrix double : 6 x 6			 ";
	cout << newCdMatrix1.bCreateMatrix(6, 6, errorCode) << endl;;
	newCdMatrix1.vPrintMatrix();
	printErrorCode();
	cout << endl;

	cout << "Matrix created from default Matrix int : -3 x -3		 ";
	cout << newCiMatrix1.bCreateMatrix(-3, -3, errorCode) << endl;;
	newCiMatrix1.vPrintMatrix();
	printErrorCode();
	cout << endl;
}

void FillGetSetMatrix() {
	cout << endl << "--FILL MATRIX, GET/SET ELEMENT  TEST--" << endl;
	ciMatrix1.vFillDefMatrix(1);
	ciMatrix2.vFillDefMatrix(2);
	ciMatrix3.vFillDefMatrix(3);

	cout << endl << "Matrix1 int" << endl;
	ciMatrix1.vPrintMatrix();
	cout << endl << "Matrix2 int" << endl;
	ciMatrix2.vPrintMatrix();
	cout << endl << "Matrix3 int" << endl;
	ciMatrix3.vPrintMatrix();

	cdMatrix1.vFillDefMatrix(1.1);
	cdMatrix2.vFillDefMatrix(2.2);
	cdMatrix3.vFillDefMatrix(3.3);

	cout << endl << "Matrix1 double" << endl;
	cdMatrix1.vPrintMatrix();
	cout << endl << "Matrix2 double" << endl;
	cdMatrix2.vPrintMatrix();
	cout << endl << "Matrix3 double" << endl;
	cdMatrix3.vPrintMatrix();

	errorCode->vSetErrorCode(NO_ERROR); 
	cout << endl << "set Matrix1[1][1] = 5	int" << endl;
	ciMatrix1[1][1] = 5;
	printErrorCode();
	ciMatrix1.vPrintMatrix();

	cout << endl << "set Matrix2[2][2] = 7	int" << endl;
	ciMatrix2.bSetValueAt(2, 2, 7, errorCode);
	printErrorCode();
	ciMatrix2.vPrintMatrix();

	cout << endl << "set Matrix3[8][8] = 5	int" << endl;
	ciMatrix3.bSetValueAt(8, 8, 5, errorCode);
	printErrorCode();
	ciMatrix3.vPrintMatrix();


	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "set Matrix1[1][1] = 5.5	double" << endl;
	cdMatrix1[1][1] = 5.5;
	printErrorCode();
	cdMatrix1.vPrintMatrix();
	cout << endl <<  "set Matrix2[2][2] = 7.7	double " << endl;
	cdMatrix2.bSetValueAt(2, 2, 7.7, errorCode);
	printErrorCode();
	cdMatrix2.vPrintMatrix();

	cout << endl << "set Matrix3[8][8] = 5.5	double " << endl;
	cdMatrix3.bSetValueAt(8, 8, 5.5, errorCode);
	printErrorCode();
	cdMatrix3.vPrintMatrix();

	cout << endl << "set Matrix3[-1][-1] = 5.5	 double " << endl;
	cdMatrix3.bSetValueAt(-1, -1, 5.5, errorCode);
	printErrorCode();
	cdMatrix3.vPrintMatrix();

	try {
		cout << endl << "Matrix1-int[1][1]\n" << ciMatrix1[1][1] << endl;
	}
	catch (out_of_range e) {
		cout << e.what() << endl;
	}
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix2-int getVal from 2, 2 \n" << ciMatrix2.tGetValueFrom(2, 2, errorCode) << endl;
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix3-int getVal from 9, 9	\n" << ciMatrix3.tGetValueFrom(9, 9, errorCode) << endl;
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix2-int getVal from 15, 4	\n" << ciMatrix2.tGetValueFrom(15, 4, errorCode) << endl;
	printErrorCode();
	ciMatrix3.vPrintMatrix();

	try {
		cout << endl << "Matrix1-double[1][1] \n" << cdMatrix1[1][1] << endl;
	}
	catch (out_of_range e) {
		cout << e.what() << endl;
	}
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix2-double getVal from 2, 2 \n" << cdMatrix2.tGetValueFrom(2, 2, errorCode) << endl;
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix2-double getVal from 6, 8 \n" << cdMatrix2.tGetValueFrom(6, 8, errorCode) << endl;
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix3-double getVal from 10, 10 \n" << cdMatrix3.tGetValueFrom(10, 10, errorCode) << endl;
	printErrorCode();
}

void ScalarProduct() {
	cout << endl << "--SCALAR PRODUCT TEST--" << endl;

	cout << endl << "Scalar product matrix1 and matrix2" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	ciMatrix1.vFillDefMatrix(2);
	ciMatrix2.vFillDefMatrix(3);
	cout << "Matrix1" << endl;
	ciMatrix1.vPrintMatrix();
	cout << endl << "Matrix2 " << endl;
	ciMatrix2.vPrintMatrix();
	cout << "scalar m1 m2: " << ciMatrix1.tScalarProduct(ciMatrix2, errorCode) << endl;
	printErrorCode();

	cout << endl << "Scalar product matrix4 and matrix5" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	ciMatrix4.vFillDefMatrix(2);
	ciMatrix5.vFillDefMatrix(3);
	cout << "Matrix4" << endl;
	ciMatrix4.vPrintMatrix();
	cout << endl << "Matrix5 " << endl;
	ciMatrix5.vPrintMatrix();
	cout << "scalar m4 m5: " << ciMatrix4.tScalarProduct(ciMatrix5, errorCode) << endl;
	printErrorCode();
}

void SetIdentyMatrix() {
	cout << endl << "--SET IDENTITY MATRIX TEST--" << endl;
	CMatrix<int>* intMatrix1 = new  CMatrix<int>(3, 3);
	CMatrix<int>* intMatrix2 = new  CMatrix<int>(3, 2);
	intMatrix1->vFillDefMatrix(2);
	intMatrix2->vFillDefMatrix(2);

	cout << endl << "Matrix1 int 3x3" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	intMatrix1->vPrintMatrix();
	intMatrix1->bSetIdentityMatrix(errorCode);
	cout << endl << "Identity Matrix from Matrix1" << endl;
	intMatrix1->vPrintMatrix();
	printErrorCode();

	cout << endl << "Matrix2 int 3x2" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	intMatrix2->vPrintMatrix();
	intMatrix2->bSetIdentityMatrix(errorCode);
	cout << endl << "Identity Matrix from Matrix2" << endl;
	intMatrix2->vPrintMatrix();
	printErrorCode();

	delete intMatrix1;
	delete intMatrix2;
}

void vectorFromCol() {
	cout << "--COLUMN VECTOR TEST--" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix1" << endl;
	ciMatrix1.bSetValueAt(2, 0, 1, errorCode);
	ciMatrix1.bSetValueAt(2, 1, 2, errorCode);
	ciMatrix1.bSetValueAt(2, 2, 3, errorCode);
	ciMatrix1.vPrintMatrix();
	cout << endl;
	cout << "vector from 2 column" << endl;
	ciMatrix1.cColumnVector(2, errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
	cout << "vector from 4 column" << endl;
	ciMatrix1.cColumnVector(4, errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
}

void vectorFromRow() {
	cout << "--ROW VECTOR TEST--" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "Matrix1" << endl;
	ciMatrix1.bSetValueAt(2, 0, 1, errorCode);
	ciMatrix1.bSetValueAt(2, 1, 2, errorCode);
	ciMatrix1.bSetValueAt(2, 2, 3, errorCode);
	ciMatrix1.vPrintMatrix();
	cout << endl;
	cout << "vector from 2 row" << endl;
	ciMatrix1.cRowVector(2, errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
	cout << "vector from 4 row" << endl;
	ciMatrix1.cRowVector(4, errorCode).vPrintMatrix();
	printErrorCode();
	cout << endl;
}

void Transpose() {
	cout << "--TRANSPOSE MATRIX TEST--" << endl;
	CMatrix<float> cfMatrix(4, 2);
	cfMatrix.vFillDefMatrix(3.1);
	cfMatrix[1][1] = 5.5;
	cfMatrix[2][1] = 1.5;
	cfMatrix[1][2] = 7.5;
	cout << endl <<"Matrix float" << endl;
	cfMatrix.vPrintMatrix();
	cout << endl << "Matrix after transposition " << endl;
	cfMatrix.cTransposition(errorCode).vPrintMatrix();

	CMatrix<int> ciMatrix(3, 7);
	ciMatrix[0][0] = 5;
	ciMatrix[2][5] = 3;
	ciMatrix[1][6] = 7;
	cout << endl << "Matrix int" << endl;
	ciMatrix.vPrintMatrix();
	cout << endl << "Matrix after transposition " << endl;
	ciMatrix.cTransposition(errorCode).vPrintMatrix();


	//cout << endl << "Matrix after transposition operator~" << endl;
	//~cfMatrix;
	//cfMatrix.vPrintMatrix();
}

void Operators() {
	cout << "--OPERATORS TEST--" << endl;
	ciMatrix1.vFillDefMatrix(1);
	ciMatrix2.vFillDefMatrix(2);
	ciMatrix3.vFillDefMatrix(3);
	cdMatrix1.vFillDefMatrix(1.1);
	cdMatrix2.vFillDefMatrix(2.2);
	cdMatrix3.vFillDefMatrix(3.3);

	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "matrix1" << endl; ciMatrix1.vPrintMatrix();
	cout << endl << "matrix2" << endl; ciMatrix2.vPrintMatrix();
	cout << endl << "matrix3" << endl; ciMatrix3.vPrintMatrix();
	cout << endl << "ADD" << endl;
	cout << "Operator 1+2" << endl;
	try {
		(ciMatrix1 + ciMatrix2).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << endl << "Add method 1.cAdd(2) " << endl;
	(ciMatrix1.cAdd(ciMatrix2, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();
	cout << endl << "Operator 1 + 3 " << endl;
	try {
		(ciMatrix1 + ciMatrix3).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << endl << "Add method 1.cAdd(3) " << endl;
	(ciMatrix1.cAdd(ciMatrix3, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "SUBSTRACT" << endl;
	cout << "Operator 1 - 2" << endl;
	try {
		(ciMatrix1 - ciMatrix2).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << "Sub method 1.cSub(2)" << endl;
	(ciMatrix1.cSubstract(ciMatrix2, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	cout << "Operator 1 - 3" << endl;
	try {
		(ciMatrix1 - ciMatrix3).vPrintMatrix(); cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	cout << "Sub method 1.cSub(3)" << endl;
	errorCode->vSetErrorCode(NO_ERROR);
	(ciMatrix1.cSubstract(ciMatrix3, errorCode)).vPrintMatrix(); cout << endl;
	printErrorCode();

	cout << "MULTIPLY BY NUMBER" << endl;
	cout << endl << "matrix1";
	ciMatrix1.vPrintMatrix();
	cout << endl << "matrix1 after matrix1 * 4";
	ciMatrix1 = ciMatrix1 * 4;
	ciMatrix1.vPrintMatrix();
	cout << endl << "matrix1 after ciMatrix1.cMultiply(6)";
	ciMatrix1 = ciMatrix1.cMultiply(6);
	ciMatrix1.vPrintMatrix();


	cout << "MULTIPLY" << endl;

	CMatrix<int> ciMatrix7(4, 3);
	ciMatrix7.vFillDefMatrix(5);
	CMatrix<int> ciMatrix8(3, 4);
	ciMatrix8.vFillDefMatrix(3);
	cout << endl << "matrix7";
	ciMatrix7.vPrintMatrix();
	cout << endl << "matrix8";
	ciMatrix8.vPrintMatrix();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl <<  "matrix7* matrix8";
	try {
		(ciMatrix7.cMultiply(ciMatrix8, errorCode).vPrintMatrix());  cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	printErrorCode();

	CMatrix<int> ciMatrix9(3, 4);
	ciMatrix9.vFillDefMatrix(5);
	CMatrix<int> ciMatrix10(2, 5);
	ciMatrix10.vFillDefMatrix(3);
	cout << endl << "matrix9";
	ciMatrix9.vPrintMatrix();
	cout << endl << "matrix10";
	ciMatrix10.vPrintMatrix();
	errorCode->vSetErrorCode(NO_ERROR);
	cout << endl << "matrix9* matrix10";
	try {
		(ciMatrix9.cMultiply(ciMatrix10, errorCode).vPrintMatrix());  cout << endl;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	printErrorCode();


	cout << "operator []:" << endl;
	ciMatrix1.bSetValueAt(1, 1, 7, errorCode);
	ciMatrix1.bSetValueAt(2, 1, 5, errorCode);
	ciMatrix1.vPrintMatrix();
	cout << "elem[1][1] " << ciMatrix1[1][1] << endl;
	cout << "elem[2][1] " << ciMatrix1[2][1] << endl;
	try {
		cout << "elem[3][1] " << ciMatrix1[3][1] << endl;
	}
	catch (out_of_range e) {
		cout << e.what() << endl;
	}

	/*
	cout << "OPERATOR -=" << endl;
	cout << "1-2" << endl;
	try {
		ciMatrix1 -= ciMatrix2;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	ciMatrix1.vPrintMatrix(); cout << endl;
	cout << "1-3" << endl;
	try {
		ciMatrix1 -= ciMatrix3;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}

	cout << "OPERATOR +=" << endl;
	cout << "1+2" << endl;
	try {
		ciMatrix1 += ciMatrix2;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	ciMatrix1.vPrintMatrix(); cout << endl;
	cout << "1+3" << endl;
	try {
		ciMatrix1 += ciMatrix3;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}

	cout << "operator *=" << endl;
	cout << "1 * 3" << endl;
	try {
		ciMatrix1 *= ciMatrix3;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	ciMatrix1.vPrintMatrix(); cout << endl;
	cout << "1 * 2" << endl;
	try {
		ciMatrix1 *= ciMatrix2;
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}

	cout << "MULTIPLY MATRIX BY CONST 2:" << endl;
	(ciMatrix1 * 2).vPrintMatrix();
	cout << endl;
	(ciMatrix1.cMultiply(2)).vPrintMatrix();
	cout << endl;
	ciMatrix1 *= 2;
	cout << endl;
	ciMatrix1.vPrintMatrix();
	*/
	
}

void ReadFromFIle() {
	cout << "--READ MATRIX FROM FILE TEST--" << endl;
	errorCode->vSetErrorCode(NO_ERROR);

	CMatrix<int> iMatrix;
	CMatrix<double> dMatrix;



	cout << endl << "Read File that doesn't exist" << endl;
	iMatrix.bReadMatrixFromFile("AAA.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	printErrorCode();

	cout << endl << "Read FileIntCorect" << endl;
	iMatrix.bReadMatrixFromFile("FileIntCorect.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileDoubleCorect" << endl;
	dMatrix.bReadMatrixFromFile("FileDoubleCorect.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileDoubleCorect into int matrix" << endl;
	iMatrix.bReadMatrixFromFile("FileDoubleCorect.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileIntCorect into double matrix" << endl;
	dMatrix.bReadMatrixFromFile("FileIntCorect.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileIntMissingElement" << endl;
	iMatrix.bReadMatrixFromFile("FileIntMissingElement.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	
	cout << endl << "Read FileDoubleMissingElement" << endl;
	dMatrix.bReadMatrixFromFile("FileDoubleMissingElement.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileIntWeirdSigns" << endl;
	iMatrix.bReadMatrixFromFile("FileIntWeirdSigns.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileIntWithEmptyLine" << endl;
	iMatrix.bReadMatrixFromFile("FileIntWithEmptyLine.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileWithDifSpaces" << endl;
	iMatrix.bReadMatrixFromFile("FileWithDifSpaces.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileString" << endl;
	iMatrix.bReadMatrixFromFile("FileString.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileIntWithWrongArg" << endl;
	iMatrix.bReadMatrixFromFile("FileIntWithWrongArg.txt", errorCode);
	iMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileDoubleWithWrongArg" << endl;
	dMatrix.bReadMatrixFromFile("FileDoubleWithWrongArg.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read EmptyFile" << endl;
	dMatrix.bReadMatrixFromFile("EmptyFile.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	cout << endl << "Read FileIntSignsNotSpaces" << endl;
	dMatrix.bReadMatrixFromFile("FileIntSignsNotSpaces.txt", errorCode);
	dMatrix.vPrintMatrix();
	printErrorCode();
	errorCode->vSetErrorCode(NO_ERROR);

	

	

}

void MatrixTest() {
	Operators();
	CreateMatrix();
	vectorFromCol();
	vectorFromRow();
	ScalarProduct();
	SetIdentyMatrix();
	Transpose();
	FillGetSetMatrix();
	ReadFromFIle();
}

int main(int argc, char* argv[]) {
	MatrixTest();
}