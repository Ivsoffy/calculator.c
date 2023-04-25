#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE 256

typedef struct {
  double operand;
  int operation;
  int priority;
} token_t;

typedef struct {
  token_t data[MAX_VALUE];
  double result[MAX_VALUE];
  int data_size;
  int result_size;
} stack1;

typedef struct {
  token_t data[MAX_VALUE];
  int first;
  int last;
} queue_t;

typedef enum {
  COS = 1,    // 0+1
  SIN,        // 2
  TAN,        // 3
  ACOS,       // 4
  ASIN,       // 5
  ATAN,       // 6
  SQRT,       // 7
  LN,         // 8
  LOG,        // 9
  ADD,        // 10
  SUB,        // 11
  MULT,       // 12
  DIV,        // 13
  MOD,        // 14
  POW,        // 15
  PLUS,       // 16
  MINUS,      // 17
  L_BRACKET,  // 18
  R_BRACKET   // 19
} operations;

// stack
int stack_add(stack1 *stack, token_t value);
int stack_get(stack1 *stack, token_t *rez);

// queue
void queue_init(queue_t *q);
int queue_add(queue_t *q, token_t x);
int algorithm(char *str, queue_t *qu, stack1 *stack, double x);
void double_to_queue(char *str, queue_t *qu, int *index);
int stack_add_res(stack1 *stack, double value);
int stack_add(stack1 *stack, token_t value);
int stack_get(stack1 *stack, token_t *rez);
int stack_get_res(stack1 *stack, double *rez);
int fill_token(token_t *tk, char *s, int *index);
int str_compare(char *s1, int *index, const char *s2);
void double_to_queue(char *str, queue_t *qu, int *index);
int is_valid_double(char *str, int index);
int validation(char *str);
int queue_get(queue_t *q, token_t *res);
int is_valid_x(char *str, double *x);
void replace_x(queue_t *q, double x);
int postfix_calculation(char *str, double *res_d, char *str_x);
