#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 
#include <algorithm> 
#include <map>
#include "CErrorMatrix.h"
#include "Constants.h"
#include <cstdlib>
#include <iomanip>
using namespace std;

template <typename T>
class CMatrix {
public:
	CMatrix();
	CMatrix(int iMSize, int iNSize);
	CMatrix(CMatrix<T>& cOther);
	CMatrix(CMatrix<T>&& cOther);
	~CMatrix();

	bool bCreateMatrix(int iMSize, int iNSize, CErrorMatrix* ccErrorCode);
	void vFillDefMatrix(T tValue);
	void vPrintMatrix();

	bool bReadMatrixFromFile(string sFileName, CErrorMatrix* cErrorCode);
	bool bCreateMatrixFromVector(vector<vector<T>> vTMatrix, CErrorMatrix* cErrorCode);

	T tScalarProduct(CMatrix<T>& tMatrix, CErrorMatrix* cErrorCode);
	CMatrix<T>& cTransposition(CErrorMatrix* cErrorCode);

	bool bIsSquareMatrix() { return iMSize == iNSize; };
	bool bSetIdentityMatrix(CErrorMatrix* cErrorCode);

	CMatrix<T> cColumnVector(int iCol, CErrorMatrix* cErrorCode);
	CMatrix<T> cRowVector(int iRow, CErrorMatrix* cErrorCode);

	int iGetIMSize() { return iMSize; };
	int iGetINSize() { return iNSize; };

	bool bSetValueAt(int iM, int iN, T tNewValue, CErrorMatrix* cErrorCode);
	T tGetValueFrom(int iM, int iN, CErrorMatrix* cErrorCode);

	CMatrix<T>& operator= (const CMatrix<T>& cOther);
	void operator= (CMatrix<T>&& cOther);

	CMatrix<T> cAdd(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode);
	CMatrix<T> cSubstract(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode);
	CMatrix<T> cMultiply(const T tVal);
	CMatrix<T> cMultiply(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode);

	CMatrix<T> operator+ (const CMatrix<T>& cOther);
	CMatrix<T> operator- (const CMatrix<T>& cOther);
	CMatrix<T> operator* (const T tVal);
	CMatrix<T> operator* (const CMatrix<T>& cOther);
	T* operator[] (int iM);

	CMatrix<T>& operator += (const CMatrix<T>& cOther);
	CMatrix<T>& operator -= (const CMatrix<T>& cOther);
	CMatrix<T>& operator *= (const T tVal);
	CMatrix<T>& operator*= (const CMatrix<T>& cOther);
	void operator~();
	
	

private:
	T** pcMatrix;
	int iMSize;
	int iNSize;

	void vDeleteMatrix();
	bool vInitializeMatrix(int iMSize, int iNSize);
	void vCopy(T** tOther);
};

template<typename T>
CMatrix<T>::CMatrix() {
	vInitializeMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
	vFillDefMatrix(DEFAULT_NUMBER_ZERO);
}

template<typename T>
CMatrix<T>::CMatrix(int iMSize, int iNSize) {
	if (!vInitializeMatrix(iMSize, iNSize))
		vInitializeMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
	vFillDefMatrix(DEFAULT_NUMBER_ZERO);
}

template<typename T>
CMatrix<T>::CMatrix(CMatrix<T>& cOther) {
	vDeleteMatrix();
	if (cOther.iMSize > 0 && cOther.iNSize > 0) {
		vCopy(cOther.pcMatrix);
	}
	else
		vInitializeMatrix(DEFAULT_SIZE, DEFAULT_SIZE);
}

template<typename T>
CMatrix<T>::CMatrix(CMatrix<T>&& cOther) {
	iMSize = cOther.iMSize;
	iNSize = cOther.iNSize;
	pcMatrix = cOther.pcMatrix;
	cOther.pcMatrix = NULL;
}

template<typename T>
CMatrix<T>::~CMatrix() {
	vDeleteMatrix();
}

template<typename T>
void CMatrix<T>::vDeleteMatrix() {
	if (pcMatrix != NULL) {
		for (int i = 0; i < iMSize; i++)
			if (pcMatrix[i] != NULL)
				delete[] pcMatrix[i];
		delete[] pcMatrix;
	}
}

template<typename T>
bool CMatrix<T>::vInitializeMatrix(int iMSize, int iNSize) {
	if (iMSize > 0 && iNSize > 0) {
		pcMatrix = new T*[iMSize];
		for (int i = 0; i < iMSize; i++)
			pcMatrix[i] = new T[iNSize];
		this->iMSize = iMSize;
		this->iNSize = iNSize;
		return true;
	}
	return false;
}

template<typename T>
void CMatrix<T>::vFillDefMatrix(T iValue) {
	for (int i = 0; i < iMSize; i++) {
		for (int j = 0; j < iNSize; j++)
			pcMatrix[i][j] = iValue;
	}
}

template<typename T>
void CMatrix<T>::vCopy(T** tOther) {
	iMSize = tOther.iMSize;
	iNSize = tOther.iNSize;

	pcMatrix = new T * [iMSize];
	for (int i = 0; i < iMSize; i++)
		pcMatrix[i] = new T[iNSize];

	for (int i = 0; i < iMSize; i++) 
		for (int j = 0; j < iNSize; j++)
			pcMatrix[i][j] = tOther[i][j];
	
}

template<typename T>
bool CMatrix<T>::bCreateMatrix(int iMSize, int iNSize, CErrorMatrix* cErrorCode) {
	bool flag = false;
	if (iMSize <= 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true; }
	if (iNSize <= 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_N_SIZE); flag = true; }
	if (!flag) {
		vDeleteMatrix();
		if (vInitializeMatrix(iMSize, iNSize))
			vFillDefMatrix(0);
		return true;
	}
	return false;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator=(const CMatrix<T>& cOther) {
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	if (bCreateMatrix(cOther.iMSize, cOther.iNSize, cErrorCode))
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				pcMatrix[i][j] = cOther.pcMatrix[i][j];
	if (cErrorCode->iGetErrorCode() != 0) throw invalid_argument(cErrorCode->sErrorInfo());
	return *this;
}

template<typename T>
void CMatrix<T>::operator=(CMatrix<T>&& cOther) {
	iMSize = cOther.iMSize;
	iNSize = cOther.iNSize;
	pcMatrix = cOther.pcMatrix;
	cOther.pcMatrix = NULL;
}

template<typename T>
bool CMatrix<T>::bSetValueAt(int iM, int iN, T tNewValue, CErrorMatrix* cErrorCode) {
	bool flag = false;
	if (iM < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true; }
	if (iN < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_N_SIZE); flag = true; }
	if (iM >= iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iN >= iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) {
		pcMatrix[iM][iN] = tNewValue;
		return true;
	}
	return false;
}

template<typename T>
T CMatrix<T>::tGetValueFrom(int iM, int iN, CErrorMatrix* cErrorCode) {
	bool flag = false;
	if (iM < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true; }
	if (iN < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_N_SIZE); flag = true; }
	if (iM >= iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iN >= iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) 
		return pcMatrix[iM][iN];
	return numeric_limits<T>::quiet_NaN();
}

template<typename T>
bool CMatrix<T>::bSetIdentityMatrix(CErrorMatrix* cErrorCode) {
	if (!bIsSquareMatrix()) cErrorCode->vSetErrorCode(INVALID_ARGUMENT);
	else {
		vFillDefMatrix(DEFAULT_NUMBER_ZERO);
		for (int i = 0; i < iMSize; i++)
			pcMatrix[i][i] = 1;
		return true;
	}
	return false;
}

template<typename T>
bool bReadMatrixFromFile(string sFileName, CErrorMatrix* cErrorCode){
	vector<vector<T>> vTMatrix;
	ifstream file(sFileName.c_str(), ios_base::in);

	if (!file.is_open()) {
		cErrorCode->vSetErrorCode(INVALID_FILE_NAME);
		return false;
	}
	else {
		string line;
		vector<T> row;
		T data;
		string err;
		while (getline(file, line)) {
			istringstream stringStream(line);
			while (!stringStream.eof()) {
				stringStream >> data;

				if (stringStream.fail()) {
					stringStream.clear();
					stringStream >> err;
					cErrorCode->vSetErrorCode(INCORRECT_VALUE);
					if (err[0] != '.') {
						row.push_back(0);
					}
				}
				else
					row.push_back(data);
			}
			vTMatrix.push_back(row);
			row.clear();
		}
		file.close();
		return bCreateMatrixFromVector(vTMatrix, cErrorCode);
	}
}

template<typename T>
bool CMatrix<T>::bCreateMatrixFromVector(vector<vector<T>> vTMatrix, CErrorMatrix* cErrorCode) {
	if (vTMatrix.size() > 0) {
		map<int, int> mDifColumnLength;
		map<int, int>::iterator iter;

		int iMaxNumOfCol = -1;
		int iNumOfCol;
		int lengthOfRow = 0;

		for (int i = 0; i < vTMatrix.size(); i++) {
			lengthOfRow = vTMatrix[i].size();
			iter = mDifColumnLength.find(lengthOfRow);
			if (iter != mDifColumnLength.end())
				mDifColumnLength[lengthOfRow] = iter->second + 1;
			else mDifColumnLength.insert(pair<int, int>(lengthOfRow, 1));
		}

		if (mDifColumnLength.size() != 1) cErrorCode->vSetErrorCode(INCORRECT_ROW_LENGTH);

		for (iter = mDifColumnLength.begin(); iter != mDifColumnLength.end(); ++iter) {
			if (iter->second > iMaxNumOfCol) {
				iMaxNumOfCol = iter->second;
				iNumOfCol = iter->first;
			}
		}

		if (bCreateMatrix(vTMatrix.size(), iNumOfCol, cErrorCode)) {
			vFillDefMatrix(DEFAULT_NUMBER_ZERO);
			for (int i = 0; i < iMSize; i++)
				for (int j = 0; j < (vTMatrix[i].size() < iNSize ? vTMatrix[i].size() : iNSize); j++)
					pcMatrix[i][j] = vTMatrix[i][j];
			return true;
		}
	}
	else {
		cErrorCode->vSetErrorCode(INCORRECT_VECTOR_SIZE);
		return false;
	}
}

template<typename T>
CMatrix<T> CMatrix<T>::cColumnVector(int iCol, CErrorMatrix* cErrorCode) {
	CMatrix<T> tResultMatrix(iMSize, 1);
	bool flag = false;
	if (iCol < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT); flag = true; }
	if (iCol >= iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE); flag = true; }
	if (!flag)
		for (int i = 0; i < iMSize; i++)
			tResultMatrix[i][0] = pcMatrix[i][iCol];
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T> CMatrix<T>::cRowVector(int iRow, CErrorMatrix* cErrorCode) {
	CMatrix<T> tResultMatrix(1, iNSize);
	bool flag = false;
	if (iRow < 0) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT); flag = true; }
	if (iRow >= iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE); flag = true; }
	if (!flag)
		for (int i = 0; i < iNSize; i++)
			tResultMatrix[0][i] = pcMatrix[iRow][i];
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T>& CMatrix<T>::cTransposition(CErrorMatrix* cErrorCode) {
	bool flag = false;
	if (iMSize < 0) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iNSize < 0) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) {
		CMatrix<T> tResultMatrix(iNSize, iMSize);
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tResultMatrix.pcMatrix[j][i] = pcMatrix[i][j];
		*this = move(tResultMatrix);
	}
	return *this;
}

template<typename T>
T CMatrix<T>::tScalarProduct(CMatrix<T>& tMatrix, CErrorMatrix* cErrorCode) {
	T result = DEFAULT_NUMBER_ZERO;
	bool flag = false;
	if (tMatrix.iGetIMSize() != 1) { cErrorCode->vSetErrorCode(INVALID_ARGUMENT_M_SIZE); flag = true; }
	if (iMSize != 1) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (tMatrix.iGetINSize() != iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) {
		for (int i = 0; i < iNSize; i++)
			result += tGetValueFrom(0, i, cErrorCode) * tMatrix.tGetValueFrom(0, i, cErrorCode);
	}
	return result;
}

template<typename T>
CMatrix<T> CMatrix<T>::cAdd(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode) {
	CMatrix<T> tResultMatrix(iMSize, iNSize);
	bool flag = false;
	if (iMSize != cOther.iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iNSize != cOther.iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) {
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tResultMatrix.pcMatrix[i][j] = pcMatrix[i][j] + cOther.pcMatrix[i][j], cErrorCode;
	}
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix<T>& cOther) {
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tResultMatrix = cAdd(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw invalid_argument(cErrorCode->sErrorInfo());
	delete cErrorCode;
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T> CMatrix<T>::cSubstract(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode) {
	CMatrix<T> tResultMatrix(iMSize, iNSize);
	bool flag = false;
	if (iMSize != cOther.iMSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_M); flag = true; }
	if (iNSize != cOther.iNSize) { cErrorCode->vSetErrorCode(INCORRECT_SIZE_N); flag = true; }
	if (!flag) {
		for (int i = 0; i < iMSize; i++)
			for (int j = 0; j < iNSize; j++)
				tResultMatrix.pcMatrix[i][j] = pcMatrix[i][j] - cOther.pcMatrix[i][j];
	}
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix<T>& cOther) {
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tResultMatrix = cSubstract(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw invalid_argument(cErrorCode->sErrorInfo());
	delete cErrorCode;
	return move(tResultMatrix);
}

template<typename T>
T* CMatrix<T>::operator[](int iM) {
	if (iM < 0) throw invalid_argument("ERROR CODE:" + to_string(INVALID_ARGUMENT));
	if (iM >= iMSize) throw out_of_range("ERROR CODE:" + to_string(INCORRECT_SIZE));
	return pcMatrix[iM];
}

template<typename T>
CMatrix<T> CMatrix<T>::cMultiply(const CMatrix<T>& cOther, CErrorMatrix* cErrorCode) {
	CMatrix<T> tResultMatrix(iMSize, cOther.iNSize);
	if (iNSize != cOther.iMSize) cErrorCode->vSetErrorCode(INCORRECT_SIZE_MULTIPLAYING);
	else {
		for (int i = 0; i < iMSize; i++) {
			for (int j = 0; j < cOther.iNSize; j++) {
				for (int k = 0; k < iNSize; k++)
					tResultMatrix.pcMatrix[i][j] += pcMatrix[i][k] * cOther.pcMatrix[k][j];

			}
		}
	}
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix<T>& cOther) {
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tResultMatrix = cMultiply(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw invalid_argument(cErrorCode->sErrorInfo());
	delete cErrorCode;  
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T> CMatrix<T>::cMultiply(const T tVal) {
	CMatrix<T> tResultMatrix(iMSize, iNSize);
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			tResultMatrix.pcMatrix[i][j] = pcMatrix[i][j] * tVal;
	return move(tResultMatrix);
}

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const T tVal) {
	return cMultiply(tVal);
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator+=(const CMatrix<T>& cOther) {
	if (iMSize != cOther.iMSize) throw invalid_argument("ERROR CODE: " + to_string(INCORRECT_SIZE_M));
	if (iNSize != cOther.iNSize) throw invalid_argument("ERROR CODE: " + to_string(INCORRECT_SIZE_N));
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			pcMatrix[i][j] = pcMatrix[i][j] + cOther.pcMatrix[i][j];
	return *this;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator-=(const CMatrix<T>& cOther) {
	if (iMSize != cOther.iMSize) throw invalid_argument("ERROR CODE: " + to_string(INVALID_ARGUMENT_M_SIZE));
	if (iNSize != cOther.iNSize) throw invalid_argument("ERROR CODE: " + to_string(INVALID_ARGUMENT_N_SIZE));
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			pcMatrix[i][j] = pcMatrix[i][j] - cOther.pcMatrix[i][j];
	return *this;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator*=(const T tVal) {
	for (int i = 0; i < iMSize; i++)
		for (int j = 0; j < iNSize; j++)
			pcMatrix[i][j] = pcMatrix[i][j] * tVal;
	return *this;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator*=(const CMatrix<T>& cOther) {
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	CMatrix<T> tResultMatrix = cMultiply(cOther, cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw invalid_argument(cErrorCode->sErrorInfo());
	*this = move(tResultMatrix);
	delete cErrorCode;
	return *this;
}

template<typename T>
void CMatrix<T>::operator~() {
	CErrorMatrix* cErrorCode = new CErrorMatrix;
	cTransposition(cErrorCode);
	if (cErrorCode->iGetErrorCode() != 0) throw logic_error(cErrorCode->sErrorInfo());
	delete cErrorCode;
}

template<typename T>
void CMatrix<T>::vPrintMatrix() {
	for (int i = 0; i < iMSize; i++) {
		cout << endl;
		for (int j = 0; j < iNSize; j++) {
			cout << setprecision(9);
			cout << pcMatrix[i][j] << " ";
		}
	}
	cout << endl;
}





