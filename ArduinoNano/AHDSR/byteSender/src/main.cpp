#include <iostream>
#include <cmath>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
    typedef unsigned char byte;
#else
    #include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>
    #include <cstring>
    #include <cstdint>
    typedef uint8_t byte;
#endif

using namespace std;

constexpr int F_CPU = 16000000;
constexpr int ocr1aPreScaler = 256;
constexpr byte RX_SECTION_TRIGGER = 0;
constexpr byte RX_SECTION_AHDSR = 1;

#ifdef _WIN32
HANDLE hSerial;
bool sendBytes(const byte* buffer, size_t size) {
    DWORD bytesWritten;
    return WriteFile(hSerial, buffer, size, &bytesWritten, NULL);
}
#else
int serialPort;
bool sendBytes(const byte* buffer, size_t size) {
    return write(serialPort, buffer, size) >= 0;
}
#endif

int getByteInput(const string& label) {
    int val;
    while (true) {
        cout << label;
        cin >> val;
        if (cin.fail() || val < 0 || val > 255) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Valor inválido. Digite um número entre 0 e 255.\n";
        } else {
            break;
        }
    }
    return val;
}

int main() {
#ifdef _WIN32
    hSerial = CreateFile("COM2", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Erro ao abrir a porta COM\n";
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Erro ao obter o estado da porta\n";
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Erro ao configurar a porta\n";
        return 1;
    }
#else
    const char* device = "/dev/ttyUSB0";
    serialPort = open(device, O_RDWR | O_NOCTTY);
    if (serialPort < 0) {
        cerr << "Erro ao abrir a porta serial.\n";
        return 1;
    }

    termios tty = {};
    if (tcgetattr(serialPort, &tty) != 0) {
        cerr << "Erro ao obter atributos da porta.\n";
        close(serialPort);
        return 1;
    }

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 10;

    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        cerr << "Erro ao configurar a porta serial.\n";
        close(serialPort);
        return 1;
    }
#endif

    while (true) {
        int section;
        cout << "\nRxByte (0 -> Trigger; 1 -> AHDSR; -1 para sair): ";
        cin >> section;

        if (section == -1) break;
        if (section != 0 && section != 1) {
            cerr << "Opção inválida.\n";
            continue;
        }

        if (section == RX_SECTION_TRIGGER) {
            int triggerMode;
            cout << "Trigger Mode (0 - Auto; 1 - Manual OFF; 3 - Manual ON): ";
            cin >> triggerMode;
            if (triggerMode != 0 && triggerMode != 1 && triggerMode != 3) {
                cerr << "Trigger mode inválido.\n";
                continue;
            }

            byte triggerBytes[2] = {RX_SECTION_TRIGGER, static_cast<byte>(triggerMode)};
            if (!sendBytes(triggerBytes, sizeof(triggerBytes))) {
                cerr << "Erro ao enviar dados.\n";
            } else {
                cout << "Trigger enviado com sucesso.\n";
            }

        } else {
            int atkSteps     = getByteInput("Attack (0-255): ");
            int holdSteps    = getByteInput("Hold (0-255): ");
            int susSteps     = getByteInput("Sustain (0-255): ");
            int decRelSteps  = getByteInput("Decay/Release (0-255): ");
            int triggerBpm;

            cout << "Trigger BPM (60, 100, 120, 150, 180): ";
            cin >> triggerBpm;

            float triggerOscFreq;
            switch (triggerBpm) {
                case 60:  triggerOscFreq = 1.0; break;
                case 100: triggerOscFreq = 1.6; break;
                case 120: triggerOscFreq = 2.0; break;
                case 150: triggerOscFreq = 2.5; break;
                case 180: triggerOscFreq = 3.0; break;
                default:
                    cerr << "BPM inválido. Usando 1Hz.\n";
                    triggerOscFreq = 1.0;
                    break;
            }

            uint16_t ocr1aValue = static_cast<uint16_t>(
                round((F_CPU / (2.0 * ocr1aPreScaler * triggerOscFreq)) - 1)
            );

            byte ahdsrBytes[7] = {
                RX_SECTION_AHDSR,
                static_cast<byte>(atkSteps),
                static_cast<byte>(holdSteps),
                static_cast<byte>(susSteps),
                static_cast<byte>(decRelSteps),
                static_cast<byte>((ocr1aValue >> 8) & 0xFF), // High
                static_cast<byte>(ocr1aValue & 0xFF)         // Low
            };

            if (!sendBytes(ahdsrBytes, sizeof(ahdsrBytes))) {
                cerr << "Erro ao enviar AHDSR.\n";
            } else {
                cout << "AHDSR enviado com sucesso.\n";
            }
        }
    }

#ifdef _WIN32
    CloseHandle(hSerial);
#else
    close(serialPort);
#endif

    return 0;
}

