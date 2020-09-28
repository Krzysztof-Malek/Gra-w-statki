/** @file */
#pragma once

/** Lista list przechwuj�ca plansze do gry */
typedef struct row {
	int data;			///<stan pola
	struct row* next;	///<adres kolejnej kolumny
	struct row* down;	///<adres kolejnego wiersza
} row_type;

/** Funkcja alokuje pami�� pod plansze
@param head g�owa wybranej planszy
@return void
*/
void make_board(row_type* head);

/** Funkcja wy�wietla plansz� na ekranie
@param head g�owa wybranej planszy
@return void
*/
void print_board(row_type* head);

/** Funkcja pyta i weryfikuje miejsce wybrane przez gracza
@param head g�owa wybranej planszy
@param copy kopia planszy dla gracza pokazuj�ca gdzie ju� strzela�
@param size wielko�� statku
@return int
*/
int choosing_place(row_type* head, row_type* copy, int size);

/** Funkcja zmienia status pola na planszy
@param head g�owa wybranej planszy
@param row wiersz
@param column kolumna
@return void
*/
void change_one(row_type* head, int row, int column);

/** Funkcja sprawdza w kt�r� stron� mo�na po�o�y� reszt� statku
@param head g�owa wybranej planszy
@param row wiersz
@param column kolumna
@param size wielko�� statku
@param f ilo�� wolnego miejsa w lew� stron�
@param f ilo�� wolnego miejsa w d�
@param f ilo�� wolnego miejsa w praw� stron�
@param f ilo�� wolnego miejsa w g�r�
@return void
*/
void chosing_the_rest_of_the_ship(row_type* head, int row, int column, int size, int f, int s, int t, int fo);

/** Funkcja sprawdza status pola na planszy
@param head g�owa wybranej planszy
@param row wiersz
@param column kolumna
@param state status w postaci liczby
@return int
*/
int check_state(row_type* head, int row, int column, int state);

/** Funkcja wywo�uj�ca tur� gracza
@param P1_board g�owa planszy gracza
@param E1_board g�owa planszy przeciwnika
@param P2_board g�owa planszy drugiego gracza
@param P liczba trafie� gracza
@return void
*/
void turn(row_type* P1_board, row_type* E1_board, row_type* P2_board, int* P);

/** Funkcja usuwaj�ca wybran� plansze - zwalnianie pami�ci
@param current wybrana plansza
@return void*/
void delete_memory(row_type* current);