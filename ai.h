#ifndef AI_H
#define AI_H

#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <random>
#include <time.h>

enum class State{RedWin,BlackWin,Draw,OnGoing};

class AI
{
public:
    AI()=delete;
    static void showBoard();
    static void setBoard(uint16_t,uint16_t);
    static bool checkValid(uint16_t,uint16_t);
    static std::tuple<bool,State> getState();
    static void checkState();
    static std::tuple<bool,int16_t> evaluate();
    static std::vector<std::tuple<uint16_t,uint16_t>> getAllPossiableMove();
    static int16_t ABmax(int16_t,int16_t);
    static int16_t ABmin(int16_t,int16_t);
    static void AImove();
private:
    static std::array<std::array<char,3>,3> mBoard;
};

#endif // AI_H
