/*
 * rtos_integrator.hpp
 * RTOS integration layer for PAD-Debugger
 */

#ifndef RTOS_INTEGRATOR_HPP
#define RTOS_INTEGRATOR_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

// Forward declarations
struct DebuggerConfig;

// RTOS types supported by the debugger
enum class RTOS_Type {
    FREERTOS,
    ZEPHYR,
    THREADX,
    EMBOS,
    RTTHREAD,
    CUSTOM
};

// Structure representing a task in the RTOS
struct RTOSTask {
    std::string name;
    int id;
    int priority;
    std::string state;  // Running, Ready, Blocked, Suspended
    void* stack_pointer;
    void* stack_start;
    size_t stack_size;
    uint32_t stack_usage;
};

// Structure representing RTOS information
struct RTOSInfo {
    RTOS_Type type;
    std::string name;
    std::string version;
    std::vector<RTOSTask> tasks;
    int current_task_id;
    int tick_rate_hz;
};

class RTOSIntegrator {
public:
    explicit RTOSIntegrator(const DebuggerConfig& config);
    ~RTOSIntegrator();

    /**
     * @brief Initialize RTOS integration
     * @return true on success, false on failure
     */
    bool initialize();

    /**
     * @brief Detect RTOS running on target
     * @return RTOS type detected
     */
    RTOS_Type detect_rtos();

    /**
     * @brief Get current RTOS information
     * @return RTOSInfo structure with current state
     */
    RTOSInfo get_rtos_info();

    /**
     * @brief Get list of supported RTOS
     * @return Vector of supported RTOS names
     */
    std::vector<std::string> get_supported_rtos();

    /**
     * @brief Refresh RTOS state information
     * @return true on success, false on failure
     */
    bool refresh_state();

    /**
     * @brief Set up RTOS-specific watchpoints
     * @return true on success, false on failure
     */
    bool setup_rtos_watchpoints();

private:
    DebuggerConfig config_;
    RTOSInfo current_rtos_info_;
    std::map<RTOS_Type, std::string> rtos_names_;

    // RTOS-specific detection and integration methods
    bool detect_freertos();
    bool detect_zephyr();
    bool detect_threadx();
    bool detect_embos();
    bool detect_rtthread();
    bool detect_custom();

    // RTOS-specific information gathering
    bool gather_freertos_info();
    bool gather_zephyr_info();
    bool gather_threadx_info();
    bool gather_embos_info();
    bool gather_rtthread_info();
    bool gather_custom_info();

    void init_rtos_names();
    void cleanup();
};

#endif // RTOS_INTEGRATOR_HPP