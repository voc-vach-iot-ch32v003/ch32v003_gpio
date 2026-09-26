#include "ch32fun.h"
#include "ch32v003_delay.h"
#include "ch32v003_gpio.h"
#include "user_config.h"

// ============================================================================
// VÍ DỤ NÂNG CAO: Giải phóng an toàn chân nạp SWIO (PD1) thành GPIO thường.
//
// ⚠️ CẢNH BÁO PHẦN CỨNG:
// Chân PD1 (SWIO) là chân DUY NHẤT dùng để nạp/gỡ lỗi chương trình trên
// CH32V003 (giao thức 1 dây minichlink). Khi gọi setSwioMode(SWIO_MODE_GPIO),
// chức năng nạp chương trình qua PD1 sẽ TẠM THỜI VÔ HIỆU HÓA cho đến khi:
//   (a) Chip được reset/cấp nguồn lại VÀ firmware không tự động giải phóng lại
//       SWIO ngay khi khởi động, HOẶC
//   (b) Firmware chủ động gọi lại setSwioMode(SWIO_MODE_DEBUG) trước khi rơi
//       vào trạng thái treo (hang) hoặc vòng lặp không lối thoát.
//
// Nếu firmware bị lỗi (treo/crash) TRONG LÚC PD1 đang ở chế độ GPIO, mạch nạp
// sẽ KHÔNG THỂ giao tiếp với chip nữa (giống hiện tượng "brick"). Cách khôi
// phục phần cứng thông thường là giữ chip ở trạng thái reset (kéo NRST hoặc
// cắt nguồn) trong lúc mạch nạp cố gắng bắt tín hiệu SWIO ngay những mili-giây
// đầu tiên sau khi cấp nguồn trở lại — không phải lúc nào cũng thành công.
//
// ĐỂ AN TOÀN, ví dụ này CHỈ giải phóng SWIO khi người dùng CHỦ ĐỘNG giữ nút
// nhấn HOLD_TO_RELEASE_BTN_PIN liên tục trong HOLD_TO_RELEASE_MS ngay sau khi
// cấp nguồn/reset. Nếu không giữ nút, chip giữ nguyên SWIO ở SWIO_MODE_DEBUG
// (mặc định) để luôn có thể nạp lại bình thường.
// ============================================================================

static uint8_t waitForHoldToRelease(void)
{
    uint32_t heldMs = 0;

    while (heldMs < HOLD_TO_RELEASE_MS)
    {
        if (digitalRead(HOLD_TO_RELEASE_BTN_PIN) != LOW) // Nhả nút giữa chừng -> hủy
        {
            return 0;
        }

        // Nhấp nháy nhanh LED để báo "đang đếm giữ nút"
        digitalToggle(STATUS_LED_PIN);
        delayMs(HOLD_POLL_INTERVAL_MS);
        heldMs += HOLD_POLL_INTERVAL_MS;
    }

    return 1; // Giữ đủ thời gian yêu cầu
}

static void setup(void)
{
    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(HOLD_TO_RELEASE_BTN_PIN, INPUT_PULLUP);

    // SWIO_MODE_DEBUG là trạng thái mặc định phần cứng, không cần gọi lại,
    // nhưng gọi tường minh ở đây để khẳng định rõ trạng thái khởi đầu an toàn.
    setSwioMode(SWIO_MODE_DEBUG);

    if (digitalRead(HOLD_TO_RELEASE_BTN_PIN) == LOW && waitForHoldToRelease())
    {
        // Người dùng đã chủ động giữ đủ lâu -> cho phép giải phóng PD1
        setSwioMode(SWIO_MODE_GPIO);
        pinMode(SWIO_AS_GPIO_PIN, OUTPUT);

        // Báo hiệu đã chuyển chế độ: LED sáng cố định 2 giây
        digitalWrite(STATUS_LED_PIN, HIGH);
        delayMs(2000);
        digitalWrite(STATUS_LED_PIN, LOW);
    }
}

static void loop(void)
{
    if (getSwioMode() == SWIO_MODE_GPIO)
    {
        // Chế độ GPIO: PD1 điều khiển tải như chân bình thường
        digitalToggle(SWIO_AS_GPIO_PIN);
        delayMs(500);
    }
    else
    {
        // Chế độ mặc định (an toàn): LED nhấp nháy chậm báo "sẵn sàng nạp lại"
        digitalToggle(STATUS_LED_PIN);
        delayMs(1000);
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
