# 03_port_level_fast_toggle

## Mục tiêu

So sánh trực quan (bằng cả xung ra thực tế và số liệu chu kỳ CPU qua log
SWIO) giữa:

- **API Arduino-style:** `digitalToggle(mcuPin)` — tự giải mã Port/PinNumber
  từ `mcuPin` ngay lúc chạy (runtime decode qua `decodeHardwarePin()`).
- **API cấp Port thẳng:** `digitalTogglePort(GPIOx, pinNumber)` — bỏ qua bước
  giải mã, thao tác thẳng thanh ghi.

Qua đó minh họa lý do thư viện cung cấp song song 2 lớp API: lớp Arduino-style
tiện dùng cho code ứng dụng, lớp Port-level dành cho vòng lặp cần tốc độ tối
đa (bit-banging, phát xung PWM phần mềm...).

## Sơ đồ nối dây (Pinout)

| Tín hiệu | Hằng số | Chân vật lý | Ghi chú |
| --- | --- | --- | --- |
| Xung kiểu Arduino-style | `TOGGLE_ARDUINO_STYLE_PIN` (`MCU_PIN3`) | PA2 | Nối que đo kênh 1 |
| Xung kiểu Port-level | `TOGGLE_PORT_LEVEL_PIN` (`MCU_PIN6`) | PC2 | Nối que đo kênh 2 |

## Cách quan sát kết quả

1. **Trực quan (Oscilloscope/Logic Analyzer):** So sánh tần số xung ra trên 2
   kênh — kênh Port-level luôn có tần số cao hơn do bỏ qua bước giải mã.
2. **Số liệu (SWIO Debug Log):** Theo dõi qua target `sdi_printf_monitor`, mỗi
   vòng benchmark in ra số chu kỳ CPU (`SysTick->CNT`) tiêu tốn cho 100.000
   lần toggle của từng API.

## Build & Nạp

```bash
pio run -e CH32V003J4M6 -t upload_and_sdi_monitor
```
