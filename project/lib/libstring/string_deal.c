#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "string_deal.h"


void replace(char *s, char a, char b)
{
  int i;
  for(i = 0; i < strlen(s); i++)
    {
      if(s[i] == a) s[i] = b;
    };
  return;
}


int strEnd(char *string, char *end)
{
  int n = strlen(string) - strlen(end);

  char *test = &string[n];

  if(strcmp(test, end) ==0)return 1;
  else return 0;
}


void moveCharLeft(char *string)
{
  char temp = string[0];

  int i = 0;
  while(string[i+1] != '\0')
    {
      string[i] = string[i+1];
      i++;
    };
  string[i] = temp;
}

void moveCharRight(char *string)
{
  char temp = string[strlen(string) - 1];

  int i = strlen(string) - 1;
  while(i != 0)
    {
      string[i] = string[i - 1];
      i--;
    };

  string[0] = temp;
}

void trimLeft(char *string)
{
  while(string[0] == 32)
    {

      int i = 0;
      while(string[i+1] != '\0')
	{
	  string[i] = string[i+1];
	  i++;
	};
      string[i] = '\0';
    };
  //else return;
}

void trimMiddle(char *string)
{
  int i = 0;
  while(string[i] != '\0'){
  if(string[i] == 32 && string[i+1] == 32)
    {
      int j = i+1;
      while(string[j + 1] != '\0')
	{
	  string[j] = string[j+1];
	  j++;
	};
      string[j] = '\0';
      //break;
    };
  i++;
  }
 
}

void trimRight(char *string)
{
  int n = strlen(string) - 1;

  if(string[n] == 32){
    string[n] = '\0';
    trimRight(string);
  }else
    return;
}


char codeLetter(char a, int n)
{
  if(a == 32 || a == 10 || a == 11)return a;
  if( a<=90 && a+ n > 90)
    {
      a = 64 + (n - (90 - a));
      return a;
    };
  if(a <= 122 && a + n > 122)
    {
      a = 96 + ( n - (122 - a));
      return a;
    };
  if( a>=65 && a <= 90 && a + n < 65)
    {
      a = 91 + (n + ( a - 65));
      return a;
    };
  if(a >= 97 && a<=122 && a + n < 97)
    {
      a = 123 + (n + (a - 97));
      return a;
    };
  
  a += n;
  return a;
  

}

char *code(char *string, int n)
{

  int i = 0;

  while(string[i] != '\0')
    {
      string[i] = codeLetter(string[i], n);
      i++;

    };
  return string;
}

int strIn(char *string, char *find)
{
  int i= 0;
  int j;
  int z;
  //char *test;
  while(string[i] != '\0')
    {
      z = i;
      j = 0;
      while(1)
	{
	  if(find[j] == '\0'){
	    return 1;
	  };
	  if(string[z] == '\0') return 0;
	  if(string[z] != find[j]) break;
	  z++;
	  j++;
	  
	};
      i++;
    };
  return 0;
}

void capitalLetterOn(char *a)
{
  if( *a <= 122 && *a >= 97)
    {
      *a -=32;
    };
}

void capitalLetterOff(char *a)
{
  if( *a <= 90 && *a >= 65)
    {
      *a +=32;
    };
}


void capitalOn(char *buffer)
{
  capitalLetterOn(&buffer[0]);
  int i = 0;
  while(buffer[i] != '\0')
    {
    if(buffer[i] == 32 && buffer[i+1] <= 122 && buffer[i+1] >=97)
      {
	capitalLetterOn(&buffer[i+1]);
      };
    }
}

void capitalOff(char *buffer)
{
  int i = 0;
  while(buffer[i] != '\0')
    {
      capitalLetterOff(&buffer[i]);
    };
}

//work with number
int checkPrime(int number)
{
  int i;
  //int j;
  int count = 0;
  if(number < 1) return 0;
  for(i = 1; i<= number/2; i++)
    {
      if(number % i == 0)
	{
	  count ++;
	};
      if(count > 1)return 0;
    };
  return 1;
}



int checkPerfectNumber(int n)
{
  int sum = 0;
  int i;

  //int rem;


  for(i = 1; i <= n/2; i++)
    {

      if(n%i == 0)
	{
	  sum = sum +i;
	};

    };

  if(sum == n)return 1;
  else return 0;
}

int getRandomNumber(int min, int max){

  int r = rand() % ((max - min) + 1);
  r += min;
  return r;
}



int decimalToBinary(int number, int *binary)
{
  int i = 0;
  while(number !=  0)
    {
      int a = number%2;
      //printf("%d\n", a);
      binary[i] = a;
      // printf("%d\n", binary[i]);
      number = number/2;
      i++;
    }
  i--;
  return i;
}




void convertHexa(int *number, int num)
{
  int i ;
  for(i = 0; i<=num; i++ ){
  if( number[i] >9 && number[i] <=15)
    {
      number[i] = number[i] + 55;
      //printf("%c", *number);
    };
  };

}


int decimalToHexa(int number, int *hexa)
{
  int i = 0;
  int a;
  while( number != 0)
    {
      a = number % 16;
      hexa[i] = a;
      printf("%d - ", hexa[i]);
      i++;
      number = number/16;
      
        printf("%d\n", number);
    };
  convertHexa(hexa,i);
  i--;
  return i;
}


int decimalToOctal(int number, int *octal)
{
  int i = 0;
  int result;
  while( number != 0)
    {
      result= number%8;
      octal[i] = result;
      i++;
      number = number/8;
    };
  i--;
  return i;
}



void printHexa(int *hexa, int num)
{
  int i;
  for(i = num; i>= 0; i--)
    {
      if(hexa[i] > 9)
	{
	  printf("%c", hexa[i]);
	}
      else
      printf("%d", hexa[i]);
    };
  printf("\n");

}






/*
int main()
{
  
  printf("INput string: ");
  char *string = (char *)malloc(sizeof(char) * 100);
  //printf("%d\n", sizeof(char*));
  gets(string);

  char *test = (char *)malloc(sizeof(char) * 100);
  strcpy(test, string);
  printf("Normal: %s\n", test);

 strcpy(test, string);
  
replace(test, 'n', 'i');

printf("Replace : %s\n", test);

strcpy(test, string);

printf("test strend: %d\n",  strEnd(test, "Dung"));
printf("test strend2: %d\n", strEnd(test, "Anh"));
  

strcpy(test, string);
moveCharLeft(test);
printf("move char left : %s\n", test);
  
strcpy(test, string);
moveCharRight(test);
printf("move char right: %s\n", test);

  strcpy(test, " ");
  strcat(test, string);
  printf("test :1%s\n", test); 
  trimLeft(test);
  printf("trim left :1%s\n",test);

  strcpy(test, "Dinh  Anh  Dung");
  trimMiddle(test);
  printf("trim middel: %s\n", test);

  strcpy(test, "Dinh  Anh  Dung    ");
  printf("test :%s123\n", test);
  trimRight(test);
  printf("test :%s123\n", test);


  strcpy(test, "Anh");
  printf("find : %d\n", strIn(string, test));
  strcpy(test, "AL");
  printf("find : %d\n", strIn(string, test));
  strcpy(test, "Dinh");
  printf("find: %d\n", strIn(string, test));

  strcpy(test, "Dung");
  printf("find: %d\n", strIn(string, test));
  return 0;
}

*/

