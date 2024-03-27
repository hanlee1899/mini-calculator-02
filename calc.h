#ifndef __CALC_H_
#define __CALC_H_

#include "queue.h"

int cal_checkSign(char queSign);
int cal_priority(char sign);
int cal_calcur(char stk);
void cal_result(void);
int cal_log_calcur(int len);
int cal_log_calcur_toStack(int len, Que* loop_end);

#endif