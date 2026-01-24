
#include <string>
#include <type_traits>
#include <vector>

struct asset
{
    void* data;
};

/* NOTE: This one trick to prevent templates with no specialization.
   It works simpl by not definition the base template struct.

   An inline comment is a compiler specific hack to provide compiler messages */
// template <typename T>
// struct asset_loader; // You must provide your own specialization of this class

/* NOTE: This is a deleted specialization triggered by an std::false_type metaprogram */
template <typename T>
struct asset_loader
{
    static_assert( std::false_type::value, "You must provide your own specialization of this "
                   "struct which provides data and functions for a loadable file type" );
};

/* NOTE: I tried this "dependant type" meta_false<T> static_assert from a
 * suggested stackoverflow article but it doesn't seem to make a difference over
 * just using std::false_type directly. I'm not sure if this is a compiler
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

struct example_type
{};

struct asset_loader_base
{
    int type;
    std::string extension;
    virtual void loader( asset* arg ) = 0;
    virtual void unloader( asset* arg ) = 0;
};

struct asset_loader_impl
{
    int type;
    std::string extension;
    void (*loader)( asset* arg );
    void (*unloader)( asset* arg );
};

template <>
struct asset_loader<example_type> : asset_loader_base
{
    int type = 5;
    std::string extension = ".example";
    void loader( asset* arg ) {}
    void unloader( asset* arg ) {}
};

template <typename T>
T* asset_load()
{
    asset_loader<T> asset_type;
    asset* match;
    asset_type.loader( match );
    return reinterpret_cast<T*>( match->data );
}

int typed_erased_assets()
{
    asset_load<example_type>();
    // NOTE: has no valid loader, won't compile
    // asset_load<int>();
    return true;
}

struct asset_subsystem
{
    std::vector<asset_loader_base*> loaders_oop;
    std::vector<asset_loader_impl> loaders;
};


template <typename T>
void asset_loader_register( asset_subsystem* subsystem )
{
    asset_loader<T> loader_data;
    asset_loader_impl loader {
        .type = loader_data.type,
        .extension = loader_data.extension
        .loader = loader_data.loader,
        .unloader = loader_data.unloader
    };
    subsystem->loaders.push_back( loader );
}

int main()
{
    typed_erased_assets();
}
