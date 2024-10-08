#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "lesson_number.txt"
#define LOGFILE "readme.md"

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

    char command[100];

    // コマンドを作成
    sprintf(command, "mkdir Lesson%d", lesson_number);

    // コマンドを実行
    int result = system(command);

    if (result == 0) {
        printf("Directory 'Lesson%d' created successfully.\n", lesson_number);
    } else {
        printf("Failed to create directory 'Lesson%d'.\n", lesson_number);
    }

    // 現在の日付を取得
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // ES(月)_(日).c のファイル名を作成
    char filename[50];
    sprintf(filename, "ES%d_%d.c", tm.tm_mon + 1, tm.tm_mday);

    // ES10_8.c を Lesson(番号) ディレクトリにコピー
    sprintf(command, "cp ES10_8.c Lesson%d/%s", lesson_number, filename);
    result = system(command);

    if (result == 0) {
        printf("File 'ES10_8.c' copied to 'Lesson%d/%s' successfully.\n", lesson_number, filename);
    } else {
        printf("Failed to copy 'ES10_8.c' to 'Lesson%d/%s'.\n", lesson_number, filename);
    }

    // 新しい lesson_number をファイルに保存
    file = fopen(FILENAME, "w");
    if (file != NULL) {
        fprintf(file, "%d", lesson_number);
        fclose(file);
    } else {
        printf("Failed to open file to save lesson number.\n");
    }

    // README.md にログを追加
    file = fopen(LOGFILE, "a");
    if (file != NULL) {
        fprintf(file, "\n| %04d/%02d/%02d | Lesson%d | %s |", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday ,lesson_number , filename);
        fclose(file);
    } else {
        printf("Failed to open log file to save log.\n");
    }

    return 0;
}