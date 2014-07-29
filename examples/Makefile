all: global-struct.s global-function.s global-class.s global-vector.s nested-class.s func-ptr.s static-cast.s

global-struct.s:
	clang -emit-llvm -S global-struct.cpp

global-function.s:
	clang -emit-llvm -S global-function.cpp

global-class.s:
	clang -emit-llvm -S global-class.cpp

global-vector.s:
	clang -emit-llvm -S global-vector.cpp

nested-class.s:
	clang -emit-llvm -S nested-class.cpp

func-ptr.s:
	clang -emit-llvm -S func-ptr.cpp

static-cast.s:
	clang -emit-llvm -S static-cast.cpp

clean:
	rm -f *.s
