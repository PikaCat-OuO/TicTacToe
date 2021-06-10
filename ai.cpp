#include "ai.h"
using namespace std;

array<array<char,3>,3> AI::mBoard{{
    {'*','*','*'},
    {'*','*','*'},
    {'*','*','*'}
}};

void AI::showBoard(){//ˢ������
    system("cls");
    for(const auto& row:mBoard){
        for(const auto& col:row) cout<<" "<<col;
        cout<<endl;
    }
}

void AI::setBoard(uint16_t row,uint16_t col){
    mBoard[row][col]='O';
}

bool AI::checkValid(uint16_t row,uint16_t col){//�������
    if(row>2 or col>2 or mBoard[row][col]!='*'){
        return false;
    }
    return true;
}

tuple<bool,State> AI::getState(){//�������̻�ȡ��ǰ״̬
    //check diagonals
    if((mBoard[0][0]==mBoard[1][1] and mBoard[1][1]==mBoard[2][2])
        or (mBoard[0][2]==mBoard[1][1] and mBoard[1][1]==mBoard[2][0])){
        if(mBoard[1][1]=='*') return {false,State::OnGoing};
        if(mBoard[1][1]=='O') return {true,State::RedWin};
        if(mBoard[1][1]=='X') return {true,State::BlackWin};
    }
    for(uint16_t i{0};i<3;++i){
        //check each row
        if(mBoard[i][0]==mBoard[i][1] and mBoard[i][1]==mBoard[i][2]){
            if(mBoard[i][0]=='*') return {false,State::OnGoing};
            if(mBoard[i][0]=='O') return {true,State::RedWin};
            if(mBoard[i][0]=='X') return {true,State::BlackWin};
        }
        //check each column
        if(mBoard[0][i]==mBoard[1][i] and mBoard[1][i]==mBoard[2][i]){
            if(mBoard[0][i]=='*') return {false,State::OnGoing};
            if(mBoard[0][i]=='O') return {true,State::RedWin};
            if(mBoard[0][i]=='X') return {true,State::BlackWin};
        }
    }
    //check for draw
    bool drawFlag{true};
    for(const auto& row:mBoard){
        for(const auto& col:row){
            if(col=='*'){
                drawFlag=false;
                break;
            }
        }
    }
    if(drawFlag) return {true,State::Draw};
    else return {false,State::OnGoing};
}

void AI::checkState(){
    auto[flag,state]=getState();
    if(flag){
        if(state==State::Draw){
            cout<<"���ֺ���!";exit(0);
        }else if(state==State::RedWin){
            cout<<"�췽ʤ��!";exit(0);
        }else{
            cout<<"�ڷ�ʤ��!";exit(0);
        }
    }
}

tuple<bool,int16_t> AI::evaluate(){
    auto[flag,state]=getState();
    if(flag){
        if(state==State::Draw) return {true,0};
        if(state==State::RedWin) return {true,-10};
        if(state==State::BlackWin) return {true,10};
    }
    return {false,0};
}

vector<tuple<uint16_t,uint16_t>> AI::getAllPossiableMove(){
    //Ѱ�ҿ����ߵĵط�
    vector<tuple<uint16_t,uint16_t>> moveablePlaces;
    for(uint16_t row=0;row<3;++row){
        for(uint16_t col=0;col<3;++col){
            if(mBoard[row][col]=='*') moveablePlaces.emplace_back(row,col);
        }
    }
    mt19937 mt(time(NULL));
    //����˳��ʹ��AI�����������
    shuffle(begin(moveablePlaces),end(moveablePlaces),mt);
    return moveablePlaces;
}

int16_t AI::ABmax(int16_t alpha,int16_t beta){
    auto[flag,score]=evaluate();
    if(flag) return score;
    //��ȡ���п����ߵĵط�
    vector<tuple<uint16_t,uint16_t>> moveablePlaces=getAllPossiableMove();
    //������ֵ����
    int16_t maxScore{-10};//���ֵ
    for(uint16_t index{0};index<moveablePlaces.size();++index){
        //��ȡ�����ƶ��ĵط�
        auto[row,col]=moveablePlaces.at(index);
        //����
        mBoard[row][col]='X';
        int16_t retScore=ABmin(alpha,beta);//��øþ���ķ���
        maxScore=max(maxScore,retScore);
        alpha=max(alpha,retScore);
        //�Ż�
        mBoard[row][col]='*';
        if(beta<=alpha) return retScore;
    }
    return maxScore;
}

int16_t AI::ABmin(int16_t alpha,int16_t beta){
    auto[flag,score]=evaluate();
    if(flag) return score;
    //��ȡ���п����ߵĵط�
    vector<tuple<uint16_t,uint16_t>> moveablePlaces=getAllPossiableMove();
    //�����Сֵ����
    int16_t minScore{10};//��Сֵ
    for(uint16_t index{0};index<moveablePlaces.size();++index){
        //��ȡ�����ƶ��ĵط�
        auto[row,col]=moveablePlaces.at(index);
        //����
        mBoard[row][col]='O';
        int16_t retScore=ABmax(alpha,beta);//��øþ���ķ���
        minScore=min(minScore,retScore);
        beta=min(beta,retScore);
        //�Ż�
        mBoard[row][col]='*';
        if(beta<=alpha) return retScore;
    }
    return minScore;
}

void AI::AImove(){//��������
    //��ȡ���п����ߵĵط�
    vector<tuple<uint16_t,uint16_t>> moveablePlaces=getAllPossiableMove();
    //������ֵ������
    int16_t maxScore{-10};//���ֵ
    uint16_t maxIndex{0};//����±�
    for(uint16_t index{0};index<moveablePlaces.size();++index){
        //��ȡ�����ƶ��ĵط�
        auto[row,col]=moveablePlaces.at(index);
        //����
        mBoard[row][col]='X';
        int16_t retScore=ABmin(maxScore,10);//��øþ���ķ���
        if(maxScore<retScore){
            maxScore=retScore;
            maxIndex=index;
        }
        //�Ż�
        mBoard[row][col]='*';
        if(10==maxScore) break;
    }
    auto[row,col]=moveablePlaces.at(maxIndex);
    mBoard[row][col]='X';
}
