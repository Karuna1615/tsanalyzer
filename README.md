# tsanalyzer
tsanalyzer Project by karuna
#include <stdio.h>
#include <string.h>

void main()
{

FILE *myfile;

FILE *output;

int i=0,j;
unsigned int buffer;

int o,count=0;
myfile=fopen("star.ts","rb");
output = fopen("output2.txt","w");

do{
    o=fread(&buffer, 1, 1, myfile);
    printf("%d: ",o); 
    if(o!=1)
    break;  
    if (i<4)
    {
    i++;
    printf("%d: ",i);  
    }
    printf("%x\n",buffer); 
    fprintf(output,"%x ",buffer);
    count++;
   }
   while(count<4);
 } 
