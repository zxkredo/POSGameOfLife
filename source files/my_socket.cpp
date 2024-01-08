#include "../headers/my_socket.h"
#include <stdexcept>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <sstream>
#include <chrono>
#include <thread>

#define SOCKET_TERMINATE_CHAR '\0'

const char* MySocket::endMessage = ":end";

MySocket* MySocket::createConnection(std::string hostName, short port) {
    WSADATA wsaData;
    struct addrinfo *result = NULL;
    struct addrinfo hints;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        throw std::runtime_error("WSAStartup failed with error: " + std::to_string(iResult) + "\n");
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(hostName.c_str(), std::to_string(port).c_str(), &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        throw std::runtime_error("getaddrinfo failed with error: " + std::to_string(iResult) + "\n");
    }

    // Create a SOCKET for connecting to server
    SOCKET connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connectSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("socket failed with error: " + std::to_string(WSAGetLastError()) + "\n");
    }

    // Connect to server
    iResult = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        throw std::runtime_error("Unable to connect to server.\n");
    }

    return new MySocket(connectSocket);
}

MySocket::MySocket(SOCKET socket) :
    connectSocket(socket) {

}

MySocket::~MySocket() {
    if (this->connectSocket != INVALID_SOCKET) {
        closesocket(this->connectSocket);
        this->connectSocket = INVALID_SOCKET;
    }
    WSACleanup();
}

void MySocket::sendData(const std::string &data) {
    size_t data_length = data.length();
    char* buffer = (char*)calloc(data_length + 1, sizeof(char));
    memcpy(buffer, data.c_str(), data_length);
    buffer[data_length] = SOCKET_TERMINATE_CHAR;

    int iResult = send(connectSocket, buffer, data_length + 1, 0 );
    if (iResult == SOCKET_ERROR) {
        throw std::runtime_error("send failed with error: " + std::to_string(WSAGetLastError()) + "\n");
    }
    free(buffer);
    buffer = NULL;
}

std::string MySocket::readData() {
    #define BUFFLENGTH 5000
    int recvbuflen = BUFFLENGTH;
    char buffer[BUFFLENGTH];
    std::stringstream r_buffer;

    bool terminateCharFound = false;
    while (!terminateCharFound)
    {
        int read_length = recv(connectSocket, buffer, recvbuflen, 0);
        if (read_length > 0) {

            for (int i = 0; i < read_length; ++i) {
                if (buffer[i] == SOCKET_TERMINATE_CHAR)
                {
                    terminateCharFound = true;
                    break;
                }
                r_buffer << buffer[i];
            }
        }
        //wait for server to write something, because we didn't receive terminate character yet
        if (!terminateCharFound)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    return r_buffer.str();
}
void MySocket::sendEndMessage() {
    this->sendData(this->endMessage);
}

#undef SOCKET_TERMINATE_CHAR