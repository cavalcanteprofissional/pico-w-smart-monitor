# TODO.md - Projeto EmbarcaTech BitDogLab

## Projeto: "Monitor de Sensores com Alerta"

### Repositório
https://github.com/cavalcanteprofissional/pico-w-smart-monitor

---

## Resumo do Progresso

| Status | Componente |
|--------|------------|
| ✅ | Joystick (lendo X/Y via ADC) |
| ✅ | Botões A/B com interrupção |
| ✅ | Buzzer com alertas |
| ✅ | Comunicação stdio USB |
| ❌ | **Display OLED** (PENDENTE - problema não resolvido) |

---

## Histórico de Versões

| Versão | Data | Descrição |
|--------|------|----------|
| v1.0 | - | Projeto inicial |
| v1.1 | - | Debug com stdio USB |
| v1.2 | - | Correção endereço 0x3C |
| v1.3 | - | Correção conforme HARDWARE.md |
| v1.4 | - | Biblioteca pico-ssd1306 |
| v1.5 | - | Endereço 0x3D + 100kHz |

---

## Problema Atual: Display OLED

### Sintoma
- Display funciona em outras aplicações
- Código não funciona após múltiplas tentativas

### Mensagem de Erro
```
[ssd1306_show] addr not acknowledged!
```

### Tentativas Realizadas

| # | Tentativa | Resultado |
|---|-----------|----------|
| 1 | Endereço 0x3C (conforme HARDWARE.md) | ❌ Erro |
| 2 | Endereço 0x3D | ❌ Erro |
| 3 | Velocidade 100kHz | ❌ Erro |
| 4 | Biblioteca pico-ssd1306 (198 ⭐) | ❌ Erro |

### Possíveis Causas
1. I2C1 pode não estar configurado corretamente para BitDogLab
2. Sequência de inicialização diferente
3. Conexão física ou pino diferente

---

## Próximos Passos (para quando puder continuar)

### 1. Obter código de referência
- Pedir ao usuário o código das "outras aplicações" que funcionam
- Analisar diferenças com a implementação atual

### 2. Usar código oficial Raspberry Pi
- Implementar driver oficial dos pico-examples
- URL: https://github.com/raspberrypi/pico-examples/blob/master/i2c/ssd1306_i2c/ssd1306_i2c.c

### 3. Criar scanner I2C
- Escanear todos os endereços I2C para detectar o endereço correto

### 4. Verificar pinagem HARDWARE.md
- I2C1 usa GPIO2 (SDA) e GPIO3 (SCL)
- Confirmar que a BitDogLab usa esses pinos

---

## Arquivos do Projeto

```
pico-w-smart-monitor/
├── CMakeLists.txt
├── README.md
├── LICENSE
├── HARDWARE.md
├── build.bat
├── build/
│   └── monitor_sensores_alerta.uf2  (última versão)
├── src/
│   ├── main.c
│   ├── display/
│   │   ├── ssd1306.c  (biblioteca pico-ssd1306)
│   │   ├── ssd1306.h
│   │   └── font.h
│   └── sensors/
│       └── joystick.c/h
└── cmake/
```

---

## Como Testar (quando retornar)

1. Compilar: `build.bat` ou comandos CMake
2. Gravar: Copiar .uf2 para BitDogLab em modo BOOT
3. Terminal: Abrir PuTTY na porta COM correta (115200 baud)

---

## Prazo: 12/04/2026