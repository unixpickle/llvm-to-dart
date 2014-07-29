part of sample_lib;

abstract class _Structure {
  int parentOffset;
  Object parentObject;
  
  dynamic getFieldAtOffset(int offset);
  dynamic getFieldAtIndex(int index);
  int getFieldOffset(int index);
}
