#include "client.h"

#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 4096

void client_handle(int client_fd) {
    char buf[BUF_SIZE];
    for (;;) {
        ssize_t n = read(client_fd, buf, sizeof(buf));
        if (n < 0) {
            perror("read");
            break;
        }
        if (n == 0) {
            printf("클라이언트 연결 종료\n");
            break;
        }
        // 받은 그대로 돌려보낸다. write가 n바이트를 한 번에 다 못 보낼 수도 있어서
        // 짧게 보내지면 나머지를 마저 보내는 루프가 필요하다(부분 쓰기 처리).
        ssize_t written = 0;
        while (written < n) {
            ssize_t w = write(client_fd, buf + written, (size_t)(n - written));
            if (w < 0) {
                perror("write");
                return;
            }
            written += w;
        }
    }
}
