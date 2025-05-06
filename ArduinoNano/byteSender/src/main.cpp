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
        int atkSteps, susSteps, holdSteps, decRelSteps;
        //int atkDir, susDir, holdDir, decRelDir;

        //cout << "Attack - direcao (1=up, 0=down): "; cin >> atkDir;
        cout << "Attack - passos (0-100): ";         cin >> atkSteps;

        //cout << "Hold - direcao (1=up, 0=down): ";   cin >> holdDir;
        cout << "Hold - passos (0-100): ";           cin >> holdSteps;

        //cout << "Sustain - direcao (1=up, 0=down): "; cin >> susDir;
        cout << "Sustain - passos (0-100): ";         cin >> susSteps;

        //cout << "Decay/Release - direcao (1=up, 0=down): "; cin >> decRelDir;
        cout << "Decay/Release - passos (0-100): ";         cin >> decRelSteps;

        //byte opcodeAtk     = (atkDir << 7) | (atkSteps & 0x7F);
        //byte opcodeHold    = (holdDir << 7) | (holdSteps & 0x7F);
        //byte opcodeSustain = (susDir << 7) | (susSteps & 0x7F);
        //byte opcodeDecRel  = (decRelDir << 7) | (decRelSteps & 0x7F);
        byte Atk     = (atkSteps & 0x7F);
        byte Hold    = (holdSteps & 0x7F);
        byte Sustain = (susSteps & 0x7F);
        byte DecRel  = (decRelSteps & 0x7F);
        byte passos[4]    = { Atk, Hold, Sustain, DecRel };

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

