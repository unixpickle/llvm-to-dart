struct SomeClass {
  char as[8];
};

void myFunction1() {
  struct MainClass {
    int a;
  };
  MainClass c;
  c.a = 2;
}

void myFunction2() {
  struct MainClass : public SomeClass {
    int myInt;
    long myLong;
    float myFloat;
    double myDouble;
    SomeClass something;
    SomeClass somethings[3];
    SomeClass somethingElses[3][2];
  };
  MainClass c;
  c.myInt = 2;
  c.myLong = 0x800000000;
  c.myFloat = 3.14;
  c.myDouble = 3.1415;
}

int main() {
  myFunction1();
  myFunction2();
  return 0;
}
