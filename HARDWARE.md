---
name: bitdoglab-hardware
description: >
  Referência completa do hardware da placa BitDogLab v5.3 (RP2040 / Raspberry Pi Pico W)
  para assistentes de código embarcado. Use este skill sempre que precisar saber qual
  pino GPIO corresponde a um periférico da BitDogLab, quais interfaces estão disponíveis
  (I2C, SPI, UART, ADC, PWM), como alimentar o sistema, ou como conectar sensores
  externos. Inclui mapa de pinos, lista de periféricos integrados, conectores de expansão
  e características elétricas do microcontrolador RP2040.
---

# BitDogLab v5.3 — Referência de Hardware para Code Assistants

> **Plataforma:** Raspberry Pi Pico W soldado na BitDogLab  
> **MCU:** RP2040 — Dual-core Arm Cortex-M0+ @ até 133 MHz  
> **Dimensões da placa:** 99 × 89 × 25 mm

---

## 1. Microcontrolador RP2040 — Especificações Rápidas

| Recurso | Detalhe |
|---|---|
| CPU | 2× Arm Cortex-M0+, até 133 MHz |
| SRAM | 264 kB |
| Flash | 2 MB QSPI embarcado |
| WiFi | 2.4 GHz 802.11n (CYW43439) |
| Bluetooth | BT 5.2 |
| GPIO multifuncionais | 26 pinos (3 analógicos) |
| UART | 2× |
| SPI | 2× |
| I2C | 2× |
| PWM | 16 canais |
| ADC | 3 pinos de entrada analógica |
| PIO | 8× I/O programáveis (state machines) |
| USB | 1.1 host/device |
| Tensão de entrada | 1,8 – 5,5 V DC |
| Temperatura de operação | −20 °C a +70 °C |
| Programação via USB | Drag-and-drop (mass storage) ou picotool |

---

## 2. Periféricos Integrados na Placa

### 2.1 LED RGB (SMD5050)
- Tipo: LED RGB comum (ânodo/cátodo comum — verificar esquemático)
- Uso típico: indicação de estado, feedback visual

### 2.2 Matriz de LEDs Coloridos 5×5 (WS2812 / NeoPixel)
- 25 LEDs RGB endereçáveis individualmente
- Protocolo: 1-wire (NZR), compatível com biblioteca `ws2812` do Pico SDK
- GPIO recomendado: verificar pinout da placa (PIO state machine)

### 2.3 Display OLED (SSD1306)
- Tamanho: 0,96 polegadas
- Resolução: 128 × 64 pixels
- Interface: **I2C**
- Endereço I2C padrão: `0x3C`
- Biblioteca C: `pico-ssd1306` ou equivalente
- Biblioteca MicroPython: `ssd1306.py` (inclusa no firmware BitDogLab)

### 2.4 Joystick Analógico
- Tipo: Plugin 13×13 mm, multi-direcional
- Saídas: 2 eixos analógicos (X e Y) → ADC do RP2040
- Botão central: GPIO digital

### 2.5 Botões A e B
- Tipo: Chave tátil 12×12×7,5 mm
- Interface: GPIO com pull-up/pull-down interno do RP2040
- Uso com interrupção: `gpio_set_irq_enabled_with_callback()`

### 2.6 Buzzers Estéreo (Esquerdo e Direito)
- Tipo: Magnético externamente excitado, 80 dB, 2,7 kHz, SMD 8,5×8,5 mm
- Interface: GPIO + PWM (para controle de frequência/tom)
- Uso típico: alertas sonoros, geração de tons via PWM

### 2.7 Microfone com Amplificador (MAX4466EXK)
- Saída analógica → ADC do RP2040
- Jumper J1 seleciona entre microfone e entrada externa ANA-IN (painel jacaré)
- Uso típico: detecção de som, medição de nível de ruído

### 2.8 Botão de Reset
- Tipo: SPST SMD tátil, 8 mm
- Função: reinicia o RP2040 (equivalente a desconectar e reconectar)

### 2.9 Chave Liga/Desliga (IP5306)
- 1 toque: liga
- 2 toques em < 1 segundo: desliga
- Circuito: IP5306 ESOP-8 (Power Bank SoC integrado)
  - Carregador: 2,1 A
  - Descarga: 2,4 A

---

## 3. Alimentação e Energia

| Fonte | Componente / Conector | Detalhe |
|---|---|---|
| Bateria principal | Li-Ion CR18650 3,7 V / 2200 mAh | Suporte integrado na placa |
| Gerenciamento | IP5306 ESOP-8 | Carrega e descarrega a bateria |
| Painel solar | Conector parafuso 2,54 mm (1×2P) | Entrada 6 V |
| Bateria externa | Conector parafuso 2,54 mm (1×2P) | Alternativa à bateria interna |
| USB | Micro-USB (cabo incluso no kit) | Programação + carregamento |

---

## 4. Conectores de Expansão I2C (Sensores Externos)

Dois conectores JST/Plugin 2,5 mm para sensores e atuadores I2C externos.

### I2C1 (pino 1 à esquerda)
| Pino | Sinal |
|---|---|
| 1 | GP3 — SCL I2C1 |
| 2 | GP2 — SDA I2C1 |
| 3 | 3,3 V |
| 4 | GND |

### I2C0 (pino 1 à esquerda)
| Pino | Sinal |
|---|---|
| 1 | GP1 — SCL I2C0 |
| 2 | GP0 — SDA I2C0 |
| 3 | 3,3 V |
| 4 | GND |

> **Tensão de operação dos conectores I2C:** 3,3 V — não conectar sensores 5 V diretamente.

---

## 5. Conector de Expansão de GPIOs (IDC 2×7, passo 2,54 mm)

Conector de 14 pinos (pino 1 no canto superior esquerdo):

| Pino | Sinal | Pino | Sinal |
|---|---|---|---|
| 1 | GND | 2 | VSYS (5 V) |
| 3 | 3,3 V | 4 | GP8 |
| 5 | GP28 | 6 | GP9 |
| 7 | AGND | 8 | GP4 |
| 9 | GP17 | 10 | GP20 |
| 11 | GP16 | 12 | GP19 |
| 13 | GND | 14 | GP18 |

---

## 6. Pinos de Expansão para Painel Jacaré / Parafuso

### Header Esquerdo J5 (1×5, pino 5 à esquerda → pino 1 à direita)
| Pino | Sinal |
|---|---|
| 5 | AGND |
| 4 | GP28 (ativo se jumper JP1 habilitado) |
| 3 | GND |
| 2 | 3,3 V |
| 1 | VSYS (5 V) |

### Header Direito J12 (1×5, pino 5 à esquerda → pino 1 à direita)
| Pino | Sinal |
|---|---|
| 5 | GND |
| 4 | GP0 |
| 3 | GP1 |
| 2 | GP2 |
| 1 | GP3 |

---

## 7. Jumpers de Configuração

| Jumper | Função |
|---|---|
| J1 | Seleciona entrada ADC: **microfone** (padrão) ou **ANA-IN** externo (painel jacaré) |
| JP1 | Habilita GP28 no header J5 |

---

## 8. Interfaces de Comunicação Disponíveis para Firmware

| Interface | Pinos disponíveis | Observações |
|---|---|---|
| I2C0 | GP0 (SDA), GP1 (SCL) | Conector externo I2C0 |
| I2C1 | GP2 (SDA), GP3 (SCL) | Conector externo I2C1 + Display OLED |
| UART0 | GP0/GP1 ou outros | Verificar conflito com I2C0 |
| UART1 | GP4/GP5 ou outros | Disponível no IDC |
| SPI | GP16–GP19 | Disponível no IDC |
| ADC | GP26, GP27, GP28 | GP28 via jumper JP1 |
| PWM | Qualquer GPIO | 16 canais independentes |
| PIO | Qualquer GPIO | Usado para WS2812 e protocolos customizados |
| WiFi/BT | Interno CYW43439 | Sem pinos externos — API lwIP/CYW43 |

---

## 9. Snippets de Inicialização em C (Pico SDK)

### Display OLED SSD1306 via I2C1
```c
#include "hardware/i2c.h"

#define I2C_PORT i2c1
#define SDA_PIN  2
#define SCL_PIN  3
#define OLED_ADDR 0x3C

i2c_init(I2C_PORT, 400 * 1000); // 400 kHz
gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
gpio_pull_up(SDA_PIN);
gpio_pull_up(SCL_PIN);
```

### Botão com Interrupção
```c
#include "hardware/gpio.h"

#define BUTTON_A 5  // confirmar pino no esquemático

gpio_init(BUTTON_A);
gpio_set_dir(BUTTON_A, GPIO_IN);
gpio_pull_up(BUTTON_A);

gpio_set_irq_enabled_with_callback(BUTTON_A,
    GPIO_IRQ_EDGE_FALL, true, &button_callback);

void button_callback(uint gpio, uint32_t events) {
    // Mantenha curto — use flags
}
```

### Buzzer via PWM
```c
#include "hardware/pwm.h"

#define BUZZER_PIN 21 // confirmar pino no esquemático

gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
uint slice = pwm_gpio_to_slice_num(BUZZER_PIN);
pwm_set_clkdiv(slice, 125.0f);   // 1 MHz
pwm_set_wrap(slice, 1000);        // 1 kHz
pwm_set_gpio_level(BUZZER_PIN, 500); // 50% duty
pwm_set_enabled(slice, true);
```

### Joystick (ADC)
```c
#include "hardware/adc.h"

adc_init();
adc_gpio_init(26); // eixo X
adc_gpio_init(27); // eixo Y

adc_select_input(0); // GP26
uint16_t x = adc_read();

adc_select_input(1); // GP27
uint16_t y = adc_read();
```

### Matriz WS2812 (via PIO)
```c
// Use o exemplo ws2812.pio do Pico SDK
// pio_add_program() + ws2812_program_init()
// Cada pixel = 32 bits (GRB + padding)
put_pixel(urgb_u32(r, g, b));
```

---

## 10. Firmware e Bibliotecas de Referência

| Recurso | Link |
|---|---|
| Pico SDK (oficial) | https://github.com/raspberrypi/pico-sdk |
| Firmware BitDogLab (Pico) | `BitDogLab.uf2` no repositório BitDogLab |
| Firmware BitDogLab (Pico W) | `BitDogLab_W.uf2` no repositório BitDogLab |
| Firmware MicroPython Pico | https://micropython.org/download/RPI_PICO/ |
| Firmware MicroPython Pico W | https://micropython.org/download/RPI_PICO_W/ |
| Repositório BitDogLab | https://github.com/BitDogLab/BitDogLab |
| Pinout Pico W | https://datasheets.raspberrypi.com/picow/pico-w-datasheet.pdf |

> O firmware BitDogLab já inclui as bibliotecas:
> - `ahtx0` — Sensor de temperatura/umidade AHT10 (I2C)
> - `bh1750` — Sensor de luminosidade (I2C)
> - `ssd1306` — Display OLED (I2C)

---

## 11. Checklist de Hardware ao Iniciar um Projeto

```
[ ] Identificar quais periféricos serão usados (mín. 2 para EmbarcaTech)
[ ] Confirmar os GPIOs correspondentes no esquemático da BitDogLab v5.3
[ ] Verificar conflitos de pinos (ex.: I2C0 vs UART0 no GP0/GP1)
[ ] Checar tensão dos sensores externos (3,3 V — não conectar 5 V nos GPIOs)
[ ] Configurar jumper J1 se usar entrada analógica externa (ANA-IN)
[ ] Habilitar JP1 se precisar de GP28 no header J5
[ ] Confirmar que o display OLED está no endereço 0x3C antes de iniciar I2C
[ ] Testar buzzer com PWM em frequências entre 500 Hz e 4 kHz para audibilidade
```
