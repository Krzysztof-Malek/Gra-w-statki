/** @file */
#pragma once
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

void make_board(row_type* head) { //funkcja tworzy planszê 10x10 alokuj¹c pamiêæ
	int t = 0;
	row_type* current = head;
	for (int j = 0; j < 10; j++) {
		current->data = 0;
		current->next = NULL;
		current->down = NULL;
		for (int i = 0; i < 9; i++) {
			current->down = (row_type*)malloc(sizeof(row_type));
			current = current->down;
			current->data = 0;
			current->next = NULL;
			current->down = NULL;
		}
		current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		if (t < 9) {
			current->next = (row_type*)malloc(sizeof(row_type));
			current = current->next;
			t++;
		}
	}
}

void print_board(row_type* head) { //funkcja wyœwietla planszê na ekranie
	int t = 0;
	printf("     A   B   C   D   E   F   G   H   I   J\n");
	printf("    _______________________________________\n");
	for (int i = 0; i < 10; i++) {
		printf(" %i ", t);
		row_type* current = head;

		for (int j = 0; j < t & t < 10; j++) {
			current = current->next;
		}
		t++;
		printf("|");

		for (int k = 0; k < 10; k++) {
			switch (current->data)
			{
			case 0: printf("   |");
				break;
			case 1: printf(" O |");
				break;
			case 2: printf(" X |");
				break;
			case 3: printf(" # |");
				break;
			default: printf("Error in the lists");
			}
			if (current->down != NULL) {
				current = current->down;
			}
		}
		printf("\n");
	}
	printf("   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
}

int choosing_place(row_type* head, row_type* copy, int size) { //funkcja pyta o pole do postawienia statku lub strza³u a tak¿e wywo³uje funkcje sprawdzaj¹ce stan pola oraz zmieniaj¹ce jego status
	int a = 10;
	int b = 10;
	int c = 0;
	row_type* current = head;
	char place[3];
	do {
		do {
			do {
				if (size != 5) {
					printf("Choose where you want to place ship size %i:\n", size);
					printf("Choose between A-J and 0-9 for example B3: ");
				}
				else {
					printf("Choose coordinates to shoot: ");
				}
				scanf("%s", &place);
				switch (place[0])
				{
				case 'A': case 'a': b = 0;
					break;
				case 'B': case 'b': b = 1;
					break;
				case 'C': case 'c': b = 2;
					break;
				case 'D': case 'd': b = 3;
					break;
				case 'E': case 'e': b = 4;
					break;
				case 'F': case 'f': b = 5;
					break;
				case 'G': case 'g': b = 6;
					break;
				case 'H': case 'h': b = 7;
					break;
				case 'I': case 'i': b = 8;
					break;
				case 'J': case 'j': b = 9;
					break;
				default: printf("Wrong letter, choose again\n");
				}
			} while (b > 9);
			switch (place[1])
			{
			case '0': a = 0;
				break;
			case '1': a = 1;
				break;
			case '2': a = 2;
				break;
			case '3': a = 3;
				break;
			case '4': a = 4;
				break;
			case '5': a = 5;
				break;
			case '6': a = 6;
				break;
			case '7': a = 7;
				break;
			case '8': a = 8;
				break;
			case '9': a = 9;
				break;
			default: printf("Wrong number, choose again\n");
			}
		} while (a > 9);

		if (size == 5) {
			if (!check_state(head, a, b, 0)) {
				Sleep(500);
				system("cls");
				printf("Miss!!!\n");
				Sleep(3000);
				change_one(head, a, b, 1);
				change_one(copy, a, b, 1);
				return 0;
			}
			else if (!check_state(head, a, b, 3)) {
				Sleep(500);
				system("cls");
				printf("Hit!!!\n");
				Sleep(3000);
				change_one(head, a, b, 2);
				change_one(copy, a, b, 2);
				return 1;
			}
			else {
				printf("Choose another spot!!!\n");
				int c = 1;
			}
		}
		else if (c = check_state(head, a, b, 3)) {
			size -= 1;
			//first
			int f = 0;
			if (b - size > -1) {
				for (int i = b; i > b - size; i--) {
					f += check_state(head, a, i - 1, 3);
				}
			}
			//second
			int s = 0;
			if (a + size < 10) {
				for (int i = a; i < a + size; i++) {
					s += check_state(head, i + 1, b, 3);
				}
			}
			//third
			int t = 0;
			if (b + size < 10) {
				for (int i = b; i < b + size; i++) {
					t += check_state(head, a, i + 1, 3);
				}
			}
			//fourth
			int fo = 0;
			if (a - size > -1) {
				for (int i = a; i > a - size; i--) {
					fo += check_state(head, i - 1, b, 3);
				}
			}
			if (f < size && s < size && t < size && fo < size) {
				printf("You can't place a ship here!!!\n");
				c = 0;
			}
			if (c) {
				change_one(head, a, b, 3);
				system("cls");
				print_board(head);
				if (size != 0) {
					chosing_the_rest_of_the_ship(head, a, b, size, f, s, t, fo);
				}
			}
		}
	} while (!c);
	return 0;
}

void change_one(row_type* head, int row, int column, int value) {//funckcja zmienia status pola
	row_type* current = head;

	for (int i = 0; i < row; i++) {
		current = current->next;
	}
	for (int i = 0; i < column; i++) {
		current = current->down;
	}
	current->data = value;
}

void chosing_the_rest_of_the_ship(row_type* head, int row, int column, int size, int f, int s, int t, int fo) {//funkcja sprawdz¹ w któr¹ stronê mo¿na po³o¿yæ resztê statku
	char first[3];
	char second[3];
	char third[3];
	char fourth[3];
	char place[3];

	printf("In which way must ship go (choose from listed coordinates)\n");

	if ((column -= size) > -1) {
		//first
		if (f == size) {
			switch (column)
			{
			case 0: first[0] = 65;
				break;
			case 1: first[0] = 66;
				break;
			case 2: first[0] = 67;
				break;
			case 3: first[0] = 68;
				break;
			case 4: first[0] = 69;
				break;
			case 5: first[0] = 70;
				break;
			case 6: first[0] = 71;
				break;
			case 7: first[0] = 72;
				break;
			case 8: first[0] = 73;
				break;
			case 9: first[0] = 74;
				break;
			default: printf("Error 1\n");
			}
			switch (row)
			{
			case 0: first[1] = 48;
				break;
			case 1: first[1] = 49;
				break;
			case 2: first[1] = 50;
				break;
			case 3: first[1] = 51;
				break;
			case 4: first[1] = 52;
				break;
			case 5: first[1] = 53;
				break;
			case 6: first[1] = 54;
				break;
			case 7: first[1] = 55;
				break;
			case 8: first[1] = 56;
				break;
			case 9: first[1] = 57;
				break;
			default: printf("Error 3\n");
			}
			printf("%c%c\n", first[0], first[1]);
		}
	}
	//second
	column += size;
	if ((row += size) < 10) {
		if (s == size) {
			switch (column)
			{
			case 0: second[0] = 65;
				break;
			case 1: second[0] = 66;
				break;
			case 2: second[0] = 67;
				break;
			case 3: second[0] = 68;
				break;
			case 4: second[0] = 69;
				break;
			case 5: second[0] = 70;
				break;
			case 6: second[0] = 71;
				break;
			case 7: second[0] = 72;
				break;
			case 8: second[0] = 73;
				break;
			case 9: second[0] = 74;
				break;
			default: printf("Error 2\n");
			}
			switch (row)
			{
			case 0: second[1] = 48;
				break;
			case 1: second[1] = 49;
				break;
			case 2: second[1] = 50;
				break;
			case 3: second[1] = 51;
				break;
			case 4: second[1] = 52;
				break;
			case 5: second[1] = 53;
				break;
			case 6: second[1] = 54;
				break;
			case 7: second[1] = 55;
				break;
			case 8: second[1] = 56;
				break;
			case 9: second[1] = 57;
				break;
			default: printf("Error 3\n");
			}
			printf("%c%c\n", second[0], second[1]);
		}
	}
	row -= size;
	if ((column += size) < 10) {
		//third

		if (t == size) {
			switch (column)
			{
			case 0: third[0] = 65;
				break;
			case 1: third[0] = 66;
				break;
			case 2: third[0] = 67;
				break;
			case 3: third[0] = 68;
				break;
			case 4: third[0] = 69;
				break;
			case 5: third[0] = 70;
				break;
			case 6: third[0] = 71;
				break;
			case 7: third[0] = 72;
				break;
			case 8: third[0] = 73;
				break;
			case 9: third[0] = 74;
				break;
			default: printf("Error 3\n");
			}

			switch (row)
			{
			case 0: third[1] = 48;
				break;
			case 1: third[1] = 49;
				break;
			case 2: third[1] = 50;
				break;
			case 3: third[1] = 51;
				break;
			case 4: third[1] = 52;
				break;
			case 5: third[1] = 53;
				break;
			case 6: third[1] = 54;
				break;
			case 7: third[1] = 55;
				break;
			case 8: third[1] = 56;
				break;
			case 9: third[1] = 57;
				break;
			default: printf("Error 3\n");
			}
			printf("%c%c\n", third[0], third[1]);
		}
	}
	//fourth
	column -= size;
	if ((row -= size) > -1) {
		if (fo == size) {
			switch (column)
			{
			case 0: fourth[0] = 65;
				break;
			case 1: fourth[0] = 66;
				break;
			case 2: fourth[0] = 67;
				break;
			case 3: fourth[0] = 68;
				break;
			case 4: fourth[0] = 69;
				break;
			case 5: fourth[0] = 70;
				break;
			case 6: fourth[0] = 71;
				break;
			case 7: fourth[0] = 72;
				break;
			case 8: fourth[0] = 73;
				break;
			case 9: fourth[0] = 74;
				break;
			default: printf("Error 4\n");
			}
			switch (row)
			{
			case 0: fourth[1] = 48;
				break;
			case 1: fourth[1] = 49;
				break;
			case 2: fourth[1] = 50;
				break;
			case 3: fourth[1] = 51;
				break;
			case 4: fourth[1] = 52;
				break;
			case 5: fourth[1] = 53;
				break;
			case 6: fourth[1] = 54;
				break;
			case 7: fourth[1] = 55;
				break;
			case 8: fourth[1] = 56;
				break;
			case 9: fourth[1] = 57;
				break;
			default: printf("Error 3\n");
			}
			printf("%c%c\n", fourth[0], fourth[1]);
		}
	}
	row += size;
	do {
		scanf("%s", &place);
		if ((place[0] == first[0] || place[0] - 32 == first[0]) && place[1] == first[1]) {
			for (int i = 0; i < size; i++) {
				column -= 1;
				change_one(head, row, column, 3);
			}
			return;
		}
		else if ((place[0] == second[0] || (place[0] - 32) == second[0]) && place[1] == second[1]) {
			for (int i = 0; i < size; i++) {
				row += 1;
				change_one(head, row, column, 3);
			}
			return;
		}
		else if ((place[0] == third[0] || (place[0] - 32) == third[0]) && place[1] == third[1]) {
			for (int i = 0; i < size; i++) {
				column += 1;
				change_one(head, row, column, 3);
			}
			return;
		}
		else if ((place[0] == fourth[0] || (place[0] - 32) == fourth[0]) && place[1] == fourth[1]) {
			for (int i = 0; i < size; i++) {
				row -= 1;
				change_one(head, row, column, 3);
			}
			return;
		}
		else {
			printf("You choosed wrong coordintaes, try again\n");
		}
	} while (1);
}

int check_state(row_type* head, int row, int column, int state) {//funkcja sprawdza stan pola
	row_type* current = head;

	for (int i = 0; i < row; i++) {
		current = current->next;
	}
	for (int i = 0; i < column; i++) {
		current = current->down;
	}
	if (current->data == state) {
		return 0;
	}
	else {
		return 1;
	}
}

void turn(row_type* P1_board, row_type* E1_board, row_type* P2_board, int* P) {//funkcja wywo³uj¹ca turê przeciwnika (wyœwietla planszê i wyso³uje funkcje do oddania strza³u)
	printf("                 Your Board\n");
	print_board(P1_board);
	printf("                 Enemy Board\n");
	print_board(E1_board);

	*P += choosing_place(P2_board, E1_board, 5);

	printf("                 Your Board\n");
	print_board(P1_board);
	printf("                 Enemy Board\n");
	print_board(E1_board);
}

void delete_memory(row_type* current) {//funkcja zwalnia pamiêæ
	do {
		if (current->next == NULL) {
			if (current->down == NULL) {
			}
			else {
				delete_memory(current->down);
				free(current->down);
				current->down = NULL;
			}
		}
		else {
			delete_memory(current->next);
			if (current->next->down == NULL) {
				free(current->next);
				current->next = NULL;
			}
		}
	} while (current->down != NULL);
}