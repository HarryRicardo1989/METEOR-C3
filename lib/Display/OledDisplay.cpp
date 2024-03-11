#include "OledDisplay.hpp"
#include <cstring>

// Comandos específicos para inicialização conforme ssd1306_init()
const uint8_t OLED::_initCommands[] = {
    0xAE,       // Desliga o display
    0xD5, 0x80, // Define o clock do display
    0xA8, 0x3F, // Multiplex
    0xD3, 0x00, // Offset de display
    0x40,       // Inicia a linha de display
    0x8D, 0x14, // Carga da bomba
    0x20, 0x00, // Modo de endereçamento da memória
    0xA1,       // Mapeamento de coluna
    0xC8,       // Mapeamento de COM
    0xDA, 0x12, // Configuração do pino de hardware COM
    0x81, 0xCF, // Contraste
    0xD9, 0xF1, // Pre-carga do período
    0xDB, 0x40, // Tensão de desreferência VCOM
    0xA4,       // Mostra o RAM de saída
    0xA6,       // Normal display
    0x2E,       // De-Scroll
    0xAF        // Liga o display
};

OLED::OLED(PROTOCOL::I2c *i2c, uint8_t address) : _i2c(*i2c), _address(address) {}

void OLED::init()
{
    for (auto cmd : _initCommands)
    {
        sendCommand(cmd);
    }
}
void OLED::initScreenBuffer()
{
    memset(screenBuffer, 0, sizeof(screenBuffer));
}
void OLED::displayClear()
{
    for (uint8_t page = 0; page < 8; page++)
    { // 8 páginas para um display de 64 linhas
        setPosition(0, page);
        uint8_t empty[128] = {0}; // 128 colunas
        sendData(empty, sizeof(empty));
    }
}
void OLED::writePixel(uint8_t x, uint8_t y, bool on)
{
    if (x >= WIDTH || y >= HEIGHT)
        return;

    uint8_t page = y / 8;
    uint8_t bit = y % 8;

    if (on)
    {
        screenBuffer[page][x] |= (1 << bit);
    }
    else
    {
        screenBuffer[page][x] &= ~(1 << bit);
    }
}
void OLED::updateDisplay()
{
    for (uint8_t page = 0; page < PAGES; page++)
    {
        setPosition(0, page);
        sendData(screenBuffer[page], WIDTH);
    }
}
void OLED::displayTextBuffered(const std::string &text, uint8_t x, uint8_t y)
{
    // Percorre cada caractere do texto
    for (size_t charIndex = 0; charIndex < text.length(); ++charIndex)
    {
        char c = text[charIndex];
        if (c < 32 || c > 127)
            continue; // Ignora caracteres fora do intervalo da fonte

        // Obtém a representação do caractere na fonte
        const uint8_t *charBitmap = font8x8_basic_tr[c - 0];

        // Percorre cada coluna (byte) do caractere
        for (int col = 0; col < 8; ++col)
        {
            // Calcula a posição x atual do pixel no buffer
            uint8_t xPos = x + charIndex * 8 + col;
            if (xPos >= WIDTH)
                break; // Previne overflow horizontal

            // Percorre cada bit do byte (coluna) para definir os pixels
            for (int bit = 0; bit < 8; ++bit)
            {
                bool pixelOn = charBitmap[col] & (1 << bit);
                writePixel(xPos, y + bit, pixelOn);
            }
        }
    }
}
void OLED::displayText(const std::string &text, uint8_t x, uint8_t y)
{
    // Ajusta y para ser o número da página, considerando que cada página tem 8 linhas
    uint8_t cur_page = y / 8; // Converte y em número de página, se necessário

    // Define a página e a coluna baseando-se em x e cur_page
    sendCommand(0xB0 | cur_page);          // Define a página de início
    sendCommand(0x00 | (x & 0x0F));        // Parte baixa de x
    sendCommand(0x10 | ((x >> 4) & 0x0F)); // Parte alta de x

    for (char c : text)
    {
        // Assegura que o caractere esteja no intervalo imprimível e ajusta baseado no índice da tabela ASCII
        if (c >= 32 && c <= 127)
        {
            // Subtrai 32 do caractere para alinhar com o início da tabela font8x8_basic_tr
            sendData(font8x8_basic_tr[static_cast<uint8_t>(c)], 8);
        }
    }
}

void OLED::displayPattern()
{
    for (uint8_t page = 0; page < 8; page++)
    {
        sendCommand(0xB0 | page); // Define a página
        for (uint8_t col = 0; col < 128; col++)
        {
            uint8_t pattern = (col / 16) % 2 == 0 ? 0xFF : 0x00; // Padrão de linhas
            sendData(&pattern, 1);                               // Envia o padrão como um ponteiro
        }
    }
}
void OLED::scroll(bool enable)
{
    if (enable)
    {
        // Comandos para ativar o scroll horizontal
        sendCommand(0x26); // Direção da direita para a esquerda
        sendCommand(0x00); // Dummy byte
        sendCommand(0x00); // Página inicial
        sendCommand(0x00); // Tempo de intervalo
        sendCommand(0x07); // Página final
        sendCommand(0x00); // Dummy byte
        sendCommand(0xFF); // Dummy byte
        sendCommand(0x2F); // Ativa o scroll
    }
    else
    {
        sendCommand(0x2E); // Desativa o scroll
    }
}

void OLED::setContrast(uint8_t contrast)
{
    sendCommand(0x81);     // Comando para ajuste de contraste
    sendCommand(contrast); // Valor do contraste
}

void OLED::sendCommand(uint8_t cmd)
{
    _i2c.WriteRegister(_address, 0x00, cmd);
}

void OLED::sendData(const uint8_t *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        _i2c.WriteRegister(_address, 0x40, data[i]);
    }
}
void OLED::displaySleep()
{
    sendCommand(0xAE); // Comando para colocar o display em sleep
}

void OLED::displayWakeUp()
{
    sendCommand(0xAF); // Comando para acordar o display
}

void OLED::setPosition(uint8_t column, uint8_t page)
{
    sendCommand(0xB0 | page);                   // Página: 0 a 7
    sendCommand(0x00 | (column & 0x0F));        // Parte mais baixa da coluna
    sendCommand(0x10 | ((column >> 4) & 0x0F)); // Parte mais alta da coluna
}

void OLED::drawBatteryIndicator(uint8_t level)
{
    // Define a posição no canto superior direito do display
    // Considerando que a barra de bateria tenha 16 pixels de largura e 8 de altura
    uint8_t startColumn = 128 - 16; // Começa a 16 pixels do lado direito
    uint8_t startPage = 0;          // No topo do display

    setPosition(startColumn, startPage);

    // Desenho do contorno da bateria
    // Primeira linha (topo)
    uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF};
    sendData(data, sizeof(data)); // Envie 4 bytes para fazer a parte superior da bateria

    // Linhas do meio (nível da bateria)
    for (int i = 0; i < 6; i++)
    { // 6 linhas para o corpo da bateria
        setPosition(startColumn, startPage + 1 + i);
        if (i < level)
        {                                                   // Nível da bateria (por exemplo, 0 a 5 para simplificar)
            uint8_t dataLevel[] = {0x81, 0xBD, 0xBD, 0x81}; // Barras preenchidas para o nível da bateria
            sendData(dataLevel, sizeof(dataLevel));
        }
        else
        {
            uint8_t dataEmpty[] = {0x81, 0x81, 0x81, 0x81}; // Barras vazias
            sendData(dataEmpty, sizeof(dataEmpty));
        }
    }

    // Última linha (base)
    setPosition(startColumn, startPage + 7);
    sendData(data, sizeof(data)); // Reutiliza o mesmo `data` para a base
}
