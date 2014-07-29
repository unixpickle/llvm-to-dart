struct MyClass {
  short (* func)(int, char);
};

short myFunction(int a, char b) {
  return (short)a + (short)b;
}

int main() {
  MyClass c;
  c.func = &myFunction;
  return c.func(3, 'a');
}