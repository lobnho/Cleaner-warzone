#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <ctime>

// Funções protótipo
void terminateProcesses();
void setRandomDNS();
void resetNetwork();
void disableGameBar();
void disableBackgroundApps();
void deleteRegistryKeys();
void cleanTempFiles();
void deleteGameFolders();
void deleteAppDataFolders();
void adjustMouseKeyboardLag();
void deleteSpecificFoldersAndFiles();
void setConsoleColor(int color);
void resetConsoleColor();
void waitForKeyPress();
int cleanDirectory(const std::string& directoryPath);
std::string getWindowsPath();
std::string getSystemTempPath();

int main() {
    // Encerrar processos específicos
    terminateProcesses();

    // Configurar DNS aleatório
    setRandomDNS();

    // Resetar rede
    resetNetwork();

    // Desabilitar Game Bar e Background Apps
    disableGameBar();
    disableBackgroundApps();

    // Deletar registros específicos
    deleteRegistryKeys();

    // Limpar arquivos temporários permanentemente
    cleanTempFiles();

    // Deletar pastas específicas de jogos
    deleteGameFolders();

    // Deletar diretórios do App Data
    deleteAppDataFolders();

    // Ajustar lag de mouse e teclado
    adjustMouseKeyboardLag();

    // Deletar diretórios e arquivos específicos
    deleteSpecificFoldersAndFiles();

    // Mensagem final em azul
    setConsoleColor(9); // Azul
    std::cout << "\nPressione qualquer tecla para fechar o aplicativo.\n";
    resetConsoleColor();

    // Aguarda que o usuário pressione qualquer tecla para fechar o programa
    waitForKeyPress();
    return 0;
}

// Função para mudar a cor do texto no console
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Função para resetar a cor do console para o padrão
void resetConsoleColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // Cor padrão (branco)
}

// Função para esperar qualquer tecla pressionada
void waitForKeyPress() {
    _getch(); // Aguarda uma tecla e retorna imediatamente
}

// Função para encerrar processos específicos
void terminateProcesses() {
    setConsoleColor(14); // Amarelo
    std::cout << "Encerrando processos especificos...\n";
    resetConsoleColor();

    std::vector<std::string> processes = {
        "steam.exe", "Battle.net.exe", "XboxPcApp.exe", "Battle.net Launcher.exe",
        "cod.exe", "EpicGamesLauncher.exe", "EpicWebHelper.exe"
    };

    for (const auto& process : processes) {
        std::string command = "taskkill /F /IM " + process + " >nul 2>&1";
        system(command.c_str());
    }

    setConsoleColor(10); // Verde
    std::cout << "Processos especificos encerrados com sucesso!\n";
    resetConsoleColor();
}

// Função para configurar DNS aleatório
void setRandomDNS() {
    setConsoleColor(14); // Amarelo
    std::cout << "Configurando DNS aleatorio...\n";
    resetConsoleColor();

    std::vector<std::string> dns_list = {
        "8.8.8.8,8.8.4.4", "208.67.222.222,208.67.220.220", "1.1.1.1,1.0.0.1",
        "9.9.9.9,149.112.112.112", "94.140.14.14,94.140.15.15", "8.26.56.26,8.20.247.20",
        "156.154.70.1,156.154.71.1", "64.6.64.6,64.6.65.6", "1.1.1.2,1.0.0.2",
        "auto"
    };

    srand(static_cast<unsigned>(time(0)));
    int random_index = rand() % dns_list.size();
    std::string dns = dns_list[random_index];

    if (dns == "auto") {
        system("netsh interface ip set dns name=\"Ethernet\" dhcp >nul 2>&1");
        system("netsh interface ip set dns name=\"Wi-Fi\" dhcp >nul 2>&1");
    } else {
        size_t comma_pos = dns.find(',');
        std::string preferred_dns = dns.substr(0, comma_pos);
        std::string alternate_dns = dns.substr(comma_pos + 1);

        std::string command = "netsh interface ip set dns name=\"Ethernet\" static " + preferred_dns + " primary >nul 2>&1";
        system(command.c_str());
        command = "netsh interface ip add dns name=\"Ethernet\" addr=" + alternate_dns + " index=2 >nul 2>&1";
        system(command.c_str());
        command = "netsh interface ip set dns name=\"Wi-Fi\" static " + preferred_dns + " primary >nul 2>&1";
        system(command.c_str());
        command = "netsh interface ip add dns name=\"Wi-Fi\" addr=" + alternate_dns + " index=2 >nul 2>&1";
        system(command.c_str());
    }

    setConsoleColor(10); // Verde
    std::cout << "DNS configurado com sucesso!\n";
    resetConsoleColor();
}

// Função para resetar a rede
void resetNetwork() {
    setConsoleColor(14); // Amarelo
    std::cout << "Resetando a rede...\n";
    resetConsoleColor();

    system("ipconfig /release >nul 2>&1");
    system("ipconfig /flushdns >nul 2>&1");
    system("ipconfig /renew >nul 2>&1");
    system("netsh int ip reset >nul 2>&1");

    setConsoleColor(10); // Verde
    std::cout << "Rede resetada com sucesso!\n";
    resetConsoleColor();
}

// Função para desabilitar o Game Bar
void disableGameBar() {
    setConsoleColor(14); // Amarelo
    std::cout << "Desabilitando Game Bar...\n";
    resetConsoleColor();

    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\PolicyManager\\default\\ApplicationManagement\\AllowGameDVR\" /v value /t REG_DWORD /d 0 /f >nul 2>&1");

    setConsoleColor(10); // Verde
    std::cout << "Game Bar desabilitado com sucesso!\n";
    resetConsoleColor();
}

// Função para desabilitar aplicativos em segundo plano
void disableBackgroundApps() {
    setConsoleColor(14); // Amarelo
    std::cout << "Desabilitando aplicativos em segundo plano...\n";
    resetConsoleColor();

    system("powercfg /x off >nul 2>&1");

    setConsoleColor(10); // Verde
    std::cout << "Aplicativos em segundo plano desabilitados com sucesso!\n";
    resetConsoleColor();
}

// Função para deletar registros específicos
void deleteRegistryKeys() {
    setConsoleColor(14); // Amarelo
    std::cout << "Deletando registros especificos...\n";
    resetConsoleColor();

    std::vector<std::string> registry_keys = {
        "HKCU\\Software\\Epic Games\\Unreal Engine", "HKCU\\Software\\Activision",
        "HKCU\\Software\\Blizzard Entertainment\\Battle.net", "HKCU\\Software\\Blizzard Entertainment\\Blizzard Error",
        "HKCU\\Software\\Valve\\Source", "HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\UserAssist\\{CEBFF5CD-ACE2-4F4F-9178-9926F41749EA}\\Count"
    };

    for (const auto& key : registry_keys) {
        std::string command = "reg delete \"" + key + "\" /f >nul 2>&1";
        system(command.c_str());
    }

    setConsoleColor(10); // Verde
    std::cout << "Registros especificos deletados com sucesso!\n";
    resetConsoleColor();
}

// Função para limpar arquivos temporários permanentemente
void cleanTempFiles() {
    setConsoleColor(14); // Amarelo
    std::cout << "Deletando arquivos temporarios...\n";
    resetConsoleColor();

    system("rd /s /q \"%TEMP%\" >nul 2>&1");
    system("rd /s /q \"%LOCALAPPDATA%\\Temp\" >nul 2>&1");
    system("rd /s /q \"%WINDIR%\\Prefetch\" >nul 2>&1");

    setConsoleColor(10); // Verde
    std::cout << "Arquivos temporarios deletados com sucesso!\n";
    resetConsoleColor();
}

// Função para deletar pastas específicas de jogos
void deleteGameFolders() {
    setConsoleColor(14); // Amarelo
    std::cout << "Deletando pastas especificas de jogos...\n";
    resetConsoleColor();

    std::vector<std::string> game_paths = {
        "Battle.net\\Call of Duty\\_retail_\\cod24\\main",
        "Battle.net\\Call of Duty\\_retail_\\xpak_cache",
        "Battle.net\\Call of Duty\\_retail_\\telescopeStorage",
        "Battle.net\\Call of Duty\\_retail_\\telescopeCache",
        "XboxGames\\Call of Duty\\Content\\xpak_cache",
        "XboxGames\\Call of Duty\\Content\\telescopeStorage",
        "XboxGames\\Call of Duty\\Content\\telescopeCache",
        "Steam\\steamapps\\common\\Call of Duty HQ\\xpak_cache",
        "Steam\\steamapps\\common\\Call of Duty HQ\\telescopeStorage",
        "Steam\\steamapps\\common\\Call of Duty HQ\\telescopeCache"
    };

    for (const auto& path : game_paths) {
        std::string command = "rd /s /q \"" + path + "\" >nul 2>&1";
        system(command.c_str());
    }

    setConsoleColor(10); // Verde
    std::cout << "Pastas especificas de jogos deletadas com sucesso!\n";
    resetConsoleColor();
}

// Função para deletar diretórios do App Data
void deleteAppDataFolders() {
    setConsoleColor(14); // Amarelo
    std::cout << "Deletando diretorios do App Data...\n";
    resetConsoleColor();

    std::vector<std::string> app_data_paths = {
        "%LOCALAPPDATA%\\Activision", "%LOCALAPPDATA%\\VALORANT", "%LOCALAPPDATA%\\CrashDumps",
        "%LOCALAPPDATA%\\CrashReportClient", "%LOCALAPPDATA%\\Blizzard Entertainment",
        "%LOCALAPPDATA%\\Battle.net\\BrowserCaches", "%LOCALAPPDATA%\\Battle.net\\Cache",
        "%LOCALAPPDATA%\\Battle.net\\Logs", "%LOCALAPPDATA%\\Steam\\htmlcache\\Cache"
    };

    for (const auto& path : app_data_paths) {
        std::string command = "rd /s /q \"" + path + "\" >nul 2>&1";
        system(command.c_str());
    }

    setConsoleColor(10); // Verde
    std::cout << "Diretorios do App Data deletados com sucesso!\n";
    resetConsoleColor();
}

// Função para ajustar lag de mouse e teclado
void adjustMouseKeyboardLag() {
    setConsoleColor(14); // Amarelo
    std::cout << "Ajustando lag de mouse e teclado...\n";
    resetConsoleColor();

    system("reg add \"HKEY_CURRENT_USER\\Control Panel\\Accessibility\\MouseKeys\" /v Flags /t REG_SZ /d 0 /f >nul 2>&1");
    system("reg add \"HKEY_CURRENT_USER\\Control Panel\\Accessibility\\Keyboard Response\" /v Flags /t REG_SZ /d 0 /f >nul 2>&1");

    setConsoleColor(10); // Verde
    std::cout << "Lag de mouse e teclado ajustado com sucesso!\n";
    resetConsoleColor();
}

// Função para deletar diretórios e arquivos específicos
void deleteSpecificFoldersAndFiles() {
    setConsoleColor(14); // Amarelo
    std::cout << "Deletando diretorios e arquivos especificos...\n";
    resetConsoleColor();

    std::vector<std::string> specific_paths = {
        "mp23/BlizzardBrowser", "mp23/.battle.net", "mp23/xpak_cache", "mp23/blob_storage",
        "mp23/telescopeCache", "mp23/telescopeStorage", "mp23/shadercache",
        "BlizzardBrowser", ".battle.net", "xpak_cache", "blob_storage",
        "telescopeCache", "telescopeStorage", "shadercache",
        "main\\*.dcache", "bootstrapper.log", "bootstrap.data.bin", "Launcher.db",
        ".patch.result", ".product.db", ".build.info"
    };

    for (const auto& path : specific_paths) {
        std::string command = "rd /s /q \"" + path + "\" >nul 2>&1";
        system(command.c_str());
    }

    setConsoleColor(10); // Verde
    std::cout << "Diretorios e arquivos especificos deletados com sucesso!\n";
    resetConsoleColor();
}
