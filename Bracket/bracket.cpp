#include <iostream>
#include <cstdio>
using namespace std;

const int MAX_STACK_SIZE = 10000;  // 스택의 최대 크기: 20

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

// 3.6 괄호 검사 프로그램
bool CheckMatching( char *filename ) {
    FILE *fp = fopen( filename , "r");
    if( fp == NULL ) error("Error: No File.\n");

    int nLine = 1, nChar = 0;
    ArrayStack stack;
    char ch;
    bool isError = false;

    while ( (ch = getc(fp)) != EOF )
    {
        if ( ch == '\n' )
        {
            nLine++;
        }
        nChar++;

        if( ch == '[' || ch == '(' || ch == '{' )
        {
            stack.push(ch);
        }
        else if( ch == ']' || ch == ')' || ch == '}' )
        {
            if(stack.isEmpty())
            {
                isError = true;
                break;
            }
            else
            {
                int prev = stack.pop();
                if( ( ch == ']' && prev != '[' ) || (ch == ')' && prev != '(') || (ch == '}' && prev != '{' ) )
                {
                    isError = true;
                    break;
                }
            }
        }
    }

    fclose(fp);
    printf("[%s] File Result:\n", filename);
    if( isError || !stack.isEmpty() )
    {
        printf("Error! (Line=%d, Word=%d)\n\n", nLine, nChar);
    }
    else
    {
        printf("   OK: (Line=%d, Word=%d)\n\n", nLine, nChar);
    }

    return !isError && stack.isEmpty();
}

// 테스트 함수
int main() {
    CheckMatching("../ArrayStack/ArrayStack.cpp");
    CheckMatching("../Student/Student.cpp");
}