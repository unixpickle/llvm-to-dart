part of sample_lib;

abstract class _Structure {
  dynamic operator[](int idx);
  int indexOfOffset(int offset);
  int offsetOfField(int index);
}
