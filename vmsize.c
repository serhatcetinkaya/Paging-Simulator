/*
Serhat Cetinkaya 21201478
Javid Karimbayli 21002742
CS342-1
Project1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>


const char *makeRandom()
{
   int r = rand()%16;
   char *str = (char *) malloc(sizeof(char));
   char s;
   if(r>9){
     if(r==10) str[0] = 'a';
     if(r==11) str[0] = 'b';
     if(r==12) str[0] = 'c';
     if(r==13) str[0] = 'd';
     if(r==14) str[0] = 'e';
     if(r==15) str[0] = 'f';
   }
   else{
     char buffer[1];
     sprintf(buffer,"%d",r);
     str[0] = buffer[0];
   }
   return str;

}
int main(int argc, char *argv[]){
  //FILE *input1 = fopen(argv[1], "r");
  int size = atoi(argv[1]);
  int i=0;
  char result[7];
  unsigned int hex;
  FILE *out = fopen("vmsizeOut.txt", "a");

  for(i=0;i<size; i++){

    sprintf (result, "%s%s%s%s%s%s%s%s", makeRandom(),makeRandom(),makeRandom(),makeRandom(),makeRandom(),makeRandom(),makeRandom(),makeRandom());
    hex = ( unsigned int)strtol(result, NULL, 16);
    fprintf(out, "%08x\n", hex);
    printf("hex is :%08x\n", hex);


  }

  return 0;
}
