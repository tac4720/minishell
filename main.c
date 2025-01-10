#include <unistd.h>
#include <fcntl.h>
int main() {
    char *argv[] = {"/usr/bin/cat", "file1", "cat", "file2", NULL};
    execve(argv[0], argv, NULL);
    return 0;
}

// int main(int ac, char **av) {
//     char *filename = av[1];
//     int fd = open(filename, O_RDONLY);
//     if (fd == -1) {
//         perror("open");
//         return 1;
//     }

//     char buf[4096];
//     ssize_t nread;
//     while ((nread = read(fd, buf, sizeof(buf))) > 0) {
//         write(STDOUT_FILENO, buf, nread);
//     }

//     return 0;
// }