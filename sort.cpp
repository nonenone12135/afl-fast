#include "sort.h"

//****************************************************
//Sort


Sort::~Sort()
{

}

u8 Sort::on_new_seed_generate(struct queue_entry *queue, struct queue_entry *q)
{
	//父类中有声明,有定义
	return 1;
}

//****************************************************

//----------------------------------------------------


//****************************************************
//1
u8 Random_Sort::aa(){
	return 1;
}
//end 1
//----------------------------------------------------



//****************************************************
//7
u8 Short_by_hamming::on_new_seed_generate(struct queue_entry *queue, struct queue_entry *q){
	//子类中,对于要覆盖的函数,有声明,有定义
	return 0;
}

//end 7
//----------------------------------------------------

//函数
double cal_two_input(struct queue_entry *qmin,struct queue_entry *qmax)
{
	// bitmap_size 基本块数量
	if (!qmin->trace_mini)
	{
		//		char msg[512];
		//		sprintf(msg, "Cannot find mini trace for %s\n", x->fname);
		//		fputs(msg, afl_log_file);
		return 0;
	}

	if (!qmax->trace_mini)
	{
		//		char msg[512];
		//		sprintf(msg, "Cannot find mini trace for %s\n", y->fname);
		//		fputs(msg, afl_log_file);
		return 0;
	}

	double dot = 0.0;

	for (unsigned int i = 0u; i < (MAP_SIZE >> 3); i++)
	{
		if (qmin->trace_mini[i] + qmax->trace_mini[i] == 1) //0表示没有元组关系,1表示有
		{
			dot++;
		}
		//		denom_a += Qa->trace_mini_persist[i] * Qa->trace_mini_persist[i];
		//		denom_b += Qb->trace_mini_persist[i] * Qb->trace_mini_persist[i];
	}

	return dot;
}
