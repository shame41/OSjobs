#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int argc,const char *argv[])
{
	int r;
	int f;
	int count=0;
	char str[256];

	f = open("/dev/shame41", O_RDWR);
	if(f < 0)
	{
		perror("----open failed!!!----\n");
		return -1;
	}
	else
	    printf("----open successed!!!----\n");
	    
	printf("----input a string:----");
	scanf("%[^\n]",str);
	
	r=write(f,str,strlen(str) * sizeof(char));
	str[r]='\0';
	
	printf("written %d characters\n",r);
	
	close(f);
	return 0;
}
