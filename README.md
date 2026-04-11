# Monitor de Sensores com Alerta

Sistema embarcado para a BitDogLab (RP2040) que exibe os valores do joystick no display OLED e dispara alertas visuais/sonoros quando thresholds são ultrapassados.

## Objetivo

Demonstrar o uso de periféricos da BitDogLab com C/C++, incluindo:
- Display gráfico OLED via I2C
- Leitura de joystick (ADC)
- Botões com interrupção
- Buzzer e LED RGB como alertas

## Hardware Necessário

- BitDogLab (RP2040)
- Display OLED 128x64 (I2C)
- Joystick analógico
- Botões A e B
- Buzzer
- LED RGB WS2812B

## Periféricos Utilizados

| Periférico | Interface | GPIO |
|------------|----------|------|
| Display OLED | I2C | GPIO2=SDA, GPIO3=SCL |
| Joystick X | ADC | GPIO26 |
| Joystick Y | ADC | GPIO27 |
| Joystick SW | GPIO | GPIO22 |
| Botão A | GPIO | GPIO5 |
| Botão B | GPIO | GPIO6 |
| Buzzer | GPIO (PWM) | GPIO10 |
| LED RGB | GPIO | GPIO7 |

## Dependências

- Pico SDK v1.5.1
- C/C++ (std C11)

## Como Compilar e Executar

```bash
# Criar diretório de build
mkdir build
cd build

# Configurar com CMake
cmake ..

# Compilar
make

# O arquivo .uf2 será gerado em build/
# Copie para a placa Pico em modo BOOT
```

## Diagrama de Conexões

O projeto usa as conexões nativas da BitDogLab:
- GPIO2 (SDA) → Display OLED
- GPIO3 (SCL) → Display OLED
- GPIO26 (ADC0) → Joystick VRx
- GPIO27 (ADC1) → Joystick VRy
- GPIO22 → Joystick SW (botão)
- GPIO5 → Botão A
- GPIO6 → Botão B
- GPIO10 → Buzzer

## Funcionamento

1. O sistema lê a posição X/Y do joystick a cada 100ms
2. Os valores são exibidos no display OLED
3. Quando o joystick ating os extremos (fora do range 200-4000), o buzzer emite um alerta sonoro
4. Os botões A e B têm interrupções configuradas e emitem sons distintos

## Licença

MIT