#include "getHost_Info.hpp"

std::string GetIPAddress() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    char host[256];
    gethostname(host, sizeof(host));

    struct addrinfo* addrinfoResult = NULL;
    struct addrinfo* ptr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // AF_INET for IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int result = getaddrinfo(host, NULL, &hints, &addrinfoResult);
    if (result != 0) {
        WSACleanup();
        return "Error getting address";
    }

    std::string ipAddress;
    for (ptr = addrinfoResult; ptr != NULL; ptr = ptr->ai_next) {
        struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
        char ipAddr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &sockaddr_ipv4->sin_addr, ipAddr, INET_ADDRSTRLEN);
        ipAddress = std::string(ipAddr);
    }

    freeaddrinfo(addrinfoResult);
    WSACleanup();

    return ipAddress;
}

std::string GetMACAddress() {
  IP_ADAPTER_INFO adapterInfo;
  ZeroMemory(&adapterInfo, sizeof(adapterInfo));
  DWORD dwBufLen = sizeof(adapterInfo);

  for (DWORD i = 0; GetAdaptersInfo(&adapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW; i++) {
    dwBufLen *= 2;
    LPBYTE pBuf = (LPBYTE)malloc(dwBufLen);
    if (GetAdaptersInfo((PIP_ADAPTER_INFO)pBuf, &dwBufLen) == ERROR_SUCCESS) {
      adapterInfo = *(PIP_ADAPTER_INFO)pBuf;
      free(pBuf);
      break;
    }
    free(pBuf);
  }

  if (adapterInfo.AddressLength != 0) {
    std::string macAddress;
    for (int i = 0; i < adapterInfo.AddressLength; i++) {
      char buffer[3];
      StringCchPrintfA(buffer, sizeof(buffer), "%02x", adapterInfo.Address[i]);
      macAddress += buffer;
      if (i < adapterInfo.AddressLength - 1) {
        macAddress += ":";
      }
    }
    return macAddress;
  } else {
    return "Unknown";
  }
}

std::string GetWindowName(HWND hWnd) {
  wchar_t windowText[MAX_PATH];
  int length = GetWindowTextW(hWnd, windowText, MAX_PATH);
  if (length > 0) {
    // Convert wide character string to UTF-8
    std::string utf8String;
    int numBytesConverted = WideCharToMultiByte(CP_UTF8, 0, windowText, length, nullptr, 0, nullptr, nullptr);
    if (numBytesConverted > 0) {
      utf8String.resize(numBytesConverted);
      WideCharToMultiByte(CP_UTF8, 0, windowText, length, &utf8String[0], numBytesConverted, nullptr, nullptr);
    }
    return utf8String;
  } else {
    return "";
  }
}

std::string GetCurrentWindowName() {
  HWND hWnd = GetForegroundWindow();
  return GetWindowName(hWnd);
}