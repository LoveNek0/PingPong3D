#pragma once
#include <string>
using namespace std;

class GameException
{
private:
    string message;

public:
    GameException(string message) {
        this->message = message;
    }
    string getMessage() {
        return this->message;
    }
};