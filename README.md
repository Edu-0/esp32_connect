# MAC Add

Projeto para ESP32 que identifica a placa pelo endereço MAC e usa uma lista de credenciais Wi‑Fi para conectar automaticamente à rede `UNIVALI IoT`.

## Visão geral

O firmware:

- lê o endereço MAC da placa com `WiFi.macAddress()`;
- compara esse valor com a tabela de credenciais em [src/wifi_credentials.h](src/wifi_credentials.h);
- encontra a senha correspondente ao MAC cadastrado;
- tenta conectar à rede Wi‑Fi configurada;
- escaneia redes disponíveis e exibe informações de sinal e segurança;
- reconecta automaticamente quando a conexão cai.

## Estrutura do projeto

- [platformio.ini](platformio.ini): configuração do projeto PlatformIO para o ESP32;
- [src/main.cpp](src/main.cpp): lógica principal de conexão e monitoramento;
- [src/wifi_credentials.h](src/wifi_credentials.h): tabela de MACs e senhas;
- [test/README](test/README): documentação de testes do projeto.

## Requisitos

- PlatformIO
- ESP32 Dev Board (`esp32dev`)
- Cabo USB para upload
- Python 3 e pip/venv, conforme necessário para o PlatformIO

## Configuração

1. Instale o PlatformIO seguindo a documentação oficial do projeto ou usando `pipx`:

   ```bash
   pipx install platformio
   pipx ensurepath
   ```

2. Abra o terminal em seguida e verifique se o comando funciona:

   ```bash
   pio --version
   ```

3. Certifique-se de que o firmware usa a placa correta no [platformio.ini](platformio.ini):

   ```ini
   [env:esp32dev]
   platform = espressif32
   board = esp32dev
   framework = arduino
   ```

## Compilar e enviar para o ESP32

No diretório do projeto, execute:

```bash
pio run
```

Para compilar e fazer upload:

```bash
pio run -t upload
```

Para abrir o monitor serial:

```bash
pio device monitor
```

Ou, se estiver usando o VS Code com a extensão PlatformIO, pode usar a task configurada no workspace para build e upload serial.

## Funcionamento

No `setup()`, o programa:

- inicia a serial;
- ativa o modo estação do Wi‑Fi;
- exibe o MAC da placa;
- lista redes disponíveis;
- tenta conectar usando o MAC cadastrado.

No `loop()`, ele verifica se a conexão caiu e tenta reconectar automaticamente a cada 5 segundos.