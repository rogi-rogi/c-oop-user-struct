#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uInt;

static struct _user {
    const char* name;
    uInt age;
    float height;
    float weight;
    /*
    static uInt age;       // wrong
    static float height;   // wrong
    static float weight;   // wrong
    struct member can't have a memory classification specifier.
    so, access modifiers are difficult to make :(
    */
    void (*setName)(const char*);
    void (*setAge)(uInt);
    void (*setHeight)(float);
    void (*setWeight)(float);
    const char* (*getName)();
    uInt (*getAge)();
    float (*getHeight)();
    float (*getWeight)();
    void (*printUserInfo)();
}_user;

typedef struct _user User, *pUser;

extern pUser newUser(const char* name, uInt age, float height, float weight);
