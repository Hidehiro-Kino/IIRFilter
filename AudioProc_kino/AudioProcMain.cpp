#include "pch.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "akcommon.h"
#include "IIRFilter_kino.h"

static IIRFilter_kino m_IIRFilter;

extern "C" __declspec(dllexport)int __stdcall set_filter(
	int filterNum,
	int fs) 
{
	int ret;

	m_IIRFilter.m_fs = (double)fs;
	ret = m_IIRFilter.set_filter_num(filterNum);

	return ret;
}

extern "C" __declspec(dllexport)int __stdcall IIR_cal_coef(
	int filterNo,
	int filterType,
	double fc,
	double gain,
	double q) 
{
	int ret;

	ret = m_IIRFilter.cal_coef_EQ(filterNo, fc, gain, q);

	return ret;
}

extern "C" __declspec(dllexport)int __stdcall exec_filter(
	uint32_t length,
	uint8_t * plnData,
	uint8_t * pOutData) {

	int ret = RET_SUCCESS;
	double x;
	int16_t* plnData2;
	int16_t* pOutData2;

	plnData2 = (int16_t*)plnData;
	pOutData2 = (int16_t*)pOutData;

	for (uint32_t i = 0; i < length; i++) {
		x = (double)plnData2[i];
		for (int j = 0; j < m_IIRFilter.m_filter_num; i++) {
			x = m_IIRFilter.exec_filter(j, x);
		}
		pOutData2[i] = (int16_t)round(x);
	}
	return ret;
}
