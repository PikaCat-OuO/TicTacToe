#include "ai.h"
using namespace std;

int main()
{
    cout<<"您要先走还是后走?先走输入0，后走输入任意内容:";
    uint64_t choice;cin>>choice;
    if(choice){
        AI::AImove();
    }
    while(true){
        //人走
        AI::showBoard();
        AI::checkState();//检查状态
        cout<<"请输入您要下的行列:";
        uint16_t row,col;cin>>row>>col;
        --row;--col;
        if(!AI::checkValid(row,col)){
            cout<<"您的输入有误，请重新输入!"<<endl;
            system("pause");continue;
        }
        AI::setBoard(row,col);
        //电脑走
        AI::showBoard();
        AI::checkState();//检查状态
        cout<<"电脑正在思考...";
        AI::AImove();
    }
    return 0;
}

