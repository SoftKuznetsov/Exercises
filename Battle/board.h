#ifndef BOARD_H
#define BOARD_H

typedef enum {
    RESULT_OK,
    RESULT_ERROR
} result_e;

constexpr unsigned char SIZE_BOARD = 10;

class Ship {
public:
    Ship();

    result_e setCell(int, int);
    result_e clearCell(int, int);
    result_e checkShips();

private:
    int board[SIZE_BOARD][SIZE_BOARD];
    const int ships_for_game[5] = {0, 4, 3, 2, 1};
    int ships[5];

    int computeLenghtShip(int x, int y, int& part_1, int& part_2);
    bool isCorrectCoordinate(int x, int y);
    bool hasShip(int x, int y);
    bool isCorrectRange(int x, int y);
};


#endif // BOARD_H
