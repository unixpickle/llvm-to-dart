part of sample_lib;

class _ListPointer<T> implements _Pointer {
  _List<T> list;
  int offset;
  
  T get selectedObject => list.list[offset ~/ list.elementSize];
  int get selectedOffset => offset % list.elementSize;
  
  _ListPointer(this.list, this.offset);

  _Pointer operator+(int bytes) {
    return new _ListPointer<T>(list, offset + bytes);
  }

  _Pointer operator-(int bytes) {
    return new _ListPointer<T>(list, offset - bytes);
  }
  
  int get int8 => new _Pointer(selectedObject, offset).int8;
  int get int16 => new _Pointer(selectedObject, offset).int16;
  int get int32 => new _Pointer(selectedObject, offset).int32;
  int get int64 => new _Pointer(selectedObject, offset).int64;
  double get float32 => new _Pointer(selectedObject, offset).float32;
  double get float64 => new _Pointer(selectedObject, offset).float64;
  
  Function get function {
    if (selectedObject is Function) {
      return selectedObject as Function;
    } else {
      return new _Pointer(selectedObject, offset).function;
    }
  }
  
  _Pointer get pointer {
    if (selectedObject is _Pointer) {
      return selectedObject as _Pointer;
    } else {
      return new _Pointer(selectedObject, offset).pointer;
    }
  }
  
  void set int8(int x) {
    new _Pointer(selectedObject, offset).int8 = x;
  }
  
  void set int16(int x) {
    new _Pointer(selectedObject, offset).int16 = x;
  }
  
  void set int32(int x) {
    new _Pointer(selectedObject, offset).int32 = x;
  }
  
  void set int64(int x) {
    new _Pointer(selectedObject, offset).int64 = x;    
  }
  
  void set float32(double x) {
    new _Pointer(selectedObject, offset).float32 = x;    
  }
  
  void set float64(double x) {
    new _Pointer(selectedObject, offset).float64 = x;
  }
}
