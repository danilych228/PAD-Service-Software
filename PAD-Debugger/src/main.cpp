/*
 * PAD-Debugger: RTOS-aware embedded debugger
 * Main application entry point
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <getopt.h>
#include <sys/stat.h>
#include <fstream>

// SDL2 for GUI components
#include <SDL2/SDL.h>
#ifdef __linux__
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif

// Include utility headers
#include "logger.hpp"
#include "debugger_core.hpp"
#include "rtos_integrator.hpp"

// Application version
const std::string VERSION = "1.0.0";

// Function declarations
void print_usage(const char* prog_name);
void print_version();

/**
 * @brief Parse command line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @param config Configuration structure to populate
 * @return True if parsing succeeded, false otherwise
 */
bool parse_arguments(int argc, char* argv[], DebuggerConfig& config);

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Print welcome message
    Logger::log(LogLevel::INFO, "PAD-Debugger v" + VERSION);
    Logger::log(LogLevel::INFO, "RTOS-aware embedded debugging tool");

    // Configuration structure
    DebuggerConfig config;
    
    // Parse command line arguments
    if (!parse_arguments(argc, argv, config)) {
        SDL_Quit();
        return 1;
    }

    // If no command was specified, show help
    if (config.command.empty()) {
        print_usage(argv[0]);
        SDL_Quit();
        return 0;
    }

    // Initialize debugger core
    DebuggerCore debugger(config);
    
    // Execute the requested command
    int result = 0;
    if (config.command == "debug") {
        result = debugger.start_debug_session();
    } else if (config.command == "connect") {
        result = debugger.connect_to_target();
    } else if (config.command == "list-rtos") {
        debugger.list_supported_rtos();
    } else if (config.command == "config") {
        debugger.handle_config_command();
    } else {
        std::cerr << "Unknown command: " << config.command << std::endl;
        print_usage(argv[0]);
        result = 1;
    }

    // Clean up SDL
    SDL_Quit();

    return result;
}

/**
 * @brief Parse command line arguments into configuration
 */
bool parse_arguments(int argc, char* argv[], DebuggerConfig& config) {
    int opt;
    int option_index = 0;

    static struct option long_options[] = {
        {"interface", required_argument, 0, 'i'},
        {"adapter", required_argument, 0, 'a'},
        {"target", required_argument, 0, 't'},
        {"rtos", required_argument, 0, 'r'},
        {"swo", required_argument, 0, 's'},
        {"config", required_argument, 0, 'c'},
        {"timeline", no_argument, 0, 'T'},
        {"watch-write", required_argument, 0, 'W'},
        {"watch-read", required_argument, 0, 'R'},
        {"watch-access", required_argument, 0, 'A'},
        {"verbose", no_argument, 0, 'v'},
        {"version", no_argument, 0, 'V'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "i:a:t:r:s:c:TW:R:A:vVh", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'i':
                config.debug_interface = optarg;
                break;
            case 'a':
                config.adapter = optarg;
                break;
            case 't':
                config.target_elf = optarg;
                break;
            case 'r':
                config.rtos = optarg;
                break;
            case 's':
                try {
                    config.swo_baudrate = std::stoi(optarg);
                } catch (const std::exception&) {
                    std::cerr << "Invalid SWO baudrate: " << optarg << std::endl;
                    return false;
                }
                break;
            case 'c':
                config.config_file = optarg;
                break;
            case 'T':
                config.timeline_enabled = true;
                break;
            case 'W':
                config.watchpoints.push_back({optarg, WatchType::WRITE});
                break;
            case 'R':
                config.watchpoints.push_back({optarg, WatchType::READ});
                break;
            case 'A':
                config.watchpoints.push_back({optarg, WatchType::ACCESS});
                break;
            case 'v':
                Logger::set_level(LogLevel::DEBUG);
                break;
            case 'V':
                print_version();
                return false; // Exit after printing version
            case 'h':
                print_usage(argv[0]);
                return false; // Exit after printing help
            default:
                print_usage(argv[0]);
                return false;
        }
    }

    // Process remaining arguments (the command)
    if (optind < argc) {
        config.command = argv[optind];
    }

    // Validate required parameters based on command
    if (config.command == "debug" && config.target_elf.empty()) {
        std::cerr << "Target ELF file is required for debug command" << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Print program usage information
 */
void print_usage(const char* prog_name) {
    std::cout << "PAD-Debugger v" << VERSION << " - RTOS-aware embedded debugger\n\n";
    std::cout << "Usage: " << prog_name << " [OPTIONS] COMMAND [ARGS...]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  debug                    Start debugging session\n";
    std::cout << "  connect                  Connect to target without starting debug session\n";
    std::cout << "  list-rtos                List all supported RTOS\n";
    std::cout << "  config                   Manage configuration settings\n\n";
    std::cout << "Options:\n";
    std::cout << "  -i, --interface TEXT     Debug interface (swd/jtag)\n";
    std::cout << "  -a, --adapter TEXT       Debug adapter (cmsis-dap, jlink, stlink)\n";
    std::cout << "  -t, --target PATH        ELF file of target firmware\n";
    std::cout << "  -r, --rtos NAME          RTOS to use (freertos, zephyr, threadx)\n";
    std::cout << "  -s, --swo BAUDRATE       Enable SWO trace at specified baudrate\n";
    std::cout << "  -c, --config PATH        Configuration file\n";
    std::cout << "  -T, --timeline           Enable task timeline visualization\n";
    std::cout << "  -W, --watch-write ADDR   Set write watchpoint at address/symbol\n";
    std::cout << "  -R, --watch-read ADDR    Set read watchpoint at address/symbol\n";
    std::cout << "  -A, --watch-access ADDR  Set access watchpoint at address/symbol\n";
    std::cout << "  -v, --verbose            Enable verbose output\n";
    std::cout << "  -V, --version            Show version information\n";
    std::cout << "  -h, --help               Show this help message\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << prog_name << " debug --target firmware.elf --interface swd --adapter cmsis-dap\n";
    std::cout << "  " << prog_name << " debug --target firmware.elf --rtos freertos --timeline\n";
    std::cout << "  " << prog_name << " debug --swo 2000000 --target firmware.elf --interface swd\n";
    std::cout << "  " << prog_name << " list-rtos\n\n";
}

/**
 * @brief Print version information
 */
void print_version() {
    std::cout << "PAD-Debugger v" << VERSION << std::endl;
    std::cout << "Copyright (c) 2023 PAD Service" << std::endl;
}