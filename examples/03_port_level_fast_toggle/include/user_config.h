/**
 * @file user_config.h
 * @author Vọc Vạch IoT
 * @brief Định nghĩa 2 chân dùng để so sánh tốc độ API Arduino-style vs Port-level.
 */

#ifndef USER_CONFIG_H
#define USER_CONFIG_H

/** @brief Chân vật lý số 3 (PA2) — toggle qua API Arduino-style digitalToggle(mcuPin). */
#define TOGGLE_ARDUINO_STYLE_PIN MCU_PIN5

/** @brief Chân vật lý số 6 (PC2) — toggle trực tiếp qua digitalTogglePort(GPIOx, pinNumber). */
#define TOGGLE_PORT_LEVEL_PIN MCU_PIN6
#define TOGGLE_PORT_LEVEL_PORT GPIOC
#define TOGGLE_PORT_LEVEL_NUM  2

/** @brief Số lần toggle dùng để đo trong mỗi vòng benchmark. */
#define BENCHMARK_ITERATIONS 100000UL

#endif // USER_CONFIG_H
