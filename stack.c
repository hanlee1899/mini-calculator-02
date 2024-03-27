#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

extern NumStk* topN;
extern SignStk* topS;

void stk_pushNum(double x) {
	if (topN == NULL) {
		NumStk* tmp_num = (NumStk*) malloc(sizeof(NumStk));
		
		tmp_num->data = x;
		tmp_num->next = NULL;
		topN = tmp_num;
	} else {
		NumStk* tmp_num = (NumStk*) malloc(sizeof(NumStk));
		
		tmp_num->data = x;
		tmp_num->next = topN;
		topN = tmp_num;
	}
}

void stk_pushSign(char x) {
	if (topS == NULL) {
		SignStk* tmp_sign = (SignStk*) malloc(sizeof(SignStk));
		
		tmp_sign->data = x;
		tmp_sign->next = NULL;
		topS = tmp_sign;
	} else {
		SignStk* tmp_sign = (SignStk*) malloc(sizeof(SignStk));
		
		tmp_sign->data = x;
		tmp_sign->next = topS;
		topS = tmp_sign;
	}
}

void stk_popNum(void) {
	NumStk* del;
	
	del = topN;
	topN = topN->next;
	free(del);
}

void stk_popSign(void) {
	SignStk* del;
	
	del = topS;
	topS = topS->next;
	free(del);
}