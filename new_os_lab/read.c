#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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
	    
	printf("----input a integer for read count:----");
	scanf("%d",&count);
	
	r=read(f,str,count * sizeof(char));
	str[r]='\0';
	
	printf("----Get a string: %s----\n",str);
	printf("----string length:%d----\n",r);
	
	getchar();
	close(f);
	return 0;
}
