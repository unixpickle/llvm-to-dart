part of sample_lib;

abstract class _Pointer {
  _Pointer operator+(int bytes);
  _Pointer operator-(int bytes);
  Uint8List dereference8();
  Uint16List dereference16();
  Uint32List dereference32();
  Uint64List dereference64();
  Object dereferenceObject();
  _Pointer dereferencePointer();
}
