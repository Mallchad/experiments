#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define CL_HPP_ENABLE_EXCEPTIONS 1

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl2.hpp>
#else
#include <CL/opencl.hpp>
#endif

int main() {
    try {
        // 1. Get available platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        if (platforms.empty()) {
            std::cerr << "No OpenCL platforms found." << std::endl;
            return 1;
        }

        // 2. Select a device
        cl::Device device;
        for (auto &p : platforms) {
            std::vector<cl::Device> devices;
            p.getDevices(CL_DEVICE_TYPE_GPU, &devices);
            if (!devices.empty()) {
                device = devices[0];
                break;
            }
        }
        if (device() == nullptr) {
             for (auto &p : platforms) {
                std::vector<cl::Device> devices;
                p.getDevices(CL_DEVICE_TYPE_CPU, &devices);
                if (!devices.empty()) {
                    device = devices[0];
                    break;
                }
            }
        }
         if (device() == nullptr) {
            std::cerr << "No suitable OpenCL device found." << std::endl;
            return 1;
        }


        // 3. Create a context and command queue
        cl::Context context(device);
        cl::CommandQueue queue(context, device);

        // 4. Load and build the program
        std::ifstream kernel_file("kernel.cl");
        std::string src(std::istreambuf_iterator<char>(kernel_file), (std::istreambuf_iterator<char>()));
        src = "";

        cl::Program::Sources sources(1, src);

        cl::Program program(context, sources);
        program.build("-cl-std=CL1.2");

        // 5. Create the kernel
        cl::Kernel kernel(program, "hello");

        // --- Your application-specific code goes here ---
        // For example, creating buffers, setting kernel arguments, and enqueuing the kernel.

        std::cout << "OpenCL setup successful." << std::endl;

    } catch (const cl::Error &err) {
        std::cerr << "OpenCL error: " << err.what() << " (" << err.err() << ")" << std::endl;
        return 1;
    } catch (const std::exception &err) {
        std::cerr << "Standard exception: " << err.what() << std::endl;
        return 1;
    }

    return 0;
}
