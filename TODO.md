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

## Projeto: "Monitor de Sensores com Alerta" (v1.1 Debug)

### Descrição
Sistema que exibe no display OLED os valores do joystick (X/Y) e alternância do botão, com alertas visuais (LED RGB) e sonoros (buzzer) quando thresholds são ultrapassados.

### Versão 1.1 - Correções Aplicadas
- [x] debug printf em cada etapa de inicialização
- [x] stdio USB ao invés de UART (mais confiável)
- [x] Display simplificado
- [x] .uf2 gerado com sucesso

---

## Etapas de Desenvolvimento

### Etapa 1: Setup do Ambiente ✅ COMPLETO
- [x] 1.1 - Instalar Pico SDK v1.5.1
- [x] 1.2 - Configurar ferramenta de build
- [x] 1.3 - Criar projeto base com CMakeLists.txt
- [x] 1.4 - Compilar firmware com sucesso

### Etapa 2: Display OLED ✅ COMPLETO (com bugs corrigidos)
- [x] 2.1 - Conectar display (I2C)
- [x] 2.2 - Biblioteca SSD1306
- [x] 2.3 - Exibir "Hello World" no OLED
- [x] 2.4 - Correção: removido include PIO desnecessário

### Etapa 3: Entradas e Interrupções ✅ COMPLETO
- [x] 3.1 - Ler joystick (ADC)
- [x] 3.2 - Configurar interrupção nos botões A/B
- [x] 3.3 - Exibir valores no OLED

### Etapa 4: Saídas e Atuadores ✅ COMPLETO
- [x] 4.1 - Controlar LED RGB (WS2812)
- [x] 4.2 - Ativar buzzer com PWM
- [x] 4.3 - Criar alertas threshold

### Etapa 5: Comunicação stdio USB ✅ COMPLETO
- [x] 5.1 - Habilitar stdio USB (CDC)
- [x] 5.2 - Log de eventos via USB

### Etapa 6: Teste na Placa Física (PENDENTE)
- [ ] 6.1 - Gravar novo firmware .uf2
- [ ] 6.2 - Testar comunicação USB
- [ ] 6.3 - Verificar display OLED
- [ ] 6.4 - Criar vídeo demonstrativo

### Etapa 7: Documentação (Pendente)
- [ ] 7.1 - README.md completo
- [ ] 7.2 - Relatório técnico (seções a-h)
- [ ] 7.3 - GitHub atualizado

---

## Problemas Encontrados e Soluções

| Problema | Causa | Solução |
|----------|------|---------|
| Firmware não executa | stdio UART não funciona | Mudar para stdio USB |
| Display não Liga | I2C travando | Adicionar debug prints |
| PuTTY não mostra nada | Porta COM ou velocidade | stdio USB usa outra porta |

---

## Arquivos do Projeto

```
monitor_sensores_alerta/
├── CMakeLists.txt          (atualizado para stdio USB)
├── README.md             (com debug e PuTTY)
├── LICENSE
├── build/
│   └── monitor_sensores_alerta.uf2  (ULTIMO FIRMWARE)
├── src/
│   ├── main.c           (v1.1 - com debug)
│   ├── display/
│   │   ├── ssd1306.c/h
│   │   └── font.c/h
│   └── sensors/
│       └── joystick.c/h
└── build.bat            (script de build)
```

---

## Como Testar o Novo Firmware

1. Copiar `build/monitor_sensores_alerta.uf2` para BitDogLab
2. Conectar via USB (NOVA porta COM pode aparecer!)
3. Abrir terminal na nova porta (115200 baud)
4. Ver mensagens de debug

---

## Próximos Passos

1. Gravar o novo firmware (v1.1)
2. Testar comunicação USB (pode aparecer nova porta COM)
3. Verificar display OLED
4. Testar joystick e botões
5. Gravar vídeo demonstrativo
6. Criar relatório técnico

---

## Prazo: 12/04/2026