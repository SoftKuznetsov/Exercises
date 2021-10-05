#include "board.h"

// public
// ----------------------------------------------
Ship::Ship() {
    for(int i = 0; i < SIZE_BOARD; i++) {
        for (int j = 0; j < SIZE_BOARD; j++) {
            board[i][j] = 0;
        }
    }

    for (int i = 0; i < 5; i++){
        ships[i] = 0;
    }
}

result_e Ship::setCell(int x, int y) {
    // check corners
    if (!isCorrectCoordinate(x, y))
        return RESULT_ERROR;

    // compute lenght ship and compare
    int len_fisrt_part= 0;
    int len_second_part = 0;
    int len = computeLenghtShip(x, y, len_fisrt_part, len_second_part);
    if (len > 4) // max lenght for ship
        return RESULT_ERROR;

    if (ships[len] + 1 > ships_for_game[len]) {
        return RESULT_ERROR;
    }

    // set cell
    board[x][y] = 1;

    // add ship
    ships[len]++;

    // delete parts of ship
    if (len_fisrt_part)
        ships[len_fisrt_part]--;
    if (len_second_part)
        ships[len_second_part]--;

    return RESULT_OK;
}

result_e Ship::clearCell(int x, int y) {
    // TODO - add functional
    return RESULT_OK;
}

result_e Ship::checkShips() {
    for (int i = 0; i < 5; i++) {
        if (ships[i] == ships_for_game[i])
            continue;
        return RESULT_ERROR;
    }

    return RESULT_OK;
}

bool Ship::isFullCell(int x, int y) {
    return board[x][y];
}

// private
// ----------------------------------------------
bool Ship::isCorrectCoordinate(int x, int y) {
    // check left up corner
    if (isCorrectRange(x - 1, y - 1)) {
        if (hasShip(x - 1, y - 1))
            return false;
    }

    // check left down corner
    if (isCorrectRange(x - 1, y + 1)) {
        if (hasShip(x - 1, y + 1))
            return false;
    }

    // check right up corner
    if (isCorrectRange(x + 1, y - 1)) {
        if (hasShip(x + 1, y - 1))
            return false;
    }

    // check right down corner
    if (isCorrectRange(x + 1, y + 1)) {
        if (hasShip(x + 1, y + 1))
            return false;
    }

    return true;
}

bool Ship::isCorrectRange(int x, int y) {
    if (x >= 0 && x < SIZE_BOARD) {
        if (y >= 0 && y < SIZE_BOARD)
            return true;
    }
    return false;
}

bool Ship::hasShip(int x, int y) {
    return board[x][y];
}

int Ship::computeLenghtShip(int x, int y, int& part_1, int& part_2) {
    int len = 0;
    int temp = 0;

    // vertical ship
    // ---------------------------------------
    temp = x;
    while (temp) { // go left
        temp--;
        if (isCorrectRange(temp, y) && hasShip(temp, y))
            len++;
        else
            break;
    }
    part_1 = len;

    temp = x;
    while (temp) { // go right
        temp++;
        if (isCorrectRange(temp, y) && hasShip(temp, y))
            len++;
        else
            break;
    }
    part_2 = len - part_1;

    if (len) {
        return len + 1; // lenght with current cell
    }

    // horizontal ship
    // -----------------------------------------
    temp = y;
    while (temp) { // go down
        temp--;
        if (isCorrectRange(x, temp) && hasShip(x, temp))
            len++;
        else
            break;
    }
    part_1 = len;

    temp = y;
    while (temp) { // go up
        temp++;
        if (isCorrectRange(x, temp) && hasShip(x, temp))
            len++;
        else
            break;
    }
    part_2 = len - part_1;

    return len + 1; // lenght with current cell
}
