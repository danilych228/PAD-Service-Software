/*
 * debugger_core.hpp
 * Core functionality for PAD-Debugger
 */

#ifndef DEBUGGER_CORE_HPP
#define DEBUGGER_CORE_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

// Enum for watchpoint types
enum class WatchType {
    READ,
    WRITE,
    ACCESS
};

// Struct for watchpoint definition
struct Watchpoint {
    std::string target;  // Address or symbol
    WatchType type;      // Type of access to watch
};

// Forward declarations
struct DebuggerConfig;

class DebuggerCore {
public:
    explicit DebuggerCore(const DebuggerConfig& config);
    ~DebuggerCore();

    /**
     * @brief Start a debugging session
     * @return 0 on success, non-zero on failure
     */
    int start_debug_session();

    /**
     * @brief Connect to target device
     * @return 0 on success, non-zero on failure
     */
    int connect_to_target();

    /**
     * @brief List all supported RTOS
     */
    void list_supported_rtos();

    /**
     * @brief Handle configuration-related commands
     */
    void handle_config_command();

private:
    DebuggerConfig config_;

    // Internal helper methods
    bool initialize_debug_interface();
    bool load_target_firmware();
    bool setup_rtos_awareness();
    bool setup_watchpoints();
    bool start_visualization();
    void cleanup();
};

// Configuration structure
struct DebuggerConfig {
    std::string command;
    std::string debug_interface = "swd";  // swd, jtag
    std::string adapter = "cmsis-dap";    // cmsis-dap, jlink, stlink
    std::string target_elf;               // ELF file path
    std::string rtos;                     // freertos, zephyr, threadx
    std::string config_file;              // Config file path
    int swo_baudrate = 0;                 // SWO trace baudrate (0 = disabled)
    bool timeline_enabled = false;        // Enable task timeline
    std::vector<Watchpoint> watchpoints;  // Memory watchpoints to set
    int debug_speed = 4000;               // Debug interface speed in kHz
};

#endif // DEBUGGER_CORE_HPP