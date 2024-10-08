#include <stdio.h>
#include <stdlib.h>

#define FILENAME "lesson_number.txt"

// created 2024/10/8 by YukkiMoru

int main() {
    int lesson_number = 1; // 初期値
    FILE *file;

    // ファイルから前回の lesson_number を読み込む
    file = fopen(FILENAME, "r");
    if (file != NULL) {
        fscanf(file, "%d", &lesson_number);
        fclose(file);
        lesson_number++; // インクリメント
    }

    char command[50];

    // コマンドを作成
    sprintf(command, "mkdir Lesson%d", lesson_number);

    // コマンドを実行
    int result = system(command);

    if (result == 0) {
        printf("Directory 'Lesson%d' created successfully.\n", lesson_number);
    } else {
        printf("Failed to create directory 'Lesson%d'.\n", lesson_number);
    }

    // main.c を Lesson(番号) ディレクトリにコピー
    sprintf(command, "cp main.c Lesson%d/", lesson_number);
    result = system(command);

    if (result == 0) {
        printf("File 'main.c' copied to 'Lesson%d' successfully.\n", lesson_number);
    } else {
        printf("Failed to copy 'main.c' to 'Lesson%d'.\n", lesson_number);
    }

    // 新しい lesson_number をファイルに保存
    file = fopen(FILENAME, "w");
    if (file != NULL) {
        fprintf(file, "%d", lesson_number);
        fclose(file);
    } else {
        printf("Failed to open file to save lesson number.\n");
    }

    return 0;
}