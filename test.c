#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  int fd = -1;
  char buf[512] = {0};
  int ret = -1;

  const char devPath[] = "/dev/register_hisangke_misc";
  fd = open(devPath, O_RDWR);
  if (fd < 0)
  {
    printf("Failed to open %s\n", devPath);
    return -1;
  }
  else
  {
    printf("Succeed to open %s\n", devPath);
  }

  // 读取
  ret = read(fd, buf, sizeof(buf) < 0);
  if (ret < 0)
  {
    printf("Failed to read %s\n", devPath);
    close(fd);
    return 0;
  }
  else
  {
    printf("Succeed to read [%s]\n", buf);
  }
  // 修改内容
  memset(buf, 0x00, sizeof(buf));//init buf 
  memcpy(buf, "Get you content", strlen("Get you content"));
  // 写入
  ret = write(fd, buf, sizeof(buf));
  if (ret < 0)
  {
    printf("Failed to write %s\n", devPath);
    close(fd);
    return 0;
  }
  else
  {
    printf("Succeed to write [%s]\n", buf);
  }
  // 读取
  ret = read(fd, buf, sizeof(buf) < 0);
  if (ret < 0)
  {
    printf("Failed to read %s\n", devPath);
    close(fd);
    return 0;
  }
  else
  {
    printf("Succeed to read [%s]\n", buf);
  }

  close(fd);

  printf("exit\n");

  fd = -1;

  return 0;
}
