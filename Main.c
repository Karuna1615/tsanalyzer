#include<stdio.h>
//function declaration
void printHeader(unsigned int buffer, int packetCount);
unsigned int swap_endian(unsigned int buffer);
void nextHeader(char n);

int main( int argc, char *argv[] )  
{
	FILE *myFile = fopen(argv[1], "rb");
	if(myFile == NULL)
	{
		printf("Failed: File could not be opened ");
		return 1;
	}
	//variable declaration
	int i=0;
    unsigned int buffer=0,x;
    int readCount, count=0;
	char input;
	do
	{   
	    //reads 4 bytes of data
		readCount=fread(&buffer,sizeof(buffer),1,myFile);
		if(readCount != 1)
		{
			break;
		}
		//swapping endianess
	    x = swap_endian(buffer);
        printf("\n\nHEADER: %08X\n\n",x);
        printHeader(x, i);
		//seeking into next packet
		fseek(myFile,184,SEEK_CUR);
        i++;
		printf("press(n): ");
	    input = getchar();
        while((getchar())!= '\n');
	}
	while (input == 'n');
	fclose(myFile);
}

//Prints Header information        
void printHeader(unsigned int buffer, int packetCount)    
{
    printf("==================TS Packet HEADER count %d================\n", packetCount);
	printf("SyncByte                :    0x%02X\n", ((buffer & 0xFF000000) >>24));
    printf("TEI                     :    0x%02X\n", ((buffer & 0x800000)>>23));
    printf("PUSI                    :    0x%02X\n", ((buffer & 0x400000)>>22));
    printf("Transport Priority      :    0x%02X\n", ((buffer & 0x200000)>>21));
    printf("PID                     :    0x%04X, %d\n", ((buffer & 0x1FFF00)>>8),((buffer & 0x1FFF00)>>8));
    printf("TSC                     :    0x%02X\n", ((buffer & 0xC0)>>6));
    printf("Adaptation Field Control:    0x%02X\n", ((buffer & 0x30)>>4));
    printf("Continuity counter      :    0x%02X\n", (buffer & 0xf));
}

//converting endians
unsigned int swap_endian(unsigned int buffer)
{
    unsigned int byte0 = (buffer & 0x000000FF) >> 0;
    unsigned int byte1 = (buffer & 0x0000FF00) >> 8;
    unsigned int byte2 = (buffer & 0x00FF0000) >> 16;
    unsigned int byte3 = (buffer & 0xFF000000) >> 24;
    return ((byte0<<24)|(byte1<<16)|(byte2<<8)|(byte3<<0)); 
}

