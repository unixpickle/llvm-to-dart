struct SuperA {
  int a;
  char c;
};

struct SuperB {
  int b;
  char c;
};

struct Sub : public SuperA, public SuperB {
  short b;
  virtual void foo() {
    b = 2;
  }
};

int main() {
  Sub s;
  s.foo();
  
  SuperA * superPtrA = static_cast<SuperA *>(&s);
  SuperB * superPtrB = static_cast<SuperB *>(&s);
  Sub * subPtr = static_cast<Sub *>(superPtrA);
  subPtr = static_cast<Sub *>(superPtrB);
  
  return sizeof(Sub);
}