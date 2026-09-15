/**
 * @file ch32v003_gpio_pins.h
 * @author Vọc Vạch IoT
 * @brief Định nghĩa sơ đồ chân vật lý (MCU_Pin_t) và chân chức năng đặc biệt (MCU_SpecialPin_t) cho CH32V003.
 * @version 1.0.0
 * @date 2026-06-07
 */

#ifndef CH32V003_GPIO_PINS_H
#define CH32V003_GPIO_PINS_H

// ============================================================================
// ĐỊNH NGHĨA CHÂN THEO SỐ THỨ TỰ VẬT LÝ TRÊN MCU (MCU_Pin_t)
// Kiến trúc Bit-packing: (Mã hóa Port << 4) | Số chân Pin.
// Trong đó: Port A = 0, Port C = 1, Port D = 2.
// ============================================================================

#if !defined(CH32V003_J4M6) && !defined(CH32V003_A4M6) && !defined(CH32V003_F4P6)
#define CH32V003_J4M6 /**< Mặc định chọn gói SOP8 nếu không xác định trước */
#endif

/**
 * @brief Định nghĩa danh sách chân vật lý dựa trên sơ đồ đóng gói IC thực tế.
 */
typedef enum
{
#if defined(CH32V003_J4M6) // ================= Bản SOP8 (8 chân) =================
    /** @brief Chân vật lý 1: Cổng Port D - Pin 6 (PD6) / Port A - Pin 1 (PA1).
     *  Default: GPIO / ADC CH1/CH3 / SYS OSCI / TIM1 CH2
     *  Alt: OPA OPN0 / TIM1 CH3 / UART URX / UART UTX */
    MCU_PIN1 = (0 << 4) | 1,

    /** @brief Chân vật lý 2: Chân Nguồn VSS (GND) */
    MCU_PIN2 = 2,

    /** @brief Chân vật lý 3: Cổng Port A - Pin 2 (PA2).
     *  Default: GPIO / ADC CH0 / SYS OSCO / TIM1 CH2N
     *  Alt: OPA OPP0 / TIM1 AETR2 */
    MCU_PIN3 = (0 << 4) | 2,

    /** @brief Chân vật lý 4: Chân Nguồn VDD (3.3V/5V) */
    MCU_PIN4 = 4,

    /** @brief Chân vật lý 5: Cổng Port C - Pin 1 (PC1).
     *  Default: GPIO / ADC CH7 / I2C SDA / TIM1 BKIN / SPI NSS / UART RX
     *  Alt: TIM1 CH1/4 / TIM1 ETR */
    MCU_PIN5 = (1 << 4) | 1,

    /** @brief Chân vật lý 6: Cổng Port C - Pin 2 (PC2).
     *  Default: GPIO / ADC CH8 / I2C SCL / TIM1 BKIN
     *  Alt: TIM1 AETR / UART RTS / TIM2 CH2 / TIM1 ETR */
    MCU_PIN6 = (1 << 4) | 2,

    /** @brief Chân vật lý 7: Cổng Port C - Pin 4 (PC4).
     *  Default: GPIO / ADC CH2 / TIM1 CH4 / SYS MCO
     *  Alt: TIM1 CH1CH2N */
    MCU_PIN7 = (1 << 4) | 4,

    /** @brief Chân vật lý 8: Cổng Port D - Pin 1 (PD1) / Port D - Pin 5 (PD5) / Port D - Pin 4 (PD4).
     *  Default: GPIO / SWD SWIO / TIM1 AETR2 / ADC A5/A7 / TIM1 CH4 / TIM1 C1ETR / UART UTX
     *  Alt: TIM1 CH3N / I2C SCL / UART URX / OPA / TIM1 C4ETR / UART UCK */
    MCU_PIN8 = (2 << 4) | 1,

#elif defined(CH32V003_A4M6) // ================= Bản SOP16 (16 chân) =================
    /** @brief Chân vật lý 1: Cổng Port C - Pin 1 (PC1).
     *  Default: GPIO / I2C SDA
     *  Alt: TIM1 BKIN / SPI NSS / UART RX / TIM1 CH1/CH4 / TIM1 ETR */
    MCU_PIN1 = (1 << 4) | 1,

    /** @brief Chân vật lý 2: Cổng Port C - Pin 2 (PC2).
     *  Default: GPIO / I2C SCL
     *  Alt: TIM1 BKIN / TIM1 AETR / UART RTS / TIM1 CH2 / TIM1 ETR */
    MCU_PIN2 = (1 << 4) | 2,

    /** @brief Chân vật lý 3: Cổng Port C - Pin 3 (PC3).
     *  Default: GPIO / TIM1 CH3
     *  Alt: TIM1 CH1N / UART CTS */
    MCU_PIN3 = (1 << 4) | 3,

    /** @brief Chân vật lý 4: Cổng Port C - Pin 4 (PC4).
     *  Default: GPIO / ADC CH2 / TIM1 CH4 / SYS MCO
     *  Alt: TIM1 CH1CH2N */
    MCU_PIN4 = (1 << 4) | 4,

    /** @brief Chân vật lý 5: Cổng Port C - Pin 6 (PC6).
     *  Default: GPIO / SPI MOSI
     *  Alt: TIM1 C1C3N / I2C SDA / UART UCTS */
    MCU_PIN5 = (1 << 4) | 6,

    /** @brief Chân vật lý 6: Cổng Port C - Pin 7 (PC7).
     *  Default: GPIO / SPI MISO / TIM1 CH2
     *  Alt: TIM1 CH2 / UART URTS / TIM1 CH2 */
    MCU_PIN6 = (1 << 4) | 7,

    /** @brief Chân vật lý 7: Cổng Port D - Pin 1 (PD1).
     *  Default: GPIO / TIM1 AETR2 / SWD SWIO
     *  Alt: TIM1 CH3N / I2C SCL / UART URX */
    MCU_PIN7 = (2 << 4) | 1,

    /** @brief Chân vật lý 8: Cổng Port D - Pin 4 (PD4).
     *  Default: GPIO / ADC CH7 / TIM1 C1ETR
     *  Alt: OPA / TIM1 C4ETR / UART UCK */
    MCU_PIN8 = (2 << 4) | 4,

    /** @brief Chân vật lý 9: Cổng Port D - Pin 5 (PD5).
     *  Default: GPIO / ADC CH5 / TIM1 CH4 / UART UTX
     *  Alt: UART URX */
    MCU_PIN9 = (2 << 4) | 5,

    /** @brief Chân vật lý 10: Cổng Port D - Pin 6 (PD6).
     *  Default: GPIO / ADC CH6 / TIM1 CH3 / UART URX
     *  Alt: UART UTX */
    MCU_PIN10 = (2 << 4) | 6,

    /** @brief Chân vật lý 11: Cổng Port D - Pin 7 (PD7).
     *  Default: GPIO / SYS NRST / TIM1 CH4 / UART CK
     *  Alt: OPA OPP1 */
    MCU_PIN11 = (2 << 4) | 7,

    /** @brief Chân vật lý 12: Cổng Port A - Pin 1 (PA1).
     *  Default: GPIO / ADC CH1 / SYS OSCI / TIM1 CH2
     *  Alt: OPA OPN0 */
    MCU_PIN12 = (0 << 4) | 1,

    /** @brief Chân vật lý 13: Cổng Port A - Pin 2 (PA2).
     *  Default: GPIO / ADC CH0 / SYS OSCO / TIM1 CH2N
     *  Alt: OPA OPP0 / TIM1 AETR2 */
    MCU_PIN13 = (0 << 4) | 2,

    /** @brief Chân vật lý 16: Cổng Port C - Pin 0 (PC0).
     *  Default: GPIO / TIM1 CH3
     *  Alt: TIM1 CH3 / SPI NSS / UART TX */
    MCU_PIN16 = (1 << 4) | 0,

#elif defined(CH32V003_F4P6) // ================= Bản TSSOP20 (20 chân) =================
    /** @brief Chân vật lý 1: Cổng Port D - Pin 4 (PD4).
     *  Default: GPIO / ADC CH7 (A7) / TIM1 C1ETR
     *  Alt: OPA / TIM1 C4ETR / UART UCK */
    MCU_PIN1 = (2 << 4) | 4,

    /** @brief Chân vật lý 2: Cổng Port D - Pin 5 (PD5).
     *  Default: GPIO / ADC CH5 (A5) / TIM1 CH4 / UART UTX
     *  Alt: UART URX */
    MCU_PIN2 = (2 << 4) | 5,

    /** @brief Chân vật lý 3: Cổng Port D - Pin 6 (PD6).
     *  Default: GPIO / ADC CH6 (A6) / TIM1 CH3 / UART URX
     *  Alt: UART UTX */
    MCU_PIN3 = (2 << 4) | 6,

    /** @brief Chân vật lý 4: Cổng Port D - Pin 7 (PD7).
     *  Default: GPIO / SYS NRST / TIM1 CH4 / UART CK
     *  Alt: OPA OPP1 */
    MCU_PIN4 = (2 << 4) | 7,

    /** @brief Chân vật lý 5: Cổng Port A - Pin 1 (PA1).
     *  Default: GPIO / ADC CH1 (A1) / SYS OSCI / TIM1 CH2
     *  Alt: OPA OPN0 */
    MCU_PIN5 = (0 << 4) | 1,

    /** @brief Chân vật lý 6: Cổng Port A - Pin 2 (PA2).
     *  Default: GPIO / ADC CH0 (A0) / SYS OSCO / TIM1 CH2N
     *  Alt: OPA OPP0 / TIM1 AETR2 */
    MCU_PIN6 = (0 << 4) | 2,

    /** @brief Chân vật lý 7: Chân Nguồn VSS (GND) */
    MCU_PIN7 = 7,

    /** @brief Chân vật lý 8: Cổng Port D - Pin 0 (PD0).
     *  Default: GPIO / TIM1 CH1N
     *  Alt: UART TXD / OPA OPN1 / I2C SDA */
    MCU_PIN8 = (2 << 4) | 0,

    /** @brief Chân vật lý 9: Chân Nguồn VDD (3.3V/5V) */
    MCU_PIN9 = 9,

    /** @brief Chân vật lý 10: Cổng Port C - Pin 0 (PC0).
     *  Default: GPIO / TIM1 CH3
     *  Alt: TIM1 CH3 / SPI NSS / UART TX */
    MCU_PIN10 = (1 << 4) | 0,

    /** @brief Chân vật lý 11: Cổng Port C - Pin 1 (PC1).
     *  Default: GPIO / I2C SDA / TIM1 BKIN / SPI NSS
     *  Alt: UART RX / TIM1 CH1/4 / TIM1 ETR */
    MCU_PIN11 = (1 << 4) | 1,

    /** @brief Chân vật lý 12: Cổng Port C - Pin 2 (PC2).
     *  Default: GPIO / I2C SCL / TIM1 BKIN
     *  Alt: TIM1 AETR / UART RTS / TIM2 CH2 / TIM1 ETR */
    MCU_PIN12 = (1 << 4) | 2,

    /** @brief Chân vật lý 13: Cổng Port C - Pin 3 (PC3).
     *  Default: GPIO / TIM1 CH3
     *  Alt: TIM1 CH1N / UART CTS */
    MCU_PIN13 = (1 << 4) | 3,

    /** @brief Chân vật lý 14: Cổng Port C - Pin 4 (PC4).
     *  Default: GPIO / ADC CH2 (A2) / TIM1 CH4 / SYS MCO
     *  Alt: TIM1 CH1CH2N */
    MCU_PIN14 = (1 << 4) | 4,

    /** @brief Chân vật lý 15: Cổng Port C - Pin 5 (PC5).
     *  Default: GPIO / SPI SCK / TIM1 T1ETR
     *  Alt: TIM1 CH3 / I2C SCL / UART UCK */
    MCU_PIN15 = (1 << 4) | 5,

    /** @brief Chân vật lý 16: Cổng Port C - Pin 6 (PC6).
     *  Default: GPIO / SPI MOSI
     *  Alt: TIM1 C1C3N / I2C SDA / UART UCTS */
    MCU_PIN16 = (1 << 4) | 6,

    /** @brief Chân vật lý 17: Cổng Port C - Pin 7 (PC7).
     *  Default: GPIO / SPI MISO / TIM1 CH2
     *  Alt: UART URTS / TIM2 CH2 */
    MCU_PIN17 = (1 << 4) | 7,

    /** @brief Chân vật lý 18: Cổng Port D - Pin 1 (PD1).
     *  Default: GPIO / TIM1 AETR2 / SWD SWIO
     *  Alt: TIM1 CH3N / I2C SCL / UART URX */
    MCU_PIN18 = (2 << 4) | 1,

    /** @brief Chân vật lý 19: Cổng Port D - Pin 2 (PD2).
     *  Default: GPIO / ADC CH3 (A3) / TIM1 CH1
     *  Alt: TIM1 CH3 / TIM1 CH2N */
    MCU_PIN19 = (2 << 4) | 2,

    /** @brief Chân vật lý 20: Cổng Port D - Pin 3 (PD3).
     *  Default: GPIO / ADC CH4 (A4) / TIM1 CH2
     *  Alt: TIM1 CH4 / TIM1 AETR */
    MCU_PIN20 = (2 << 4) | 3,
#endif
} MCU_Pin_t;

// ============================================================================
// ĐỊNH NGHĨA CHÂN NGOẠI VI ĐẶC BIỆT (MCU_SpecialPin_t)
// ============================================================================

/**
 * @brief Định nghĩa các chân chức năng đặc biệt của hệ thống (I2C, UART, SPI, ADC, v.v.).
 */
typedef enum
{
    // ------------------------------------------------------------------------
    // 1. CHẮC CHẮN CÓ TRÊN MỌI GÓI VỎ (SOP8, SOP16, TSSOP20)
    // ------------------------------------------------------------------------
    
    /** @brief [GIAO TIẾP] Chân nạp chương trình Single-wire (SWIO). (Default PD1) */
    MCU_SWIO = (2 << 4) | 1,

    /** @brief [GIAO TIẾP] I2C SDA Mặc định (PC1). */
    MCU_I2C_SDA = (1 << 4) | 1,

    /** @brief [GIAO TIẾP] I2C SCL Mặc định (PC2). */
    MCU_I2C_SCL = (1 << 4) | 2,

    /** @brief [GIAO TIẾP] UART TX Mặc định (PD5). */
    MCU_UART_TX = (2 << 4) | 5,

    /** @brief [GIAO TIẾP] UART RX Mặc định (PD6). */
    MCU_UART_RX = (2 << 4) | 6,

    /** @brief [GIAO TIẾP] SPI NSS Mặc định (PC1). */
    MCU_SPI_NSS = (1 << 4) | 1,

    /** @brief [NGOẠI VI ANALOG] ADC CH5 Mặc định (PD4). */
    MCU_ADC_CH5 = (2 << 4) | 4,

    /** @brief [NGOẠI VI ANALOG] ADC CH7 Mặc định (PC1). */
    MCU_ADC_CH7 = (1 << 4) | 1,

    /** @brief [NGOẠI VI ANALOG] ADC CH8 Mặc định (PC2). */
    MCU_ADC_CH8 = (1 << 4) | 2,

    // --- REMAP CHO GÓI VỎ BẤT KỲ (Khả dụng trên SOP8/SOP16/TSSOP20) ---
    
    /** @brief [GIAO TIẾP REMAP] UART TX Remap-2 (PD6). */
    MCU_UART_TX_REMAP2 = (2 << 4) | 6,

    /** @brief [GIAO TIẾP REMAP] UART RX Remap-2 (PD5). */
    MCU_UART_RX_REMAP2 = (2 << 4) | 5,

    /** @brief [GIAO TIẾP REMAP] UART TX Remap-1 (PD0 - Dùng trên SOP8 pin 8). */
    MCU_UART_TX_REMAP1 = (2 << 4) | 0,

    /** @brief [GIAO TIẾP REMAP] UART RX Remap-1 (PD1 - Dùng trên SOP8 pin 8). */
    MCU_UART_RX_REMAP1 = (2 << 4) | 1,

    /** @brief [GIAO TIẾP REMAP] I2C SDA Remap-1 (PD0 - Dùng trên SOP8 pin 8). */
    MCU_I2C_SDA_REMAP1 = (2 << 4) | 0,

    /** @brief [GIAO TIẾP REMAP] I2C SCL Remap-1 (PD1 - Dùng trên SOP8 pin 8). */
    MCU_I2C_SCL_REMAP1 = (2 << 4) | 1,

    /** @brief [GIAO TIẾP REMAP] UART RX Remap-3 (PC1). */
    MCU_UART_RX_REMAP3 = (1 << 4) | 1,


#if defined(CH32V003_A4M6) || defined(CH32V003_F4P6)
    // ------------------------------------------------------------------------
    // 2. BỔ SUNG CHO SOP16 VÀ TSSOP20 (A4M6 & F4P6)
    // ------------------------------------------------------------------------

    /** @brief [HỆ THỐNG] Chân Reset cứng (NRST) (PD7). */
    MCU_NRST = (2 << 4) | 7,

    /** @brief [GIAO TIẾP] SPI MOSI Mặc định (PC6). */
    MCU_SPI_MOSI = (1 << 4) | 6,

    /** @brief [GIAO TIẾP] SPI MISO Mặc định (PC7). */
    MCU_SPI_MISO = (1 << 4) | 7,

    /** @brief [NGOẠI VI ANALOG] ADC CH0 Mặc định (PA2). */
    MCU_ADC_CH0 = (0 << 4) | 2,

    /** @brief [NGOẠI VI ANALOG] ADC CH1 Mặc định (PA1). */
    MCU_ADC_CH1 = (0 << 4) | 1,

    /** @brief [NGOẠI VI ANALOG] ADC CH2 Mặc định (PC4). */
    MCU_ADC_CH2 = (1 << 4) | 4,

    /** @brief [NGOẠI VI ANALOG] ADC CH6 Mặc định (PD5). */
    MCU_ADC_CH6 = (2 << 4) | 5,

    // --- REMAP BỔ SUNG CHO SOP16 & TSSOP20 ---

    /** @brief [GIAO TIẾP REMAP] SPI NSS Remap-1 (PC0). */
    MCU_SPI_NSS_REMAP1 = (1 << 4) | 0,

    /** @brief [GIAO TIẾP REMAP] UART TX Remap-3 (PC0). */
    MCU_UART_TX_REMAP3 = (1 << 4) | 0,

    /** @brief [GIAO TIẾP REMAP] I2C SDA Remap-2/3 (PC6). */
    MCU_I2C_SDA_REMAP2 = (1 << 4) | 6,
#endif


#if defined(CH32V003_F4P6)
    // ------------------------------------------------------------------------
    // 3. BỔ SUNG CHO ĐẦY ĐỦ CHÂN TSSOP20 (F4P6)
    // ------------------------------------------------------------------------

    /** @brief [GIAO TIẾP] SPI SCK Mặc định (PC5). */
    MCU_SPI_SCK = (1 << 4) | 5,

    /** @brief [NGOẠI VI ANALOG] ADC CH3 Mặc định (PC5). */
    MCU_ADC_CH3 = (1 << 4) | 5,

    /** @brief [NGOẠI VI ANALOG] ADC CH4 Mặc định (PC3). */
    MCU_ADC_CH4 = (1 << 4) | 3,

    // --- REMAP BỔ SUNG CHO TSSOP20 ---

    /** @brief [GIAO TIẾP REMAP] I2C SCL Remap-2/3 (PC5). */
    MCU_I2C_SCL_REMAP2 = (1 << 4) | 5,

    // --- TIỆN ÍCH PHẦN CỨNG SẴN CÓ TRÊN BOARD PHÁT TRIỂN ---

    /** @brief Chân LED tích hợp trên kit Twen32F003 (PD1). */
    LED_BUILTIN_TWEN32F003 = (2 << 4) | 1,

    /** @brief Chân Nút nhấn tích hợp trên kit Twen32F003 (PC0). */
    BTN_BUILTIN_TWEN32F003 = (1 << 4) | 0
#endif
} MCU_SpecialPin_t;

#endif // CH32V003_GPIO_PINS_H
