#include "options.h"
#include <stdio.h>
#include <assert.h>

void testOptionUnwrap() {
  int result = 5;
  Option_t valid = Some(&result);
  int* val = unwrap(valid);
  assert(*val == 5 && "Value did not return 5");
}

void testOptionWrapOr() {
  char flag = 'f';
  char default_flag = 'c';
  Option_t invalid = None;
  Option_t valid = Some(&flag);

  char* value = unwrap_or(invalid, &default_flag);
  assert(*value == default_flag && "'unwrap_or' did not return default on None type");

  char* validValue = unwrap_or(valid, &default_flag);
  assert(*validValue == flag && "'unwrap_or' did not return value on Some type");
}

void* defaultFn()
{
  int v = 5;
  int *value;
  value = &v;
  return (void*)value;
};

void testOptionWrapOrElse()
{
  Option_t none = None;
  int* value = unwrap_or_else(none, defaultFn);

  assert(*value == 5 && "Did not return proper return value");
}

int main() {
  testOptionUnwrap();
  testOptionWrapOr();
  testOptionWrapOrElse();
  printf("All tests ok\n");
  return 0;
}
