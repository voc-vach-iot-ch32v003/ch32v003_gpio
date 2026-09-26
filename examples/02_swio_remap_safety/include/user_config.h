/**
 * @file user_config.h
 * @author Vọc Vạch IoT
 * @brief Định nghĩa chân dùng trong ví dụ giải phóng/khôi phục chân SWIO.
 */

#ifndef USER_CONFIG_H
#define USER_CONFIG_H

/** @brief Chân vật lý số 3 (PA2) — LED báo trạng thái chế độ hiện tại. */
#define STATUS_LED_PIN MCU_PIN3

/** @brief Chân vật lý số 5 (PC1) — Nút nhấn "giữ để giải phóng" SWIO. */
#define HOLD_TO_RELEASE_BTN_PIN MCU_PIN5

/** @brief Chân SWIO (PD1) — chỉ dùng làm GPIO SAU KHI đã gọi setSwioMode(SWIO_MODE_GPIO). */
#define SWIO_AS_GPIO_PIN MCU_SWIO

/** @brief Thời gian (ms) phải giữ nút lúc khởi động để cho phép giải phóng SWIO. */
#define HOLD_TO_RELEASE_MS 3000
#define HOLD_POLL_INTERVAL_MS 50

#endif // USER_CONFIG_H
