#ifndef __STACK_H_
#define __STACK_H_

typedef struct NumStk {
	double data; 
	struct NumStk* next;
} NumStk;

typedef struct SignStk {
	char data;
	struct SignStk* next;
} SignStk;

void stk_pushNum(double x);
void stk_pushSign(char x);
void stk_popNum(void);
void stk_popSign(void);

#endif