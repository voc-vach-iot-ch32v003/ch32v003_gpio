#include "ch32fun.h"
#include "ch32v003_delay.h"
#include "ch32v003_gpio.h"
#include "user_config.h"

// Ví dụ cơ bản: Đọc nút nhấn (Pull-up) để đảo trạng thái LED (Push-Pull).
// Đây là project PlatformIO độc lập, biên dịch/nạp chạy được ngay,
// khác với đoạn code rút gọn minh họa trong README chính của thư viện.

static void setup(void)
{
    // Cấu hình LED làm đầu ra Push-Pull
    pinMode(LED_PIN, OUTPUT);

    // Cấu hình Nút nhấn làm đầu vào có điện trở kéo lên Pull-up
    pinMode(BTN_PIN, INPUT_PULLUP);
}

static void loop(void)
{
    // Nút nhấn tích cực mức LOW (do dùng Pull-up)
    if (digitalRead(BTN_PIN) == LOW)
    {
        digitalToggle(LED_PIN);
        delayMs(BTN_DEBOUNCE_MS); // Chống dội nút nhấn
    }
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
