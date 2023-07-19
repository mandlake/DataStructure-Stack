#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const int MAZE_SIZE = 6;

// 2차원 좌표 클래스
struct Location2D {
    int row; // 현재 위치의 행 번호
    int col; // 현재 위치의 열 번호
    Location2D ( int r=0, int c=0 ) { row = r; col = c; }
    // 위치 p가 자신의 이웃인지 검사하는 함수
    bool isNeighbor( Location2D &p )
    {
        return( (row==p.row && (col==p.col-1 || col==p.col+1)) || (col==p.col && (row==p.row-1 || row==p.row+1)) );
    }
    // p가 자신과 같은 위치인지를 검사(연산자 오버로딩 사용)
    bool operator==( Location2D &p )
    {
        return row==p.row && col==p.col;
    }
};

// 3.11
char map[MAZE_SIZE][MAZE_SIZE] = { // ‘1’: 막힌표시.‘0’:이동 가능
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};
bool isValidLoc( int r, int c ) // (r,c)가 갈수 있는 위치인지 검사
{
    if( r < 0 || c < 0 || r>=MAZE_SIZE || c>=MAZE_SIZE ) return false;
    else return map[r][c] == '0' || map[r][c] == 'x' ;
}

int main() {
    stack <Location2D> locStack;
    Location2D entry(1,0);                  // 미로 입구
    locStack.push( entry );                 // 스택에 삽입
    while ( locStack.empty() == false ) {   // 스택이 비어있지 않는 동안
        Location2D here = locStack.top();
        locStack.pop();
        int r = here.row, c = here.col;
        printf( "(%d,%d) ", r, c );
        if( map[r][c] == 'x' ) {
            printf(" Success\n");
            return 0;
        }
        else {
            map[r][c] = '.';                // 위-아래-왼쪽-오른쪽 확인
            if( isValidLoc(r-1, c) ) locStack.push(Location2D(r-1,c));
            if( isValidLoc(r+1, c) ) locStack.push(Location2D(r+1,c));
            if( isValidLoc(r, c-1) ) locStack.push(Location2D(r,c-1));
            if( isValidLoc(r, c+1) ) locStack.push(Location2D(r,c+1));
        }
    }
    printf("Fail\n");
}