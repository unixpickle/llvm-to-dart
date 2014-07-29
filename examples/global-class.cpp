class B {
public:
  B() : f(3), g(f + 2) {}

  float f;
  float g;

  virtual void myFunction() {}
  virtual void myFunction2() {}
  virtual unsigned long long myFunction3() {return 3;};
};

B b;

int main() {
  b.f = 3;
  b.g = 2.5;
}

