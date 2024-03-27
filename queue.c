#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "queue.h"
#include "stack.h"

extern NumStk* topN;
extern SignStk* topS;
extern Que* front;
extern Que* rear;

void que_enQueue(char x) {
	if (front == NULL && rear == NULL) {
		Que* tmp = (Que*) malloc(sizeof(Que));
		
		tmp->next = NULL;
		tmp->data = x;
		front = tmp;
		rear = tmp;
	} else {
		Que* tmp = (Que*) malloc(sizeof(Que));
		
		tmp->next = NULL;
		tmp->data = x;
		rear->next = tmp;
		rear = tmp;
	}
}

void que_deQueue(void) {
	Que* del;

	del = front;
	front = front->next;
	
	if (front == NULL) {
		rear = NULL;
	}

	free(del);
}

void que_deQueue_space(Que* where) {
	Que* del_before;
	Que* del_where;

	del_before = where;
	del_where = where->next;
	del_before->next = del_where->next;
	
	if (del_where->next == NULL) {
		rear = del_before;
	}

	free(del_where);
}

void que_check_grammar(void) {
	int sign = 0;
	int open_bracket = 0;
	int close_bracket = 0;
	int error_openclose = 0;
	int num_signal = 0;
	int opt_signal = 0;
	int space_signal = 0;
	int error_cnt = 0;
	Que* check;
	Que* check_n1;
	Que* check_n2;

	check = front;

	while (check->next != NULL) {
		if (check->next->data == ' ') {
			space_signal++;
			que_deQueue_space(check);
		} else {
			check = check->next;
		}
	}

	if (front->data == ' ') {
		space_signal++;
		que_deQueue();
	}

	check = front;
	
	while (check != NULL) {
		error_cnt++;

		if (check->data == '(') {
			open_bracket++;
		}

		if (check->data == ')') {
			close_bracket++;
		}

		if (check->data >= '0' && check->data <= '9') {
			num_signal++;
		}

		if (check->data == '+' || check->data == '-'
		|| check->data == '*' || check->data == '/'
		|| check->data == '%' || check->data == '^'
		|| check->data == '(' || check->data == ')') {
			opt_signal++;
		}

		if (error_openclose == 0 && open_bracket < close_bracket) {
			printf("[Error] : 닫는 괄호가 여는 괄호보다 먼저일 수 없습니다.\n");
			printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
			sign++;
			error_openclose = 1;
		}

		if (check == rear) {
			if (check->data == '+' || check->data == '-'
			|| check->data == '*' || check->data == '/'
			|| check->data == '%' || check->data == '^'
			|| check->data == '(' || check->data == 'l'
			|| check->data == 'o' || check->data == 'g'
			|| check->data == '.') {
				printf("[Error] : 마지막 입력 데이터는 숫자이거나, 닫힌 괄호이어야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
				sign++; 
			}
		}

		if (check == front) {
			if (check->data == '*' || check->data == '/'
			|| check->data == '%' || check->data == '^'
			|| check->data == 'o' || check->data == 'g'
			|| check->data == '.') {
				printf("[Error] : 수식의 시작은 열린 괄호이거나, 숫자, log의 l, 단항연산자이어야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째,    오류 부분 : %c\n\n", error_cnt, check->data);
				sign++; 
			} 
		}

		if (check->next != NULL) {
			if (((check->data >= '0' && check->data <= '9') || check->data == '.') && check->next->data == 'l') {
				printf("[Error] : log 의 l 전에는 열린 괄호와 계산 연산자만 입력되어야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt, error_cnt + 1, check->next->data);
				sign++;
			}

			if (check->data == 'l' && check->next->data != 'o') {
				printf("[Error] : log 입력을 위해 l 다음으로 o 가 와야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++;
			}

			if (check->data != 'l' && check->next->data == 'o') {
				printf("[Error] : log 입력을 위해 o 전에 l 이 와야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt, error_cnt + 1, check->next->data);
				sign++;
			}

			if (check->data == 'o' && check->next->data != 'g') {
				printf("[Error] : log 입력을 위해 o 다음으로 g 가 와야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++;
			}

			if (check->data != 'o' && check->next->data == 'g') {
				printf("[Error] : log 입력을 위해 g 전에 o 가 와야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt, error_cnt + 1, check->next->data);
				sign++;
			}

			if (check->data == 'g' && (check->next->data != '2' && check->next->data != '1')) {
				printf("[Error] : log 입력을 위해 g 다음으로 밑수인 2 나 10이 와야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++;
			}

			if (check->data == 'g' && (check->next->data == '2' || check->next->data == '1')) {
				check_n1 = check->next;
				
				if (check_n1->next == NULL) {
					printf("[Error] : log는 밑과 괄호까지 입력되어야 합니다.  ex) log2(5)\n\n");
					sign++;
				} else {
					if (check_n1->data == '2' && check_n1->next->data != '(') {
						printf("[Error] : log는 괄호까지 입력되어야 합니다.  ex) log2(5)\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt + 1, error_cnt + 2, check_n1->data);
						sign++;
					}

					if (check_n1->data == '1' && check_n1->next->data != '0') {
						printf("[Error] : log 입력의 밑수는 2 나 10 만 입력될 수 있습니다.  ex) log2(5), log10(13)\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt + 1, error_cnt + 2, check_n1->data);
						sign++;
					}

					check_n2 = check_n1->next;

					if (check_n2->data == '0' && check_n2->next == NULL) {
						printf("[Error] : log는 괄호까지 밑과 괄호까지 입력되어야 합니다.  ex) log2(5), log10(13)\n\n");
						sign++;
					}

					if (check_n2->next != NULL) {
						if (check_n2->data == '0' && check_n2->next->data != '(') {
							printf("[Error] : log는 괄호까지 입력되어야 합니다.  ex) log10(13)\n");
							printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt + 2, error_cnt + 3, check_n2->data);
							sign++;
						}
					}
				}
			}

			if (check->data == ')' && ((check->next->data >= '0' && check->next->data <= '9')
			|| (check->next->data == '(' || check->next->data == 'l'
			|| check->next->data == 'o' || check->next->data == 'g'
			|| check->next->data == '.'))) {
				printf("[Error] : 닫힌 괄호 다음으로 계산 연산자만 올 수 있습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++;
			}

			if (check->data == '(' && (check->next->data == '*'
			|| check->next->data == '/'	|| check->next->data == '%'
			|| check->next->data == '^' || check->next->data == 'o'
			|| check->next->data == 'g' || check->next->data == '.')) {
				printf("[Error] : 열린 괄호 다음으로 단항연산자와 log, 피연산자만 올 수 있습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++; 
			}

			if (check->data == '(' && check->next->data == ')') {
				printf("[Error] : 괄호 안에는 수식이 존재해야 합니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++; 
			}

			if (!((check->data >= '0' && check->data <= '9') || check->data == ')') && check->next->data == ')') {
				printf("[Error] : 닫는 괄호 전에 피연산자와 닫는 괄호만 올 수 있습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt, error_cnt + 1, check->next->data);
				sign++; 
			}

			if ((check->data == '+' || check->data == '-'
			|| check->data == '*' || check->data == '/'
			|| check->data == '%' || check->data == '^')
			&& (check->next->data == '+' || check->next->data == '-'
			|| check->next->data == '*' || check->next->data == '/'
			|| check->next->data == '%' || check->next->data == '^')) { 
				printf("[Error] : + - * / %% ^ 와 같은 계산 연산자는 연속적으로 입력될 수 없습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++; 
			}

			if (check->data == '.' && check->next->data == '.') {
				printf("[Error] : . 은 연속적으로 입력 될 수 없습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++; 
			}

			if (check->data == '.' && (check->next->data == '+'
			|| check->next->data == '-' || check->next->data == '*'
			|| check->next->data == '/' || check->next->data == '%'
			|| check->next->data == '^')) {
				printf("[Error] : . 다음으로 계산 연산자가 입력 될 수 없습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++;
			}

			if (check->data == '.' && check->next->data == '(') {
				printf("[Error] : . 다음으로 열린 괄호가 입력 될 수 없습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++;
			}

			if ((check->data == '+' || check->data == '-'
			|| check->data == '*' || check->data == '/'
			|| check->data == '%' || check->data == '^')
			&& check->next->data == '.') {
				printf("[Error] : 계산 연산자 다음으로 . 이 입력 될 수 없습니다.\n");
				printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : next of %c\n\n", error_cnt, error_cnt + 1, check->data);
				sign++;
			}

			check_n1 = check->next;
			
			if (check == front) {
				if ((check->data >= '0' && check->data <= '9') && check_n1->data == '(') {
					printf("[Error] : 열린 괄호 전에 피연산자가 올 수 없습니다.\n");
					printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt, error_cnt + 1, check_n1->data);
					sign++;
				}
			}

			if (check_n1->next != NULL) {
				check_n2 = check_n1->next;
				
				if (check == front) {
					if ((check_n1->data >= '0' && check_n1->data <= '9') && check_n2->data == '(') {
						printf("[Error] : 열린 괄호 전에 피연산자가 올 수 없습니다.\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt + 1, error_cnt + 2, check_n2->data);
						sign++;
					}
				}

				if (check_n2->next != NULL) {
					if (check == front) {
						if ((check_n2->data >= '0' && check_n2->data <= '9') && check_n2->next->data == '(') {
							printf("[Error] : 열린 괄호 전에 피연산자가 올 수 없습니다.\n");
							printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt + 2, error_cnt + 3, check_n2->next->data);
							sign++;
						}
					}

					if (check_n2->next->data == '(' && check_n2->data == '2' && check_n1->data == 'g') {
						check = check->next;
						continue;
					}

					if (check_n2->next->data == '(' && check_n2->data == '0'
					&& check_n1->data == '1' && check->data == 'g') {
						check = check->next;
						continue;
					}

					if (check != front && (check_n2->data >= '0' && check_n2->data <= '9')
					&& check_n2->next->data == '(') {
						printf("[Error] : 열린 괄호 전에 피연산자가 올 수 없습니다.\n");
						printf("잘못된 데이터 -> 오류 생성 위치 : 수식의 %d 번째와 %d 번째 사이,    오류 부분 : before of %c\n\n", error_cnt + 2, error_cnt + 3, check_n2->next->data);
						sign++;		
					}
				}
			}
		}

		check = check->next;
	}

	if (open_bracket - close_bracket != 0) {
		printf("[Error] : 괄호의 짝이 맞지않습니다.\n\n");
		sign++;
	}

	if (space_signal > 0 && (num_signal == 0 && opt_signal == 0)) {
		printf("[Error] : 입력이 모두 공백입니다. \n\n");
		sign++;
	}

	if (num_signal == 0 && opt_signal > 0) {
		printf("[Error] : 피연산자가 입력되어야 합니다. \n\n");
		sign++;
	}

	if (sign > 0) {
		printf("[Error Count]-----------------------\n");
		printf("오류 메시지의 개수 : %d 개\n", sign);
		printf("------------------------------------\n\n");
		exit(-1);
	}
}

void que_toStack(int len) {
	char qToStack[len];
	int cnt = 0;
	int checksign_signal = 0;
	char front_sign;
	int front_sign_cnt = 0;
	int unary_operator_signal = 0;
	int cal_log_signal = 0;

	que_check_grammar();
	front_sign = front->data;

	for (int i = 0; i < len; i++) {
		qToStack[i] = '\0';
	}

	while (front != NULL) {
		if (front_sign_cnt == 0 && (front_sign == '+' || front_sign == '-')) {
			unary_operator_signal = que_unary_operator(len);

			if (unary_operator_signal == 1) {
				while (front != NULL) {
					que_deQueue();
				}

				return;
			}

			front_sign_cnt = 1;
		}

		if (front == NULL && rear == NULL) {
			break;
		}

		if ((front->data >= '0' && front->data <= '9') || front->data == '.') {
			qToStack[cnt++] = front->data;
			que_deQueue();

			if (front == NULL && rear == NULL) {
				stk_pushNum(atof(qToStack));
				break;
			}

			if (front->data == '+' || front->data == '-'
			|| front->data == '*' || front->data == '/'
			|| front->data == '%' || front->data == '^'
			|| front->data == ')') {
				stk_pushNum(atof(qToStack));
				cnt = 0;

				for (int i = 0; i < len; i++) {
					qToStack[i] = '\0';
				}
			}	
		}

		if (front->data == '(' && (front->next->data == '+' || front->next->data == '-')) {
			unary_operator_signal = que_unary_operator(len);

			if (unary_operator_signal == 1) {
				while (front != NULL) {
					que_deQueue();
				}

				return;
			}
		}

		if (front->data == '+' || front->data == '-'
		|| front->data == '*' || front->data == '/'
		|| front->data == '%' || front->data == '^'
		|| front->data == '(' || front->data == ')') {
			checksign_signal = cal_checkSign(front->data);

			if (checksign_signal == 1) {
				while (front != NULL) {
					que_deQueue();
				}

				return;
			}

			que_deQueue();
			
			if (front == NULL && rear == NULL) {
				break;
			}
		}

		if (front->data == 'l') {
			que_deQueue();
			que_deQueue();
			que_deQueue();
			cal_log_signal = cal_log_calcur(len);
			
			if (cal_log_signal == 1) {
				return;
			}
		}
	}
}

int que_unary_operator(int len) {
	int return_signal = 0;
	int cal_log_signal = 0;
	char qToStack[len];
	int cnt = 0;
	int checksign_signal = 0;
	char front_data;
	double num;

	for (int i = 0; i < len; i++) {
		qToStack[i] = '\0';
	}

	front_data = front->data;
	
	if (front->data == '(') {
		stk_pushSign(front->data);
		que_deQueue();
		front_data = front->data;
	}
	
	que_deQueue();
	
	if (front->data >= '0' && front->data <= '9') {
		while (1) {
			if ((front->data >= '0' && front->data <= '9') || front->data == '.') {
				qToStack[cnt++] = front->data;
				que_deQueue();

				if (front == NULL && rear == NULL) {
					num = atof(qToStack);
					
					if (front_data == '+') {
						stk_pushNum(num);
					}

					if (front_data == '-') {
						num *= -1;
						stk_pushNum(num);
					}

					return 0;
				}

				if (front->data == '+' || front->data == '-'
				|| front->data == '*' || front->data == '/'
				|| front->data == '%' || front->data == '^'
				|| front->data == ')') {
					num = atof(qToStack);
					
					if (front_data == '+') {
						stk_pushNum(num);
					}

					if (front_data == '-') {
						num *= -1;
						stk_pushNum(num);
					}

					break;
				}
	 		}
		}
	}

	if (front->data == 'l') {
		que_deQueue();
		que_deQueue();
		que_deQueue();		
		cal_log_signal = cal_log_calcur(len);
		
		if (cal_log_signal == 1) {
			return 1;
		}

		num = topN->data;
		
		if (front_data == '-') {
			num *= -1;
			stk_popNum();
			stk_pushNum(num);
		}

		return 0; 
	}

	if (front->data == '(') {
		while (1) {
			if ((front->data >= '0' && front->data <= '9') || front->data == '.') {
				qToStack[cnt++] = front->data;
				que_deQueue();

				if (front == NULL && rear == NULL) {
					stk_pushNum(atof(qToStack)); 
					break; 
				}

				if (front->data == '+' || front->data == '-'
				|| front->data == '*' || front->data == '/'
				|| front->data == '%' || front->data == '^'
				|| front->data == ')') { 
					stk_pushNum(atof(qToStack));
					cnt = 0;

					for (int i = 0; i < len; i++) {
						qToStack[i] = '\0';
					}
				}
			}

			if (front->data == '(' && (front->next->data == '+' || front->next->data == '-')) {
				return_signal = que_unary_operator(len);
				
				if (return_signal == 1) {
					return 1;
				}
			}

			if (front->data == '+' || front->data == '-'
			|| front->data == '*' || front->data == '/'
			|| front->data == '%' || front->data == '^'
			|| front->data == '(' || front->data == ')') { 
				checksign_signal = cal_checkSign(front->data);
				
				if (checksign_signal == 1) { 
					while (front != NULL) {
						que_deQueue();
					}

					return 1;
				}

				que_deQueue();
				
				if (front == NULL && rear == NULL) {
					break;
				}
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

		if (front_data == '-') {
			num = topN->data * -1;
			stk_popNum();
			stk_pushNum(num);
		}
	}

	return 0;
}

void que_toStack_end(void) {
	int calcur_signal = 0;

	while (topS != NULL) {
		calcur_signal = cal_calcur(topS->data);
		
		if (calcur_signal == 1) {
			return;
		}
	}

	cal_result();
}