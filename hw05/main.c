#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_ERROR 0
#define ERROR_WRONG_INPUT 100
#define ERROR_HOUSE_DIM_OUT_OF_RANGE 101
#define ERROR_HOUSE_WITH_IS_NOT_ODD 102
#define ERROR_FENCE_WIDTH_INVALID 103
// std error outputs
#define CHYBNY_VSTUP "Error: Chybny vstup!\n"
#define VSTUP_MIMO_INTERVAL "Error: Vstup mimo interval!\n"
#define SIRKA_NENI_LICHE_CISLO "Error: Sirka neni liche cislo!\n"
#define NEPLATNA_VELIKOST_PLOTU "Error: Neplatna velikost plotu!\n"
const int house_dim_min = 3;
const int house_dim_max = 69;

enum
{
  MANDATORY,
  OPTIONAL
};

int test_house_dim(int w, int h);
int test_fence_dim(int h, int f_w);

int print_roof(int w, int h);
int print_house(int w, int h, int f_w);
int fill_house(int w, int h, int f_w, int i, int j);
int print_fence(int w, int h, int f_w, int i, int j);

int read_input(int *w, int *h, int *f_w);

int main(int argc, char *argv[])
{
  int ret = NO_ERROR;
  int w, h, f_w;
  ret = read_input(&w, &h, &f_w);
  switch (ret)
  {
  case ERROR_WRONG_INPUT:
    fprintf(stderr, CHYBNY_VSTUP);
    // prints if the input is not a number
    break;
  case ERROR_HOUSE_DIM_OUT_OF_RANGE:
    fprintf(stderr, VSTUP_MIMO_INTERVAL);
    // print if input is out of range
    break;
  case ERROR_HOUSE_WITH_IS_NOT_ODD:
    fprintf(stderr, SIRKA_NENI_LICHE_CISLO);
    // print if width is not odd number
    break;
  case ERROR_FENCE_WIDTH_INVALID:
    fprintf(stderr, NEPLATNA_VELIKOST_PLOTU);
    // print if fence width is not smaller then house width
    break;
    // end switch

  /*
   * All errors handled => only printing.
   * MANDATORY is value 0 same as NO_ERROR
   * OPTIONAL is value 1
   * It would be better to use some defined constants
   * But in previous cases 0 (NO_ERROR) and 1 are not checked so this the
   * only place where 0 and 1 can fall
   */
  case MANDATORY: // occurs if input has 2 numbers
    print_roof(w, h);
    ret = print_house(w, h, f_w);
    break;
  case OPTIONAL: // occurs if input has 3 numbers
    print_roof(w, h);
    ret = print_house(w, h, f_w);
    break;
  // Just for sure
  default:
    printf("Default case");
    break;
  } // end switch
  return ret;
}

/*
 * Validate input before plotting anything
 */
int read_input(int *w, int *h, int *f_w)
{
  int ret = ERROR_WRONG_INPUT;
  int test_dims_code = NO_ERROR;
  if (scanf("%i %i", w, h) == 2)
  {
    test_dims_code = test_house_dim(*w, *h);
    if (test_dims_code != NO_ERROR)
    {
      return test_dims_code;
    }
    // width and height are OK
    ret = MANDATORY;
  }
  // decides if read also fence width
  bool read_fence_width = ret == MANDATORY;
  if (read_fence_width)
  {
    bool fence_width_value_ok = scanf("%i", f_w) == 1;
    if (!fence_width_value_ok)
    {
      // wrong fence width return immediately
      return ERROR_WRONG_INPUT;
    }
    test_dims_code = test_fence_dim(*h, *f_w);
    if (test_dims_code != NO_ERROR)
    {
      return test_dims_code;
    }
    ret = OPTIONAL;
  }
  return ret;
}

/*
 * Only printing, no validity checks
 */
int print_roof(int w, int h)
{
  int roof_height = (w - 1) / 2; // height of roof
  for (int i = 0; i < roof_height; ++i)
  {
    for (int j = 0; j < roof_height + i + 1; ++j)
    {
      if ((j == roof_height + i) || ((j == roof_height - i)))
        printf("X");
      else
        printf(" ");
    }
    printf("\n");
  }
  return NO_ERROR;
}

/*
 * Only printing, no validity checks
 */
int print_house(int w, int h, int f_w)
{
  for (int i = 0; i < h; ++i)
  {
    for (int j = 0; j < w; ++j)
    {
      if ((i == 0) || (i == h - 1))
        printf("X");
      if (((j == 0) || (j == w - 1)) && (i >= 1) && (i < h - 1))
        printf("X");
      if (w > 3)
        fill_house(w, h, f_w, i, j);
      else
      {
        if ((j < w - 2) && (i >= 1) && (i < h - 1))
          printf(" ");
      }
      if ((i > (h - f_w - 1)) && (j == w - 1))
        print_fence(w, h, f_w, i, j);
    }
    printf("\n");
  }
  return NO_ERROR;
}

/*
 * Only printing, no validity checks
 */
int fill_house(int w, int h, int f_w, int i, int j)
{
  if ((j < w - 2) && (i >= 1) && (i < h - 1))
  {
    if ((i % 2 != 0) && (j % 2 == 0))
      printf("o");
    else if ((i % 2 == 0) && ((j + 1) % 2 == 0))
      printf("o");
    else
      printf("*");
  }
  return NO_ERROR;
}

/*
 * Only printing, no validity checks
 */
int print_fence(int w, int h, int f_w, int i, int j)
{
  int max_fence = h - f_w;
  int min_fence = h - 1;
  int len_fence = w + f_w / 2 + 1;
  for (j = w + 1; j < (len_fence); ++j)
  {
    if ((i == max_fence) || (i == min_fence))
    {
      if ((f_w % 2 != 0) && (j == w + 1))
      {
        printf("|");
      }
      printf("-|");
    }
    else
    {
      if ((f_w % 2 != 0) && (j == w + 1))
      {
        printf("|");
      }
      printf(" |");
    }
  }
  return NO_ERROR;
}

// testing if input is in range
// testing if first input is odd number
int test_house_dim(int w, int h)
{
  int ret = NO_ERROR;
  int dim_ok = (house_dim_min <= w) && (w <= house_dim_max) &&
               (house_dim_min <= h) && (h <= house_dim_max);
  if (!dim_ok)
  {
    ret = ERROR_HOUSE_DIM_OUT_OF_RANGE;
    // test on invalid dimension goes before test of width
    return ret;
  }
  if (w % 2 == 0)
  {
    ret = ERROR_HOUSE_WITH_IS_NOT_ODD;
    return ret;
  }
  return ret;
}

// testing if third input is smaller than high of house
int test_fence_dim(int h, int f_w)
{
  if (f_w > 0 && f_w < h)
  {
    return NO_ERROR;
  }
  else
  {
    return ERROR_FENCE_WIDTH_INVALID;
  }
}