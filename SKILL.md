---
name: embarcatech-projeto-final
description: >
  Guia completo para construir o Projeto Final do programa EmbarcaTech Expansão
  usando a placa BitDogLab (RP2040) com C/C++. Use este skill sempre que o usuário
  mencionar EmbarcaTech, BitDogLab, RP2040, projeto final embarcado, ou pedir
  ajuda para criar firmware, relatório técnico, README ou estrutura de repositório
  para um projeto de sistemas embarcados com IoT. Inclui todos os requisitos
  obrigatórios, entregáveis e critérios de avaliação do programa.
---

# EmbarcaTech — Projeto Final (Expansão)

Este skill orienta a construção completa do projeto final do programa EmbarcaTech,
cobrindo firmware, estrutura de repositório, relatório técnico e boas práticas.
O prazo de entrega é **12/04/2026**.

---

## 1. Visão Geral dos Entregáveis e Pontuação

| Entregável | Peso |
|---|---|
| Código-fonte em repositório público | 2,0 pt |
| Relatório técnico (seções a–h) | 4,0 pt |
| Vídeo demonstrativo (máx. 3 min) | 2,0 pt |
| Hardware físico na BitDogLab | 2,0 pt |
| *(alternativa)* Somente simulação Wokwi | 1,0 pt |

> **Atenção:** projetos entregues apenas com simulação Wokwi recebem nota menor.
> Priorize sempre a execução física na placa BitDogLab.

---

## 2. Requisitos Obrigatórios do Firmware

Antes de escrever qualquer linha de código, confirme que o projeto atende a **todos** os itens abaixo:

### 2.1 Hardware / Plataforma
- [ ] Placa **BitDogLab** com microcontrolador **RP2040**
- [ ] Mínimo de **dois periféricos** do kit didático (ex.: botões, LED RGB, buzzer, joystick, acelerômetro MPU6050, display OLED SSD1306)
- [ ] **Display gráfico** (obrigatório)
- [ ] **Interface UART** (obrigatório)
- [ ] **Interrupção** (obrigatório — ao menos uma IRQ configurada)
- [ ] *(Bônus)* **DMA** — Direct Memory Access

### 2.2 Software / Firmware
- [ ] Linguagem obrigatória: **C/C++** (SDK do Pico / RP2040)
- [ ] Outras linguagens aceitas apenas em camadas de alto nível (dashboard, servidor MQTT, scripts Python de integração)

### 2.3 Comunicação (Opcional, mas recomendado para nota máxima)
- [ ] **WiFi** e/ou **Bluetooth** (módulo CYW43439 presente na BitDogLab)
- [ ] Protocolos IoT: **MQTT**, CoAP, UDP, TCP/IP ou HTTP

---

## 3. Estrutura Recomendada do Repositório

```
meu-projeto-embarcatech/
├── CMakeLists.txt
├── README.md                  # Obrigatório — ver seção 4
├── LICENSE                    # ex.: MIT
├── .gitignore
├── src/
│   ├── main.c
│   ├── display/
│   │   ├── ssd1306.c
│   │   └── ssd1306.h
│   ├── sensors/
│   │   ├── sensor_xyz.c
│   │   └── sensor_xyz.h
│   ├── communication/
│   │   ├── mqtt_client.c
│   │   └── mqtt_client.h
│   └── utils/
│       ├── uart_log.c
│       └── uart_log.h
├── lib/                       # Bibliotecas externas / submódulos
├── docs/
│   ├── relatorio_tecnico.md   # ou .pdf
│   └── fluxograma.png
├── simulation/
│   └── diagram.json           # Wokwi (complementar, não substituto)
└── media/
    └── demo_video_link.txt    # Link do vídeo demonstrativo
```

### Boas práticas de controle de versão
- Faça commits **atômicos** e com mensagens claras (ex.: `feat: adiciona leitura do sensor DHT22`)
- Use **branches** por funcionalidade (`feature/display-oled`, `feature/mqtt`)
- Marque a entrega final com uma **tag** de release (`v1.0.0`)

---

## 4. README.md — Estrutura Mínima Exigida

O README será avaliado. Inclua obrigatoriamente:

```markdown
# Nome do Projeto

Breve descrição do projeto e problema resolvido.

## Objetivo
...

## Hardware Necessário
- BitDogLab (RP2040)
- [Outros componentes]

## Periféricos Utilizados
- Display OLED SSD1306 (I2C)
- [...]

## Dependências
- Pico SDK v1.x
- [Outras bibliotecas]

## Como Compilar e Executar
```bash
mkdir build && cd build
cmake ..
make
# Flash via UF2 ou picotool
```

## Diagrama de Conexões
[Imagem ou descrição das conexões]

## Licença
MIT — veja [LICENSE](LICENSE)

## Créditos e Ferramentas de IA Utilizadas
...
```

---

## 5. Arquitetura de Firmware — Padrão Recomendado

Organize o firmware em módulos coesos. Exemplo de fluxo principal:

```c
int main() {
    // 1. Inicialização do sistema
    stdio_init_all();          // UART habilitada
    init_display();            // Display gráfico
    init_sensors();            // Sensores / atuadores
    init_interrupts();         // IRQs obrigatórias
    init_wifi_mqtt();          // Comunicação IoT (se aplicável)

    // 2. Loop principal
    while (true) {
        read_sensors();        // Aquisição de dados
        process_data();        // Lógica de controle
        update_display();      // Saída visual
        send_data_iot();       // Publicação MQTT/HTTP
        sleep_ms(LOOP_DELAY);
    }
}
```

### Módulos essenciais a implementar

| Módulo | Responsabilidade |
|---|---|
| `display/` | Renderização no OLED via I2C (SSD1306 ou similar) |
| `sensors/` | Leitura de ADC, I2C, SPI ou GPIO |
| `communication/` | WiFi, MQTT, HTTP ou UART serial |
| `utils/uart_log` | Log via UART para depuração |
| `interrupts` | Handlers de IRQ (botões, timers, etc.) |

### Sobre interrupções (obrigatório)
```c
// Exemplo: interrupção por botão
gpio_set_irq_enabled_with_callback(BUTTON_PIN,
    GPIO_IRQ_EDGE_FALL, true, &button_isr);

void button_isr(uint gpio, uint32_t events) {
    // Handler — mantenha rápido, use flags
    button_pressed = true;
}
```

### Sobre DMA (bônus)
Use DMA para transferências sem bloqueio da CPU, por exemplo ao alimentar o display ou ler ADC em burst.

---

## 6. Relatório Técnico — Seções Obrigatórias

O relatório vale **4 pontos**. Escreva cada seção com rigor técnico.

### a. Apresentação
- Contexto do problema e motivação
- Por que este projeto é relevante?

### b. Objetivos
- **Geral:** o que o sistema realiza globalmente
- **Específicos:** metas mensuráveis (ex.: "medir temperatura a cada 5 s e exibir no display")

### c. Requisitos Funcionais
Liste no formato:

| RF | Descrição | Entrada | Saída |
|---|---|---|---|
| RF01 | Leitura de temperatura | Sensor NTC/DHT | Valor em °C no display |
| RF02 | Alerta sonoro | Temp > limiar | Buzzer ativo |
| ... | ... | ... | ... |

### d. Arquitetura de Hardware
- Diagrama de blocos ou esquemático
- Tabela de componentes: nome, função, interface (I2C/SPI/GPIO/ADC)

### e. Arquitetura do Firmware
- Diagrama de módulos
- Descrição de cada módulo e suas responsabilidades
- Como os módulos se comunicam (filas, flags, callbacks)

### f. Fluxograma
Inclua um fluxograma do loop principal cobrindo:
`Inicialização → Leitura de Sensores → Processamento → Atualização Display → Comunicação IoT → (repetir)`

### g. Indicação do Uso de IA
Descreva **honestamente** como ferramentas de IA (ex.: Claude, ChatGPT, Copilot) foram usadas:
- Geração ou revisão de código
- Redação de trechos do relatório
- Criação de fluxogramas ou esquemas
- Depuração assistida

### h. Conclusão
- Resultados alcançados vs. objetivos propostos
- Dificuldades encontradas e como foram superadas
- Melhorias futuras

---

## 7. Vídeo Demonstrativo (máx. 3 minutos)

Roteiro sugerido:
1. **(0–30s)** Apresentação: nome, projeto e problema resolvido
2. **(30s–2min)** Demonstração ao vivo na BitDogLab: mostre todos os periféricos funcionando
3. **(2–3min)** Destaque para funcionalidade IoT (se implementada) e conclusão

Dicas:
- Grave em ambiente bem iluminado
- Mostre o display funcionando claramente
- Mencione brevemente o código se relevante
- Publique no YouTube (não listado) ou Google Drive e inclua o link no README

---

## 8. Checklist Final Antes de Entregar

```
CÓDIGO
[ ] Repositório público acessível
[ ] README.md completo
[ ] Código compila sem erros
[ ] Ao menos 2 periféricos BitDogLab integrados
[ ] Display gráfico funcional
[ ] UART configurada e em uso
[ ] Ao menos 1 interrupção configurada
[ ] Commits organizados com mensagens claras
[ ] LICENSE presente

RELATÓRIO
[ ] Seções a até h completas
[ ] Fluxograma incluído
[ ] Uso de IA declarado

VÍDEO
[ ] Duração ≤ 3 minutos
[ ] Demonstração física na BitDogLab
[ ] Link acessível no README

HARDWARE
[ ] Testado e validado fisicamente na placa
```

---

## 9. Referências Úteis

- [Pico SDK — Documentação Oficial](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [BitDogLab — Repositório de exemplos](https://github.com/BitDogLab)
- [Wokwi Simulator para RP2040](https://wokwi.com)
- Biblioteca SSD1306: `pico-ssd1306` (disponível no GitHub)
- Biblioteca MQTT: `pico-mqtt` ou lwIP integrado ao Pico W SDK
