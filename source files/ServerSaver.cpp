//
// Created by Tatry on 8. 1. 2024.
//

#include <sstream>
#include "../headers/ServerSaver.h"
#include "../headers/my_socket.h"

void ServerSaver::saveWorldToServer(world_t worldToSave, std::string fileName) {
    MySocket* socket = MySocket::createConnection("frios2.uniza.sk", 18235);
    std::stringstream dataToSend;
    dataToSend << "w" << fileName << ServerSaver::endRowChar;
    for (const auto &row : worldToSave) {
        for (const bool &cell: row)
        {
            if (cell)
            {
                dataToSend << ServerSaver::trueCellChar;
            }
            else
            {
                dataToSend << ServerSaver::falseCellChar;
            }
            dataToSend << ServerSaver::endRowChar;
        }
    }
    socket->sendData(dataToSend.str());
    socket->sendEndMessage();
}

void ServerSaver::getWorldFromServer(std::string fileName) {
}
