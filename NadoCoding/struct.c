#include <stdio.h>

struct GameInfo
{
    char *name;
    int year;
    int price;
    char *company;

    struct GameInfo *friendGame; // 연관 업체 게임
};

typedef struct
{
    char *name;
    int year;
    int price;
    char *company;

    struct GameInfo *friendGame; // 연관 업체 게임
} GAME_INFO;

int main(void)
{

    // 게임 출시
    // 이름 : game
    // 발매 년도 : 2017년
    // 가격 : 50원
    // 제작사 : company
    // char *name = "game";
    // int year = 2017;
    // int price = 50;
    // char *company = "company";

    // 구조체 사용
    // struct GameInfo gameInfo1;
    // gameInfo1.name = "game";
    // gameInfo1.year = 2017;
    // gameInfo1.price = 50;
    // gameInfo1.company = "company";

    // // 구조체 출력
    // printf("-- Game Info -- \n\n");
    // printf("이름        : %s\n", gameInfo1.name);
    // printf("발매 년도   : %d\n", gameInfo1.year);
    // printf("가격        : %d\n", gameInfo1.price);
    // printf("제작사      : %s\n", gameInfo1.company);

    // struct GameInfo gameInfo2 = {"game2", 2020, 100, "friend"};
    // // 구조체 출력
    // printf("-- Game Info -- \n\n");
    // printf("이름        : %s\n", gameInfo2.name);
    // printf("발매 년도   : %d\n", gameInfo2.year);
    // printf("가격        : %d\n", gameInfo2.price);
    // printf("제작사      : %s\n", gameInfo2.company);

    // 구조체 포인터
    // struct GameInfo *gamePtr; // 미션맨
    // gamePtr = &gameInfo1;
    // printf("-- 미션맨의 게임 출시 정보 -- \n\n");
    // printf("이름        : %s\n", (*gamePtr).name);
    // printf("발매 년도   : %d\n", (*gamePtr).year);
    // printf("가격        : %d\n", (*gamePtr).price);
    // printf("제작사      : %s\n", (*gamePtr).company);
    // printf("이름        : %s\n", gamePtr->name);
    // printf("발매 년도   : %d\n", gamePtr->year);
    // printf("가격        : %d\n", gamePtr->price);
    // printf("제작사      : %s\n", gamePtr->company);

    // 연관 업체 게임 소개
    // gameInfo1.friendGame = &gameInfo2;
    // printf("\n\n-- 연관 업체의 게임 출시 정보 -- \n\n");
    // printf("이름        : %s\n", gameInfo1.friendGame->name);
    // printf("발매 년도   : %d\n", gameInfo1.friendGame->year);
    // printf("가격        : %d\n", gameInfo1.friendGame->price);
    // printf("제작사      : %s\n", gameInfo1.friendGame->company);

    typedef struct GameInfo 게임정보;
    게임정보 game1 = {"한글 게임", 2000, 10, "수연"};
    printf("-- Game1 Info -- \n\n");
    printf("이름        : %s\n", game1.name);
    printf("발매 년도   : %d\n", game1.year);
    printf("가격        : %d\n", game1.price);
    printf("제작사      : %s\n", game1.company);

    GAME_INFO game3;
    game3.name = "game3";
    game3.year = 2022;
    game3.price = 2000;
    game3.company = "PUBG";

    printf("-- Game3 Info -- \n\n");
    printf("이름        : %s\n", game3.name);
    printf("발매 년도   : %d\n", game3.year);
    printf("가격        : %d\n", game3.price);
    printf("제작사      : %s\n", game3.company);

    return 0;
}