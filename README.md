# General

My goal is to create a simple tool that compiles C++ programs to Dart. The [emscripten](https://github.com/kripken/emscripten) project converts LLVM bitcode to JavaScript. In a similar fashion, this project will convert LLVM IR to Dart.

# Restrictions

The conversion between C++ and Dart is made difficult by C++'s pointer semantics. Because of this, several restrictions are in place:

**Do not cast a pointer to an integer or vice versa**

Doing so makes assumptions about the size of a pointer. Dart has no concept of "pointers" in the numeric sense.

	char myData[3];
	uint64_t myPtr = (uint64_t)myData;
	char * myData2 = (char *)myPtr;

**Do not cast a structure to a pointer and use the pointer to make cross-field memory accesses**

Structures are not backed by a single buffer. Instead, each field has its own memory store. This is done so function pointers and other data can be stored in the middle of a structure.

	struct {
	  char c1;
	  char c2;
	} obj; 
	short * s = (short *)&obj;
	s[0] = 0x1337;

# LLVM IR Patterns

Here are some common examples of LLVM IR patters and my thoughts on how I will represent them.

## Field access

    %c = alloca %struct.MainClass.0, align 8
    %1 = getelementptr inbounds %struct.MainClass.0* %c, i32 0, i32 1

Steps:

 * Use GEP to get a pointer to the field
 * Dereference the field

Thoughts:

 * A structure is allocated on the stack by declaring it as a variable.
 * A structure is represented as a `_Pointer` object.
 * The `getelementptr` call should simply add a number to the `_Pointer` object.
 * Reading a value simply dereferences a pointer.

## Static cast

    %s = alloca %struct.Sub, align 8
    ...
    %1 = bitcast %struct.Sub* %s to i8*
    %2 = getelementptr inbounds i8* %1, i64 16
    %3 = bitcast i8* %2 to %struct.SuperB*

Steps:

 * Cast structure to `uint8_t *`
 * Offset the pointer by 0x16 or some other offset
 * Cast pointer to other structure's type
