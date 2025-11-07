#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(WIN32)
#include <windows.h>
#else
#include <unistd.h>
//#include <limits.h>
#define MAX_PATH 4096
#endif

#define BUF_SIZE (32 * 1024 * 1024)

void get_output_path(const char *input_path, char *output_path, size_t size) {
    char exe_path[MAX_PATH];
	
#if defined(WIN32)
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);

    // Find last backslash to isolate directory
    char *last_slash = strrchr(exe_path, '\\');
    if (last_slash) *(last_slash + 1) = '\0';  // Truncate after last backslash
#else
	ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);

    if (len != -1) {
        //exe_path[len] = '\0';  // Null-terminate the path
        //printf("Executable path (including exe) %s\n", exe_path);
		// Find last backslash to isolate directory
		char* last_slash = strrchr(exe_path, '/');
		if (last_slash) *(last_slash + 1) = '\0';  // Truncate after last backslash
		//printf("Executable path %s\n", exe_path);
    }
#endif

    // Extract filename from input path
    const char *filename = strrchr(input_path, '\\');
    filename = filename ? filename + 1 : input_path;
	//printf("%s",filename);
	
	snprintf(output_path, size, "%s%s", exe_path, filename);

    // // Split filename and extension
    // const char *dot = strrchr(filename, '.');
    // size_t base_len = dot ? (size_t)(dot - filename) : strlen(filename);

    // char base_name[MAX_PATH];
    // strncpy(base_name, filename, base_len);
    // base_name[base_len] = '\0';

    // const char *ext = dot ? dot : "";

    // // Construct new filename
    // char new_filename[MAX_PATH];
    // snprintf(new_filename, sizeof(new_filename), "%s%s", base_name, ext);

    // // Combine with executable directory
    // snprintf(output_path, size, "%s%s", exe_path, new_filename);
}

int main(int argc, char *argv[]) {
	FILE *fptr;
	FILE *fout;
	char length;
	char OutFileName[MAX_PATH];
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
		
		//strcpy(OutFileName, argv[i]);
		get_output_path(argv[i], OutFileName, sizeof(OutFileName));
		printf("%s",OutFileName);
		//return 0;
		
		length = strlen(OutFileName);
		
		//Read 2 bytes into buffer
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
			//Write the 2 bytes we read into fout. For mp4, the first two bytes are discarded.
			fwrite(buffer,sizeof(unsigned char),2,fout);
		}
		else
		{
			printf("Unknown file type for %s\n",OutFileName);
			continue;
		}
			
		
		//Write the rest of the file into fout.
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
