# 🔌 ch32v003_gpio

Thư viện quản lý và điều khiển GPIO nâng cao theo phong cách Arduino dành cho vi điều khiển **CH32V003**. Thư viện hoạt động trên nền framework **ch32v003fun**, hỗ trợ tự động giải mã chân vật lý theo từng gói vỏ đóng gói (`SOP8`, `SOP16`, `TSSOP20`), tự động cấp xung nhịp (Clock Tree), cung cấp các API làm việc trực tiếp theo Port và quản lý nâng cao chân nạp SWIO (PD1).

---

## 🚀 Tính năng nổi bật

- **Ánh xạ chân vật lý thông minh (Bit-packing Pinout):** Sử dụng các hằng số `MCU_PINx` trực quan theo đúng số thứ tự chân cắm vật lý trên IC thực tế.
- **Tự động cấp xung (Auto Clock Gating):** Tự động bật Clock APB2 cho `GPIOA`, `GPIOC`, `GPIOD` hoặc `AFIO` ngay trong hàm `pinMode()`.
- **API phong cách Arduino & Port cấp thấp:** Hỗ trợ đầy đủ `pinMode()`, `digitalWrite()`, `digitalRead()`, `digitalToggle()` truyền thẳng `MCU_PINx` hoặc gọi trực tiếp theo Port (`pinModePort()`, `digitalWritePort()`).
- **Quản lý linh hoạt chân SWIO (PD1):** Cung cấp API `setSwioMode()`, `getSwioMode()`, `toggleSwioMode()` cho phép chuyển đổi giữa chân nạp chương trình và chân GPIO thường.
- **Tối ưu hóa tốc độ ghi/đọc:** Thao tác trực tiếp trên các thanh ghi phần cứng `BSHR`, `BCR`, `INDR`, `CFGLR` của CH32V003.

---

## 📑 Cấu trúc hàm (API Reference)

### 1. API chuẩn phong cách Arduino (Truyền chân vật lý `MCU_PINx`)

| Hàm xử lý                         | Tham số                                  | Giá trị trả về   | Mô tả                                                                                  |
| --------------------------------- | ---------------------------------------- | ---------------- | -------------------------------------------------------------------------------------- |
| **`pinMode(mcuPin, mode)`**       | `uint8_t mcuPin`, `PinMode_t mode`       | `void`           | Cấu hình chế độ (Input, Push-Pull, Open-Drain, Alternate Function...) cho chân vật lý. |
| **`digitalWrite(mcuPin, state)`** | `uint8_t mcuPin`, `DigitalState_t state` | `void`           | Xuất mức logic (`HIGH` / `LOW`) ra chân vật lý.                                        |
| **`digitalRead(mcuPin)`**         | `uint8_t mcuPin`                         | `DigitalState_t` | Đọc mức logic hiện tại của chân vật lý (`HIGH` hoặc `LOW`).                            |
| **`digitalToggle(mcuPin)`**       | `uint8_t mcuPin`                         | `void`           | Đảo ngược trạng thái logic đầu ra của chân vật lý.                                     |

### 2. API làm việc trực tiếp theo Cổng Port (Tốc độ cao)

| Hàm xử lý                                       | Tham số                                                      | Giá trị trả về | Mô tả                                                                                           |
| ----------------------------------------------- | ------------------------------------------------------------ | -------------- | ----------------------------------------------------------------------------------------------- |
| **`pinModePort(GPIOx, pinNumber, mode)`**       | `GPIO_TypeDef* GPIOx`, `uint8_t pinNumber`, `PinMode_t mode` | `void`         | Cấu hình chế độ cho chân theo chỉ số bit (0-7) trực tiếp trên Port (`GPIOA`, `GPIOC`, `GPIOD`). |
| **`digitalWritePort(GPIOx, pinNumber, state)`** | `GPIO_TypeDef* GPIOx`, `uint8_t pinNumber`, `uint8_t state`  | `void`         | Xuất mức logic ra chân theo Port bằng thanh ghi `BSHR`/`BCR`.                                   |
| **`digitalReadPort(GPIOx, pinNumber)`**         | `const GPIO_TypeDef* GPIOx`, `uint8_t pinNumber`             | `uint8_t`      | Đọc trực tiếp bit trạng thái đầu vào từ thanh ghi `INDR`.                                       |
| **`digitalTogglePort(GPIOx, pinNumber)`**       | `GPIO_TypeDef* GPIOx`, `uint8_t pinNumber`                   | `void`         | Đảo trạng thái pin trực tiếp trên Port chỉ định.                                                |

### 3. API Quản lý chân gỡ lỗi / nạp chương trình (SWIO)

| Hàm xử lý                   | Tham số               | Giá trị trả về | Mô tả                                                                               |
| --------------------------- | --------------------- | -------------- | ----------------------------------------------------------------------------------- |
| **`setSwioMode(swioMode)`** | `SwioMode_t swioMode` | `void`         | Thiết lập chế độ nạp `SWIO_MODE_DEBUG` hoặc giải phóng thành GPIO `SWIO_MODE_GPIO`. |
| **`getSwioMode()`**         | Không có              | `SwioMode_t`   | Trả về chế độ hoạt động hiện tại của chân SWIO (PD1).                               |
| **`toggleSwioMode()`**      | Không có              | `void`         | Đảo chuyển đổi giữa chế độ nạp chương trình và GPIO thường.                         |

---

## ⚙️ Cấu hình môi trường (`platformio.ini`)

Bảng mã hóa chân vật lý `MCU_PINx` tự động thay đổi theo gói đóng vỏ IC thực tế của bạn thông qua cờ build flag khai báo trong `platformio.ini`:

```ini
; 1. Bản SOP8 (8 chân)
build_flags = -DCH32V003_J4M6

; 2. Bản SOP16 (16 chân)
build_flags = -DCH32V003_A4M6

; 3. Bản TSSOP20 (20 chân)
build_flags = -DCH32V003_F4P6

```

_(Mặc định nếu không khai báo cờ nào, thư viện sẽ tự động chọn bản SOP8 `CH32V003_J4M6`)._

---

## 📝 Code mẫu sử dụng

```c
#include "ch32fun.h"
#include <ch32v003_gpio.h>
#include <ch32v003_delay.h>

// Định nghĩa chân LED và Nút nhấn theo số chân vật lý thực tế trên IC (VD: Bản SOP8)
#define LED_PIN MCU_PIN3  // Chân vật lý số 3 (PA2)
#define BTN_PIN MCU_PIN5  // Chân vật lý số 5 (PC1)

void setup() {
    // Cấu hình LED làm đầu ra Push-Pull
    pinMode(LED_PIN, OUTPUT);

    // Cấu hình Nút nhấn làm đầu vào có điện trở kéo lên Pull-up
    pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
    // Đọc trạng thái nút nhấn (Tích cực mức LOW)
    if (digitalRead(BTN_PIN) == LOW) {
        // Đảo trạng thái LED
        digitalToggle(LED_PIN);
        delayMs(200); // Chống dội nút nhấn
    }
}

int main() {
    SystemInit();
    delayMs(1000); // Khoảng chờ an toàn tránh brick chip

    setup();
    while (1) {
        loop();
    }
}

```

---
