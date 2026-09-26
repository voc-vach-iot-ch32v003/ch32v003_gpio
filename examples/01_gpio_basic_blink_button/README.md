# 01_gpio_basic_blink_button

## Mục tiêu

Ví dụ cơ bản nhất của thư viện `ch32v003_gpio`: cấu hình một chân làm đầu ra
điều khiển LED, một chân làm đầu vào Pull-up đọc trạng thái nút nhấn, và đảo
LED mỗi khi nút nhấn được nhấn (có chống dội bằng `delayMs`).

Đây là project PlatformIO độc lập chạy được ngay — khác với đoạn code rút gọn
trong Quick Start của README chính, dùng để bạn clone về nạp thử trực tiếp.

## Sơ đồ nối dây (Pinout)

| Tín hiệu | Hằng số | Chân vật lý (mọi gói vỏ) | Ghi chú |
| --- | --- | --- | --- |
| LED | `LED_PIN` (`MCU_PIN3`) | PA2 | Nối LED qua điện trở ~330Ω xuống GND |
| Nút nhấn | `BTN_PIN` (`MCU_PIN5`) | PC1 | Một chân nối GND, chân còn lại nối vào PC1 (dùng Pull-up nội) |

## Build & Nạp

```bash
# Bản SOP8 (mặc định)
pio run -e CH32V003J4M6 -t upload_and_sdi_monitor

# Bản SOP16
pio run -e CH32V003A4M6 -t upload_and_sdi_monitor

# Bản TSSOP20
pio run -e CH32V003F4P6 -t upload_and_sdi_monitor
```

## Kết quả mong đợi

Mỗi lần nhấn nút, LED trên `PA2` đảo trạng thái Bật/Tắt.
