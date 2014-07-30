part of sample_lib;

class _List<T> {
  final List<T> list;
  final int elementSize;
  
  _List(this.elementSize) : list = new List<T>() {
  }
}
