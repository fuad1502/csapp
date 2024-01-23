#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  int fileno = open(argv[1], O_RDONLY, 0);
  struct stat file_stat;
  fstat(fileno, &file_stat);

  char *buf = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fileno, 0);

  write(1, buf, file_stat.st_size);
}
