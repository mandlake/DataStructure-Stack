#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_STACK_SIZE 100
inline void error(char *str) {
    printf("%s\n", str);
    exit(1);
}

// OperandStack.h
class OperandStack {
    double data[MAX_STACK_SIZE];
    int top;

public:
    OperandStack() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == MAX_STACK_SIZE; }

    void push(double e)
    {
        if( isFull() ) error ("스택 포화 에러");
        data[++top] = e;
    }
    double pop( )
    {
        if( isEmpty() ) error ("스택 공백 에러");
        return data[top--];
    }
};

double calcPostfixExpr( FILE *fp = stdin )
{
    char c;
    double val;
    OperandStack st;
    while ((c=getc(fp)) != '\n')
    {
        if( c=='+' || c=='-' || c=='*' || c=='/' )
        {
            double val2 = st.pop();
            double val1 = st.pop();
            switch( c )
            {
                case '+': st.push(val1 + val2); break;
                case '-': st.push(val1 - val2); break;
                case '*': st.push(val1 * val2); break;
                case '/': st.push(val / val2); break;
            }
        }
        else if ( c >= '0' && c <= '9')
        {
            ungetc( c, fp );
            fscanf( fp, "%lf", &val );
            st.push( val );
        }
    }
    return (st.pop());
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

// precedence
int precedence( char op )
{
    switch (op)
    {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

// infix2Postfix.h
void infix2Postfix( FILE *fp = stdin )
{
    char c, op;
    double val;
    ArrayStack st;

    while ( (c=getc(fp)) != '\n' )
    {
        if ((c>='0' && c<='9'))
        {
            ungetc( c, fp );
            fscanf( fp, "%lf", &val );
            printf("%4.1f ", val);
        }
        else if( c=='(' ) st.push( c );
        else if( c==')' )
        {
            while (!st.isEmpty())
            {
                op = st.pop();
                if(op=='(') break;
                else printf( "%c ", op );
            }
        }
        else if( c=='+' || c=='-' || c=='*' || c=='/' )
        {
            while ( !st.isEmpty() )
            {
                op = st.peek();
                if ( precedence(c) <= precedence(op) )
                {
                    printf( "%c ", op );
                    st.pop();
                }
                else break;
            }
            st.push( c );
        }
    }
    while (!st.isEmpty())
        printf( "%c ", st.pop() );
}

// test
int main() 
{
    printf("Enter Formula (Infix) = ");
    infix2Postfix();    // Infix 수식을 PostFix로 변환
}