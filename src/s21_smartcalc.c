#include "s21_smartcalc.h"

// int main(){
//   char* str = "9.4342345235235*9.4342345235235";
//   double res;
//   int m = postfix_calculation(str, &res, "0");
//   printf("%d = %lf", m, res);
//   return 0;
// }

int stack_add(stack1 *stack, token_t value) {
  int error_code = 0;
  if (stack->data_size >= MAX_VALUE) error_code = 1;  // else
  stack->data[(stack->data_size) + 1] = value;
  stack->data_size++;
  return error_code;
}

int stack_get(stack1 *stack, token_t *rez) {
  int error_code = 0;
  if (stack->data_size == 0)
    error_code = 1;
  else {
    *rez = stack->data[stack->data_size];
    stack->data[stack->data_size] = (token_t){0};
    stack->data_size--;
  }
  return error_code;
}

void queue_init(queue_t *q) {
  q->first = 1;
  q->last = 0;
}

void stack_init(stack1 *st) {
  st->data_size = 0;
  st->result_size = 0;
}

int queue_add(queue_t *q, token_t x) {
  int error_code = 0;
  if (q->last < MAX_VALUE - 1) {
    q->last++;
    q->data[q->last] = x;
  } else
    error_code = 1;
  return error_code;
}

int queue_get(queue_t *q, token_t *res) {
  int error_code = 0;
  if (q->last == 0)
    error_code = 1;
  else {
    *res = q->data[q->first];
    q->data[q->first] = (token_t){0, 0, 0};
    if (q->last == q->first) {
      q->first = 1;
      q->last = 0;
    } else
      q->first++;
  }
  return error_code;
}

int postfix_calculation(char *str, double *res_d, char *str_x) {
  *res_d = 0;
  int error_code = 0;
  if (validation(str)) {
    double x1 = 0, x2 = 0, x0 = 0, x = 0;
    queue_t qu;
    queue_init(&qu);
    stack1 st;
    stack_init(&st);
    stack1 temp;
    stack_init(&temp);
    token_t temp2 = {0};
    if (strchr(str, 'x')) {
      if (!is_valid_x(str_x, &x)) {
        error_code = 1;
      }
    }
    if ((error_code == 0) && (!algorithm(str, &qu, &st, x))) {
      while (!queue_get(&qu, &temp2)) {
        int oper = temp2.operation;
        if (!oper) {  // is it number
          stack_add_res(&temp, temp2.operand);
        } else {
          if ((oper == PLUS) || (oper == MINUS) || oper < 10) {
            stack_get_res(&temp, &x0);
          } else {
            stack_get_res(&temp, &x2);
            stack_get_res(&temp, &x1);
          }
          if (oper == ADD)
            stack_add_res(&temp, (x1 + x2));
          else if (oper == SUB)
            stack_add_res(&temp, (x1 - x2));
          else if (oper == MULT)
            stack_add_res(&temp, (x1 * x2));
          else if (oper == DIV)
            stack_add_res(&temp, (x1 / x2));
          else if (oper == MOD)
            stack_add_res(&temp, fmod((double)x1, x2));
          else if (oper == POW)
            stack_add_res(&temp, pow(x1, x2));
          else if (oper == PLUS)
            stack_add_res(&temp, x0);
          else if (oper == MINUS)
            stack_add_res(&temp, 0 - x0);
          else if (oper == COS)
            stack_add_res(&temp, cos(x0));
          else if (oper == SIN)
            stack_add_res(&temp, sin(x0));
          else if (oper == TAN)
            stack_add_res(&temp, tan(x0));
          else if (oper == ACOS)
            stack_add_res(&temp, acos(x0));
          else if (oper == ASIN)
            stack_add_res(&temp, asin(x0));
          else if (oper == ATAN)
            stack_add_res(&temp, atan(x0));
          else if (oper == SQRT)
            stack_add_res(&temp, sqrt(x0));
          else if (oper == LN)
            stack_add_res(&temp, log(x0));
          else if (oper == LOG)
            stack_add_res(&temp, log10(x0));
        }
      }
      stack_get_res(&temp, res_d);
    } else {
      error_code = 1;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int stack_add_res(stack1 *stack, double value) {
  int error_code = 0;
  if (stack->result_size >= MAX_VALUE) error_code = 1;
  stack->result[stack->result_size] = value;
  stack->result_size++;
  return error_code;
}

int stack_get_res(stack1 *stack, double *rez) {
  int error_code = 0;
  if (stack->result_size == 0) error_code = 1;
  stack->result_size--;
  *rez = stack->result[stack->result_size];
  return error_code;
}

int algorithm(char *str, queue_t *qu, stack1 *stack, double x) {
  int i = 0, error_code = 0;
  token_t token = {0, 0, 0};
  token_t temp_tk = {0};
  char a = str[i];
  while ((a != '\0') && (!error_code)) {
    token = (token_t){0, 0, 0};
    if (strchr("1234567890", a)) {
      if (is_valid_double(str, i)) {
        double_to_queue(str, qu, &i);
      } else {
        error_code = 1;
      }

    } else if (strchr("()+-*/^mcstal", a) && fill_token(&token, str, &i)) {
      if (token.operation < 10) {  // funcs
        stack_add(stack, token);
      } else if (token.operation == R_BRACKET) {
        while ((stack->data[(stack->data_size)].operation != L_BRACKET) &&
               (stack->data[(stack->data_size)].operation > 9)) {
          if (!stack_get(stack, &temp_tk)) {
            queue_add(qu, temp_tk);
          } else {
            error_code = 1;
            break;
          }
        }
        if (!error_code) {
          if (stack->data[(stack->data_size)].operation > 9) {
            stack_get(stack, &temp_tk);
          }
          if (!stack_get(stack, &temp_tk)) {
            if (temp_tk.operation < 10)
              queue_add(qu, temp_tk);
            else
              stack_add(stack, temp_tk);
          }
        }
      } else {
        while ((stack->data_size) &&
               ((stack->data[stack->data_size]).operation != L_BRACKET) &&
               ((stack->data[stack->data_size]).operation != R_BRACKET) &&
               ((stack->data[stack->data_size]).operation > 9) &&
               (((stack->data[stack->data_size]).priority < token.priority) ||
                ((stack->data[stack->data_size]).priority == token.priority &&
                 token.operation != POW))) {
          token_t tk5 = (token_t){0};
          stack_get(stack, &tk5);
          queue_add(qu, tk5);
        }
        stack_add(stack, token);
      }
    } else if (a == 'x') {
      replace_x(qu, x);
      i++;
    } else {
      error_code = 1;
    }
    a = str[i];
  }

  while ((!stack_get(stack, &temp_tk)) && (temp_tk.operation != 0)) {
    if (temp_tk.operation == L_BRACKET || temp_tk.operation == R_BRACKET) {
      error_code = 1;
      break;
    } else {
      queue_add(qu, temp_tk);
    }
  }
  return error_code;
}

int is_valid_x(char *str, double *x) {
  int error_code = 1;
  queue_t q;
  queue_init(&q);
  if (is_valid_double(str, 0)) {
    int i = 0;
    double_to_queue(str, &q, &i);
    *x = q.data[q.last].operand;
  } else {
    error_code = 0;
  }
  return error_code;
}

void replace_x(queue_t *q, double x) {
  token_t t = {0};
  t.operand = x;
  queue_add(q, t);
}

int fill_token(token_t *tk, char *s, int *index) {
  int error_code = 1, flag = 0;
  const char *operations = "()+-*/^";
  const char functions[][6] = {"cos(",  "sin(",  "tan(", "acos(",
                               "asin(",  // \0
                               "atan(", "sqrt(", "ln(",  "log("};
  if (strchr(operations, s[*index])) {
    if (s[*index] == '+') {
      if ((s[*index - 1] != '(') && (*index)) {
        tk->operation = ADD;
        tk->priority = 6;
      } else {
        tk->operation = PLUS;
        tk->priority = 2;
      }
    } else if (s[*index] == '-') {
      if ((s[*index - 1] != '(') && (*index)) {
        tk->operation = SUB;
        tk->priority = 6;
      } else {
        tk->operation = MINUS;
        tk->priority = 2;
      }
    } else if (s[*index] == '(') {
      tk->operation = L_BRACKET;
      tk->priority = 1;
    } else if (s[*index] == '/') {
      tk->operation = DIV;
      tk->priority = 5;
    } else if (s[*index] == '*') {
      tk->operation = MULT;
      tk->priority = 5;
    } else if (s[*index] == ')') {
      tk->operation = R_BRACKET;
      tk->priority = 1;
    } else if (s[*index] == '^') {
      tk->operation = POW;
      tk->priority = 4;
    }
    (*index)++;
  } else if (str_compare(s, index, "mod")) {
    tk->operation = MOD;
    tk->priority = 5;
  } else {
    flag = 1;
    for (int i = 0; i < 9; i++) {
      if (str_compare(s, index, functions[i])) {
        tk->operation = i + 1;
        tk->priority = 3;
        flag = 0;
        break;
      }
    }
  }
  if (flag) {
    error_code = 0;
  }
  return error_code;
}

int str_compare(char *s1, int *index, const char *s2) {
  int res = 1;
  int i = 0, k = 0;
  for (i = *index; i < *index + (int)strlen(s2); i++) {
    if (s1[i] != s2[k]) {
      res = 0;
      break;
    }
    k++;
  }
  if (res) *index = i;
  return res;
}

void double_to_queue(char *str, queue_t *qu, int *index) {
  char *tempstr = NULL;
  char *strtemp = &str[*index];
  token_t temp = {0, 0, 0};
  temp.operand = strtod(&str[*index], &tempstr);
  (*index) += (tempstr - strtemp);
  queue_add(qu, temp);
}

int is_valid_double(char *str, int index) {
  int flag = 0, error_code = 1;
  while ((flag != 2) &&
         (str[index] == '.' || strchr("1234567890", str[index]))) {
    if (str[index] == '.') flag++;
    index++;
  }
  if (flag == 2) {
    error_code = 0;
  }
  return error_code;
}

int validation(char *str) {
  int flag = 1;
  int bracket = 0;
  if (str != NULL && strlen(str) > 0) {
    if (strchr(".*/^m)", str[0])) {
      flag = 0;
    } else if (strchr("-+", str[0]) && strchr("*/^m)", str[1])) {
      flag = 0;
    } else if (str[0] == '(') {
      bracket++;
    }
    if (strlen(str) > 1) {
      int i = 1;
      while (str[i] != '\0') {
        if (str[i] == '(') {
          bracket++;
        } else if (str[i] == ')') {
          bracket--;
        }
        if ((strchr("m*/^+-", str[i]) && strchr("*/^+-", str[i - 1])) ||
            (strchr("m*/^", str[i]) && strchr("(", str[i - 1])) ||
            (strchr("1234567890", str[i - 1]) && strchr("(", str[i])) ||
            (strchr("cstal", str[i]) && !strchr("artdo*/^+-(", str[i - 1])) ||
            (str[i - 1] == '(' && str[i] == ')') ||
            ((str[i] == str[i - 1] && str[i] == '.')) ||
            (str[i - 1] == ')' &&
             (str[i] != 'a' && str[i] != 't' && str[i] != 's' &&
              str[i] != 'c' && str[i] != 'l' && str[i] != 'm' &&
              str[i] != '+' && str[i] != '-' && str[i] != '*' &&
              str[i] != '/' && str[i] != '^' && str[i] != '\0' &&
              str[i] != ')'))) {
          flag = 0;
          break;
        }
        if (bracket < 0) {
          flag = 0;
          break;
        }
        if ((str[i] == 'x' && !strchr("*/^+-(d", str[i - 1])) ||
            (str[i - 1] == 'x' && !strchr("*/^+-)m", str[i]))) {
          flag = 0;
          break;
        }
        i++;
      }
    }
  } else {
    flag = 0;
  }
  if (bracket != 0) {
    flag = 0;
  }
  if (!strchr("0123456789x)", str[strlen(str) - 1])) flag = 0;
  if (strchr("+-*/^", str[strlen(str) - 1])) flag = 0;
  return flag;
}
