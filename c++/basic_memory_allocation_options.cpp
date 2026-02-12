
#include <memory>

struct render_context
{
};

void basic_memory_allocation_options()
{
  size_t size_of_host_context = sizeof(render_context);
  render_context* host_context = (render_context*)malloc(size_of_host_context);

  *host_context = render_context(); // actually initialize it

// modern C++ alternatives
host_context = new render_context();
// my way
// host_context = memory_allocate<render_context>(1);
auto host_context1 = make_unique<render_context>();
auto host_context2 = make_shared<render_context>();
// allocate on stack, also valid
render_context host_context_;
render_context* host_context3 = &host_context_; // take the pointer to the stack, careful it dies in scope.

}

int main()
{   basic_memory_allocation_options(); }
