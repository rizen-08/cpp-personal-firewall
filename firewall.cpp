#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "windivert.h" 

int main() {
    std::ifstream file("config.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not find or open config.txt\n";
        return 1;
    }
    std::string portString;
    std::getline(file, portString);
    int blockedPort = std::stoi(portString); 

    std::cout << "Config loaded! Blocking outbound TCP port: " << blockedPort << "\n";

    std::string filterString = "outbound and tcp.DstPort == " + std::to_string(blockedPort);

    HANDLE handle = WinDivertOpen(filterString.c_str(), WINDIVERT_LAYER_NETWORK, 0, 0);

    if (handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Failed to open WinDivert. Are you Administrator?\n";
        return 1;
    }

    char packet[65535];
    UINT packetLen;
    WINDIVERT_ADDRESS addr;

    std::cout << "Firewall is running. Press Ctrl+C to stop.\n";

    while (TRUE) {
        if (WinDivertRecv(handle, packet, sizeof(packet), &packetLen, &addr)) {
            std::cout << "[*] BLOCKED traffic trying to use Port " << blockedPort << "!\n";
        }
    }

    WinDivertClose(handle);
    return 0;
}