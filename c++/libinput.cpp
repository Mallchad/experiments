
#include <print>
#include <format>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstdint>

// posix
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// 3rd party dependences
#include <libinput.h>

// Requires access to 'input' user group


static int open_restricted(const char *path, int flags, void *user_data)
{
    int fd = open(path, flags);
    return fd < 0 ? -errno : fd;
}

static void close_restricted(int fd, void *user_data)
{
    close(fd);
}

const static struct libinput_interface interface = {
    .open_restricted = open_restricted,
    .close_restricted = close_restricted,
};


int main(void)
{
    udev* udev_context = udev_new();

    struct libinput *li;
    struct libinput_event *event;

    li = libinput_udev_create_context( &interface, NULL, udev_context );
    libinput_udev_assign_seat(li, "seat0");
    libinput_dispatch(li);

    // struct pollfd pfd = {
    //     .fd = libinput_get_fd( li ),
    //     .events = POLLIN,
    //     .revents = 0,
    // };


    static bool do_exit = false;
    while (do_exit == false)
    {
        // poll(&pfd, 1, -1);
        libinput_dispatch( li );
        event = nullptr;
        while ((event = libinput_get_event(li)) != NULL)
        {
            printf( "Event Created: ");

            // handle the event here
            // Debug characteristics
            libinput_event_type event_type = libinput_event_get_type( event );
            libinput_event_pointer* x_event = libinput_event_get_pointer_event( event );
            double x {};
            double y {};

            switch (event_type)
            {
                case LIBINPUT_EVENT_POINTER_MOTION:
                    x =  libinput_event_pointer_get_dx( x_event );
                    y =  libinput_event_pointer_get_dy( x_event );
                    printf( "Pointer motion event [%f %f]\n", x, y );
                    break;

                case LIBINPUT_EVENT_POINTER_MOTION_ABSOLUTE:
                    x =  libinput_event_pointer_get_absolute_x( x_event );
                    y =  libinput_event_pointer_get_absolute_y( x_event );
                    printf( "Pointer motion absolute event [%f %f]\n", x, y );
                    break;

                case LIBINPUT_EVENT_POINTER_BUTTON:
                    printf( "Pointer button event\n" );
                    break;

                case LIBINPUT_EVENT_KEYBOARD_KEY:
                    printf( "Key event \n" );
                    break;
            }
            // printf

            libinput_event_destroy(event);
            libinput_dispatch(li);
        }
    }
    libinput_unref(li);

    return 0;
}
