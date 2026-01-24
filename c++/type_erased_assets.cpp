
#include <string>
#include <type_traits>

struct asset
{
    void* data;
};

template <typename T>
struct asset_loader; // You must provide your own specialization of this class

struct example_type
{};


template <>
struct asset_loader<example_type>
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
    // has no valid loader
    asset_load<int>();
    return true;
}

int main()
{
    typed_erased_assets();
}
