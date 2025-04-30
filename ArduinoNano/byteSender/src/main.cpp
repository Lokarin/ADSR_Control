#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    HANDLE hSerial = CreateFile("COM2", GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                OPEN_EXISTING, 0, NULL);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Erro ao abrir a porta COM\n";
        return 1;
    }
    
    // Configura a porta
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Erro ao obter o estado da porta\n";
        return 1;
    }
    
    dcbSerialParams.BaudRate = CBR_9600; // Mesmo baudrate que o ATmega
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Erro ao configurar a porta\n";
        return 1;
    }

    while(true) {
        // Coleta os valores do usuário
        int atkSteps, decRelSteps, susSteps;
        int atkDir, decRelDir, susDir;

        cout << "Attack - direcao (1=up, 0=down): "; cin >> atkDir;
        cout << "Attack - passos (0-100): ";     cin >> atkSteps;

        cout << "Decay/Release - direcao (1=up, 0=down): "; cin >> decRelDir;
        cout << "Decay/Release - passos (0-100): ";     cin >> decRelSteps;

        cout << "Sustain - direcao (1=up, 0=down): "; cin >> susDir;
        cout << "Sustain - passos (0-100): ";     cin >> susSteps;

        // Gera opcodes
        BYTE opcodeAtk     = (atkDir << 7) | (atkSteps & 0x7F);
        BYTE opcodeDecRel  = (decRelDir << 7) | (decRelSteps & 0x7F);
        BYTE opcodeSustain = (susDir << 7) | (susSteps & 0x7F);
    
        // Envia os três bytes
        DWORD bytesWritten;
        BYTE opcodes[3] = { opcodeAtk, opcodeDecRel, opcodeSustain }; // exemplo
    
        if (!WriteFile(hSerial, opcodes, sizeof(opcodes), &bytesWritten, NULL)) {
            cerr << "Erro ao enviar dados." << endl;
        } else {
            cout << "Enviado: "
                 << "ATK=0x" << hex << (int)opcodeAtk
                 << ", DEC/REL=0x" << (int)opcodeDecRel
                 << ", SUS=0x" << (int)opcodeSustain
                 << " (" << dec << bytesWritten << " bytes)" << endl;
        }
    }
    
    CloseHandle(hSerial);
    return 0;
}