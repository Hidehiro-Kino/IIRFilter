#include "pch.h"
#include <math.h>
#include "IIRFilter_kino.h"

IIRFilter_kino::IIRFilter_kino() {
	m_filter_num = 0;
	m_filter_para = NULL;
	m_fs = DEFALUT_FS;
}

// �f�X�g���N�^�̒�`
IIRFilter_kino::~IIRFilter_kino() {
	if (m_filter_para != NULL) {
		delete[] m_filter_para; // �������̉��
	}
}

// Filter�i���̐ݒ�
int IIRFilter_kino::set_filter_num(int num) {
	int ret;

	// �G���[����
	if (num <= 0) {
		return(RET_ERROR_PARA);
	}

	// �p�����[�^�̏�����
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