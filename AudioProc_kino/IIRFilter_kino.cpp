#include "pch.h"
#include <math.h>
#include "IIRFilter_kino.h"

IIRFilter_kino::IIRFilter_kino() {
	m_filter_num = 0;
	m_filter_para = NULL;
	m_fs = DEFALUT_FS;
}

// デストラクタの定義
IIRFilter_kino::~IIRFilter_kino() {
	if (m_filter_para != NULL) {
		delete[] m_filter_para; // メモリの解放
	}
}

// Filter段数の設定
int IIRFilter_kino::set_filter_num(int num) {
	int ret;

	// エラー処理
	if (num <= 0) {
		return(RET_ERROR_PARA);
	}

	// パラメータの初期化
	if (m_filter_para != NULL) {
		delete[] m_filter_para;
	}

	m_filter_para = new IIR_FILTER_PARA[num];

	if (m_filter_para != NULL) {
		m_filter_num = num;
		ret = RET_SUCCESS;
	}
	else {
		ret = RET_ERROR_PARA;
	}

	return ret;
}

// Filter変数の初期化
int IIRFilter_kino::init_filter_para() {
	int i;

	if (m_filter_num <= 0) {
		return (RET_ERROR_PARA);
	}

	for (i = 0; i < m_filter_num; i++) {
		m_filter_para[i].data.x1 = 0.0;
		m_filter_para[i].data.y1 = 0.0;
		m_filter_para[i].data.x2 = 0.0;
		m_filter_para[i].data.y2 = 0.0;
	}

	return RET_SUCCESS;
}

// Filter係数の計算(EQ)
int IIRFilter_kino::cal_coef_EQ(
	int fltNo,
	double fc,
	double gain,
	double q
) {
	double w0, alpha, tempA;

	if ((fltNo < 0) || (fltNo >= m_filter_num)) {
		return (RET_ERROR_PARA);
	}

	if ((fc == 0) || (fc >= m_fs / 2.0)) {
		return (RET_ERROR_PARA);
	}

	w0 = 2.0 * M_PI * fc / m_fs;
	alpha = sin(w0) / (2.0 * q);
	tempA = sqrt(pow(10.0, gain / 20.0));

	m_filter_para[fltNo].coef.a0 = (1.0 + alpha * tempA) / (1.0 + alpha / tempA);
	m_filter_para[fltNo].coef.a1 = -2.0 * cos(w0) / (1.0 + (alpha / tempA));
	m_filter_para[fltNo].coef.a2 = (1.0 - alpha * tempA) / (1.0 + alpha / tempA);
	m_filter_para[fltNo].coef.b1 = -m_filter_para[fltNo].coef.a1;
	m_filter_para[fltNo].coef.b2 = -(1.0 - alpha / tempA) / (1.0 + alpha / tempA);
}

double IIRFilter_kino::exec_filter(
	int fltNo, double inData
) {
	double y;
	IIR_FILTER_COEF* fltCoef;
	IIR_FILTER_DATA* fltData;

	if ((fltNo < 0) || (fltNo >= m_filter_num)) {
		return 0.0;
	}

	fltCoef = &(m_filter_para[fltNo].coef);
	fltData = &(m_filter_para[fltNo].data);

	y = fltCoef->a0 * inData
		+ fltCoef->a1 * fltData->x1 + fltCoef->b1 * fltData->y1
		+ fltCoef->a2 * fltData->x2 + fltCoef->b2 * fltData->y2;

	fltData->x2 = fltData->x1;
	fltData->y2 = fltData->y1;
	fltData->x1 = inData;
	fltData->y1 = y;

	return y;
}


