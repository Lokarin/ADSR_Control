#include <iostream>

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

int main() {
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

    while (true) {
        int atkSteps, susSteps, holdSteps, decRelSteps, triggerFrequency, vcaInputFrequency;

        cout << "Attack - passos (0-100): ";                 cin >> atkSteps;

        cout << "Hold - passos (0-100): ";                   cin >> holdSteps;

        cout << "Sustain - passos (0-100): ";                cin >> susSteps;

        cout << "Decay/Release - passos (0-100): ";          cin >> decRelSteps;

        cout << "Trigger frequency (1Hz, 3Hz): ";            cin >> triggerFrequency;

        cout << "VCA sign in frequency (200Hz, 1000Hz): ";   cin >> vcaInputFrequency;

        switch (triggerFrequency)
        {
        case 1:
            triggerFrequency = 0;
            break;
        case 3:
            triggerFrequency = 1;
            break;
        default:
            triggerFrequency = 0;
            break;
        }

        switch (vcaInputFrequency)
        {
        case 200:
            vcaInputFrequency = 0;
            break;
        case 1000:
            vcaInputFrequency = 1;
            break;
        default:
            vcaInputFrequency = 0;
            break;
        }

        byte Atk       = (atkSteps & 0x7F);
        byte Hold      = (holdSteps & 0x7F);
        byte Sustain   = (susSteps & 0x7F);
        byte DecRel    = (decRelSteps & 0x7F);
        byte Trigger   = (triggerFrequency & 0x7F);
        byte VcaInput = (vcaInputFrequency & 0x7F);
        byte passos[6] = {Atk, Hold, Sustain, DecRel, Trigger, VcaInput};

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
#endif
    }

#ifdef _WIN32
    CloseHandle(hSerial);
#else
    close(serialPort);
#endif
    return 0;
}

