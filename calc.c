#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "queue.h"
#include "stack.h"

extern NumStk* topN;
extern SignStk* topS;
extern Que* front;
extern Que* rear;

int cal_checkSign(char queSign) {
	int stk;
	int q;
	int calcur_signal = 0;

	if (queSign == ')') {
		while (topS->data != '(') {
			calcur_signal = cal_calcur(topS->data);

			if (calcur_signal == 1) {
				return 1;
			}
		}

		stk_popSign();
		return 0;
	}

	if (topS == NULL) {
		stk_pushSign(queSign);
		return 0;
	} else {
		stk = cal_priority(topS->data);
		q = cal_priority(queSign);
	}

	if (stk >= q) {
		if (topS->data == '(') {
			stk_pushSign(queSign);
			return 0;
		} else {
			calcur_signal = cal_calcur(topS->data);

			if (calcur_signal == 1) {
				return 1;
			}

			stk_pushSign(queSign);
		}
	} else {
		stk_pushSign(queSign);
	}

	return 0;
}

int cal_priority(char opt) {
	switch (opt) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
		case '^':
			return 2;
		case '(':
		case ')':
			return 3;
	}
}

int cal_calcur(char opt) {
	double result = 1.0;

	if (opt == '+') {
		result = topN->next->data + topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '-') {
		result = topN->next->data - topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '*') {
		result = topN->next->data * topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '/') {
		if (topN->data == 0) {
			printf("Divided by zero\n\n");

			while (topN != NULL) {
				stk_popNum();
			}

			while (topS != NULL) {
				stk_popSign();
			}

			return 1;
		}

		result = topN->next->data / topN->data;
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '%') {
		if (topN->data == 0) {
			printf("Modulo by zero\n\n");

			while (topN != NULL) {
				stk_popNum();
			}

			while (topS != NULL) {
				stk_popSign();
			}

			return 1;
		}

		result = fmod(topN->next->data, topN->data);
		stk_popSign();
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	} else if (opt == '^') {
		for (int i = 0; i < topN->data; i++) {
			result *= topN->next->data;
		}

		stk_popSign();	
		stk_popNum();
		stk_popNum();
		stk_pushNum(result);
		return 0;
	}
}

void cal_result(void) {
	if (topN == NULL) {
		return;
	} else {
		if (topN->data == 0) {
			topN->data = 0;
		}

		printf("result: %.2lf\n\n", topN->data);
		stk_popNum();
	}
}

int cal_log_calcur(int len) {
	int return_signal = 0;
	double data_from_log;
	int open_cnt = 0;
	int close_cnt = 0;
	Que* cur;
	Que* end;

	if (front->data == '2') {
		que_deQueue();
		cur = front;

		while (1) {
			if (cur->data == '(') {
				open_cnt++;
			}

			if (cur->data == ')') {
				close_cnt++;
			}

			if (open_cnt == close_cnt) {
				end = cur;
				break;
			}

			cur = cur->next;
		}

		return_signal = cal_log_calcur_toStack(len, end);
		
		if (return_signal == 1) {
			while (front != NULL) {
				que_deQueue();
			}

			return 1;
		}

		if (topN->data <= 0) {
			printf("log의 진수부분은 0보다 커야 합니다. 현재 log 입력상황 : log2(%.2lf)\n\n", topN->data);
			
			while (topN != NULL) {
				stk_popNum();
			}

			while (topS != NULL) {
				stk_popSign();
			}

			while (front != NULL) {
				que_deQueue();
			}

			return 1;
		}

		data_from_log = log2(topN->data);
		stk_popNum();
		stk_pushNum(data_from_log);
		return 0;
	}

	if (front->data == '1') {
		que_deQueue();
		que_deQueue();
		cur = front;

		while (1) {
			if (cur->data == '(') {
				open_cnt++;
			}

			if (cur->data == ')') {
				close_cnt++;
			}

			if (open_cnt == close_cnt) {
				end = cur;
				break;
			}

			cur = cur->next;
		}

		return_signal = cal_log_calcur_toStack(len, end);
		
		if (return_signal == 1) {
			while (front != NULL) {
				que_deQueue();
			}

			return 1;
		}

		if (topN->data <= 0) {
			printf("log의 진수부분은 0보다 커야 합니다. 현재 log 입력상황 : log10(%.2lf)\n\n", topN->data);
			
			while (topN != NULL) {
				stk_popNum();
			}

			while (topS != NULL) {
				stk_popSign();
			}

			while (front != NULL) {
				que_deQueue();
			}

			return 1; 
		}

		data_from_log = log10(topN->data);
		stk_popNum();
		stk_pushNum(data_from_log);
		return 0;
	}
}

int cal_log_calcur_toStack(int len, Que* loop_end) {
	char toStack[len];
	int cnt = 0;
	int checksign_signal = 0;
	int unary_operator_signal = 0;
	int cal_log_signal = 0;

	for (int i = 0; i < len; i++) {
		toStack[i] = '\0';
	}

	while (1) {
		if ((front->data >= '0' && front->data <= '9') || front->data == '.') { 
			toStack[cnt++] = front->data;
			que_deQueue();

			if (front->data == ' ' || front->data == '+'
			|| front->data == '-' || front->data == '*'
			|| front->data == '/' || front->data == '%'
			|| front->data == '^' || front->data == ')') {
				stk_pushNum(atof(toStack));
				cnt = 0;

				for (int i = 0; i < len; i++) {
					toStack[i] = '\0';
				}
			}
		}

		if (front->data == '(' && (front->next->data == '+' || front->next->data == '-')) {
			unary_operator_signal = que_unary_operator(len);

			if (unary_operator_signal == 1) {
				while (front != NULL) {
					que_deQueue();
				}

				return 1;
			}
		}

		if (front->data == '+' || front->data == '-'
		|| front->data == '*' || front->data == '/'
		|| front->data == '%' || front->data == '^'
		|| front->data == '(' || front->data == ')') { 
			checksign_signal = cal_checkSign(front->data);

			if (checksign_signal == 1) {
				return 1;
			}

			if (front == loop_end) {
				que_deQueue();
				return 0;
			}

			que_deQueue();
		}

		if (front->data == 'l') {
			que_deQueue();
			que_deQueue();
			que_deQueue();
			cal_log_signal = cal_log_calcur(len);

			if (cal_log_signal == 1) {
				return 1;
			}
		}	
	}
}