part of sample_lib;

class _StructurePointer implements _Pointer {
  final _Structure structure;
  final int offset;
  
  dynamic get selectedField => structure[structure.indexOfOffset(offset)];
  
  int get selectedOffset {
    return offset - structure.offsetOfField(structure.indexOfOffset(offset));
  }
  
  _StructurePointer(this.structure, this.offset);
  
  _Pointer operator+(int size) {
    return new _StructurePointer(structure, offset + size);
  }
  
  _Pointer operator-(int size) {
    return new _StructurePointer(structure, offset - size);
  }
  
  int get int8 => new _Pointer(selectedField, selectedOffset).int8;
  int get int16 => new _Pointer(selectedField, selectedOffset).int16;
  int get int32 => new _Pointer(selectedField, selectedOffset).int32;
  int get int64 => new _Pointer(selectedField, selectedOffset).int64;
  double get float32 => new _Pointer(selectedField, selectedOffset).float32;
  double get float64 => new _Pointer(selectedField, selectedOffset).float64;
  
  Function get function {
    int idx = structure.indexOfOffset(offset);
    int startOff = structure.offsetOfField(idx);
    var field = structure[idx];
    if (field is Function) {
      if (offset != startOff) {
        throw new RangeError('bad Function alignment');
      }
      return field as Function;
    } else {
      return new _Pointer(field, startOff).function;
    }
  }
  
  _Pointer get pointer {
    int idx = structure.indexOfOffset(offset);
    int startOff = structure.offsetOfField(idx);
    var field = structure[idx];
    if (field is _Pointer) {
      if (offset != startOff) {
        throw new RangeError('bad _Pointer alignment');
      }
      return field as _Pointer;
    } else {
      return new _Pointer(field, startOff).pointer;
    }
  }
  
  void set int8(int x) {
    new _Pointer(selectedField, selectedOffset).int8 = x;    
  }
  
  void set int16(int x) {
    new _Pointer(selectedField, selectedOffset).int16 = x;
  }
  
  void set int32(int x) {
    new _Pointer(selectedField, selectedOffset).int32 = x;
  }
  
  void set int64(int x) {
    new _Pointer(selectedField, selectedOffset).int64 = x;    
  }
  
  void set float32(double x) {
    new _Pointer(selectedField, selectedOffset).float32 = x;    
  }
  
  void set float64(double x) {
    new _Pointer(selectedField, selectedOffset).float64 = x;
  }
}
