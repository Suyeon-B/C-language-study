#pragma warning(disable : 4996)
#include <stdio.h>

int main_printfscanf(void)
{
    // 정수형 변수 예제
    int age = 12;
    printf("%d\n", age);
    age = 13;
    printf("%d\n", age);

    // 실수형 변수에 대한 예제
    float f = 46.5;
    printf("%.2f\n", f);
    double d = 4.428;
    printf("%.2lf\n", d);
    const int YEAR = 2000;
    printf("%d\n", YEAR);

    // printf
    // 연산
    int add = 3 + 7; // 10
    printf("3+7 = %d\n", add);

    // scanf
    // 키보드 입력을 받아서 저장
    int input;
    printf("값을 입력하세요 : ");
    scanf("%d", &input);
    printf("입력값 : %d\n", input);

    int one, two, three;
    printf("세 개의 정수를 입력하세요 : ");
    scanf("%d %d %d", &one, &two, &three);
    printf("첫 번째 값: %d\n", one);
    printf("두 번째 값: %d\n", two);
    printf("세 번째 값: %d\n", three);

    // 문자(한 글자), 문자열(한 글자 이상의 여러 글자)
    char str[256];
    scanf("%s", str);
    printf("%s\n", str);

    // 프로젝트
    // 경찰관이 범죄자의 정보를 입수 (조서 작성)
    // 이름, 나이, 몸무게, 키, 범죄명
    char name[256];
    printf("what is your name? ");
    scanf("%s", name);

    int age;
    printf("How old are you? ");
    scanf("%d", &age);

    float weight;
    printf("How much do you weigh? ");
    scanf("%f", &weight);

    double height;
    printf("How tall are you? ");
    scanf("%lf", &height);

    char chrime[256];
    printf("What crimes were you guilty of? ");
    scanf("%s", chrime);

    // 조서 내용 출력
    printf("\n\n -- 범죄자 정보 -- \n\n");
    printf("name    : %s\n", name);
    printf("age     : %d\n", age);
    printf("weight  : %.2f\n", weight);
    printf("height  : %.2lf\n", height);
    printf("chrime  : %s\n", chrime);

    return 0;
}