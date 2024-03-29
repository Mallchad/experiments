
#pragma once

#include <cstdint>
#include <cstddef>
// Non-Trivial Containers
#include <string_view>
#include <vector>

/**
   These are a collection of macros that provide code search hints, build system
   hints, and stub helper macros like stubs.
*/

// States the declaration origin, is distinct from things like  forward declarations
#define DECLARE
// States a function definition or a declaration of any kind
#define FUNCTION
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

// States a class or structis being inherited
#define INHERIT
// States the following code containers members
#define MEMBERS
// States the following code containers functions
#define FUNCTIONS
// States the following code contains friend declarations
#define FRIENDS

// States following hints are public
#define PUBLIC_DATA public
#define PUBLIC_MEMBERS public
#define PUBLIC_VARIABLES public
#define PUBLIC_FUNCTIONS public
// States the following hints are protected (internal to the class)
#define INTERNAL_DATA protected
#define INTERNAL_MEMBERS protected
#define INTERNAL_VARIABLES protected
#define INTERNAL_FUNCTIONS protected
// States the following hints are private
#define PRIVATE_DATA private
#define PRIVATE_MEMBERS private
#define PRIVATE_VARIABLES private
#define PRIVATE_FUNCTIONS private
#define FRIEND_CLASSES friend

// Will break the Unreal Header Tool if defined
// (It's parsing system is particularly basic and will misinterpret tokens)
#ifndef __UNREAL__
#define ABSTRACT
#define ABSTRACT_CLASS class
#define DECLARE_CLASS class
#define PURE_VIRTUAL
#endif

// No Operation empty statements, can silence warnings
#define NOOP (void)(0)
#define NOP (void)(0)
// Empty macros, can pad declarations for tools
#define NODECLARE
#define NODEC

// Confusing Static Usage
#define INTERNAL static
#define GLOBAL static

// Forward Declarations
FORWARD template<typename _CharT, typename _Traits, typename _Alloc> class basic_string;

// -- Redirectable typedefs --
typedef int8_t   fint8;
typedef int16_t fint16;
typedef int32_t fint32;
typedef int64_t fint64;

typedef uint8_t   fuint8;
typedef uint16_t fuint16;
typedef uint32_t fuint32;
typedef uint64_t fuint64;

// Fixed width floats only supported
typedef float ffloat;
typedef double fdouble;

// String types
typedef std::string fstring;
typedef std::string_view fstring_view;
typedef const char* cstring;
typedef const char* fpath;
