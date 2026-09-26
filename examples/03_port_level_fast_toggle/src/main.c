#include "ch32fun.h"
#include "ch32v003_delay.h"
#include "ch32v003_debug.h"
#include "ch32v003_gpio.h"
#include "user_config.h"

// ============================================================================
// VÍ DỤ: So sánh tốc độ API Arduino-style (digitalToggle qua macro giải mã
// mcuPin) với API cấp Port thẳng (digitalTogglePort) — dùng SysTick->CNT để
// đo số chu kỳ CPU tiêu tốn cho cùng một số lần toggle.
//
// API Arduino-style tiện dùng vì tự giải mã Port/PinNumber từ mcuPin ngay lúc
// chạy (runtime decode qua decodeHardwarePin trong macro EXECUTE_ON_PIN), phù
// hợp code ứng dụng/prototype. API cấp Port bỏ qua bước giải mã này, phù hợp
// vòng lặp tốc độ cao (bit-banging giao tiếp, phát xung PWM phần mềm...).
//
// Kết nối que đo Logic Analyzer/Oscilloscope vào 2 chân để quan sát trực quan
// sự khác biệt tần số xung ra, đồng thời xem log số chu kỳ qua SWIO printf.
// ============================================================================

static void setup(void)
{
    pinMode(TOGGLE_ARDUINO_STYLE_PIN, OUTPUT_50M);
    pinMode(TOGGLE_PORT_LEVEL_PIN, OUTPUT_50M);

    printf("=== Benchmark digitalToggle() vs digitalTogglePort() ===\r\n");
    printf("So lan toggle moi vong: %lu\r\n", (unsigned long)BENCHMARK_ITERATIONS);
}

static void loop(void)
{
    // ============================================================================
    // TEST 1: PORT-LEVEL (Chạy trước để nạp cache hệ thống)
    // ============================================================================
    const uint32_t startPort = SysTick->CNT;
    for (uint32_t i = 0; i < BENCHMARK_ITERATIONS; i++)
    {
        digitalTogglePort(TOGGLE_PORT_LEVEL_PORT, TOGGLE_PORT_LEVEL_NUM);
    }
    const uint32_t cyclesPortLevel = SysTick->CNT - startPort;
    delayMs(200);

    // ============================================================================
    // TEST 2: ARDUINO-STYLE (Chạy ngay sau, cùng một kiểu vòng lặp)
    // ============================================================================
    const uint32_t startArduino = SysTick->CNT;
    for (uint32_t i = 0; i < BENCHMARK_ITERATIONS; i++)
    {
        digitalToggle(TOGGLE_ARDUINO_STYLE_PIN);
    }
    const uint32_t cyclesArduinoStyle = SysTick->CNT - startArduino;
    delayMs(200);

    // In kết quả so sánh công bằng
    printf("=== Benchmark Kết Quả Đồng Bộ ===\r\n");
    printf("Arduino-style (digitalToggle):    %lu chu ky CPU\r\n", (unsigned long)cyclesArduinoStyle);
    printf("Port-level    (digitalTogglePort): %lu chu ky CPU\r\n", (unsigned long)cyclesPortLevel);
    printf("---------------------------------------------------\r\n");

    delayMs(2000);
}

int main(void)
{
    SystemInit();
    delayMs(1000); // Khoảng chờ an toàn để nạp mạch tránh kẹt chip

    setup();

    while (1)
    {
        loop();
    }
}
