
#pragma once

// Basic functionality headers
#include <cstdint>

/**
   These are a collection of macros that provide code search hints, build system
   hints, and stub helper macros like stubs.
*/

// States the declaration origin, is distinct from things like  forward declarations
#define DECLARE
// States a function definition or a declaration of any kind
#define FUNCTION
// States any kind of function differention, ie lambda, function pointers
// Made to support trialing return type, doesn't work with operators.
#define PROCEDURE auto
// States a variable declaration, primarily intended for classes and structs
#define DATA
// States a variable declaration
#define VARIABLE
#define VAR
// States a forward declaration
#define FWD
#define FWD_FUNCTION
#define FWD_CLASS class
#define FWD_STRUCT struct
#define FORWARD
#define FORWARD_FUNCTION
#define FORWARD_CLASS class
#define FORWARD_STRUCT struct
// States a function should be pure
#define PURE  = 0
#define PURE_FUNCTION
// States a class is intended to be inheritable
#define BASE
#define BASE_FUNCTION
// States a constructor declaration or definition
#define CONSTRUCTOR
// States a destructor declaration or definition
#define DESTRUCTOR
// States a move constructor declaration or definition
#define MOVE_CONSTRUCTOR
// States a move constructor declaration or definition
#define COPY_CONSTRUCTOR
/// Defines a copy-assignment specific equals operator (=)
#define COPY_ASSIGNMENT
// States a conversion function, essentially typecasting
#define CONVERSION
// Member variable immediately evaluated at compile time
#define IMMEDIATE static constexpr

// States a class or structis being inherited
#define INHERIT
// States the following code containers members
#define MEMBERS
// States the following code containers functions
#define FUNCTIONS
// States the following code contains friend declarations
#define FRIENDS

// Marks a fold expression
#define FOLD


// Will break the Unreal Header Tool if defined
// (It's parsing system is particularly basic and will misinterpret tokens)
#ifndef __UNREAL__
#define ABSTRACT
#define ABSTRACT_CLASS class
#define DECLARE_CLASS class
#define PURE_VIRTUAL
#endif

// No Operation empty statements, can silence warnings or be used as breakpoints
#define NOP asm("nop")
// Empty macros, can pad declarations for tools
#define NODECLARE
#define NODEC

// Confusing Static Usage
#define INTERNAL static
#define GLOBAL static

#define FORCEINLINE __attribute__((always_inline))

// -- Redirectable typedefs --
using fint8   = int8_t;
using fint16  = int16_t;
using fint32  = int32_t;
using fint64  = int64_t;

using fuint8  = uint8_t;
using fuint16 = uint16_t;
using fuint32 = uint32_t;
using fuint64 = uint64_t;

using i8   = int8_t;
using i16  = int16_t;
using i32  = int32_t;
using i64  = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
struct u128 { u64 d[2]; };
struct u256 { u64 d[4]; };
struct u512 { u64 d[8]; };
struct u1024 { u64 d[16]; };
struct u2048 { u64 d[32]; };
struct u4096 { u64 d[64]; };

// Fixed width floats only supported
using ffloat  = float;
using fdouble = double;

using f32 = float;
using f64 = double;

using isize = i64;
using usize = u64;

using byte = u8;

// String types
// using fstring = std::basic_string<char>;
// using fstring_view = std::basic_string_view<char>;
using cstring = const char*;
// using fpath = const char*;

// -- More complex Stuff --
#define INVOKE_MEMBER(object, function, ...) ((object).*(function))(__VA_ARGS__)
