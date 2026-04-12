# TODO.md - Projeto EmbarcaTech BitDogLab

## Periféricos Disponíveis na BitDogLab

| Periférico | Interface | GPIO |
|------------|-----------|------|
| Display OLED 128x64 | I2C | GPIO2=SDA, GPIO3=SCL |
| LED RGB (catodo comum) | GPIO | Pino único (WS2812B) |
| Matriz 5x5 WS2812B | GPIO | GPIO7 |
| Botão A | GPIO | GPIO5 |
| Botão B | GPIO | GPIO6 |
| Joystick (VRx, VRy, SW) | ADC | GPIO26, GPIO27, GPIO22 |
| Buzzer A | PWM | GPIO10 |
| Buzzer B | PWM | GPIO11 |
| Microfone (MAX4466) | ADC | GPIO28 |
| Botão Reset | GPIO | GPIO21 |

---

## Projeto Sugerido: "Monitor de Sensores com Alerta"

### Descrição
Sistema que exibe no display OLED os valores do joystick (X/Y) e alternância do botão, com alertas visuais (LED RGB) e sonoros (buzzer) quando thresholds são ultrapassados.

### Requisitos Obrigatórios a Cumprir
- [x] Display gráfico OLED ✓
- [x] UART (stdio) ✓
- [x] Interrupção (botão A ou B) ✓
- [x] Mínimo 2 periféricos ✓
- [x] Código em C/C++ ✓

---

## Etapas de Desenvolvimento

### Etapa 1: Setup do Ambiente (Completo)
- [x] 1.1 - Instalar Pico SDK
- [x] 1.2 - Configurar ferramenta de build (VS Code ou terminal)
- [x] 1.3 - Criar projeto base com CMakeLists.txt
- [x] 1.4 - Testar compilação "blink" básico

### Etapa 2: Display OLED (Completo)
- [x] 2.1 - Conectardisplay (I2C)
- [x] 2.2 - Biblioteca SSD1306
- [x] 2.3 - exibir "Hello World" no OLED

### Etapa 3: Entradas e Interrupções (Completo)
- [x] 3.1 - Ler joystick (ADC)
- [x] 3.2 - Configurar interrupção nos botões A/B
- [x] 3.3 - Exibir valores no OLED

### Etapa 4: Saídas e Atuadores (Completo)
- [x] 4.1 - Controlar LED RGB (WS2812)
- [x] 4.2 - Ativar buzzer com PWM
- [x] 4.3 - Criar alertas threshold

### Etapa 5: Comunicação UART (Completo)
- [x] 5.1 - Habilitar stdio UART
- [x] 5.2 - Log de eventos via USB/UART

### Etapa 6: Integração Final (Pendente)
- [ ] 6.1 - Loop principal funcional
- [ ] 6.2 - Teste completo na placa física
- [ ] 6.3 - Criar vídeo demonstrativo

### Etapa 7: Documentação (Pendente)
- [ ] 7.1 - README.md completo
- [ ] 7.2 - Relatório técnico (seções a-h)
- [ ] 7.3 - Estruturar repositório Git

---

## Arquivos Criados

```
monitor_sensores_alerta/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── src/
│   ├── main.c
│   ├── display/
│   │   ├── ssd1306.c
│   │   ├── ssd1306.h
│   │   ├── font.c
│   │   └── font.h
│   ├── sensors/
│   │   ├── joystick.c
│   │   └── joystick.h
│   └── utils/
│       ├── uart_log.c
│       └── uart_log.h
└── cmake/
    └── fetch_sdk.cmake
```

## Próximos Passos

1. Compilar o projeto com o Pico SDK instalado
2. Testar na BitDogLab física
3. Criar relatório técnico completo
4. Gravar vídeo demonstrativo
5. Entregar até 12/04/2026

---

## Prazo: 12/04/2026