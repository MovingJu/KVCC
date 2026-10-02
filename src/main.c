// M0: 블로킹 소켓, 클라이언트 한 번에 하나만 받는 echo 서버.
// 목적은 KV 프로토콜을 넣기 전에 가장 단순한 accept-read-write 루프부터 확인하는 것.
// 소켓 생성(server.c)과 클라이언트 처리(client.c)를 분리하고, main.c는 둘을 엮는
// accept 루프만 맡는다.
#include "client.h"
#include "server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 6380
#define BACKLOG 16

int main(void) {
    int listen_fd = server_create_listener(PORT, BACKLOG);
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

        client_handle(client_fd);
        close(client_fd);
    }

    close(listen_fd);
    return 0;
}
