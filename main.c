/** @file */
/*
Projekt PK2 - Gra w statki
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "struct.h"
#include "functions.c"

int main() {
	row_type* board_1;
	board_1 = (row_type*)malloc(sizeof(row_type));
	row_type* board_2;
	board_2 = (row_type*)malloc(sizeof(row_type));
	row_type* board_3;
	board_3 = (row_type*)malloc(sizeof(row_type));
	row_type* board_4;
	board_4 = (row_type*)malloc(sizeof(row_type));

	make_board(board_1);
	make_board(board_2);
	make_board(board_3);
	make_board(board_4);
	printf("Player 1 Turn:\n");
	printf("Press enter to continue...\n");
	getchar();
	system("cls");

	printf("                  Player 1\n");
	printf("                 Your Board\n");
	print_board(board_1);

	//Stawianie statków
	char size[2];
	int o = 0;
	int a = 0, b = 0;
	int s4 = 0, s3 = 1, s2 = 2, s1 = 3;
	for (int i = 0; i < 10; i++) {
		do {
			o = 0;
			printf("Wchich size of ship do you want to drop (1-4): ");

			scanf("%s", &size);
			while ((getchar()) != '\n');	//usuwanie resty z buforu input

			if (size[1]) {
				size[0] = '5';
			}

			switch (size[0]) {
			case '1': if (s1 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s1 -= 1;
					break;
			case '2':if (s2 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s2 -= 1;
					break;
			case '3':if (s3 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s3 -= 1;
					break;
			case '4':if (s4 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s4 -= 1;
					break;
			default: {size[0] = 5; printf("Wrong size\n"); }
			}
		} while (size[0] == 5);

		choosing_place(board_1, NULL, (size[0] - 48));

		system("cls");
		printf("                  Player 1\n");
		printf("                 Your Board\n");
		print_board(board_1);
	}
	printf("Press enter to continue...\n");
	getchar();
	Sleep(500);
	getchar();

	system("cls");
	Sleep(500);
	printf("Player 2 Turn:\n");
	printf("Press enter to continue...\n");
	getchar();
	system("cls");
	Sleep(500);

	printf("                  Player 2\n");
	printf("                 Your Board\n");
	print_board(board_3);

	s4 = 0; s3 = 1; s2 = 2; s1 = 3;
	for (int i = 0; i < 10; i++) {
		do {
			printf("Wchich size of ship do you want to drop (1-4): ");
			scanf("%s", &size);
			while ((getchar()) != '\n');

			if (size[1]) {
				size[0] = '5';
			}

			switch (size[0]) {
			case '1': if (s1 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s1 -= 1;
					break;
			case '2':if (s2 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s2 -= 1;
					break;
			case '3':if (s3 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s3 -= 1;
					break;
			case '4':if (s4 < 0) {
				printf("This size was used\n");
				size[0] = 5;
			}
					s4 -= 1;
					break;
			default: {size[0] = 5; printf("Wrong size\n"); }
			}
		} while (size[0] == 5);

		choosing_place(board_3, NULL, (size[0] - 48));

		system("cls");
		printf("                  Player 2\n");
		printf("                 Your Board\n");
		print_board(board_3);
	}
	Sleep(300);
	printf("Press enter to continue...\n");
	getchar();
	getchar();

	//Rozpoczêcie rozgrywki
	int P1_score = 0;
	int P2_score = 0;
	int t = 0;
	Sleep(300);
	system("cls");
	printf("Time for Battle!!!\n");
	printf("Press enter to continue...");
	getchar();
	do {
		system("cls");
		Sleep(300);
		printf("Player 1 turn\n");
		printf("Press enter to continue...");
		getchar();

		Sleep(500);

		do {
			system("cls");

			printf("                  Player 1\n");
			t = P1_score;
			if (P1_score != 20) {
				turn(board_1, board_2, board_3, &P1_score);
			}
		} while (t < P1_score && P1_score != 20);
		printf("Press enter to continue...");
		getchar();
		getchar();

		if (P1_score != 20) {
			Sleep(500);
			system("cls");
			printf("Player 2 turn\n");
			printf("Press enter to continue...");
			getchar();

			do {
				system("cls");

				printf("                  Player 2\n");
				t = P2_score;
				if (P1_score != 20) {
					turn(board_3, board_4, board_1, &P2_score);
				}
			} while (t < P2_score && P2_score != 20);
			printf("Press enter to continue...");
			getchar();
			getchar();
		}
	} while (P1_score != 20 && P2_score != 20);

	if (P1_score == 20) {
		Sleep(500);
		system("cls");
		printf("Player 1 WON!!!\n");
	}
	else {
		Sleep(500);
		system("cls");
		printf("Player 2 WON!!!\n");
	}

	//usuwanie wycieków
	delete_memory(board_1);
	free(board_1);
	getchar();
	delete_memory(board_2);
	free(board_2);
	delete_memory(board_3);
	free(board_3);
	delete_memory(board_4);
	free(board_4);

	return 0;
}