# c-oop-user-struct

> C 언어에서 객체 지향 프로그래밍 구현하기

C 언어에서 구조체와 함수 포인터를 활용하여 객체 지향 프로그래밍의 핵심 개념들을 구현하는 방법을 보여주는 교육용 프로젝트입니다.

## 🎯 프로젝트 목적

- C 언어에서 클래스와 객체 개념 구현
- 함수 포인터를 통한 메서드 구현
- 생성자 패턴과 제한적 캡슐화 구현
- OOP 개념의 C 언어 적용 학습 (한계점 포함)

## 📁 프로젝트 구조

```
c-oop-user-struct/
├── class.h      # User 클래스 정의 및 인터페이스
├── class.c      # User 클래스 구현
├── main.c       # 사용 예제 및 테스트
└── README.md    # 프로젝트 문서
```

## 🔧 주요 기능

### User 클래스 구현

- **속성**: 이름, 나이, 키, 몸무게
- **메서드**:
  - Setter: `setName()`, `setAge()`, `setHeight()`, `setWeight()`
  - Getter: `getName()`, `getAge()`, `getHeight()`, `getWeight()`
  - 유틸리티: `printUserInfo()`

### OOP 개념 구현

- **클래스**: 구조체 + 함수 포인터
- **생성자**: `newUser()` 함수
- **제한적 캡슐화**: static 함수를 통한 메서드 은닉 (필드 은닉은 불가능)
- **메서드**: 함수 포인터를 통한 인스턴스 메서드

## 🚀 사용 방법

### 컴파일

```bash
gcc -o user_program main.c class.c
```

### 실행

```bash
./user_program
```

### 예제 코드

```c
#include "class.h"

int main() {
    // User 객체 생성
    pUser user = newUser("mike", 26, 178.4, 72.6);

    // 사용자 정보 출력
    user->printUserInfo();

    // 메모리 해제
    free(user);

    return 0;
}
```

### 실행 결과

```
-------[user info]-------
  name   : mike
  age    : 26
  height : 178.40(cm)
  weight : 72.60(kg)
-------------------------
```

## 💡 핵심 개념

### 1. 구조체 기반 클래스

```c
typedef struct _user {
    const char* name;
    uInt age;
    float height;
    float weight;

    // 메서드 포인터들
    void (*setName)(const char*);
    uInt (*getAge)();
    void (*printUserInfo)();
    // ...
} User, *pUser;
```

### 2. 함수 포인터를 통한 메서드

- 구조체 내부에 함수 포인터 선언
- 초기화 시 실제 함수와 연결
- 객체처럼 `user->printUserInfo()` 형태로 호출 가능

### 3. Static을 활용한 제한적 캡슐화

- **메서드만** static으로 선언하여 private 효과 구현
- ⚠️ 구조체 멤버 변수(필드)는 static 선언 불가능 (C 언어 제한)
- static 메서드는 외부에서 직접 접근 불가능
- 구조체의 함수 포인터를 통해서만 접근 가능

## 🎓 학습 포인트

1. **C 언어의 한계**: 진정한 OOP 지원 부족
2. **창의적 해결책**: 구조체와 함수 포인터 활용
3. **메모리 관리**: 동적 할당과 해제의 중요성
4. **설계 패턴**: 생성자 패턴과 초기화 과정

## ⚠️ 주의사항

- **완전한 캡슐화 불가능**: `static` 필드는 구조체 멤버로 사용할 수 없어 멤버 변수 은닉이 불가능
- **메모리 관리**: 메모리 누수 방지를 위해 반드시 `free()` 호출 필요
- **Thread Safety**: 전역 `this` 포인터로 인한 멀티스레드 환경에서의 안전성 이슈
- **진정한 OOP 아님**: C 언어의 한계로 인해 OOP를 모방한 것일 뿐, 진정한 객체 지향은 아님

## 🔗 확장 가능성

### 📌 다중 객체 지원 개선

현재 전역 `this` 포인터 방식은 **하나의 객체만 동시에 처리할 수 있는 한계**가 있습니다. 하지만 C 언어에서 **self 포인터를 명시적으로 넘기지 않으면서도** 객체의 메서드를 호출하는 방법으로는 **현재 구현이 최선의 접근법**입니다.

**대안적 접근법들:**

- **명시적 self 전달**: `user_setName(user, "name")` 형태 (Java/C++ 스타일 포기)
- **스레드별 저장소**: `__thread` 키워드 활용 (플랫폼 종속적)
- **컨텍스트 스택**: 현재 객체를 스택으로 관리 (복잡성 증가)

### 🧬 상속 구현 가능성

**구조체 컴포지션**을 통해 상속 구현 가능:

```c
typedef struct {
    User super;      // 부모 클래스를 첫 번째 멤버로 배치
    char* email;     // 추가 속성
    char* phone;
} ExtendedUser;

// 안전한 업캐스팅: ExtendedUser* → User*
User* base = (User*)&extended_user;
```

C 표준은 구조체의 첫 번째 멤버가 구조체 시작 주소와 동일함을 보장합니다.

### ⚡ 가상 함수 테이블 (Vtable) 구현 가능성

**함수 포인터 테이블**을 통해 다형성 구현 가능:

```c
typedef struct {
    void (*draw)(Shape* self);
    double (*area)(Shape* self);
} ShapeVTable;

typedef struct {
    ShapeVTable* vtable;  // 가상 함수 테이블
    int x, y;
} Shape;

// 가상 함수 호출: shape->vtable->draw(shape);
```

단, 메모리 오버헤드와 복잡성이 크게 증가합니다.

### 🔧 제네릭/템플릿 구현 가능성

C에서 제네릭 구현을 위한 주요 기법들:

**1. 매크로 기반 템플릿**

```c
#define DECLARE_VECTOR(TYPE) \
    typedef struct { \
        TYPE* data; \
        size_t size; \
    } Vector_##TYPE;
```

**2. Template Headers (권장)**

```c
// vector.h - 다중 포함 가능한 헤더
#ifndef T
#error "T must be defined"
#endif

typedef struct {
    T* data;
    size_t count;
} Vector;
```

**3. Void 포인터 + 크기 정보**

```c
typedef struct {
    void* data;
    size_t element_size;
    size_t count;
} GenericVector;
```

### 💡 권장사항

- **단순한 경우**: 현재 구조 유지 (가장 직관적)
- **상속 필요시**: 구조체 컴포지션 활용
- **다형성 필요시**: 함수 포인터 테이블 검토
- **제네릭 필요시**: Template Headers 방식 추천
- **복잡한 OOP**: C++ 사용

## ⚖️ 라이선스

모든 코드의 상업목적 사용을 금지하며, 교육 목적으로만 사용할 수 있습니다.
