part of sample_lib;

class _BufferPointer implements _Pointer {
  final ByteData data;
  
  int get offset => data.offsetInBytes;
  ByteBuffer get buffer => data.buffer;
  
  _BufferPointer(ByteBuffer b, int o) : data = new ByteData.view(b, o);

  _Pointer operator+(int size) {
    return new _BufferPointer(buffer, offset + size);
  }

  _Pointer operator-(int size) {
    return new _BufferPointer(buffer, offset - size);
  }
  
  int get int8 => data.getUint8(0);
  int get int16 => data.getUint16(0, Endianness.LITTLE_ENDIAN);
  int get int32 => data.getUint32(0, Endianness.LITTLE_ENDIAN);
  int get int64 => data.getUint64(0, Endianness.LITTLE_ENDIAN);
  double get float32 => data.getFloat32(0, Endianness.LITTLE_ENDIAN);
  double get float64 => data.getFloat64(0, Endianness.LITTLE_ENDIAN);
  
  Function get function {
    throw new UnsupportedError('cannot cast buffer to Function');
  }
  
  _Pointer get pointer {
    throw new UnsupportedError('cannot cast buffer to _Pointer');
  }
  
  void set int8(int x) => data.setUint8(0, x);
  void set int16(int x) => data.setUint16(0, x, Endianness.LITTLE_ENDIAN);
  void set int32(int x) => data.setUint32(0, x, Endianness.LITTLE_ENDIAN);
  void set int64(int x) => data.setUint64(0, x, Endianness.LITTLE_ENDIAN);
  void set float32(double x) => data.setFloat32(0, x, Endianness.LITTLE_ENDIAN);
  void set float64(double x) => data.setFloat64(0, x, Endianness.LITTLE_ENDIAN);
}
