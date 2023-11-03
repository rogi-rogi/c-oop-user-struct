#include "class.h"

pUser this; //flag

static void _setName(const char*);
static void _setAge(uInt);
static void _setHeight(float);
static void _setWeight(float);
static const char* _getName();
static uInt _getAge();
static float _getHeight();
static float _getWeight();
static void _printUserInfo();

static void initialization()
{
    this->setName = _setName;
    this->setAge = _setAge;
    this->setHeight = _setHeight;
    this->setWeight = _setWeight;
    this->getName = _getName;
    this->getAge = _getAge;
    this->getHeight = _getHeight;
    this->getWeight = _getWeight;
    this->printUserInfo = _printUserInfo;
}
static void constructor(const char* name, uInt age, float height, float weight)
{
    this->setName(name);
    this->setAge(age);
    this->setHeight(height);
    this->setWeight(weight);
}

pUser newUser(const char* name, uInt age, float height, float weight)
{
    this = (pUser)malloc(sizeof(User));
    initialization();
    constructor(name, age, height, weight);
    return this;
}

static void _setName(const char* _name) { this->name = _name;}
static void _setAge(uInt _age)          { this->age = _age; }
static void _setHeight(float _height)   { this->height = _height; }
static void _setWeight(float _weight)   { this->weight = _weight; }
static const char* _getName()           { return this->name; }
static uInt _getAge()                   { return this->age; }
static float _getHeight()               { return this->height; }
static float _getWeight()               { return this->weight; }
static void _printUserInfo()
{
    puts(  "-------[user info]-------");
    printf("  name   : %s\n", this->getName());
    printf("  age    : %u\n", this->getAge());
    printf("  height : %.2f(cm)\n", this->getHeight());
    printf("  weight : %.2f(kg)\n", this->getWeight());
    puts(  "-------------------------");
}
