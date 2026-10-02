#ifndef KVCC_CLIENT_H
#define KVCC_CLIENT_H

// 연결된 클라이언트 소켓 하나를 처리한다. 현재(M0)는 echo만 한다 — 받은 바이트를
// 그대로 돌려보낸다. 클라이언트가 연결을 끊으면(EOF) 반환하고, fd는 닫지 않는다
// (닫는 책임은 호출자에게 있다).
void client_handle(int client_fd);

#endif
