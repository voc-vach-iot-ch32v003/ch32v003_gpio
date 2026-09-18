/**
 * @file    ch32v003_gpio_pins.h
 * @author  Vọc Vạch IoT
 * @brief   Định nghĩa sơ đồ chân vật lý (MCU_Pin_t) và chân chức năng đặc biệt
 *          (MCU_SpecialPin_t) cho CH32V003.
 * @version 1.0.0
 * @date    2026-06-07
 *
 * ---------------------------------------------------------------------------
 * QUY ƯỚC MÃ HÓA:      MCU_PIN = (Chỉ số Port << 4) | Chỉ số Pin
 *                      Port A = 0 | Port C = 1 | Port D = 2
 *                      Port 15 (0xF) = Port giả lập cho chân nguồn VDD/VSS.
 *
 * QUY ƯỚC ĐẶT TÊN:     MCU_PIN<số thứ tự chân vật lý>
 *                      Chân GỘP NỘI BỘ có thêm hằng số hậu tố _P<pad> mang doc
 *                      chi tiết của từng pad; MCU_PIN<n> giữ giá trị pad mặc
 *                      định để code cũ biên dịch lại không bị vỡ.
 *
 * PHÂN LOẠI CHỨC NĂNG: Theo ma trận Alternate Function của lõi silicon.
 *                      Default   = khả dụng khi bit remap của ngoại vi = 00.
 *                      Remap 1/2/3 = phải set bit remap tương ứng trong
 * AFIO_PCFR1.
 *
 * ---------------------------------------------------------------------------
 * VỀ CHÂN GỘP NỘI BỘ (Internal Bonding — chỉ có ở bản SOP-8 / J4M6):
 *
 *      Mỗi pad vẫn có thanh ghi CFGLR/OUTDR/INDR riêng dù dùng chung một đầu
 *      kim loại. Khi kích hoạt một pad, các pad anh em trên cùng chân PHẢI được
 *      đưa về Input Floating hoặc Analog, nếu không hai bộ đệm ngõ ra sẽ tranh
 *      chấp trên cùng sợi bonding.
 * ---------------------------------------------------------------------------
 */

#ifndef CH32V003_GPIO_PINS_H
#define CH32V003_GPIO_PINS_H

#if !defined(CH32V003_J4M6) && !defined(CH32V003_A4M6) &&                      \
    !defined(CH32V003_F4P6)
#define CH32V003_J4M6 /**< Mặc định chọn gói SOP8 nếu không xác định trước */
#endif

/* ==========================================================================
 * CHỈ SỐ PORT & MACRO TIỆN ÍCH
 * ========================================================================== */
#define MCU_PORT_INDEX_A (0U) /*!< Port A */
#define MCU_PORT_INDEX_C (1U) /*!< Port C */
#define MCU_PORT_INDEX_D (2U) /*!< Port D */
#define MCU_PORT_INDEX_POWER                                                   \
  (15U) /*!< Port giả lập: chân nguồn, không phải GPIO */

#define MCU_PIN_GET_PORT(pin) (((unsigned)(pin) >> 4U) & 0x0FU)
#define MCU_PIN_GET_NUM(pin) ((unsigned)(pin) & 0x0FU)
#define MCU_PIN_IS_GPIO(pin)                                                   \
  ((MCU_PIN_GET_PORT(pin) <= MCU_PORT_INDEX_D) && (MCU_PIN_GET_NUM(pin) <= 7U))

/* ==========================================================================
 * DANH SÁCH CHÂN VẬT LÝ THEO GÓI VỎ
 * ========================================================================== */
typedef enum
{
#if defined(CH32V003_J4M6) // ================= Bản SOP8 (8 chân) =================

    /**
     * @brief PIN 1 — Gộp chân nội bộ: PA1 + PD6. Pad mặc định là PA1.
     *
     * Chi tiết chức năng xem tại MCU_PIN1_PA1 và MCU_PIN1_PD6.
     */
    MCU_PIN1 = (MCU_PORT_INDEX_A << 4) | 1,

    /**
     * @brief PIN 1 — Pad PA1 (pad mặc định của chân vật lý số 1)
     *
     * Port A - Pin 1 (PA1):
     * - Default: GPIO | ADC Kênh 1 (A1) | TIM1 CH2
     *            | OPA OPN0 (Op-Amp ngõ vào đảo kênh 0)
     * - Hệ thống (không qua remap): SYS OSCI — Ngõ vào thạch anh ngoại
     * - Alternative:
     *   - Remap 2: TIM1 CH2
     */
    MCU_PIN1_PA1 = (MCU_PORT_INDEX_A << 4) | 1,

    /**
     * @brief PIN 1 — Pad PD6 (pad phụ, dùng chung đầu kim loại với PA1)
     *
     * Port D - Pin 6 (PD6):
     * - Default: GPIO | ADC Kênh 6 (A6) | UART RX (URX)
     * - Alternative:
     *   - Remap 2: UART TX (UTX)
     *   - Remap 3: TIM2 CH3
     */
    MCU_PIN1_PD6 = (MCU_PORT_INDEX_D << 4) | 6,

    /**
     * @brief PIN 2 — VSS (GND). Không phải GPIO, dùng Port giả lập 0xF.
     */
    MCU_PIN2 = (MCU_PORT_INDEX_POWER << 4) | 2,

    /**
     * @brief PIN 3 — Port A - Pin 2 (PA2). Chân đơn, không gộp.
     *
     * Port A - Pin 2 (PA2):
     * - Default: GPIO | ADC Kênh 0 (A0) | TIM1 CH2N (kênh 2 đảo)
     *            | OPA OPP0 (Op-Amp ngõ vào không đảo kênh 0)
     * - Hệ thống (không qua remap): SYS OSCO — Ngõ ra thạch anh ngoại
     * - Alternative:
     *   - Remap 1: ADC AETR2 (External Trigger 2)
     *   - Remap 2: TIM1 CH2N (kênh 2 đảo)
     */
    MCU_PIN3 = (MCU_PORT_INDEX_A << 4) | 2,

    /**
     * @brief PIN 4 — VDD (3.3V/5V). Không phải GPIO, dùng Port giả lập 0xF.
     */
    MCU_PIN4 = (MCU_PORT_INDEX_POWER << 4) | 4,

    /**
     * @brief PIN 5 — Port C - Pin 1 (PC1). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 1 (PC1):
     * - Default: GPIO | I2C SDA | SPI NSS
     * - Alternative:
     *   - Remap 1: TIM1 BKIN (Break Input) | TIM2 CH4
     *   - Remap 2: TIM2 CH1 | TIM2 ETR
     *   - Remap 3: TIM1 BKIN | TIM2 CH1 | TIM2 ETR | UART RX (URX)
     */
    MCU_PIN5 = (MCU_PORT_INDEX_C << 4) | 1,

    /**
     * @brief PIN 6 — Port C - Pin 2 (PC2). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 2 (PC2):
     * - Default: GPIO | I2C SCL | TIM1 BKIN (Break Input) | UART RTS
     * - Alternative:
     *   - Remap 1: ADC AETR (External Trigger) | TIM2 CH2 | UART RTS
     *   - Remap 2: TIM1 BKIN (Break Input)
     *   - Remap 3: TIM1 ETR
     */
    MCU_PIN6 = (MCU_PORT_INDEX_C << 4) | 2,

    /**
     * @brief PIN 7 — Port C - Pin 4 (PC4). Chân đơn, không gộp.
     *
     * Port C - Pin 4 (PC4):
     * - Default: GPIO | ADC Kênh 2 (A2) | TIM1 CH4 | SYS MCO (Ngõ ra Clock)
     * - Alternative:
     *   - Remap 1: TIM1 CH2N (kênh 2 đảo)
     *   - Remap 2: TIM1 CH4
     *   - Remap 3: TIM1 CH1
     */
    MCU_PIN7 = (MCU_PORT_INDEX_C << 4) | 4,

    /**
     * @brief PIN 8 — Gộp chân nội bộ: PD1 + PD5 + PD4. Pad mặc định là PD1.
     *
     * Đây đồng thời là chân nạp/gỡ lỗi SWIO. Chi tiết từng pad xem tại
     * MCU_PIN8_PD1, MCU_PIN8_PD5 và MCU_PIN8_PD4.
     */
    MCU_PIN8 = (MCU_PORT_INDEX_D << 4) | 1,

    /**
     * @brief PIN 8 — Pad PD1 (pad mặc định của chân vật lý số 8)
     *
     * Port D - Pin 1 (PD1):
     * - Default: GPIO | SWD SWIO (Nạp/Debug 1 dây) | TIM1 CH3N (kênh 3 đảo)
     *            | ADC AETR2 (External Trigger 2)
     * - Alternative:
     *   - Remap 1: I2C SCL | TIM1 CH3N (kênh 3 đảo) | UART RX (URX)
     *   - Remap 2: TIM1 CH3N (kênh 3 đảo)
     */
    MCU_PIN8_PD1 = (MCU_PORT_INDEX_D << 4) | 1,

    /**
     * @brief PIN 8 — Pad PD5 (pad phụ)
     *
     * Port D - Pin 5 (PD5):
     * - Default: GPIO | ADC Kênh 5 (A5) | UART TX (UTX)
     * - Alternative:
     *   - Remap 2: UART RX (URX)
     *   - Remap 3: TIM2 CH4
     */
    MCU_PIN8_PD5 = (MCU_PORT_INDEX_D << 4) | 5,

    /**
     * @brief PIN 8 — Pad PD4 (pad phụ)
     *
     * Port D - Pin 4 (PD4):
     * - Default: GPIO | ADC Kênh 7 (A7) | TIM2 CH1 | TIM2 ETR
     *            | UART CK (Clock đồng bộ) | OPA OPO (Op-Amp ngõ ra)
     * - Alternative:
     *   - Remap 2: TIM1 ETR
     *   - Remap 3: TIM1 CH4
     */
    MCU_PIN8_PD4 = (MCU_PORT_INDEX_D << 4) | 4,

#elif defined(CH32V003_A4M6) // ================= Bản SOP16 (16 chân) =================

    /**
     * @brief PIN 1 — Port C - Pin 1 (PC1). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 1 (PC1):
     * - Default: GPIO | I2C SDA | SPI NSS
     * - Alternative:
     *   - Remap 1: TIM1 BKIN (Break Input) | TIM2 CH4
     *   - Remap 2: TIM2 CH1 | TIM2 ETR
     *   - Remap 3: TIM1 BKIN | TIM2 CH1 | TIM2 ETR | UART RX (URX)
     */
    MCU_PIN1 = (MCU_PORT_INDEX_C << 4) | 1,

    /**
     * @brief PIN 2 — Port C - Pin 2 (PC2). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 2 (PC2):
     * - Default: GPIO | I2C SCL | TIM1 BKIN (Break Input) | UART RTS
     * - Alternative:
     *   - Remap 1: ADC AETR (External Trigger) | TIM2 CH2 | UART RTS
     *   - Remap 2: TIM1 BKIN (Break Input)
     *   - Remap 3: TIM1 ETR
     */
    MCU_PIN2 = (MCU_PORT_INDEX_C << 4) | 2,

    /**
     * @brief PIN 3 — Port C - Pin 3 (PC3). Chân đơn, không gộp.
     *
     * Port C - Pin 3 (PC3):
     * - Default: GPIO | TIM1 CH3
     * - Alternative:
     *   - Remap 1: TIM1 CH1N (kênh 1 đảo) | UART CTS
     *   - Remap 2: TIM1 CH3
     *   - Remap 3: TIM1 CH1N (kênh 1 đảo)
     */
    MCU_PIN3 = (MCU_PORT_INDEX_C << 4) | 3,

    /**
     * @brief PIN 4 — Port C - Pin 4 (PC4). Chân đơn, không gộp.
     *
     * Port C - Pin 4 (PC4):
     * - Default: GPIO | ADC Kênh 2 (A2) | TIM1 CH4 | SYS MCO (Ngõ ra Clock)
     * - Alternative:
     *   - Remap 1: TIM1 CH2N (kênh 2 đảo)
     *   - Remap 2: TIM1 CH4
     *   - Remap 3: TIM1 CH1
     */
    MCU_PIN4 = (MCU_PORT_INDEX_C << 4) | 4,

    /**
     * @brief PIN 5 — Port C - Pin 6 (PC6). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 6 (PC6):
     * - Default: GPIO | SPI MOSI
     * - Alternative:
     *   - Remap 1: SPI MOSI | TIM1 CH1
     *   - Remap 2: I2C SDA | UART CTS
     *   - Remap 3: I2C SDA | TIM1 CH3N (kênh 3 đảo) | UART CTS
     */
    MCU_PIN5 = (MCU_PORT_INDEX_C << 4) | 6,

    /**
     * @brief PIN 6 — Port C - Pin 7 (PC7). Chân đơn, không gộp.
     *
     * Port C - Pin 7 (PC7):
     * - Default: GPIO | SPI MISO
     * - Alternative:
     *   - Remap 1: SPI MISO | TIM1 CH2
     *   - Remap 2: UART RTS
     *   - Remap 3: TIM1 CH2 | TIM2 CH2 | UART RTS
     */
    MCU_PIN6 = (MCU_PORT_INDEX_C << 4) | 7,

    /**
     * @brief PIN 7 — Port D - Pin 1 (PD1). Chân nạp/gỡ lỗi mặc định.
     *
     * Port D - Pin 1 (PD1):
     * - Default: GPIO | SWD SWIO (Nạp/Debug 1 dây) | TIM1 CH3N (kênh 3 đảo)
     *            | ADC AETR2 (External Trigger 2)
     * - Alternative:
     *   - Remap 1: I2C SCL | TIM1 CH3N (kênh 3 đảo) | UART RX (URX)
     *   - Remap 2: TIM1 CH3N (kênh 3 đảo)
     */
    MCU_PIN7 = (MCU_PORT_INDEX_D << 4) | 1,

    /**
     * @brief PIN 8 — Port D - Pin 4 (PD4). Chân đơn, không gộp.
     *
     * Port D - Pin 4 (PD4):
     * - Default: GPIO | ADC Kênh 7 (A7) | TIM2 CH1 | TIM2 ETR
     *            | UART CK (Clock đồng bộ) | OPA OPO (Op-Amp ngõ ra)
     * - Alternative:
     *   - Remap 2: TIM1 ETR
     *   - Remap 3: TIM1 CH4
     */
    MCU_PIN8 = (MCU_PORT_INDEX_D << 4) | 4,

    /**
     * @brief PIN 9 — Port D - Pin 5 (PD5). Chân đơn, không gộp.
     *
     * Port D - Pin 5 (PD5):
     * - Default: GPIO | ADC Kênh 5 (A5) | UART TX (UTX)
     * - Alternative:
     *   - Remap 2: UART RX (URX)
     *   - Remap 3: TIM2 CH4
     */
    MCU_PIN9 = (MCU_PORT_INDEX_D << 4) | 5,

    /**
     * @brief PIN 10 — Port D - Pin 6 (PD6). Chân đơn, không gộp.
     *
     * Port D - Pin 6 (PD6):
     * - Default: GPIO | ADC Kênh 6 (A6) | UART RX (URX)
     * - Alternative:
     *   - Remap 2: UART TX (UTX)
     *   - Remap 3: TIM2 CH3
     */
    MCU_PIN10 = (MCU_PORT_INDEX_D << 4) | 6,

    /**
     * @brief PIN 11 — Port D - Pin 7 (PD7). Mặc định là Reset phần cứng.
     *
     * Muốn dùng làm GPIO thường phải tắt chức năng NRST trong Option Byte.
     *
     * Port D - Pin 7 (PD7):
     * - Default: GPIO | SYS NRST (Reset phần cứng) | TIM2 CH4
     *            | OPA OPP1 (Op-Amp ngõ vào không đảo kênh 1)
     * - Alternative:
     *   - Remap 1: UART CK (Clock đồng bộ)
     *   - Remap 2: TIM2 CH4 | UART CK (Clock đồng bộ)
     */
    MCU_PIN11 = (MCU_PORT_INDEX_D << 4) | 7,

    /**
     * @brief PIN 12 — Port A - Pin 1 (PA1). Chân đơn, không gộp.
     *
     * Port A - Pin 1 (PA1):
     * - Default: GPIO | ADC Kênh 1 (A1) | TIM1 CH2
     *            | OPA OPN0 (Op-Amp ngõ vào đảo kênh 0)
     * - Hệ thống (không qua remap): SYS OSCI — Ngõ vào thạch anh ngoại
     * - Alternative:
     *   - Remap 2: TIM1 CH2
     */
    MCU_PIN12 = (MCU_PORT_INDEX_A << 4) | 1,

    /**
     * @brief PIN 13 — Port A - Pin 2 (PA2). Chân đơn, không gộp.
     *
     * Port A - Pin 2 (PA2):
     * - Default: GPIO | ADC Kênh 0 (A0) | TIM1 CH2N (kênh 2 đảo)
     *            | OPA OPP0 (Op-Amp ngõ vào không đảo kênh 0)
     * - Hệ thống (không qua remap): SYS OSCO — Ngõ ra thạch anh ngoại
     * - Alternative:
     *   - Remap 1: ADC AETR2 (External Trigger 2)
     *   - Remap 2: TIM1 CH2N (kênh 2 đảo)
     */
    MCU_PIN13 = (MCU_PORT_INDEX_A << 4) | 2,

    /**
     * @brief PIN 14 — VSS (GND). Không phải GPIO, dùng Port giả lập 0xF.
     */
    MCU_PIN14 = (MCU_PORT_INDEX_POWER << 4) | 14,

    /**
     * @brief PIN 15 — VDD (3.3V/5V). Không phải GPIO, dùng Port giả lập 0xF.
     */
    MCU_PIN15 = (MCU_PORT_INDEX_POWER << 4) | 15,

    /**
     * @brief PIN 16 — Port C - Pin 0 (PC0). Chân đơn, không gộp.
     *
     * Port C - Pin 0 (PC0):
     * - Default: GPIO | TIM2 CH3
     * - Alternative:
     *   - Remap 1: SPI NSS | TIM1 CH3
     *   - Remap 2: TIM2 CH3
     *   - Remap 3: UART TX (UTX)
     */
    MCU_PIN16 = (MCU_PORT_INDEX_C << 4) | 0,

#elif defined(CH32V003_F4P6) // ================= Bản TSSOP20 (20 chân)
    // =================

    /**
     * @brief PIN 1 — Port D - Pin 4 (PD4). Chân đơn, không gộp.
     *
     * Port D - Pin 4 (PD4):
     * - Default: GPIO | ADC Kênh 7 (A7) | TIM2 CH1 | TIM2 ETR
     *            | UART CK (Clock đồng bộ) | OPA OPO (Op-Amp ngõ ra)
     * - Alternative:
     *   - Remap 2: TIM1 ETR
     *   - Remap 3: TIM1 CH4
     */
    MCU_PIN1 = (MCU_PORT_INDEX_D << 4) | 4,

    /**
     * @brief PIN 2 — Port D - Pin 5 (PD5). Chân đơn, không gộp.
     *
     * Port D - Pin 5 (PD5):
     * - Default: GPIO | ADC Kênh 5 (A5) | UART TX (UTX)
     * - Alternative:
     *   - Remap 2: UART RX (URX)
     *   - Remap 3: TIM2 CH4
     */
    MCU_PIN2 = (MCU_PORT_INDEX_D << 4) | 5,

    /**
     * @brief PIN 3 — Port D - Pin 6 (PD6). Chân đơn, không gộp.
     *
     * Port D - Pin 6 (PD6):
     * - Default: GPIO | ADC Kênh 6 (A6) | UART RX (URX)
     * - Alternative:
     *   - Remap 2: UART TX (UTX)
     *   - Remap 3: TIM2 CH3
     */
    MCU_PIN3 = (MCU_PORT_INDEX_D << 4) | 6,

    /**
     * @brief PIN 4 — Port D - Pin 7 (PD7). Mặc định là Reset phần cứng.
     *
     * Muốn dùng làm GPIO thường phải tắt chức năng NRST trong Option Byte.
     *
     * Port D - Pin 7 (PD7):
     * - Default: GPIO | SYS NRST (Reset phần cứng) | TIM2 CH4
     *            | OPA OPP1 (Op-Amp ngõ vào không đảo kênh 1)
     * - Alternative:
     *   - Remap 1: UART CK (Clock đồng bộ)
     *   - Remap 2: TIM2 CH4 | UART CK (Clock đồng bộ)
     */
    MCU_PIN4 = (MCU_PORT_INDEX_D << 4) | 7,

    /**
     * @brief PIN 5 — Port A - Pin 1 (PA1). Chân đơn, không gộp.
     *
     * Port A - Pin 1 (PA1):
     * - Default: GPIO | ADC Kênh 1 (A1) | TIM1 CH2
     *            | OPA OPN0 (Op-Amp ngõ vào đảo kênh 0)
     * - Hệ thống (không qua remap): SYS OSCI — Ngõ vào thạch anh ngoại
     * - Alternative:
     *   - Remap 2: TIM1 CH2
     */
    MCU_PIN5 = (MCU_PORT_INDEX_A << 4) | 1,

    /**
     * @brief PIN 6 — Port A - Pin 2 (PA2). Chân đơn, không gộp.
     *
     * Port A - Pin 2 (PA2):
     * - Default: GPIO | ADC Kênh 0 (A0) | TIM1 CH2N (kênh 2 đảo)
     *            | OPA OPP0 (Op-Amp ngõ vào không đảo kênh 0)
     * - Hệ thống (không qua remap): SYS OSCO — Ngõ ra thạch anh ngoại
     * - Alternative:
     *   - Remap 1: ADC AETR2 (External Trigger 2)
     *   - Remap 2: TIM1 CH2N (kênh 2 đảo)
     */
    MCU_PIN6 = (MCU_PORT_INDEX_A << 4) | 2,

    /**
     * @brief PIN 7 — VSS (GND). Không phải GPIO, dùng Port giả lập 0xF.
     */
    MCU_PIN7 = (MCU_PORT_INDEX_POWER << 4) | 7,

    /**
     * @brief PIN 8 — Port D - Pin 0 (PD0). Chỉ tồn tại trên bản TSSOP-20.
     *
     * Port D - Pin 0 (PD0):
     * - Default: GPIO | TIM1 CH1N (kênh 1 đảo)
     *            | OPA OPN1 (Op-Amp ngõ vào đảo kênh 1)
     * - Alternative:
     *   - Remap 1: I2C SDA | UART TX (UTX)
     *   - Remap 2: TIM1 CH1N (kênh 1 đảo)
     */
    MCU_PIN8 = (MCU_PORT_INDEX_D << 4) | 0,

    /**
     * @brief PIN 9 — VDD (3.3V/5V). Không phải GPIO, dùng Port giả lập 0xF.
     */
    MCU_PIN9 = (MCU_PORT_INDEX_POWER << 4) | 9,

    /**
     * @brief PIN 10 — Port C - Pin 0 (PC0). Chân đơn, không gộp.
     *
     * Port C - Pin 0 (PC0):
     * - Default: GPIO | TIM2 CH3
     * - Alternative:
     *   - Remap 1: SPI NSS | TIM1 CH3
     *   - Remap 2: TIM2 CH3
     *   - Remap 3: UART TX (UTX)
     */
    MCU_PIN10 = (MCU_PORT_INDEX_C << 4) | 0,

    /**
     * @brief PIN 11 — Port C - Pin 1 (PC1). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 1 (PC1):
     * - Default: GPIO | I2C SDA | SPI NSS
     * - Alternative:
     *   - Remap 1: TIM1 BKIN (Break Input) | TIM2 CH4
     *   - Remap 2: TIM2 CH1 | TIM2 ETR
     *   - Remap 3: TIM1 BKIN | TIM2 CH1 | TIM2 ETR | UART RX (URX)
     */
    MCU_PIN11 = (MCU_PORT_INDEX_C << 4) | 1,

    /**
     * @brief PIN 12 — Port C - Pin 2 (PC2). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 2 (PC2):
     * - Default: GPIO | I2C SCL | TIM1 BKIN (Break Input) | UART RTS
     * - Alternative:
     *   - Remap 1: ADC AETR (External Trigger) | TIM2 CH2 | UART RTS
     *   - Remap 2: TIM1 BKIN (Break Input)
     *   - Remap 3: TIM1 ETR
     */
    MCU_PIN12 = (MCU_PORT_INDEX_C << 4) | 2,

    /**
     * @brief PIN 13 — Port C - Pin 3 (PC3). Chân đơn, không gộp.
     *
     * Port C - Pin 3 (PC3):
     * - Default: GPIO | TIM1 CH3
     * - Alternative:
     *   - Remap 1: TIM1 CH1N (kênh 1 đảo) | UART CTS
     *   - Remap 2: TIM1 CH3
     *   - Remap 3: TIM1 CH1N (kênh 1 đảo)
     */
    MCU_PIN13 = (MCU_PORT_INDEX_C << 4) | 3,

    /**
     * @brief PIN 14 — Port C - Pin 4 (PC4). Chân đơn, không gộp.
     *
     * Port C - Pin 4 (PC4):
     * - Default: GPIO | ADC Kênh 2 (A2) | TIM1 CH4 | SYS MCO (Ngõ ra Clock)
     * - Alternative:
     *   - Remap 1: TIM1 CH2N (kênh 2 đảo)
     *   - Remap 2: TIM1 CH4
     *   - Remap 3: TIM1 CH1
     */
    MCU_PIN14 = (MCU_PORT_INDEX_C << 4) | 4,

    /**
     * @brief PIN 15 — Port C - Pin 5 (PC5). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 5 (PC5):
     * - Default: GPIO | SPI SCK | TIM1 ETR
     * - Alternative:
     *   - Remap 1: SPI SCK | TIM1 ETR | TIM2 CH1 | TIM2 ETR
     *   - Remap 2: I2C SCL
     *   - Remap 3: I2C SCL | TIM1 CH3 | UART CK (Clock đồng bộ)
     */
    MCU_PIN15 = (MCU_PORT_INDEX_C << 4) | 5,

    /**
     * @brief PIN 16 — Port C - Pin 6 (PC6). Chịu mức 5V khi VDD = 3.3V.
     *
     * Port C - Pin 6 (PC6):
     * - Default: GPIO | SPI MOSI
     * - Alternative:
     *   - Remap 1: SPI MOSI | TIM1 CH1
     *   - Remap 2: I2C SDA | UART CTS
     *   - Remap 3: I2C SDA | TIM1 CH3N (kênh 3 đảo) | UART CTS
     */
    MCU_PIN16 = (MCU_PORT_INDEX_C << 4) | 6,

    /**
     * @brief PIN 17 — Port C - Pin 7 (PC7). Chân đơn, không gộp.
     *
     * Port C - Pin 7 (PC7):
     * - Default: GPIO | SPI MISO
     * - Alternative:
     *   - Remap 1: SPI MISO | TIM1 CH2
     *   - Remap 2: UART RTS
     *   - Remap 3: TIM1 CH2 | TIM2 CH2 | UART RTS
     */
    MCU_PIN17 = (MCU_PORT_INDEX_C << 4) | 7,

    /**
     * @brief PIN 18 — Port D - Pin 1 (PD1). Chân nạp/gỡ lỗi mặc định.
     *
     * Port D - Pin 1 (PD1):
     * - Default: GPIO | SWD SWIO (Nạp/Debug 1 dây) | TIM1 CH3N (kênh 3 đảo)
     *            | ADC AETR2 (External Trigger 2)
     * - Alternative:
     *   - Remap 1: I2C SCL | TIM1 CH3N (kênh 3 đảo) | UART RX (URX)
     *   - Remap 2: TIM1 CH3N (kênh 3 đảo)
     */
    MCU_PIN18 = (MCU_PORT_INDEX_D << 4) | 1,

    /**
     * @brief PIN 19 — Port D - Pin 2 (PD2). Chỉ tồn tại trên bản TSSOP-20.
     *
     * Port D - Pin 2 (PD2):
     * - Default: GPIO | ADC Kênh 3 (A3) | TIM1 CH1
     * - Alternative:
     *   - Remap 1: TIM2 CH3
     *   - Remap 2: TIM1 CH1
     *   - Remap 3: TIM1 CH2N (kênh 2 đảo)
     */
    MCU_PIN19 = (MCU_PORT_INDEX_D << 4) | 2,

    /**
     * @brief PIN 20 — Port D - Pin 3 (PD3). Chỉ tồn tại trên bản TSSOP-20.
     *
     * Port D - Pin 3 (PD3):
     * - Default: GPIO | ADC Kênh 4 (A4) | ADC AETR (External Trigger)
     *            | TIM2 CH2 | UART CTS
     * - Alternative:
     *   - Remap 1: TIM1 CH4
     *   - Remap 2: TIM2 CH2
     */
    MCU_PIN20 = (MCU_PORT_INDEX_D << 4) | 3, 
#endif
} MCU_Pin_t;

/* ==========================================================================
 * CHÂN CHỨC NĂNG ĐẶC BIỆT
 *
 * Dùng chung quy ước mã hóa với MCU_Pin_t nên truyền thẳng vào hàm HAL được.
 * Mỗi hằng số chỉ khai báo khi pad tương ứng thực sự có mặt trên gói vỏ đang
 * biên dịch — dùng nhầm sẽ báo lỗi lúc compile thay vì chạy sai âm thầm.
 * ========================================================================== */
typedef enum
{
    /* ---------------- HỆ THỐNG ---------------- */

    /** @brief [HỆ THỐNG] SWIO — Nạp/Debug 1 dây (PD1). Có trên mọi gói vỏ. */
    MCU_SWIO = (MCU_PORT_INDEX_D << 4) | 1,

    /** @brief [HỆ THỐNG] OSCI — Ngõ vào thạch anh ngoại (PA1). */
    MCU_OSCI = (MCU_PORT_INDEX_A << 4) | 1,

    /** @brief [HỆ THỐNG] OSCO — Ngõ ra thạch anh ngoại (PA2). */
    MCU_OSCO = (MCU_PORT_INDEX_A << 4) | 2,

    /** @brief [HỆ THỐNG] MCO — Ngõ ra Clock hệ thống (PC4). */
    MCU_MCO = (MCU_PORT_INDEX_C << 4) | 4,

    /* ---------------- I2C ---------------- */

    /** @brief [I2C] SDA mặc định (PC1). */
    MCU_I2C_SDA = (MCU_PORT_INDEX_C << 4) | 1,

    /** @brief [I2C] SCL mặc định (PC2). */
    MCU_I2C_SCL = (MCU_PORT_INDEX_C << 4) | 2,

    /** @brief [I2C] SCL Remap-1 (PD1). Trùng chân SWIO — cân nhắc khi dùng. */
    MCU_I2C_SCL_REMAP1 = (MCU_PORT_INDEX_D << 4) | 1,

    /* ---------------- UART ---------------- */

    /** @brief [UART] TX mặc định (PD5). */
    MCU_UART_TX = (MCU_PORT_INDEX_D << 4) | 5,

    /** @brief [UART] RX mặc định (PD6). */
    MCU_UART_RX = (MCU_PORT_INDEX_D << 4) | 6,

    /** @brief [UART] TX Remap-2 (PD6) — đảo vai trò so với mặc định. */
    MCU_UART_TX_REMAP2 = (MCU_PORT_INDEX_D << 4) | 6,

    /** @brief [UART] RX Remap-2 (PD5) — đảo vai trò so với mặc định. */
    MCU_UART_RX_REMAP2 = (MCU_PORT_INDEX_D << 4) | 5,

    /** @brief [UART] RX Remap-1 (PD1). Trùng chân SWIO. */
    MCU_UART_RX_REMAP1 = (MCU_PORT_INDEX_D << 4) | 1,

    /** @brief [UART] RX Remap-3 (PC1). */
    MCU_UART_RX_REMAP3 = (MCU_PORT_INDEX_C << 4) | 1,

    /** @brief [UART] CK — Clock đồng bộ mặc định (PD4). */
    MCU_UART_CK = (MCU_PORT_INDEX_D << 4) | 4,

    /** @brief [UART] RTS mặc định (PC2). */
    MCU_UART_RTS = (MCU_PORT_INDEX_C << 4) | 2,

    /* ---------------- SPI ---------------- */

    /** @brief [SPI] NSS mặc định (PC1). */
    MCU_SPI_NSS = (MCU_PORT_INDEX_C << 4) | 1,

    /* ---------------- ADC ---------------- */

    /** @brief [ADC] Kênh 0 — A0 (PA2). */
    MCU_ADC_CH0 = (MCU_PORT_INDEX_A << 4) | 2,

    /** @brief [ADC] Kênh 1 — A1 (PA1). */
    MCU_ADC_CH1 = (MCU_PORT_INDEX_A << 4) | 1,

    /** @brief [ADC] Kênh 2 — A2 (PC4). */
    MCU_ADC_CH2 = (MCU_PORT_INDEX_C << 4) | 4,

    /** @brief [ADC] Kênh 5 — A5 (PD5). */
    MCU_ADC_CH5 = (MCU_PORT_INDEX_D << 4) | 5,

    /** @brief [ADC] Kênh 6 — A6 (PD6). */
    MCU_ADC_CH6 = (MCU_PORT_INDEX_D << 4) | 6,

    /** @brief [ADC] Kênh 7 — A7 (PD4). */
    MCU_ADC_CH7 = (MCU_PORT_INDEX_D << 4) | 4,

    /** @brief [ADC] External Trigger 2 — AETR2 mặc định (PD1). */
    MCU_ADC_AETR2 = (MCU_PORT_INDEX_D << 4) | 1,

    /** @brief [ADC] External Trigger 2 — AETR2 Remap-1 (PA2). */
    MCU_ADC_AETR2_REMAP1 = (MCU_PORT_INDEX_A << 4) | 2,

    /* ---------------- OP-AMP ---------------- */

    /** @brief [OPA] OPN0 — Ngõ vào đảo kênh 0 (PA1). */
    MCU_OPAMP_N0 = (MCU_PORT_INDEX_A << 4) | 1,

    /** @brief [OPA] OPP0 — Ngõ vào không đảo kênh 0 (PA2). */
    MCU_OPAMP_P0 = (MCU_PORT_INDEX_A << 4) | 2,

    /** @brief [OPA] OPO — Ngõ ra Op-Amp, nhãn "OPA" trên sơ đồ chân (PD4). */
    MCU_OPAMP_OUT = (MCU_PORT_INDEX_D << 4) | 4,

#if defined(CH32V003_A4M6) || defined(CH32V003_F4P6)
    /* ====== CHỈ CÓ TRÊN SOP16 & TSSOP20 ====== */

    /** @brief [HỆ THỐNG] NRST — Reset phần cứng (PD7). */
    MCU_NRST = (MCU_PORT_INDEX_D << 4) | 7,

    /** @brief [SPI] MOSI mặc định (PC6). */
    MCU_SPI_MOSI = (MCU_PORT_INDEX_C << 4) | 6,

    /** @brief [SPI] MISO mặc định (PC7). */
    MCU_SPI_MISO = (MCU_PORT_INDEX_C << 4) | 7,

    /** @brief [SPI] NSS Remap-1 (PC0). */
    MCU_SPI_NSS_REMAP1 = (MCU_PORT_INDEX_C << 4) | 0,

    /** @brief [UART] TX Remap-3 (PC0). */
    MCU_UART_TX_REMAP3 = (MCU_PORT_INDEX_C << 4) | 0,

    /** @brief [UART] RTS Remap-2 (Trùng 3) (PC7). */
    MCU_UART_RTS_REMAP2 = (MCU_PORT_INDEX_C << 4) | 7,

    /** @brief [UART] RTS Remap-3 (Trùng 2) (PC7). */
    MCU_UART_RTS_REMAP3 = (MCU_PORT_INDEX_C << 4) | 7,

    /** @brief [UART] CK Remap-1 (Trùng 2) (PD7, dùng chung chân NRST). */
    MCU_UART_CK_REMAP1 = (MCU_PORT_INDEX_D << 4) | 7,

    /** @brief [UART] CK Remap-2 (Trùng 1) (PD7, dùng chung chân NRST). */
    MCU_UART_CK_REMAP2 = (MCU_PORT_INDEX_D << 4) | 7,

    /** @brief [I2C] SDA Remap-2 (Trùng 3) (PC6). */
    MCU_I2C_SDA_REMAP2 = (MCU_PORT_INDEX_C << 4) | 6,

    /** @brief [I2C] SDA Remap-3 (Trùng 2) (PC6). */
    MCU_I2C_SDA_REMAP3 = (MCU_PORT_INDEX_C << 4) | 6,

    /** @brief [OPA] OPP1 — Ngõ vào không đảo kênh 1 (PD7, dùng chung NRST). */
    MCU_OPAMP_P1 = (MCU_PORT_INDEX_D << 4) | 7,
#endif

#if defined(CH32V003_F4P6)
    /* ====== CHỈ CÓ TRÊN TSSOP20 ====== */

    /** @brief [SPI] SCK mặc định (PC5). */
    MCU_SPI_SCK = (MCU_PORT_INDEX_C << 4) | 5,

    /** @brief [I2C] SCL Remap-2 (Trùng 3) (PC5). */
    MCU_I2C_SCL_REMAP2 = (MCU_PORT_INDEX_C << 4) | 5,

    /** @brief [I2C] SCL Remap-3 (Trùng 2) (PC5). */
    MCU_I2C_SCL_REMAP3 = (MCU_PORT_INDEX_C << 4) | 5,

    /** @brief [I2C] SDA Remap-1 (PD0). */
    MCU_I2C_SDA_REMAP1 = (MCU_PORT_INDEX_D << 4) | 0,

    /** @brief [UART] TX Remap-1 (PD0). */
    MCU_UART_TX_REMAP1 = (MCU_PORT_INDEX_D << 4) | 0,

    /** @brief [UART] CTS mặc định (PD3). */
    MCU_UART_CTS = (MCU_PORT_INDEX_D << 4) | 3,

    /** @brief [ADC] Kênh 3 — A3 (PD2). */
    MCU_ADC_CH3 = (MCU_PORT_INDEX_D << 4) | 2,

    /** @brief [ADC] Kênh 4 — A4 (PD3). */
    MCU_ADC_CH4 = (MCU_PORT_INDEX_D << 4) | 3,

    /** @brief [ADC] External Trigger — AETR mặc định (PD3). */
    MCU_ADC_AETR = (MCU_PORT_INDEX_D << 4) | 3,

    /** @brief [ADC] External Trigger — AETR Remap-1 (PC2). */
    MCU_ADC_AETR_REMAP1 = (MCU_PORT_INDEX_C << 4) | 2,

    /** @brief [OPA] OPN1 — Ngõ vào đảo kênh 1 (PD0). */
    MCU_OPAMP_N1 = (MCU_PORT_INDEX_D << 4) | 0,

    /* --- Tiện ích phần cứng trên kit Twen32F003 --- */

    /** @brief LED tích hợp trên kit Twen32F003 (PD1 — trùng SWIO). */
    LED_BUILTIN_TWEN32F003 = (MCU_PORT_INDEX_D << 4) | 1,

    /** @brief Nút nhấn tích hợp trên kit Twen32F003 (PC0). */
    BTN_BUILTIN_TWEN32F003 = (MCU_PORT_INDEX_C << 4) | 0,
#endif
} MCU_SpecialPin_t;

#endif /* CH32V003_GPIO_PINS_H */
