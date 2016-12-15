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

struct list{
  unsigned int start;
  unsigned int end;
  struct list *next;
}; typedef struct list LIST;

struct frame{
  unsigned int virtual_address;
  int entry_time, used_time;
}; /*typedef struct frame FRAME;*/

struct frame *frames;

int main(int argc, char *argv[]){
  FILE *input1 = fopen(argv[1], "r");
  FILE *input2 = fopen(argv[2], "r");
  FILE *out = fopen(argv[4], "a");
  unsigned int x , a, start, end, target;
  unsigned int pg1, pg2, offset;
  unsigned int offset_perde = 0xfff;
  unsigned int page2perde = 0x3ff;
  unsigned int check, victim;
  char buffer[10];
  int flag, empty = 0, i, j, entry_time = 1, used_time = 1;
  int M = atoi(argv[3]);
  int frame_size = M*4096;
  int algo = atoi(argv[6]);
  LIST *head = NULL, *current;

  while (fscanf(input1, "%x", &a) > 0){
    LIST *node = malloc(sizeof(struct list));
    start = a;
    fscanf(input1, "%x", &a);
    end = a;
    node->start = start;
    node->end = end;
    node->next = NULL;
    if (head == NULL){
      head = node;
      current = node;
    }else{
      current->next = node;
      current = current->next;
    }
  }

  frames = malloc(frame_size*sizeof(struct frame));
  for (i = 0; i < frame_size; i++){
    frames[i].entry_time = 0;
    frames[i].used_time = 0;
    frames[i].virtual_address = 0;
  }

  unsigned int **pagetable = malloc(sizeof(unsigned int*)*1024);
  for (i = 0; i < 1024; i++){
    pagetable[i] = malloc(sizeof(unsigned int)*1024);
  }
  while (fscanf(input2, "%x", &a) > 0){
    target = a;
    current = head;
    flag = 0;
    while (current != NULL){
      if (target >= current->start && target <= current->end){
        flag = 1;
      }
      current = current->next;
    }
    if (flag == 0){
      fputs("e\n", out);
    }else{
      ///////////////////////////////////////
      pg1 = target >> 22;
      pg2 = target >> 12;
      pg2 = pg2 & page2perde;
      offset = target & offset_perde;
      check = pagetable[pg1][pg2] << 12;
      check = check | offset;
      /*printf("pg1: %u\tpg2: %u\toffset: %u\tcheck: %u\n", pg1, pg2, offset, check);
      printf("target: %u\tframe: %u\n", target, frames[check].virtual_address);*/
      if (frames[check].virtual_address == target){
        sprintf(buffer, "%08x", target);
        fputs("0x", out);
        fputs(buffer, out);
        fputs("\n", out);
        used_time++;
        frames[check].used_time = used_time;
      }else{
        ////// page fault case
        empty = 0;
        for (i = offset; i < frame_size; i=i+4096){
          if (frames[i].entry_time == 0){
            empty = 1;
            break;
          }
        }
        if (empty == 1){
          frames[i].virtual_address = target;
          entry_time++;
          used_time++;
          frames[i].entry_time = entry_time;
          frames[i].used_time = used_time;
          pagetable[pg1][pg2] = i / 4096;
          sprintf(buffer, "%08x", target);
          fputs("0x", out);
          fputs(buffer, out);
          fputs(" x\n", out);
        }else{
          // LRU
          if (algo == 1){
            victim = offset;
            for (j = offset; j < frame_size; j=j+4096){
              if (frames[j].used_time < frames[victim].used_time){
                victim = j;
              }
            }
          }else{
            // FIFO
            victim = offset;
            for (j = offset; j < frame_size; j=j+4096){
              if (frames[j].entry_time < frames[victim].entry_time){
                victim = j;
              }
            }
          }
          frames[victim].virtual_address = target;
          entry_time++;
          used_time++;
          frames[victim].entry_time = entry_time;
          frames[victim].used_time = used_time;
          pagetable[pg1][pg2] = victim / 4096;
          sprintf(buffer, "%08x", target);
          fputs("0x", out);
          fputs(buffer, out);
          fputs(" x\n", out);
        }
      }
    }
  }

  return 0;
}
