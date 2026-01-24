
#include <string>
#include <type_traits>
#include <vector>
#include <cstdlib>

struct asset
{
    int type = 0;
    std::string name {};
    void* data = nullptr;
    bool loaded = false;
};

/* NOTE: This one trick to prevent templates with no specialization.
   It works simpl by not definition the base template struct.

   An inline comment is a compiler specific hack to provide compiler messages */
// template <typename T>
// struct asset_loader; // You must provide your own specialization of this class

/* NOTE:  This  is a  deleted  specialization  triggered by  an  std::false_type
 metaprogram,  it provides  a  vtable  free implementation  that  can have  it's
 function  pointers stored  in an  identical type,  that is  type-erased, called
 asset_loader_impl'.

 Interestly, because  we're dealing with raw  files, type erasure does  not have
 much of a functional purpose, it is mainly done for convenient to skip the step
 of casting the final loaded file struct manually with 'reinterpret_cast<T*>()',
 with the help of  a little enum this can also be made  type safe, so the loader
 should never give you a bogus pointer. */
template <typename T>
struct asset_loader
{
    static_assert( std::false_type::value, "You must provide your own specialization of this "
                   "struct which provides data and functions for a loadable file type" );
};

/* NOTE:  I  tried this  "dependant  type"  meta_false<T> static_assert  from  a
 * suggested stackoverflow article but it doesn't seem to make a difference over
 * just  using std::false_type  directly. I'm  not sure  if this  is a  compiler
 * specific hack but it doesn't seem to mind on either ROOT, clang or gcc */
// template <typename T>
// struct meta_false : std::false_type {};

// template <typename T>
// struct asset_loader; // You must provide your own specialization of this class

// template <typename T>
// struct asset_loader
// {
//     static_assert( meta_false<T>::value, "You must provide your own specialization of this "
//                    "struct which provides data and functions for a loadable file type" );
// };

/* NOTE: This is an example of an in-memory representation of an asset to be
 * loaded off disk */
struct example_type
{
    int value = 0;
};

#if EXPERIMENTS_INHERITANCE_ON

/* NOTE: This is a abstract base class variable of loader. It is likely slightly
   faster to  use with  very high call  counts but is  much more  challenging to
   serialize.   Any  loader   that  inherits   this   will  be   stored  in   an
   'asset_loader_base' pointer  and will be  subject to virtual dispatch  in the
   usual way. */
struct asset_loader_base
{
    int type;
    std::string extension;
    virtual void loader( asset* arg ) = 0;
    virtual void unloader( asset* arg ) = 0;
};

template <>
struct asset_loader<example_type> : asset_loader_base
{
    using t_self_type = example_type;
    using t_self = asset_loader<t_self_type>;
    int type = 5;
    std::string extension = ".example";
    void loader( asset* arg )
    {
        arg->type = 5;
        t_self_type* result = new t_self_type;
        result->value = 42;

        arg->data = result;
    }
    void unloader( asset* arg ) {}
};
#else // EXPERIMENTS_INHERITANCE_ON

/* NOTE: This is kind  of a implimentation holder, it's only purpose  is to be a
   trampoline   to   kick   off   to    an   actual   implimentation   using   a
   specialization. Except  not using  inheritance. Please  note you  actually do
   have to  register the type  with the subsystem  either way, because  we can't
   enumerate valid types in  C++, we do actually have have  to specify each type
   individually in some list somehow.  */
struct asset_loader_impl
{
    int type;
    std::string extension;
    void (*loader)( asset* arg );
    void (*unloader)( asset* arg );
};

/* NOTE: This is a template specialization of  a loader. It simple acts as a way
 * of defining  some variables  in a  way plays nicely  with C++'s  type system.
 * Because of type specialization we can associate a type with a variable. Which
 * means we can do very light metaprogramming / type introspection. */
template <>
struct asset_loader<example_type>
{
    using t_self_type = example_type;
    using t_self = asset_loader<t_self_type>;
    int type = 5;
    std::string extension = ".example";

    /* This absolutely HAVE to be static or it becomes a member reference
    function which has digusting syntax and is generaly hard to use correctly. */
    static void loader( asset* arg )
    {
        arg->type = 5;
        t_self_type* result = new t_self_type;
        result->value = 42;

        arg->data = result;
    }

    static void unloader( asset* arg ) {}
};

#endif // EXPERIMENTS_INHERITANCE_ON


/** NOTE: Makes a call into a type erased loader and then casts it back to the
 * type that's requested. We can also do runtime type checking here */
template <typename T>
T* asset_load( std::string name )
{
    asset_loader<T> asset_type;
    asset* match = new asset;
    match->type = 5;
    if (asset_type.type != match->type)
    {   printf( "Matched type was not the type requested, this is likely a bug '%s' %d %d \n",
                match->name.c_str(), asset_type.type, match->type );
        return nullptr;
    }
    asset_type.loader( match );
    return reinterpret_cast<T*>( match->data );
}

struct asset_subsystem
{
#if EXPERIMENTS_INHERITANCE_ON
    std::vector<asset_loader_base*> loaders_oop;
#else
    std::vector<asset_loader_impl> loaders;
#endif
};


/** Register the type for use in runtime introspection, C++ can't enumerate
 * types so we have to make do with registering it into a list with some
 * manually written introspection data.
 *
 * Interestingly you  don't actually *have* to  register the loader to  just use
 * it, but  it won't  be able to  do smart polymorphic  things like  running the
 * functions automatically  based on conditions  you write.  Reguardless  of how
 * you  do it,  each individual  loader will  have to  be embedded  into a  list
 * somewhere to be properly polymorphic. */
template <typename T>
void asset_loader_register( asset_subsystem* subsystem )
{
    /* NOTE: By creating a struct*/
    asset_loader<T> loader_data;
    asset_loader_impl loader {
        .type = loader_data.type,
        .extension = loader_data.extension,
        .loader = &loader_data.loader,
        .unloader = &loader_data.unloader
    };
    subsystem->loaders.push_back( loader );
}

// Function to make it easier to run throguh ROOT/cling
int type_erased_assets()
{
    asset_subsystem subsystem;
    asset_loader_register<example_type>( &subsystem );
    auto foo = asset_load<example_type>( "null_file" );
    printf( "loaded value: %d \n", foo->value );

    /* NOTE: has no valid loader, won't compile.
     it will provide an appropriate error message telling you to write a loader. */
    // asset_load<int>();

    return true;
}

int main()
{
    type_erased_assets();
}
