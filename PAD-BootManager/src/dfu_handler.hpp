#ifndef DFU_HANDLER_HPP
#define DFU_HANDLER_HPP

#include <string>

class DFUHandler {
public:
    DFUHandler();
    
    bool initiateDFU(const std::string& device);
    bool uploadFirmware(const std::string& firmwarePath);
};

#endif // DFU_HANDLER_HPP