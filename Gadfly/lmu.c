
#include <mach/mach.h>
#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>

uint64_t readlmu()
{
    io_service_t service =
        IOServiceGetMatchingService(kIOMasterPortDefault,
                                    IOServiceMatching("AppleLMUController"));

    if (!service) {
        fprintf(stderr, "failed to find ambient light sensors\n");
        abort();
    }

    kern_return_t kr;
    io_connect_t dataPort = 0;
    kr = IOServiceOpen(service, mach_task_self(), 0, &dataPort);
    IOObjectRelease(service);
    if (kr != KERN_SUCCESS) {
        mach_error("IOServiceOpen:", kr);
        abort();
    }

    uint32_t outputs = 2;
    uint64_t values[outputs];
    kr = IOConnectCallMethod(dataPort, 0, nil, 0, nil, 0, values, &outputs, nil, 0);
    if (kr != KERN_SUCCESS) {
        fprintf(stderr, "could not get sensor value");
        abort();
    }

    return values[0];
}


