
#pragma once

#include "code_helpers.h"
#include "error.hpp"
#include "math.hpp"
#include "core.h"

// Forward Declarations
namespace std
{
    FORWARD template<typename _t> class initializer_list;
    FORWARD template <typename _t_pointer, typename _t_deleter> class unique_ptr;
    FORWARD template<typename _t, typename _t_alloc> class vector;
}
FORWARD struct id;

/** To check for implimented functions place the INTERFACE_DEFINE_FUNCTION macro
 * at the bottom of the .h file. It will not work properly if it is put in a
 * .cpp file, although it will work it will just throw undefined references and
 * linker error which defeats the point of the macro
 *
 */

#define INTERFACE_DEFINE_FUNCTION(interface_function_name)      \
    static_assert(1);                                                     \
    // static_assert( std::is_member_function_pointer<             \
    //                decltype( &interface_function_name )>()); \

// Use derived class as a debug-only virtual interface
#ifdef DEBUG_INTERFACE
    // Use INTERFACE macro after interface defined function to help validate it
    #define INTERFACE override

    #define INTERFACE_IMPLEMENT_RENDERER(...)
    #define INTERFACE_RENDERER \
        : i_renderer

// Fall back to primitive error system
#else
    #define INTERFACE
#def    ine INTERFACE_RENDERER
#endif

typedef internal_id<id_type::display> display_id;
typedef internal_id<id_type::window> window_id;
typedef internal_id<id_type::graphics_context> context_id;
typedef internal_id<id_type::vertex_attribute> attribute_id;
typedef internal_id<id_type::buffer> buffer_id;
typedef internal_id<id_type::mesh> mesh_id;
typedef internal_id<id_type::shader> shader_id;
typedef internal_id<id_type::shader_program> shader_program_id;

enum class shader_type
{
    vertex,
    fragment,
    geometry,
    compute,
    tesselation_control,
    tesselation_eval
};

/// All attributes are baked when copied to the graphiccs layer
// be mindful of this
struct mesh
{
    fstring name;
    ffloat3* vertex_buffer = nullptr;
    fuint32* vertex_index_buffer = nullptr;
    ffloat4* vertex_color_buffer = nullptr;
    fuint32 vertex_count = 0;
    fuint32 index_count = 0;
    fuint32 color_count = 0;
    shader_program_id shader_program_id;
};

typedef shader_type fshader_type;
typedef mesh fmesh;

#ifdef DEBUG_INTERFACE
/// Interface for Platform Specific Renderer Layer
class i_renderer
{
protected:

public:
    virtual fhowdit
    FUNCTION initialize() PURE;

    virtual fhowdit
    FUNCTION deinitialize() PURE;

    virtual display_id
    FUNCTION display_context_create( ) PURE;

    virtual fhowdit
    FUNCTION display_context_destroy( display_id target ) PURE;

    virtual window_id
    FUNCTION window_create() PURE;

    virtual fhowdit
    FUNCTION window_destroy( window_id target ) PURE;

    /// Create the context for the relevant platform and return an id
    virtual context_id
    FUNCTION context_create() PURE;

    virtual fhowdit
    FUNCTION context_destroy( context_id target ) PURE;

    /// Set the context to the context ID
    virtual fhowdit
    FUNCTION context_set_current( context_id target ) PURE;

    /// Register a new shader object and return an ID
    virtual shader_id
    FUNCTION shader_create( fstring name, shader_type type_request ) PURE;

    /** Attempt to load a shader program from disk, either code or a compiled binary.
     * This might may be an intermediate compile format or a platform specific
     * pre-compiled or cached shader
     *
     * This is intentionally seperate to manage the performance penality of
     * loading things from disk */
    virtual fhowdit
    FUNCTION shader_load( shader_id target, fpath shader_file, bool binary = false ) PURE;

    /** Attempt to compile the provided shader to a native-loadable code.
     * This is intentionally seperate to management the performance penaltiy
     * of compiling shaders at runtime */
    virtual fhowdit
    FUNCTION shader_compile( shader_id target, fstring code ) PURE;

    /// \shaders_attach attach the listed shader ID's if presence
    virtual shader_program_id
    FUNCTION shader_program_create( fstring name,
                                    std::initializer_list<shader_id> shaders_attach ) PURE;

    virtual fhowdit
    FUNCTION shader_program_compile( shader_program_id target ) PURE;

    virtual fhowdit
    FUNCTION shader_program_attach( shader_program_id target, shader_id shader_attached ) PURE;

    virtual fhowdit
    FUNCTION shader_program_detach( shader_program_id target, shader_id shader_detached ) PURE;

    virtual fhowdit
    FUNCTION shader_program_run( shader_program_id target ) PURE;

    virtual mesh_id
    FUNCTION mesh_create( fmesh mesh ) PURE;

    virtual fhowdit
    FUNCTION draw_mesh( mesh_id target,
                        ftransform target_transform,
                        shader_program_id target_shader ) PURE;

    virtual fhowdit
    FUNCTION draw_test_triangle( ffloat4 p_color ) PURE;

    virtual fhowdit
    FUNCTION draw_test_circle( ffloat4 p_color ) PURE;

    virtual fhowdit
    FUNCTION draw_test_rectangle( ffloat4 p_color ) PURE;

    /// Draw a a wide gradient that goes to opposing colour around a defined circle
    virtual fhowdit
    FUNCTION draw_test_signfield( ffloat4 p_color ) PURE;

    /// Attempt to refresh the display and window contexts
    virtual fhowdit
    FUNCTION refresh() PURE;

    virtual
    DESTRUCTOR ~i_renderer() {}
};
#endif
