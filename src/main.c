// M0: 블로킹 소켓, 클라이언트 한 번에 하나만 받는 echo 서버.
// 목적은 KV 프로토콜을 넣기 전에 가장 단순한 accept-read-write 루프부터 확인하는 것.
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 6380
#define BACKLOG 16
#define BUF_SIZE 4096

static int make_listen_socket(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(fd, BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

    return fd;
}

static void handle_client(int client_fd) {
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

int main(void) {
    int listen_fd = make_listen_socket();
    printf("KVCC listening on port %d (M0: echo, single client)\n", PORT);

    for (;;) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
        printf("클라이언트 접속: %s:%d\n", ip, ntohs(client_addr.sin_port));

        handle_client(client_fd);
        close(client_fd);
    }

    close(listen_fd);
    return 0;
}
