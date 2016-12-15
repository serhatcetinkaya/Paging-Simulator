/*
Copyright (C) 2016  Serhat Çetinkaya serhatcetinkayaa@gmail.com
                    Javid Karimbayli karimbayli.j@gmail.com
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
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
