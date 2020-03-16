/******************/
/* Leroy Valencia */
/*    03/27/20    */
/*   CS-241-006   */
/******************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

int b2dMode = 0;
int d2bMode = 0;
int bit = 8;
int verbose = 0;

/* Notes args start at [1] */

void printUsage();
bool validateBinary(unsigned long int);
bool validateDecimal(char *);
void convertB2D(char *);
void convertD2B(unsigned long);

int main(int argc, char *argv[])
{
  char *ptr; 
  unsigned long unsignedLong;
/*     int i;
  printf("%d\n", argc);
      for(i = 1; i < argc; i++)
    {
      printf("%s ", argv[i]);
    }
    printf("\n"); */

  if(argc != 4)
  {
    printf("ERROR: incorrect number of arguments\n");
    printUsage();
    return 1;
  }
  
/* Parse 1st parameter */

  if(strcmp(argv[1], "-b2d") == 0)
  {
    if(verbose) printf("You chose b2d\n");
    b2dMode = 1;
  }
  else if(strcmp(argv[1], "-d2b") == 0)
  {
    if(verbose) printf("You chose d2b\n");
    d2bMode = 1;
  }
  else
  {
    printf("ERROR: argument 1 must be -b2d | -d2b\n");
    printUsage();  
  }

  /* Parse 2nd Parameter */
  
  if(strcmp(argv[2], "-8") == 0) bit = 7;
  else if(strcmp(argv[2], "-16") == 0) bit = 15;
  else if(strcmp(argv[2], "-32") == 0) bit = 31;
  else if(strcmp(argv[2], "-64") == 0) bit = 63;
  else
  {
    printf("ERROR: argument 2 must be: -8 | -16 | -32 | -64\n");
    printUsage();
  }

  /* Parsing 3rd Parameter */

  unsignedLong = strtoul(argv[3], &ptr, 10);
  if(b2dMode == 1)
  {
    if(validateBinary(unsignedLong))
    {
      if(verbose) printf("Valid Binary\n");
      convertB2D(argv[3]);
    }else
    {
      printf("ERROR: argument 3 is not a binary integer\n");
      printUsage();
    }
  }
  else if (d2bMode == 1)
  {
    if(validateDecimal(argv[3]))
    {
      if(verbose) printf("Valid decimal\n");
      convertD2B(unsignedLong);
    } else
    {
      printf("ERROR: argument 3 is not a decimal integer\n");
      printUsage();
    }
    
  }

  return 0;
}

bool validateBinary(unsigned long num)
{
  int j, error;
  if(verbose) printf("Validating that %lu is binary\n", num);
  error = 0;
  while(num != 0)
  {
    j = num%10;
    if ((j != 1) && (j != 0))
    {
      error++;
      break;
    }
    num /= 10;
  }
  return error > 0 ? false : true;
}

bool validateDecimal(char * num)
{
  int i, tally;
  if(verbose) printf("Validating that %s\n", num);
  tally = 0;
  for(i = 0; i < strlen(num); i++)
  {
    if((num[i] >= '0') && (num[i] <= '9'))
    {
      tally++;
    }
  }
  return tally == strlen(num) ? true : false;
}

void convertB2D(char * num)
{
  int dec, total, len, i;
  total = 0;
  len = strlen(num);
  if(verbose) printf("Converting the string %s\n", num);
  /* Loop 6 times */
  for(i = 0; i < len; i++)
  {
    /* printf("%c ", num[i]); */
    if(num[i] == '1')
    {
      total = 2 * total;
      dec = total + 1;
      printf("\n1: %d\n", dec);
    }
    else
    {
      total = 2 * total;
      dec = total + 0;
      printf("\n0: %d\n", dec);
    }
    
  }
  printf("\n%d\n", dec);
}

void convertD2B(unsigned long num)
{
  int i, k, count;
  count = 0;
  if(verbose) printf("Converting the ul %lu\n", num);
  for(i = bit; i >= 0; i--)
  {
    k = num >> i;
    if(k & 1)
    {
      printf("1");
      count++;
    }
    else
    {
      printf("0");
      count++;
    }
    if(count == 4)
    {
      printf(" ");
      count = 0;
    }
  }

  printf("\n");
}

void printUsage()
{
  printf(
          "usage:\n"
          "binary OPTION SIZE NUMBER\n"
          "  OPTION:\n"
          "    -b2d  NUMBER is binary and output will be in decimal.\n"
          "    -d2b  NUMBER is decimal and output will be in binary.\n\n"

          "  SIZE:\n"
          "    -8    input is an unsigned 8-bit integer.\n"
          "    -16   input is an unsigned 16-bit integer.\n"
          "    -32   input is an unsigned 32-bit integer.\n"
          "    -64   input is an unsigned 64-bit integer.\n\n"

          "  NUMBER:\n"
          "    number to be converted.\n\n");
}