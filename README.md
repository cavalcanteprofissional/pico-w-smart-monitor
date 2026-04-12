# Monitor de Sensores com Alerta

**Sistema embarcado para BitDogLab (RP2040) que exibe os valores do joystick no display OLED e dispara alertas sonoros quando thresholds são ultrapassados.**

## Objetivo

Demonstrar o uso de periféricos da BitDogLab com C/C++, incluindo:
- Display gráfico OLED via I2C
- Leitura de joystick (ADC)
- Botões com interrupção
- Buzzer como alerta sonoro

## Hardware Necessário

- BitDogLab (RP2040) - Ja tem todos os periféricos integrados
- Cabo USB-C para programação e alimentação

## Periféricos Utilizados

| Periférico | Interface | GPIO |
|------------|-----------|-------|
| Display OLED 128x64 | I2C | GPIO2=SDA, GPIO3=SCL |
| Joystick X | ADC | GPIO26 |
| Joystick Y | ADC | GPIO27 |
| Joystick SW | GPIO | GPIO22 |
| Botão A | GPIO | GPIO5 |
| Botão B | GPIO | GPIO6 |
| Buzzer | GPIO | GPIO10 |
| LED RGB | GPIO | GPIO7 |

## Dependências

- Pico SDK v1.5.1
- Ferramenta de build (make, cmake)
- C/C++ (std C11)

## Como Compilar

```bash
# 1. Clone o repositório
git clone https://github.com/cavalcanteprofissional/pico-w-smart-monitor.git
cd pico-w-smart-monitor

# 2. Crie o diretório de build
mkdir build
cd build

# 3. Configure o projeto (certifique-se de ter o Pico SDK instalado)
# Se o SDK não estiver no PATH, defina PICO_SDK_PATH:
# export PICO_SDK_PATH=/caminho/para/pico-sdk
cmake ..

# 4. Compile
make
```

O arquivo `.uf2` será gerado em `build/monitor_sensores_alerta.uf2`

---

## Como Gravar na BitDogLab (Passo a Passo)

### Método 1: Modo BOOT (Recomendado para iniciantes)

1. **Compile o projeto** (veja seção anterior)

2. **Conecte a BitDogLab ao computador**
   - Use um cabo USB-C válido (o cabo de dados, não apenas carregador)

3. **Entre no modo de bootloader:**
   - Pressione e **segure o botão BOOT** (GPIO21 - botão branco pequeno)
   - Conecte o cabo USB enquanto **segura o botão BOOT**
   - Solte o botão BOOT após 2-3 segundos
   - O computador vai detectar um novo dispositivo de armazenamento chamado **"RPI-RP2"**

4. **Copie o firmware:**
   - Abra o Explorador de Arquivos (Windows) ou Nautilus (Linux)
   - Arraste o arquivo `monitor_sensores_alerta.uf2` para a unidade "RPI-RP2"
   - A placa vai reiniciar automaticamente e o firmware estará gravado

### Método 2: Usando picotool (Mais rápido para desenvolvimento)

```bash
# Instale o picotool (Linux/Mac/WSL):
sudo apt install picotool    # Debian/Ubuntu
brew install picotool        # macOS

# Ou compile do source:
# https://github.com/raspberrypi/picotool

# Grave o firmware:
picotool load build/monitor_sensores_alerta.uf2

# Reinicie a placa:
picotool reboot
```

### Método 3: Usando OpenOCD (Para depuração)

```bash
# Instale o OpenOCD
sudo apt install openocd

# Conecte o Debug Probe ou use o bootloader SWD

# Grave e depure:
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "program build/monitor_sensores_alerta.uf2 verify reset exit"
```

---

## Como Testar o Funcionamento

### 1. Abra o Terminal Serial

O firmwareenvia logs via UART. Precisa de um terminal serial:

| Sistema | Software Recomendado |
|---------|------------------|
| Windows | PuTTY, Tera Term, Arduino IDE |
| Linux | screen, minicom, Cutecom |
| macOS | screen, Coolterm |

**Configurações:**
- **Porta:** Determine no Gerenciador de Dispositivos (Windows) ou `/dev/tty/usb-*` (Linux/Mac)
- **Velocidade:** 115200 baud
- **Bits de dados:** 8
- **Paridade:** Nenhuma
- **Bits de parada:** 1

### 2. Conecte e Observe

1. Conecte a BitDogLab via USB
2. Abra o terminal serial com as configurações acima
3. Pressione o **botão de reset** (GPIO21) ou reconecte o USB

4. **Você deve ver estas mensagens:**
```
=== Monitor de Sensores com Alerta ===
Display OLED inicializado
Joystick inicializado
Botoes inicializados
Buzzer inicializado
Sistema pronto!
Iniciando loop principal...
JoyX: 2048
JoyY: 2048
```

### 3. Teste Cada Funcionalidade

| Funcionalidade | Como Testar | Resultado Esperado |
|-------------|------------|----------------|
| **Display OLED** | Observe ao iniciar | "Monitor de Sensores" aparece no display |
| **Joystick X** | Mova o joystick para esquerda/direita | Valores mudam (0-4095) no display e UART |
| **Joystick Y** | Mova o joystick para cima/baixo | Valores mudam (0-4095) no display e UART |
| **Joystick SW** | Pressione o joystick para baixo | "SW:PRESSIONADO!" no display |
| **Botão A** | Pressione o botão A | Beep curto + "Botao A pressionado!" no UART |
| **Botão B** | Pressione o botão B | Beep longo + "Botao B pressionado!" no UART |
| **Alerta** | Leve o joystick ao extremo (perto do 0 ou 4095) | Buzzer emite beep de alerta |

### 4. Vídeo Demonstrativo

Grave um vídeo de até 3 minutos mostrando:
1. O projeto compilando
2. O firmware sendo gravado na BitDogLab
3. Todos os periféricos funcionando
4. Mostre o display OLED com os valores do joystick
5. Demonstre os botões e alertas

Publique no YouTube (não listado) e adicione o link no README.

---

---

## Verificação e Depuração (usando PuTTY)

Após gravar o firmware, siga estes passos para verificar se tudo está funcionando:

### 1. Encontrar a Porta Serial

1. Conecte a BitDogLab ao computador via USB
2. Pressione **Windows + X** e clique em **"Gerenciador de Dispositivos"**
3. Expanda **"Portas (COM e LPT)"**
4. Anote o número COM exibido (ex: COM3, COM4, etc.)

### 2. Abrir o PuTTY

1. Baixe o PuTTY em: https://www.putty.org/ (ou use o já instalado)
2. Abra o PuTTY
3. Na tela inicial:
   - Selecione **"Serial"** (não SSH)
   - Em **"Serial line"**, digite a porta encontrada (ex: `COM4`)
   - Em **"Speed"**, digite `115200`
4. Clique em **"Open"**

### 3. Verificar a Comunicação

Uma nova janela黑色的’ll open. Se tudo estiver funcionando, você verá:

```
=== Monitor de Sensores com Alerta ===
Display OLED inicializado
Joystick inicializado
Botoes inicializados
Buzzer inicializado
Sistema pronto!
Iniciando loop principal...
JoyX: 2048
JoyY: 2048
```

Se aparecerem caracteres estranhos ou nada:
- Verifique a velocidade (deve ser 115200)
- Verifique a porta COM correta

### 4. Testar Funcionalidades

| Ação | Resultado Esperado no Terminal |
|------|----------------------------|
| Mova joystick X | `JoyX: 0` a `JoyX: 4095` |
| Mova joystick Y | `JoyY: 0` a `JoyY: 4095` |
| Pressione botão A | `Botao A pressionado!` + beep |
| Pressione botão B | `Botao B pressionado!` + beep |
| Joystick ao extremo | Alerta sonoro no buzzer |

### 5. Observar o Display OLED

Ao mesmo tempo que observa o terminal, verifique o display OLED:
- Linha 1: "Joystick:" + valor X
- Linha 2: "Y:" + valor Y
- Linha 3: Estado do botão do joystick
- Linha 4: "A:PRESSIONADO" ou "B:PRESSIONADO" quando clicado

---

## Solução de Problemas

| Problema | Solução |
|----------|--------|
| Display não exibe nada | Verifique conexões I2C (GPIO2, GPIO3) ou reinicie |
| Joystick valores fixos em 0 ou 4095 | Verifique conexões ADC ou substitua o potenciômetro |
| Botões não respondem | Verifique pull-ups internos (gpio_pull_up) |
| Sem comunicação serial | Verifique a porta e velocidade (115200) |
| Erro na compilação | Certifique-se do Pico SDK instalado corretamente |
| "No known device" ao gravar | Use outro cabo USB ou porta |

---

## Arquitetura do Projeto

```
src/
├── main.c              - Loop principal
├── display/
│   ├── ssd1306.c/h   - Driver do display OLED
│   └── font.c/h       - Fonte 5x8 para texto
├── sensors/
│   └── joystick.c/h   - Leitura de ADC e botões
└── utils/
    └── uart_log.c/h  - Logging via UART
```

---

## LICENÇA

MIT - veja o arquivo [LICENSE](LICENSE)

---

## Créditos

- Projeto desenvolvido para o programa EmbarcaTech Expansão
- Baseado na BitDogLab (RP2040) da Escola 4.0 da UNICAMP
- Usa Pico SDK da Raspberry Pi