# Personal C++ Network Firewall

A high-performance, user-space personal firewall built in C++ for Windows. This application utilizes the WinDivert library to hook into the Windows network stack, allowing for real-time packet inspection and filtering at the kernel level.

## Features
* **Dynamic IP Filtering:** Blocks outbound connections to specific IPv4 and IPv6 addresses using a configurable `blocklist.txt`.
* **Kernel-Level Performance:** Uses WinDivert to drop packets natively within the OS kernel before they consume user-space memory.
* **Smart Parsing:** Automatically detects and appropriately routes IPv4 vs. IPv6 packet filtering rules.
* **Strict Typing Detection:** Sanitizes IP inputs to prevent kernel-level syntax crashes.

## Technologies Used
* **C++** (Core engine)
* **WinDivert / Windows Filtering Platform** (Packet interception & kernel-level filtering)

## How to Run
1. Download the [WinDivert](https://github.com/basil00/WinDivert) library.
2. Place `windivert.h`, `WinDivert.lib`, `WinDivert.dll`, and `WinDivert64.sys` in the project directory alongside the source code.
3. Compile the application (e.g., using MinGW/GCC): 
   `g++ firewall.cpp -o firewall.exe WinDivert.lib -lws2_32`
4. Add target IPs to `blocklist.txt` (one per line).
5. Run `.\firewall.exe` in an **Administrator** command prompt or PowerShell window.
