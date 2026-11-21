#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc , char *argv[]){
	//int ch;
	unsigned char buff[16];
	unsigned long off = 0;
	int extra = 0;
	int *ext = &extra;
	size_t n;
	if(argc != 2){
		printf("incorrect syntax\n");
		exit(EXIT_FAILURE);
	}
	FILE *target;
	if((target = fopen(argv[1],"rb")) == NULL){
		printf("file not found\n");
		exit(EXIT_FAILURE);
	}
	//while((ch = fgetc(target))!= EOF){
	//	printf("%02x",ch);
	//}
	while((n = fread(buff,1,sizeof(buff),target)) > 0){
		printf("%08lx: ",off);
		for(size_t i = 0; i<n ; i++){
			printf("%02x",buff[i]);
			if(i%2 != 0){
				printf(" ");
				if(n<15){
				(*ext)++;
			}
			}
			}
			if(n < 15){
				int space;
				space =40-((2*n)+(*ext));
				for(int s=0;s<space;s++){
				printf(" ");
			}
			}
			printf(" ");
			for(size_t i = 0; i < n; i++){
				putchar(isprint(buff[i]) ? buff[i] : '.');
			if(i == 15){
				printf("\n");
			}
			
		}
		off += n;
	}
	
	putchar('\n');
	fclose(target);
}
