#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_STRING = 100;
const int MAX_STACK_SIZE = 20;

// 3.3 Student.h
class Student {
    int id;                 // 학번
    char name[MAX_STRING];  // 이름
    char dept[MAX_STRING];  // 소속 학과
public:
    Student(int i=0, char *n="", char *d="") { set( i, n, d ); }
    void set(int i, char *n, char *d)
    {
        id = i;
        strcpy( name, n );  // 문자열 복사 함수
        strcpy( dept, d );  // 문자열 복사 함수
    }
    void display() {
        printf(" id:%-15d name:%-10s dept:%-20s\n", id, name, dept);
    }
};

// 오류 처리 함수
inline void error(char *message) {
    printf("%s\n", message);
    exit(1);
}

// 3.4 StudentStack.h
class StudentStack {
    int top;                    // 요소의 개수
    Student data[MAX_STACK_SIZE];

public:
    StudentStack() { top=-1; }  // 스택 생성자
    ~StudentStack() {}          // 스택 소멸자
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK_SIZE-1; }

    void push(Student e)
    {
        if( isFull() ) { error ("Stack error"); }
        data[++top] = e;
    }

    Student pop()
    {
        if( isEmpty() ) { error ("Stack error"); }
        return data[top--];
    }

    Student peek()
    {
        if( isEmpty() ) { error ("Stack error"); }
        return data[top];
    }

    void display()
    {
        printf("[Total Students Number = %2d]\n", top+1);
        for (int i=0; i<=top; i++)
        {
            data[i].display();      // 각 학생 정보 출력
        }
        printf("\n");
    }
};

// 실행 함수
int main() {
    StudentStack stk;
    stk.push( Student(2015130007, "HongGilDong", "DepartmentOfComputerEngineering") );
    stk.push( Student(2015130100, "LeeSoonSin", "DepartmentOfMechanicalEngineering") );
    stk.push( Student(2015130135, "HwangHi", "DepartmentOfLaw") );
    stk.display();
    stk.pop();
    stk.display();
}