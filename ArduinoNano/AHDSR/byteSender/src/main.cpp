#include <iostream>
#include <cmath>

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

int main(int argc, char *argv[]) {
    const int F_CPU = 16000000;
    const int ocr1aPreScaler = 256;
    int waveFormMode, waveFormFreq;
    int rxHandlerSection;
    int triggerMode;
    int atkSteps, susSteps, holdSteps, decRelSteps, triggerBpm, vcaInputFrequency, ocr1aValue;
    float triggerOscFreq;

#ifdef _WIN32
    HANDLE hSerial = CreateFile("COM2", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

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
    int serialPort = open(device, O_RDWR | O_NOCTTY);

    if (serialPort < 0) {
        cerr << "Erro ao abrir a porta serial.\n";
        return 1;
    }

    termios tty;
    memset(&tty, 0, sizeof tty);

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
    while(true) {
        cout << "Rxbyte (0 -> Enviar trigger bytes; 1 -> Enviar AHDSR btyes): ";
        cin >> rxHandlerSection;

        if (rxHandlerSection == 0) {
            cout << "Trigger Mode (0 - Auto; 1 - Manual e Desligado; 3 - Manual e Ligado): ";
            cin >> triggerMode;
            byte rxHandleSectionByte = 0;
            byte trigMode = (triggerMode);
            byte triggerBytes[2] = {rxHandleSectionByte, trigMode};

            #ifdef _WIN32
                DWORD bytesWritten;
                if (!WriteFile(hSerial, triggerBytes, sizeof(triggerBytes), &bytesWritten, NULL)) {
                    cerr << "Erro ao enviar dados." << endl;
                } else {
                    cout << "Enviado: "
                        << "RxByte=0x" << hex << (int)rxHandleSectionByte
                        << ", TrigMode=0x" << (int)triggerMode
                        << " (" << dec << bytesWritten << " bytes)" << endl;
                }
            #else
                ssize_t bytesWritten = write(serialPort, triggerBytes, sizeof(triggerBytes));
                if (bytesWritten < 0) {
                    cerr << "Erro ao enviar dados.\n";
                } else {
                    cout << "Enviado: "
                        << "RxByte=0x" << hex << (int)rxHandleSectionByte
                        << ", TrigMode=0x" << (int)triggerMode
                        << " (" << dec << bytesWritten << " bytes)" << endl;
                }
            #endif

        } else {
            cout << "Attack - (0-255): ";                       cin >> atkSteps;

            cout << "Hold - (0-255): ";                         cin >> holdSteps;

            cout << "Sustain - (0-255): ";                      cin >> susSteps;

            cout << "Decay/Release - (0-255): ";                cin >> decRelSteps;

            cout << "WaveForm Mode: (1 - Sine, 2 - triangle) "; cin >> waveFormMode;
            
            cout << "WaveForm Freq: ";                          cin >> waveFormFreq;

            cout << "Trigger BPM (60, 100, 120, 150, 180): ";   cin >> triggerBpm;    

            switch (triggerBpm) {
                case 60:
                    triggerOscFreq = 1;
                    break;
                case 100:
                    triggerOscFreq = 1.6;
                    break;
                case 120:
                    triggerOscFreq = 2;
                    break;
                case 150:
                    triggerOscFreq = 2.5;
                    break;
                case 180:
                    triggerOscFreq = 3;
                    break;
                default:
                    triggerOscFreq = 1;
                    break;
                }

            double temp;
            temp = ( (double)(F_CPU) / (2 * ocr1aPreScaler * triggerOscFreq) ) - 1;
            int ocr1aValue = static_cast<int>(round((F_CPU / (2.0 * ocr1aPreScaler * triggerOscFreq)) - 1));
            
            byte rxHandleSectionByte = 1;
            byte Atk                 = (atkSteps);
            byte Hold                = (holdSteps);
            byte Sustain             = (susSteps);
            byte DecRel              = (decRelSteps);
            byte wfMode              = (waveFormMode);
            byte wfFreq              = (waveFormFreq);
            byte wfFreqHigh          = (waveFormFreq >> 8) & 0xFF;
            byte wfFreqLow           = (waveFormFreq & 0xFF);
            byte Trigger             = (ocr1aValue);
            byte TriggerHigh         = (ocr1aValue >> 8) & 0xFF;
            byte TriggerLow          = (ocr1aValue & 0xFF);
            byte ahdsrBytes[10]      = {rxHandleSectionByte, Atk, Hold, Sustain, DecRel, wfMode, wfFreqHigh, wfFreqLow, TriggerHigh, TriggerLow};

            #ifdef _WIN32
                DWORD bytesWritten;
                if (!WriteFile(hSerial, ahdsrBytes, sizeof(ahdsrBytes), &bytesWritten, NULL)) {
                    cerr << "Erro ao enviar dados." << endl;
                } else {
                    cout << "Enviado: "
                        << "RxByte=0x" << hex << (int)rxHandleSectionByte
                        << ", ATK=0x" << (int)Atk
                        << ", HOLD=0x" << (int)Hold
                        << ", SUS=0x" << (int)Sustain
                        << ", DEC/REL=0x" << (int)DecRel
                        << ", WFMODE=0x" << (int)wfMode
                        << ", WFFREQ=0x" << (int)wfFreq
                        << ", TRIG_FREQ=0x" << (int)Trigger
                        << " (" << dec << bytesWritten << " bytes)" << endl;
                }
            #else
                ssize_t bytesWritten = write(serialPort, ahdsrBytes, sizeof(ahdsrBytes));
                if (bytesWritten < 0) {
                    cerr << "Erro ao enviar dados.\n";
                } else {
                    cout << "Enviado: "
                        << "RxByte=0x" << hex << (int)rxHandleSectionByte
                        << ", ATK=0x" << (int)Atk
                        << ", HOLD=0x" << (int)Hold
                        << ", SUS=0x" << (int)Sustain
                        << ", DEC/REL=0x" << (int)DecRel
                        << ", TRIG_FREQ=0x" << (int)Trigger
                        << " (" << dec << bytesWritten << " bytes)" << endl;
                }
            #endif
    }   }
    #ifdef _WIN32
        CloseHandle(hSerial);
    #else
        close(serialPort);
    #endif

    return 0;
}

