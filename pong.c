#include <stdio.h>
#include <unistd.h>  // Это нужно для sleep()

void draw_game(int x_ball, int y_ball, int y_left_pannel, int y_right_pannel, int score_left,
               int score_right);
void clear_screen();
int input_func(int y_left_pannel, int y_right_pannel);
int phisics(int x_ball, int y_ball, int y_left_pannel, int y_right_pannel, int flag);

int main(void) {
    int x_ball = 40;
    int y_ball = 12;  // начальные координаты шарика в центре поля

    int y_left_pannel = 12;
    int y_right_pannel = 12;  // начальные координаты панели (будем определять координату по нижней грани)

    int flag = 3;  // по флагам будем определять направление движения шара
    int input_flag = 0;  // по этому флагу определяем что нам ввел пользователь

    int score_left = 0;
    int score_right = 0;

    printf(
        "Чтобы перемещать ракетки воспользуйтесь клавишами A/Z и K/M, чтобы пропустить ход нажмите пробел\n");
    printf("Are you ready to start? (1/0) ");
    int ans;
    scanf("%d", &ans);
    if (ans == 0) {
        flag = 0;
    }

    while (score_left < 21 && score_right < 21) {
        if (flag == -1 || flag == -2) {  // как бы по новой инициализируем игру
            x_ball = 40;
            y_ball = 12;

            int y_left_pannel = 12;
            int y_right_pannel = 12;
        }
        if (flag == -1) {
            score_left = score_left + 1;
            if (score_left == 21) {
                printf("Победа левого!");
            } else {
                flag = 1;
            }
        }
        if (flag == -2) {
            score_right = score_right + 1;
            if (score_right == 21) {
                printf("Победа правого!");
            } else {
                flag = 9;
            }
        }

        while (flag > 0) {
            draw_game(x_ball, y_ball, y_left_pannel, y_right_pannel, score_left, score_right);

            flag = phisics(x_ball, y_ball, y_left_pannel, y_right_pannel, flag);

            if (flag == 9) {  // летит вправо - вверх
                x_ball = x_ball + 2;
                y_ball = y_ball - 3;
            }
            if (flag == 1) {  // летит влево - вниз
                x_ball = x_ball - 2;
                y_ball = y_ball + 3;
            }
            if (flag == 7) {  // летит влево - вверх
                x_ball = x_ball - 2;
                y_ball = y_ball - 3;
            }
            if (flag == 3) {  // летит вправо - вниз
                x_ball = x_ball + 2;
                y_ball = y_ball + 3;
            }

            input_flag = input_func(y_left_pannel, y_right_pannel);

            if (input_flag == 7) {
                y_left_pannel = y_left_pannel - 2;
            } else if (input_flag == 1) {
                y_left_pannel = y_left_pannel + 2;
            } else if (input_flag == 9) {
                y_right_pannel = y_right_pannel - 2;
            } else if (input_flag == 3) {
                y_right_pannel = y_right_pannel + 2;
            } else {
                printf("Вы ввели недопустимую команду - попробуйте еще раз: ");
                input_flag = input_func(y_left_pannel, y_right_pannel);
            }
        }
    }
    return 0;
}

int input_func(int y_left_pannel, int y_right_pannel) {
    char first, second;
    int input_flag;

    scanf("%c%c", &first, &second);
    if ((first == 'A' || second == 'A') && y_left_pannel > 3) {
        input_flag = 7;  // поднимается вверх
    } else if ((first == 'Z' || second == 'Z') && y_left_pannel < 24) {
        input_flag = 1;  // опускается вниз
    } else if ((second == 'K' || first == 'K') && y_right_pannel > 3) {
        input_flag = 9;  // поднимается вверх
    } else if ((second == 'M' || first == 'M') && y_right_pannel < 24) {
        input_flag = 3;  // опускается вниз
    } else {
        input_flag = 0;
    }

    return input_flag;
}

int phisics(int x_ball, int y_ball, int y_left_pannel, int y_right_pannel, int flag) {
    if (x_ball >= 78) {  // достиг правой границы
        if (y_right_pannel >= y_ball &&
            y_right_pannel - 3 < y_ball) {  // проверка на отрисовку правой рокетки
            if (flag == 9) {  // определяем как к нам прилетел шарик и как его надо отбить
                flag = 7;
            }
            if (flag == 3) {
                flag = 1;
            }
        } else {
            flag = -1;
        }
    }

    if (x_ball <= 2) {  // достиг левой границы
        if (y_left_pannel >= y_ball && y_left_pannel - 3 < y_ball) {  // проверка на отрисовку правой рокетки
            if (flag == 7) {  // определяем как к нам прилетел шарик и как его надо отбить
                flag = 9;
            }
            if (flag == 1) {
                flag = 3;
            }
        } else {
            flag = -2;
        }
    }

    if (y_ball <= 1) {  // достиг верхней границы
        if (flag == 9) {  // определяем как к нам прилетел шарик и как его надо отбить
            flag = 3;
        }
        if (flag == 7) {
            flag = 1;
        }
    }

    if (y_ball >= 24) {  // достиг нижней границы
        if (flag == 3) {  // определяем как к нам прилетел шарик и как его надо отбить
            flag = 9;
        }
        if (flag == 1) {
            flag = 7;
        }
    }

    return flag;
}

void draw_game(int x_ball, int y_ball, int y_left_pannel, int y_right_pannel, int score_left,
               int score_right) {
    clear_screen();
    // отрисовываем поле, предварительно очистив холст!
    for (int i = 0; i < 80; i++) {
        printf("-");
    }
    printf("\n");

    for (int y = 0; y < 25; y++) {
        if (y == y_ball) {  // условие на отрисовку шарика

            if (y_left_pannel >= y && y_left_pannel - 3 < y) {  // проверка на отрисовку левой рокетки
                printf("|");
            } else {
                printf(" ");
            }

            for (int j = 1; j < x_ball; j++) {
                printf(" ");
            }
            printf("*");
            for (int j = x_ball; j < 78; j++) {
                printf(" ");
            }

            if (y_right_pannel >= y && y_right_pannel - 3 < y) {  // проверка на отрисовку правой рокетки
                printf("|");
            } else {
                printf(" ");
            }

            printf("\n");

        } else {
            // printf("|                                                            |");
            if (y_left_pannel >= y && y_left_pannel - 3 < y) {  // проверка на отрисовку левой рокетки
                printf("|");
            } else {
                printf(" ");
            }
            for (int j = 1; j < 79; j++) {
                printf(" ");
            }
            if (y_right_pannel >= y && y_right_pannel - 3 < y) {  // проверка на отрисовку правой рокетки
                printf("|");
            } else {
                printf(" ");
            }

            printf("\n");
        }
    }
    for (int i = 0; i < 80; i++) {
        printf("-");
    }
    printf("\n");

    printf("счет левого игрока: %d                                     ", score_left);
    printf("счет правого игрока: %d", score_right);
    printf("\n");

    // usleep(80000);
}

void clear_screen() {
    printf("\033[2J\033[H");  // ANSI escape codes
}
