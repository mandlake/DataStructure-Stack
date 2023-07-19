#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_STACK_SIZE = 20;  // 스택의 최대 크기: 20

// 오류 처리 함수
inline void error(char *message) {
    printf("%s\n", message);
    exit(1);
}

// 프로그램 3.1 ArrayStack.h
class ArrayStack
{
    int top;                    // 스택 상단을 사리키는 변수
    int data[MAX_STACK_SIZE];   // 요소의 배열

public:
    ArrayStack() { top = -1; }  // 스택 생성자
    ~ArrayStack() {}             // 스택 소멸자
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK_SIZE-1; }

    void push ( int e )         // 맨 위에 항목 삽입
    {
        if( isFull() ) { error ("Stack error"); }
        data[++top] = e;
    }

    int pop ( )                 // 맨 위의 요소를 삭제하지 않고 반환
    {
        if( isEmpty() ) { error ("Stack error"); }
        return data[top--];
    }

    int peek ( )                // 삭제하지 않고 요소 반환
    {
        if( isEmpty() ) { error ("Stack error"); }
        return data[top];
    }

    void display ( )            // 스택 내용을 화면에 출력
    {
        printf("[Stack Items Number = %2d] ==> ", top+1);
        for (int i=0; i<=top; i++)
        {
            printf("<%2d>", data[i]);
        }
        printf("\n");
    }
};

// 실행 함수
int main()
{
    ArrayStack stack;
    for(int i=1; i<10; i++) {
        stack.push(i);
    }
    stack.display();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.display();
}