#pragma once
#include "akcommon.h"

#define DEFALUT_FS 48000.0

// enum: �񋓌^�i0,1,.. �����l�����蓖�Ă���j
enum FilterType {
	TYPE_THROUGH = 0,
	TYPE_1STHPF,
	TYPE_1STLPF,
	TYPE_EQ,
};

//IIR Filter �W���itypedef��t���Ă����ƁA���struct���ȗ��ł���j�i�\���̂̃����o��;�ŋ�؂�j
typedef struct {
	double a0;
	double a1;
	double a2;
	double b1;
	double b2;
}IIR_FILTER_COEF;

typedef struct {
	double x1;
	double x2;
	double y1;
	double y2;
}IIR_FILTER_DATA;

typedef struct {
	IIR_FILTER_COEF coef;
	IIR_FILTER_DATA data;
}IIR_FILTER_PARA;

class IIRFilter_kino
{
	private:

	public:
		IIRFilter_kino();
		virtual ~IIRFilter_kino();

		int m_filter_num;
		double m_fs;

		IIR_FILTER_PARA* m_filter_para;

		int set_filter_num(int num);
		int set_coef_through(int filtNo);
		int cal_coef_EQ(int filtNo, double fc, double gain, double q);
		int cal_coef_HPF1(int filtNo, double fc);
		int cal_coef_LPF1(int filtNo, double fc);
		int init_filter_para();
		double exec_filter(int filtNo, double inData);
};

