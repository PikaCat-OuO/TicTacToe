#include "ai.h"
using namespace std;

int main()
{
    cout<<"��Ҫ���߻��Ǻ���?��������0������������������:";
    uint64_t choice;cin>>choice;
    if(choice){
        AI::AImove();
    }
    while(true){
        //����
        AI::showBoard();
        AI::checkState();//���״̬
        cout<<"��������Ҫ�µ�����:";
        uint16_t row,col;cin>>row>>col;
        --row;--col;
        if(!AI::checkValid(row,col)){
            cout<<"����������������������!"<<endl;
            system("pause");continue;
        }
        AI::setBoard(row,col);
        //������
        AI::showBoard();
        AI::checkState();//���״̬
        cout<<"��������˼��...";
        AI::AImove();
    }
    return 0;
}

