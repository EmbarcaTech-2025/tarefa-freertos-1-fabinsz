# Tarefa: Roteiro de FreeRTOS #1 - EmbarcaTech 2025

Autor: **Fábio Gabriel da Silva Barbosa**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, junho de 2025

---

##  Descrição do Projeto

Este projeto implementa um sistema multitarefa embarcado usando FreeRTOS na plataforma BitDogLab. O sistema controla três periféricos de forma concorrente:

- LED RGB que alterna ciclicamente entre as cores vermelho, verde e azul
- Buzzer que emite bipes periodicamente
- Dois botões para controle:
  - Botão A: suspende/retoma a tarefa do LED
  - Botão B: suspende/retoma a tarefa do buzzer

##  Componentes Utilizados

- BitDogLab (Raspberry Pi Pico)
- LED RGB (pinos 11, 12, 13)
- Buzzer (pino 10)
- Botões (pinos 5, 6)

##  Tasks do FreeRTOS

1. **LED RGB Task (Prioridade 1)**
   - Controla o ciclo de cores do LED RGB
   - Tempo de alternância: 1 segundo por cor

2. **Buzzer Task (Prioridade 1)**
   - Controla o buzzer
   - Bipe a cada 2 segundos (100ms ON, 1900ms OFF)

3. **Button Control Task (Prioridade 2)**
   - Monitora os botões
   - Implementa debouncing de 200ms
   - Controla suspensão/retomada das outras tasks

##  Como Executar

1. Clone o repositório
2. Configure o ambiente de desenvolvimento:
   ```bash
   cd tarefa-freertos-1
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Carregue o programa na BitDogLab

##  Funcionalidades

- LED RGB alterna automaticamente entre as cores
- Buzzer emite bipes periodicamente
- Botão A controla a execução da task do LED
- Botão B controla a execução da task do buzzer
- Debouncing implementado nos botões
- Prioridades diferentes para cada task

##  Referências

- [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [Raspberry Pi Pico Documentation](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html)

---

## 📜 Licença
GNU GPL-3.0.
