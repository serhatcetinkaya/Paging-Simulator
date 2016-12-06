#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char *hexToBin(char *buffer);
char *pageLevelOne(char *binary);
char *pageLevelTwo(char *binary);
char *pageOffset(char *binary);
int binToDecimal(char *binary);

int main(int argc, char *argv[]){

  char *binary = (char *) malloc(sizeof(char)*32);
  char *pt1 = (char *) malloc(sizeof(char)*10);
  char *pt2 = (char *) malloc(sizeof(char)*10);
  char *offset = (char *) malloc(sizeof(char)*12);
  FILE *fp1 = fopen(argv[1], "r");
  FILE *fp2 = fopen(argv[2], "r");



  fclose(fp1);
  fclose(fp2);
}
char *hexToBin(char *buffer){
  char *binary = (char *) malloc(sizeof(char)*32);
  int i;

  for (i = 2; i < strlen(buffer); i++){
    printf("buffer[i] is: %d\n", buffer[i]);
    if (buffer[i] == 48)
      strcat(binary, "0000");
    if (buffer[i] == 49)
      strcat(binary, "0001");
    if (buffer[i] == 50)
      strcat(binary, "0010");
    if (buffer[i] == 51)
      strcat(binary, "0011");
    if (buffer[i] == 52)
      strcat(binary, "0100");
    if (buffer[i] == 53)
      strcat(binary, "0101");
    if (buffer[i] == 54)
      strcat(binary, "0110");
    if (buffer[i] == 55)
      strcat(binary, "0111");
    if (buffer[i] == 56)
      strcat(binary, "1000");
    if (buffer[i] == 57)
      strcat(binary, "1001");
    if (buffer[i] == 65)
      strcat(binary, "1010");
    if (buffer[i] == 66)
      strcat(binary, "1011");
    if (buffer[i] == 67)
      strcat(binary, "1100");
    if (buffer[i] == 68)
      strcat(binary, "1101");
    if (buffer[i] == 69)
      strcat(binary, "1110");
    if (buffer[i] == 70)
      strcat(binary, "1111");
    if (buffer[i] == 97)
      strcat(binary, "1010");
    if (buffer[i] == 98)
      strcat(binary, "1011");
    if (buffer[i] == 99)
      strcat(binary, "1100");
    if (buffer[i] == 100)
      strcat(binary, "1101");
    if (buffer[i] == 101)
      strcat(binary, "1110");
    if (buffer[i] == 102)
      strcat(binary, "1111");
  }
  return binary;
}
char *pageLevelOne(char *binary){
  char *pt1 = (char *) malloc(sizeof(char)*10);
  int i;

  for (i = 0; i < 10; i++){
    if (binary[i] == 48){
      strcat(pt1, "0");
    }else{
      strcat(pt1, "1");
    }
  }
  return pt1;
}
char *pageLevelTwo(char *binary){
  char *pt2 = (char *) malloc(sizeof(char)*10);
  int i;

  for (i = 10; i < 20; i++){
    if (binary[i] == 48){
      strcat(pt2, "0");
    }else{
      strcat(pt2, "1");
    }
  }
  return pt2;
}
char *pageOffset(char *binary){
  char *offset = (char *) malloc(sizeof(char)*12);
  int i;

  for (i = 20; i < strlen(binary); i++){
    if (binary[i] == 48){
      strcat(offset, "0");
    }else{
      strcat(offset, "1");
    }
  }
  return offset;
}
int binToDecimal(char *binary){
  int i,j,result = 0, temp = 1, length = strlen(binary);
  for (i = 0; i < length; i++){
    if (binary[i] == 49){
      for (j = (length - i) - 1; j > 0; j--){
        temp = temp * 2;
      }
      result = result + temp;
      temp = 1;
    }
  }
  return result;
}