//
// Created by Tatry on 8. 1. 2024.
//

#ifndef POSGAMEOFLIFECLIENT_SERVERSAVER_H
#define POSGAMEOFLIFECLIENT_SERVERSAVER_H


#include <vector>
#include <string>

class ServerSaver {
    typedef std::vector<std::vector<bool>> world_t;
private:
    static const char trueCellChar = 'X';
    static const char falseCellChar = '.';
    static const char endRowChar = '\n';
public:
    static void saveWorldToServer(const world_t& worldToSave, const std::string& fileName);
    static void getWorldFromServer(const std::string& fileName);

};


#endif //POSGAMEOFLIFECLIENT_SERVERSAVER_H
