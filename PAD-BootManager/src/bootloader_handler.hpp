#ifndef BOOTLOADER_HANDLER_HPP
#define BOOTLOADER_HANDLER_HPP

#include <string>

class BootloaderHandler {
public:
    BootloaderHandler();
    
    void enterBootloaderMode(const std::string& device);
    bool verifyFirmwareImage(const std::string& firmwarePath);
};

#endif // BOOTLOADER_HANDLER_HPP