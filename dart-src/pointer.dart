part of sample_lib;

abstract class _Pointer {
  _Pointer operator+(int bytes);
  _Pointer operator-(int bytes);
  
  int get int8;
  int get int16;
  int get int32;
  int get int64;
  double get float32;
  double get float64;
  Function get function;
  _Pointer get pointer;
  
  void set int8(int x);
  void set int16(int x);
  void set int32(int x);
  void set int64(int x);
  void set float32(double x);
  void set float64(double x);
  
  factory _Pointer(dynamic o, int offset) {
    // TODO: this
  }
}
