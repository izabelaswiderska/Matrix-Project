#pragma once
#include "CErrorMatrix.h"

CErrorMatrix::CErrorMatrix() {
	iLastErrorCode = NO_ERROR;
}

int CErrorMatrix::iGetErrorCode() {
	return iLastErrorCode;
}

void CErrorMatrix::vSetErrorCode(int iError) {
	iLastErrorCode = iError;
}

string CErrorMatrix::sErrorInfo() {
	return "ERROR CODE: " + to_string(iLastErrorCode);
}

void CErrorMatrix::vClear() {
	iLastErrorCode = NO_ERROR;
}


