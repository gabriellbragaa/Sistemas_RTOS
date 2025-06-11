# Sistemas_RTOS

# Gerenciamento de Recursos com FreeRTOS no Raspberry Pi Pico - Passo a Passo no Final para o Ambiente de Compilação.

Este repositório contém uma série de atividades realizadas na placa **Raspberry Pi Pico**, com foco em **conceitos de sistemas operacionais embarcados** utilizando o **sistema operacional em tempo real (RTOS) FreeRTOS**.

## 🔧 Estrutura da Placa Utilizada

- **Placa**: Raspberry Pi Pico (RP2040)
- **Processador**: Dual-core ARM Cortex-M0+
- **Periféricos utilizados**:
  - GPIOs para LEDs e botões
  - ADC (conectado a um potenciômetro)
  - UART para depuração (via USB)
  - Timer e interrupções

---

## 📋 Atividades Desenvolvidas

### ✅ 1. Gerenciamento de Tasks

- Criação de múltiplas tasks concorrentes com prioridades distintas.
- Demonstração de preempção e escalonamento cooperativo.
- Controle de tempo com `vTaskDelay()` e `vTaskDelayUntil()`.

### ✅ 2. Uso de Semáforos

- **Semáforos binários** para sincronização entre interrupções e tasks.
- **Semáforos de mutex** para proteger recursos compartilhados (ex: UART).
- Exemplo de uso: Acionamento de LED apenas após liberação de semáforo gerado por interrupção de botão.

### ✅ 3. Leitura de ADC com Potenciômetro

- Configuração do ADC interno do Raspberry Pi Pico.
- Leitura periódica do valor de um **potenciômetro** conectado a um canal ADC.
- Comunicação do valor via **fila** para outra task responsável por acionar LEDs com base na tensão lida.

### ✅ 4. Tratamento de Interrupções com Tasks e Semáforos

- Criação de **ISRs (Interrupt Service Routines)** para GPIOs (ex: botão).
- Sinalização de tasks a partir da interrupção via `xSemaphoreGiveFromISR()`.
- Garantia de tempo determinístico e separação entre ISR e lógica de controle.

### ✅ 5. Criação e Gerenciamento de Filas

- Implementação de comunicação inter-task com **queues (filas)**.
- Troca de dados como leituras analógicas e comandos de controle.
- Demonstração de filas com diferentes tamanhos e estruturas de dados.

---

### ✅ 6. Build e Compilação

- Dentro do ambiente de desenvolvimento, crie a pasta build --> Ex: mkdir build
- Build trabalha como um ambiente de compilação, dentro dela voçê adiciona o comando " cmake .. ", que prepara o ambiente.
- Após isso, faça o make.
- Copie e cole a imagem gerada para a placa.


### ✅ 7. Para Vizualizar a Impressão

- sudo minicom -s
- Porta serial (ex: /dev/ttyUSB0, /dev/ttyAMA0, etc.) --> Substitua por /dev/ttyACM0  .
- Ou faça diretamente via terminal com o comando: sudo minicom -D /dev/ttyACM0 -b 115200  .
