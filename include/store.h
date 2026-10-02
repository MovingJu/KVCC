#ifndef KVCC_STORE_H
#define KVCC_STORE_H

// 문자열 키 -> 문자열 값 저장소. 내부는 uthash(체이닝 해시테이블, include/store.c 참고)다.
// 여러 Store 인스턴스를 독립적으로 만들 수 있다 — 나중에(M5) 스레드마다 하나씩
// 둬서 샤딩할 때 이 구조를 그대로 재사용한다.
typedef struct Store Store;

Store *store_create(void);
void store_destroy(Store *s);

// value는 store_set 내부에서 복사된다 — 호출자는 넘긴 뒤 바로 버려도 된다.
void store_set(Store *s, const char *key, const char *value);

// 반환된 포인터는 store의 내부 버퍼를 가리킨다 — 같은 키에 store_set/store_del이
// 다시 호출되기 전까지만 유효하다. 필요하면 호출자가 복사해서 써야 한다.
const char *store_get(Store *s, const char *key);

// 지웠으면 1, 애초에 없었으면 0을 반환한다.
int store_del(Store *s, const char *key);

#endif
