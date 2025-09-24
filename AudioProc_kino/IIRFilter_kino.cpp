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