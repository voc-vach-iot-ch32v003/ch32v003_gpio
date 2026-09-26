# 02_swio_remap_safety

## ⚠️ CẢNH BÁO TRƯỚC KHI NẠP

Ví dụ này thao tác trực tiếp với chân **SWIO (PD1)** — chân **DUY NHẤT** dùng
để nạp/gỡ lỗi chương trình trên CH32V003. Đọc kỹ toàn bộ README này và phần
comment cảnh báo đầu file `src/main.c` trước khi nạp vào phần cứng thật.

Nếu firmware bị lỗi trong lúc PD1 đang ở chế độ GPIO, mạch nạp minichlink có
thể **không giao tiếp lại được** với chip (hiện tượng tương tự "brick"). Ví dụ
này đã cài sẵn cơ chế an toàn "giữ nút để giải phóng" nhằm giảm rủi ro, nhưng
không loại bỏ hoàn toàn rủi ro phần cứng.

## Mục tiêu

Minh họa cách dùng API `setSwioMode()` / `getSwioMode()` / `toggleSwioMode()`
một cách **có chủ đích và có thể khôi phục**, thay vì gọi vô điều kiện ngay
lúc khởi động (cách làm dễ dẫn đến mất khả năng nạp lại chip).

## Cơ chế an toàn "Hold-to-Release"

1. Sau khi cấp nguồn/reset, chip mặc định giữ nguyên `SWIO_MODE_DEBUG`.
2. Nếu người dùng **giữ nút nhấn liên tục 3 giây** ngay sau khi boot (LED
   nhấp nháy nhanh báo đang đếm), chip mới gọi `setSwioMode(SWIO_MODE_GPIO)`
   để giải phóng PD1 thành GPIO điều khiển tải.
3. Nếu không giữ nút (hoặc nhả giữa chừng), chip **giữ nguyên chế độ debug**
   — luôn có thể nạp lại bình thường qua minichlink.

## Sơ đồ nối dây (Pinout)

| Tín hiệu | Hằng số | Chân vật lý | Ghi chú |
| --- | --- | --- | --- |
| LED trạng thái | `STATUS_LED_PIN` (`MCU_PIN3`) | PA2 | Báo trạng thái đang giữ nút / chế độ hiện tại |
| Nút giữ để giải phóng | `HOLD_TO_RELEASE_BTN_PIN` (`MCU_PIN5`) | PC1 | Pull-up nội, tích cực mức LOW |
| Tải điều khiển qua SWIO | `SWIO_AS_GPIO_PIN` (`MCU_SWIO`) | PD1 | **CHỈ** hoạt động như GPIO sau khi giải phóng thành công |

## Cách khôi phục nếu chip "không phản hồi" mạch nạp

- Nếu PD1 đang ở chế độ GPIO và mạch nạp không bắt được tín hiệu: giữ chip ở
  trạng thái reset (ví dụ kéo GND vào NRST nếu board có chân này, hoặc rút
  nguồn) trong lúc lệnh `pio run -t upload` đang chờ, sau đó thả reset đúng
  lúc để minichlink kịp bắt tín hiệu SWIO trong vài mili-giây đầu.
- Cách chắc chắn nhất: **không giữ nút** khi cấp nguồn — firmware sẽ tự giữ
  nguyên chế độ debug và luôn nạp lại được bình thường.

## Build & Nạp

```bash
pio run -e CH32V003J4M6 -t upload_and_sdi_monitor
```
