#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(char argc, char * argv[])
{
    int fd;
    int ret;
    char buf[64] = "hello";
    char buf2[64] = "";
    int num[2]={123,2};
    char* num2 = (char*)num;
    
    /* 将要打开的文件的路径通过main函数的参数传入 */
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    
    fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        perror("fail to open file");
        return -1;
    }
    
    /* write data */
    ret = write(fd, num2, sizeof(num));
    if (ret < 0)
    {
        printf("read err!");
        return -1;
    }

    /* read data */
    ret = read(fd, num2, sizeof(num));
    if (ret < 0)
    {
        printf("read err!");
        return -1;
    }
    printf("buf2 = %d\n", num[0]);
    
    
    
    close(fd);
    return 0;
}
