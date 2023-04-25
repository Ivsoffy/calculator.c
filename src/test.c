#include <check.h>

#include "s21_smartcalc.h"

START_TEST(test_case_1) {
  char str[256] = "1.675+256+123";
  char str_x[256];
  double res = 0;
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(380.675, res, 1e-6);
  strcpy(str, "212.242.2+253");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
  strcpy(str, "sin(3)/");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
  strcpy(str, "-(3)*(-1-(7*(-(-(-(-7))))))");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(150, res, 1e-6);
  strcpy(str, "(8+2*5)/(1+3*2-4)");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(6, res, 1e-6);
  strcpy(str, "(1+2)*4*cos(10*7-2)+sin(2*10)");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(6.1946615206, res, 1e-6);
  strcpy(str, "4^acos(2/4)/tan(2*2)");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(3.688367786, res, 1e-6);
  strcpy(str, "ln(55/(2+sqrt(77)))");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(1.63010785436, res, 1e-6);
  strcpy(str, "-sqrt(x^log(5-x))+ln(55/(2+x))");
  strcpy(str_x, "1.45");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(1.66132917093, res, 1e-6);
  strcpy(str, "(1+2)4(cos(x*7-2)+sin(2*x))70^(-10)+5(-3)");
  strcpy(str_x, "0");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
}
END_TEST

START_TEST(test_case_2) {
  char str[256] = "asin(2/x)mod(x)+atan(x)";
  char str_x[256] = "2";
  double res = 0;
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(2.6779450446, res, 1e-6);
  strcpy(str, "1/2*3");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(1.5, res, 1e-6);
  strcpy(str, "2^3^2");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(512, res, 1e-6);
  strcpy(str, "(8+2*5)/(1+3)*2)-((4)");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
  strcpy(str, "ln(22)/log(53)/sqrt(100.3453)");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0.1789574165, res, 1e-6);
  strcpy(str, "11.124.15-35");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
  strcpy(str, "(34-)(2)");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
  strcpy(str, "ln(55/(2+sqrt(77)))");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(1.63010785436, res, 1e-6);
  strcpy(str, "3(2+3)");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
  strcpy(str, "1.57464.54");
  postfix_calculation(str, &res, str_x);
  ck_assert_double_eq_tol(0, res, 1e-6);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_case_1);
  tcase_add_test(tc1_1, test_case_2);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);
  return 0;
}
