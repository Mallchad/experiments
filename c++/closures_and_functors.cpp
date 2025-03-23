
/**
   In this file is laid out a minimal implimentation of 'std::function'. As well
   as various other demonstrations in relation to function types. This
   implimentation, named 'procedure', is a closure type function object (or
   function pointer wrapper) which means it allows for storing and swapping
   functions with a context object to be called at a later date.

   The context object serves to provide the necessary static internal data for
   the function to carry out its intended task, ie the 'this' pointer, or a
   snapshot of internal state.
*/


#include "libraries/code_helpers.h"
#include <cstdio>
#include <functional>
#include <utility>

/** Proxy function to make it possible to store typing information for
 * type-erased function pointers */
template <typename t_procedure, typename t_context, typename t_args>
bool procedure_closure_proxy( void (*proc)(), void* context, t_args args )
{
    // Extract closure data from using types
    auto _proc = reinterpret_cast<t_procedure>( proc );
    auto _context = *static_cast<t_context*>( context );
    return _proc( _context, args);
}

/** A type erased function pointer
 *
 * This version is a fairly naive implimentation that only works on standard
 * function types, ie not member functions, lambdas, or functors. It would be
 * easily expandable to support multiple arguments. Multiple closure captures
 * (multiple context arguments), is a bit more difficult, and the user API would
 * become awkward anyway.
 *
 * Acts on 'context_data' provided by during assignment, which is always treated as correct.
 * Extra paremeter data is provided as 'args' during a call invocation
 * signature of the callable
 *
 * The function signature of the assigned must be in the form
 * bool <name>(context, ...t_args)
 * The context is an abitrary value that provides the non-argument data the stored function
 * needs to operator, ie the 'this' pointer. It may also be a copyable structure or container. */
template <typename t_args>
struct procedure
{
    using t_closure = bool (*)( void(*)(), void*, t_args );
    using t_generic_func = void(*)();
    /// The wrapped procedure which may be called to yield the stored closure
    t_closure data = nullptr;
    /// The real assigned procedure without closures
    void (*proc_data)() = nullptr;
    /// The context the stored procedure requires
    void* context_data = nullptr;
    constexpr static i64 small_storage_size = 32;
    byte small_storage[ small_storage_size ] = {};
    void (*tmp_ptr)();

    template <typename t_procedure, typename t_copyable>
    void
    assign( t_procedure proc, t_copyable context )
    {
        static_assert( sizeof(t_copyable) < small_storage_size,
                       "context type does not fix on the stack, consider increasing small "
                       "size or allocating some memory for it before assigning." );
        data = &procedure_closure_proxy<t_procedure, t_copyable>;
        context_data = small_storage;
        t_copyable* writehead = reinterpret_cast<t_copyable*>( context_data );
        *writehead = context;
        proc_data = reinterpret_cast<t_generic_func>( proc );
    }

    bool
    operator () ( t_args args )
    {
        if (data == nullptr)
        { return false; }
        return data( proc_data, context_data, args);
    }
};

// -- Alternate and Test Implimentations

/** This is a naive implimentation of a type-erased function wrapper that
 * supports all kinds of functors, function pointers, lambdas, and function
 * objects. This requires additional indirection through a vtable, as opposed to
 * just a type-restoring 1-3 line template-function that wraps it, this
 * implimentation is much more generic.
 *
 * This function is not a closure and cannot capture context on it's own. */
template<typename t_return, typename...  t_args>
struct basic_procedure
{
    using t_self = basic_procedure<t_return, t_args...>;
    FORWARD struct i_procedure_impl;
    FORWARD template <typename t_procedure> struct virtual_procedure;

    i_procedure_impl* impl = nullptr;

    struct i_procedure_impl
    {
        virtual bool invoke(t_args ...args) = 0;
        virtual DESTRUCTOR ~i_procedure_impl() = default;
    };

    template <typename t_procedure>
    struct virtual_procedure : i_procedure_impl
    {
        t_procedure data;

        CONSTRUCTOR virtual_procedure( t_procedure&& proc ) : data( std::move(proc) ) {}

        bool invoke( t_args ...args ) override final
        { return data( args... ); }
        ~virtual_procedure() override {}
    };

    /** WARNING: This is a quirk/defect in C++ that means that lambdas for some
     * reason absolutely will not pass through a constructor correctly and will
     * end in a bad state, eventually leading to a segfault. This is a
     * cautionary tale in the janky behaviour of constructors that always seems
     * to prop up, so we have a copy assignment operator, that works for the
     * lambdas, and the constructor, so we can initialize-on-decleration */
    CONSTRUCTOR basic_procedure() { }

    template <typename t_procedure>
    CONSTRUCTOR basic_procedure( t_procedure&& proc )
    {
        delete impl;
        this->impl = new virtual_procedure<t_procedure>( std::forward<t_procedure>(proc) );
    }

    template <typename t_procedure>
    t_self& operator = ( t_procedure&& proc )
    {
        delete impl;
        this->impl = new virtual_procedure<t_procedure>( std::forward<t_procedure>(proc) );
        return *this;
    }

    template<typename t_procedure>
    void assign( t_procedure&& proc )
    {
        delete impl;
        impl = new virtual_procedure<t_procedure>( std::forward<t_procedure>(proc) );
    }

    bool invoke( t_args ...args )
    { return impl->invoke( std::forward<t_args>( args )... ); }

    bool operator () ( t_args ...args )
    { return this->invoke( std::forward<t_args>( args )... ); }

    DESTRUCTOR ~basic_procedure()
    { delete this->impl; }

};

template <typename t_procedure>
struct generic_procedure;

/** This is a more robust and generic implimentation that bundles the previous
 * two implimentations together. It is a type-erased wrapper that supports all
 * function types (function pointers, lambdas, function objects) AND supports
 * closures, or atleast, that's the idea.
 *
 * It can provide an abitrary number of arguments as well as capture 1 context
 * argument. The 'context' argument will replace the first argument when the funciton is called
 * and it is intended to provide meaningful information like 'this' pointers and state, but it may
* provide anything really, this can be used as an alternative to a lambda. */
template <typename t_return, typename ... t_args>
struct generic_procedure< t_return( t_args... ) >
{
    using t_function = t_return( t_args... );
    using t_function_ptr = t_function*;
    using t_self = generic_procedure< t_function_ptr >;
    FORWARD struct i_procedure_impl;
    FORWARD template <typename t_procedure> struct procedure_impl;
    FORWARD template <typename t_procedure, typename t_context> struct closure;
    i_procedure_impl* impl = nullptr;
    IMMEDIATE isize small_size = 100;
    byte small_storage[ small_size ];

    /** WARNING: This is a quirk/defect in C++ that means that lambdas for some
     * reason absolutely will not pass through a constructor correctly and will
     * end in a bad state, eventually leading to a segfault. This is a
     * cautionary tale in the janky behaviour of constructors that always seems
     * to prop up, so we have a copy assignment operator, that works for the
     * lambdas, and the constructor, so we can initialize-on-decleration */

    CONSTRUCTOR generic_procedure() {}

    template <typename t_procedure>
    CONSTRUCTOR generic_procedure( t_procedure proc )
    { assign( proc ); }

    template <typename t_procedure>
    t_self& operator = ( t_procedure proc )
    { assign( proc ); }

    template <typename t_procedure>
    void assign( t_procedure proc )
    {
        constexpr i64 procedure_size = sizeof(procedure_impl<t_procedure>);
        static_assert( procedure_size < small_size,
                       "procedure object or pointer is too large to fit on the stack." );
        delete impl;
        impl = new(small_storage) procedure_impl<t_procedure> { std::forward<t_procedure>( proc ) };
    }


    template <typename t_procedure, typename t_context>
    void assign_closure( t_procedure proc, t_context context )
    {
        constexpr i64 closure_size = sizeof( closure_impl<t_procedure, t_context>);
        static_assert( closure_size < small_size,
                       "procedure object or pointer is too large to fit on the stack." );
        delete impl;
        impl = new closure_impl<t_procedure, t_context>
            { std::forward<t_procedure>( proc ), context };
    }

    t_return invoke( t_args&& ... args)
    { return impl->invoke( std::forward<t_args>(args)... ); }

    t_return
    operator () ( t_args&& ... args )
    { return this->invoke( std::forward<t_args>(args)... ); }

    // NOTE: It's on the stack, doesn't need to be freed. Reconsider if it moves onto the heap.
    // DESTRUCTOR ~generic_procedure()
    // { delete this->impl; }

    // -- Magic Internal Setup --

    /** Setup a base type to enable switching between functors with vtables */
    struct i_procedure_impl
    {
        virtual bool invoke(t_args ...args) PURE;
        virtual DESTRUCTOR ~i_procedure_impl() = default;
    };

    /** Closure implimentation, passes static data back to the function */
    template <typename t_procedure, typename t_context>
    struct closure_impl final : i_procedure_impl
    {
        t_procedure proc;
        t_context context;

        CONSTRUCTOR closure_impl( t_procedure&& _proc, t_context _context )
            : proc( std::move(_proc) ),
              context( _context ) {}

        t_return
        invoke( t_args ...args ) override final
        { return proc( context, args...); }
    };

    /** Context-less implimentation, supports most function types */
    template <typename t_procedure>
    struct procedure_impl final : i_procedure_impl
    {
        t_procedure proc;

        CONSTRUCTOR procedure_impl( t_procedure&& _proc )
            : proc( std::move(_proc) ) {}

        t_return
        invoke( t_args ...args ) override final
        { return proc( args...); }
    };

};


// I suggest you rename procedure_args to your preffered name, I suggest simply
// 'procedure', 'function' or 'closure

/** Common type that eliminates the need for inputting awkward function types,
 * ie 'bool(int, int)'. Arguments only.  It is fairly rare to require anything
 * but a void reassignable functions so bool is a good default. */
template <typename ... t_args>
using procedure_args = generic_procedure<bool( t_args... )>;

template <typename ... t_args>
using procedure_void = generic_procedure<void( t_args... )>;


// -- Demonstration Setup
bool print_num(int context, int arg)
{
    printf( "print_num arg: %d\n", arg );
    return true;
}

int main()
{
    int bind = 42;
    procedure<int> callable;
    // Assigning a simple function
    callable.assign( &print_num, 0 );
    callable( 1 );
    // Lambdas won't even pass basic error checking
    // callable.assign( []() { printf("bound simple lambda\n"); return 1;}, 0 );

    // vtable version works with more types
    basic_procedure<bool, int, int> function_callable =  [bind](int, int) -> bool
    { printf("bound simple lambda %d\n", bind); return false; } ;
    function_callable.invoke( 20, 25 );
    function_callable.invoke( 0, 5 );

    function_callable.assign( print_num );
    function_callable.invoke( 10, 15 );

    function_callable.assign( [bind](int, int) -> bool
        { printf("bound simple lambda %d\n", bind); return false; } );
    function_callable.invoke( 1, 1 );

    bind = 256;
    function_callable = [bind](int, int) -> bool
    { printf("bound simple lambda %d\n", bind); return false; } ;
    function_callable.invoke( 20, 25 );

    // -- Combined Closure Generic Function --
    generic_procedure<bool(int, int)> _test1 = [bind](int a, int b) -> bool
    { printf("bound simple lambda %d\n", bind + a + b); return false; };
    _test1.invoke( 64, 95 );
    generic_procedure<bool(int, int)> generic_callable = print_num;
    generic_callable.invoke( 1, 2 );

    // Simplified argument only interface
    procedure_args<int, int> simple_callable = print_num;
    simple_callable.invoke(1, 812 );
    simple_callable(  1, 92315 );

    procedure_args<int> closure_callable;
    closure_callable.assign_closure( print_num, 747 );
    closure_callable.invoke( 78512 );

    struct v3 { u32 x, y, z; };
    closure_callable.assign_closure( []( int a, int b) -> bool
        { print_num(a,  a + b  ); return true; }, 10 );
    closure_callable.invoke( 10 );
    procedure_args<> closure_noargs;
    closure_noargs.assign_closure( []( v3 a )
        { printf("closure sum: %d\n", (a.x + a.y+ a.z)); return true; }, v3{1, 2, 3 } );
    closure_noargs.invoke();

}

int closures_and_functors()
{ main(); return 1;}
