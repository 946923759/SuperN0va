#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (32 * 1024 * 1024)

int main(int argc, char *argv[]) {
	FILE *fptr;
	FILE *fout;
	char length;
	char OutFileName[255];
	size_t BytesRead;
	unsigned char *buffer;
	
	buffer = (unsigned char *)malloc(BUF_SIZE);
	if(buffer == NULL)
	{
		printf("Cannot alloc %d bytes\n", BUF_SIZE);
		exit(-1);
	}
	//fptr = fopen("./1641360836300_352.ndf","rb");
	for (unsigned int i=1;i<argc;i++)
	{
		fptr = fopen(argv[i], "rb");
		
		if(fptr == NULL)
		{
		  printf("Error!\n");   
		  exit(1);             
		}
		
		strcpy(OutFileName, argv[i]);
		
		length = strlen(OutFileName);
		
		fread(buffer,sizeof(unsigned char),2,fptr);
		
		printf("%0x %0x\n", buffer[0], buffer[1]);
		if (buffer[0]==0 && buffer[1]==0)
		{
			printf("Is mp4\n");
			OutFileName[length-3] = 'm';
			OutFileName[length-2] = 'p';
			OutFileName[length-1] = '4';
			fout = fopen(OutFileName, "wb");
		}
		else if (buffer[0]==0x89 && buffer[1]==0x50)
		{
			printf("Is png\n");
			OutFileName[length-3] = 'p';
			OutFileName[length-2] = 'n';
			OutFileName[length-1] = 'g';
			fout = fopen(OutFileName, "wb");
			fwrite(buffer,sizeof(unsigned char),2,fout);
		}
		else
		{
			printf("Unknown file type for %s\n",OutFileName);
			continue;
		}
			
		
		for(;;)
		{
			BytesRead = fread(buffer, sizeof(unsigned char), BUF_SIZE, fptr);
			
			fwrite(buffer, sizeof(unsigned char), BytesRead, fout);
			
			if(BytesRead < BUF_SIZE)
			{
				break;  //file is done
			}
			
		}
		printf("Wrote %s\n",OutFileName);
		
		fclose(fptr);
		fclose(fout);
	}
	
	free(buffer);
	
    return 0;
}
