#pragma once
#include <iostream>
#include <vector>
#include "Errors.h"
#include <string>
using namespace std;

class CErrorMatrix {
public:
	CErrorMatrix();
	int iGetErrorCode();
	void vSetErrorCode(int iError);
	string sErrorInfo();
	void vClear();

private:
	int iLastErrorCode;
};