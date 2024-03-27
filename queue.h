#ifndef __QUEUE_H_
#define __QUEUE_H_

typedef struct Que {
	char data;
	struct Que* next;
} Que;

void que_enQueue(char x);
void que_deQueue(void);
void que_deQueue_space(Que* where);
void que_check_grammar(void);
void que_toStack(int len);
int que_unary_operator(int len);
void que_toStack_end(void);

#endif