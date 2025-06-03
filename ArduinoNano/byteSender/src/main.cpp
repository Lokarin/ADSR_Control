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
    if (argc != 7) {
       cerr << "OTARIO, É ASSIM: " << argv[0] << " atkSteps holdSteps susSteps decRelSteps triggerBPM vcaInputFreq\n";
       return 1;
    }

    int atkSteps           = atoi(argv[1]);
    int holdSteps          = atoi(argv[2]);
    int susSteps           = atoi(argv[3]);
    int decRelSteps        = atoi(argv[4]);
    int triggerBpm         = atoi(argv[5]);
    int vcaInputFrequency  = atoi(argv[6]);

    const int F_CPU = 16000000;
    const int ocr1aPreScaler = 256;
    const int ocr2aPreScaler = 256;

#ifdef _WIN32
    HANDLE hSerial = CreateFile("COM6", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

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
        float triggerOscFreq;
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
        int ocr2aValue = static_cast<int>(round((F_CPU / (2.0 * ocr2aPreScaler * vcaInputFrequency)) - 1));

        byte Atk         = (atkSteps);
        byte Hold        = (holdSteps);
        byte Sustain     = (susSteps);
        byte DecRel      = (decRelSteps);
        byte Trigger     = (ocr1aValue);
        byte TriggerHigh = (ocr1aValue >> 8) & 0xFF;
        byte TriggerLow  = (ocr1aValue & 0xFF);        
        byte VcaInput    = (ocr2aValue); 
        byte passos[7]   = {Atk, Hold, Sustain, DecRel, TriggerHigh, TriggerLow, VcaInput};

#ifdef _WIN32
        DWORD bytesWritten;
        if (!WriteFile(hSerial, passos, sizeof(passos), &bytesWritten, NULL)) {
            cerr << "Erro ao enviar dados." << endl;
        } else {
            cout << "Enviado: "
                 << "ATK=0x" << hex << (int)Atk
                 << ", HOLD=0x" << (int)Hold
                 << ", SUS=0x" << (int)Sustain
                 << ", DEC/REL=0x" << (int)DecRel
                 << ", TRIG_FREQ=0x" << (int)Trigger
                 << ", VCA_FREQ=0x" << (int)VcaInput
                 << " (" << dec << bytesWritten << " bytes)" << endl;
        }
    CloseHandle(hSerial);
#else
        ssize_t bytesWritten = write(serialPort, passos, sizeof(passos));
        if (bytesWritten < 0) {
            cerr << "Erro ao enviar dados.\n";
        } else {
            cout << "Enviado: "
                 << "ATK=0x" << hex << (int)Atk
                 << ", HOLD=0x" << (int)Hold
                 << ", SUS=0x" << (int)Sustain
                 << ", DEC/REL=0x" << (int)DecRel
                 << ", TRIG=0x" << (int)Trigger
                 << ", VCA=0x" << (int)VcaInput
                 << " (" << dec << bytesWritten << " bytes)" << endl;
        }
    close(serialPort);
#endif

    return 0;
}
