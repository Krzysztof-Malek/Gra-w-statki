/** @file */
#pragma once

/** Lista list przechwuj¹ca plansze do gry */
typedef struct row {
	int data;			///<stan pola
	struct row* next;	///<adres kolejnej kolumny
	struct row* down;	///<adres kolejnego wiersza
} row_type;

/** Funkcja alokuje pamiêæ pod plansze
@param head g³owa wybranej planszy
@return void
*/
void make_board(row_type* head);

/** Funkcja wyœwietla planszê na ekranie
@param head g³owa wybranej planszy
@return void
*/
void print_board(row_type* head);

/** Funkcja pyta i weryfikuje miejsce wybrane przez gracza
@param head g³owa wybranej planszy
@param copy kopia planszy dla gracza pokazuj¹ca gdzie ju¿ strzela³
@param size wielkoœæ statku
@return int
*/
int choosing_place(row_type* head, row_type* copy, int size);

/** Funkcja zmienia status pola na planszy
@param head g³owa wybranej planszy
@param row wiersz
@param column kolumna
@return void
*/
void change_one(row_type* head, int row, int column);

/** Funkcja sprawdza w któr¹ stronê mo¿na po³o¿yæ resztê statku
@param head g³owa wybranej planszy
@param row wiersz
@param column kolumna
@param size wielkoœæ statku
@param f iloœæ wolnego miejsa w lew¹ stronê
@param f iloœæ wolnego miejsa w dó³
@param f iloœæ wolnego miejsa w praw¹ stronê
@param f iloœæ wolnego miejsa w górê
@return void
*/
void chosing_the_rest_of_the_ship(row_type* head, int row, int column, int size, int f, int s, int t, int fo);

/** Funkcja sprawdza status pola na planszy
@param head g³owa wybranej planszy
@param row wiersz
@param column kolumna
@param state status w postaci liczby
@return int
*/
int check_state(row_type* head, int row, int column, int state);

/** Funkcja wywo³uj¹ca turê gracza
@param P1_board g³owa planszy gracza
@param E1_board g³owa planszy przeciwnika
@param P2_board g³owa planszy drugiego gracza
@param P liczba trafieñ gracza
@return void
*/
void turn(row_type* P1_board, row_type* E1_board, row_type* P2_board, int* P);

/** Funkcja usuwaj¹ca wybran¹ plansze - zwalnianie pamiêci
@param current wybrana plansza
@return void*/
void delete_memory(row_type* current);