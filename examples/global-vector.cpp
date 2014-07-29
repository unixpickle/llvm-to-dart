int myGlobal = 3;
int myGlobalList[2] = {2, 1};

int main() {
  myGlobal = 4;

  int * ptr = myGlobalList;
  *ptr = 2;
  ++ptr;
  *ptr = 3;

  return 0;
}

