
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
template<typename t_return, typename...  t_args>
struct basic_procedure
{
    FORWARD struct i_procedure_impl;
    FORWARD template <typename t_procedure> struct virtual_procedure;

    i_procedure_impl* impl = nullptr;

    struct i_procedure_impl
    {
        virtual bool invoke(t_args ...args) = 0;
        virtual DESTRUCTOR ~i_procedure_impl() = default;
    };

    template<typename t_procedure>
    struct virtual_procedure : i_procedure_impl
    {
        t_procedure data;

        CONSTRUCTOR virtual_procedure( t_procedure&& proc ) : data( std::move(proc) ) {}

        // template<typename... t_args>
        bool invoke( t_args ...args ) override final
        { return data( args... ); }
        ~virtual_procedure() override {}
    };

    template<typename t_procedure>
    CONSTRUCTOR basic_procedure( t_procedure&& proc )
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
    basic_procedure<bool, int, int> function_callable = print_num;
    function_callable.invoke( 0, 5 );
    // basic_procedure<> lambda_callable = [bind]() { printf("bound simple lambda %d\n", bind); return 1;};
    // lambda_callable.invoke();
}

int closures_and_functors()
{ main(); return 1;}
