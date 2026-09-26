/**
 * @file user_config.h
 * @author Vọc Vạch IoT
 * @brief Định nghĩa chân LED và Nút nhấn dùng trong ví dụ Blink + Button.
 */

#ifndef USER_CONFIG_H
#define USER_CONFIG_H

/** @brief Chân vật lý số 3 (PA2 trên mọi gói vỏ) điều khiển LED. */
#define LED_PIN MCU_PIN3

/** @brief Chân vật lý số 5 (PC1 trên mọi gói vỏ) đọc nút nhấn. */
#define BTN_PIN MCU_PIN5

/** @brief Thời gian chống dội cơ học của nút nhấn (mili-giây). */
#define BTN_DEBOUNCE_MS 200

#endif // USER_CONFIG_H
