#ifndef KVCC_SERVER_H
#define KVCC_SERVER_H

// 지정된 포트에 bind/listen까지 끝낸 리스닝 소켓 fd를 반환한다.
// 실패하면 원인을 stderr에 출력하고 프로세스를 종료한다(M0 단계에서는 복구할 방법이 없음).
int server_create_listener(int port, int backlog);

#endif
