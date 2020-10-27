﻿
#include "CardDeckLib.h"
#include <exception>
#include <stdio.h>
#include <ctime>


const char* Rangs[] = { "Двойка", "Тройка", "Четвёрка", "Пятёрка", "Шестёрка", "Семёрка", "Восьмёрка", "Девятка", "Десятка", "Валет", "Дама", "Король", "Туз" };
const char* Suits[] = { "Бубе", "Червей", "Пики", "Крести" };

namespace CardDeckClass {


	/* --------------------------------------------------------- */
	/*				    	  Конструкторы					 	 */
	/* --------------------------------------------------------- */

	/* Пустой конструктор
	 Инициализируется пустая колода */
	CardDeck::CardDeck() {
		for (int i = 0; i < SZ; ++i)
			cards[i] = { '0', '0' };
	}


	/* Инициализирующий конструктор с заданием количества карт, масть и ранг которых определяются случайно
	Выбрасывается исключение, если n > SZ */
	CardDeck::CardDeck(int n) {
		if (n > 1 && n <= SZ) {
			srand(time(NULL));
			for (int i = 0; i < n; ++i) {
				int rang = 49 + rand() % 13;
				int suit = 49 + rand() % 4;
				if (FindCurrentCard(rang, suit) == -1)
					cards[i] = { (char)rang, (char)suit };
				else i--;
			}
			for (int i = n; i < SZ; ++i)
				cards[i] = { '0', '0' };
		}
		else throw std::exception("Неверное количество карт в колоде. Попробуйте еще раз");
	}


	// Инициализирующий конструктор с начальной инициализацией одной карты
	CardDeck::CardDeck(int r, int s) {
		cards[0] = { (char)r, (char)s };
		for (int i = 1; i < SZ; i++)
			cards[i] = { '0','0' };
	}



	/* --------------------------------------------------------- */
	/*				      Сеттеры - set'теры					 */
	/* --------------------------------------------------------- */


	/* Добавить новую карту в колоду с помощью генератора случайных чисел
	Если созданная карта уже существует, состояние создается заново*/
	CardDeck& CardDeck::AddNewCard() {
		int rc;
		srand(time(NULL));
		do {
			int rang = 49 + rand() % 13;
			int suit = 49 + rand() % 4;
			rc = FindCurrentCard(rang, suit);
			if (rc == -1)
				cards[GetCurrentSize()] = { (char)rang, (char)suit };
		} while (rc != -1);
		return *this;
	}


	/* --------------------------------------------------------- */
	/*	     		      Компараторы для qsort					 */
	/* --------------------------------------------------------- */

	// Сравнение ранга двух карт по рангу
	int CardDeck::CompareRang(const void* x1, const void* x2) {
		return (((Card*)x1)->rang - ((Card*)x2)->rang);
	}


	// Сравнение ранга двух карт по масти
	int CardDeck::CompareSuit(const void* x1, const void* x2) {
		return (((Card*)x1)->suit - ((Card*)x2)->suit);
	}

	/* --------------------------------------------------------- */
	/*															 */
	/* --------------------------------------------------------- */

	// Сортировка деки по масти (Бубе -> Черви -> Пики -> Крести)
	CardDeck& CardDeck::SortSuit() {
		qsort(this->cards, GetCurrentSize(), sizeof(Card), CompareSuit);
		return *this;
	}


	// Сортировка деки по условию лабы (по масти: Бубе -> Черви -> Пики -> Крести, и по убыванию рангу) 
	CardDeck& CardDeck::DefaultSort() {
		SortSuit();
		int suit_ends = 0;
		int suit_beginning = 0;
		for (int i = 49; i < 53; i++) {
			if (suit_beginning == GetCurrentSize())
				return *this;
			while (suit_ends < GetCurrentSize() && this->GetCurrentSuit(suit_ends + 1) == i)
				suit_ends++;
			qsort(this->cards + suit_beginning, suit_ends - suit_beginning, sizeof(Card), CompareRang);
			suit_beginning = suit_ends;
		}
		return *this;
	}


	/* --------------------------------------------------------- */
	/*				      Геттеры - get'теры 					 */
	/* --------------------------------------------------------- */


	// Вернуть текущее кол-во карт в деке
	int CardDeck::GetCurrentSize() const {
		for (int i = 0; i < SZ; ++i)
			if ((i == (SZ - 1)) || (cards[i].rang == '0'))
				return i;
	}


	// Поиск конкретной карты в колоде; в случае успеха возвращает индекс массива с этой картой, иначе -1
	int CardDeck::FindCurrentCard(int r, int s) const {
		for (int i = 0; i < SZ; ++i) {
			// Т.к. все карты располагаются в начале, если доходим до пустой ячейки, заканчивем поиск с -1
			if ((cards[i].rang == '0') || (i == (SZ - 1)))
				return -1;
			if (cards[i].rang == r && cards[i].suit == s)
				return i;
		}
		return -1;
	}

	// Получить ранг карты по ее номеру в группе
	int CardDeck::GetCurrentRang(int i) const {
		if (i < 1 || i > GetCurrentSize())
			throw std::exception("Неправильный номер карты (либо больший, либо меньший возможного)");
		return cards[--i].rang;
	}


	// Получить масть карты по ее номеру в группе
	int CardDeck::GetCurrentSuit(int i) const {
		if (i < 1 || i > GetCurrentSize())
			throw std::exception("Неправильный номер карты (либо больший, либо меньший возможного)");
		return cards[i - 1].suit;
	}


	// Получить подгруппу карт заданной масти из текущей деки (Возвращается новый экземпляр класса)
	CardDeck& CardDeck::GetSuitDeck(int s) const {
		if (s < 1 || s > 4)
			throw std::exception("Пожалуйста, выберите существующий ранг: --> ");
		CardDeck res;
		int j = 0;
		for (int i = 0; i < GetCurrentSize(); ++i) {
			if (!this->GetCurrentSuit(i + 1))
				return res;
			if (this->GetCurrentSuit(i + 1) == (s + 48))
				res.cards[j++] = cards[i];
		}
		return res;
	}



	/* --------------------------------------------------------- */
	/*						 Друзья класса 						 */
	/* --------------------------------------------------------- */

	// Ввод состояния деки из входного потока (с возможным выбрасыванием исключения)
	std::istream& operator >> (std::istream& stream, CardDeck& deck) {
		std::cout << "Пожалуйста, введите кол-во карт в колоде: --> ";
		int size;
		input_Type(size);
		if (size > deck.SZ || size < 1)
			throw std::exception("Некорректное число карт (либо больше, либо меньше возможного). Попробуйте еще раз.");
		for (int i = 0; i < size; ++i) {
			std::cout << "Карта #" << i + 1 << ": выберите\n --> 1. Добавить случайную карту\n --> 2. Ввести карту самостоятельно\n";
			int rc = 0;
			input_Type(rc);
			while (rc != 1 && rc != 2) {
				std::cout << "Пожалуйста, выберите 1 или 2: --> ";
				input_Type(rc);
			}

			if (rc == 1) {
				deck.AddNewCard();
				std::cout << "Карта #" << i + 1 << ": Случайная карта успешно добавлена: " << Rangs[deck.cards[i].rang - 49] << ' ' << Suits[deck.cards[i].suit - 49] << '\n';
			}
			else {
				std::cout << "Пожалуйста, выберите ранг карты: 2 - 10; либо 11 - Валет, 12 - Дама, 13 - Король, 14 - Туз: --> ";
				int rang;
				input_Type(rang);
				while (rang < 1 || rang > 14) {
					std::cout << "Пожалуйста, выберите существующий ранг: -->";
					input_Type(rang);
				}
				std::cout << "Пожалуйста, выберите масть карты: 1 - Бубе, 2 - Черви, 3 - Пики, 4 - Крести: --> ";
				int suit;
				input_Type(suit);
				while (suit < 1 || suit > 4) {
					std::cout << "Пожалуйста, выберите существующую масть: -->";
					input_Type(suit);
				}
				if (deck.FindCurrentCard(rang + 47, suit + 48) != -1) {
					throw std::exception("Такая карта уже существует в колоде. Попробуйте заново.");
				}
				else {
					deck.cards[i].rang = rang + 47;
					deck.cards[i].suit = suit + 48;
					std::cout << "Карта #" << i + 1 << " добавлена: " << Rangs[deck.cards[i].rang - 49] << ' ' << Suits[deck.cards[i].suit - 49] << '\n';
				}
			}
		}
		return stream;
	}


	// Вывод текущей деки в выходной поток
	std::ostream& operator << (std::ostream& stream, const CardDeck& deck) {
		if (!deck.GetCurrentSize())
			stream << "Колода пуста.";
		else {
			stream << "Колода:" << std::endl;
			for (int i = 0; i < deck.GetCurrentSize(); ++i) {
				stream << i + 1 << ": " << Rangs[deck.GetCurrentRang(i + 1) - 49] << ' ' << Suits[deck.GetCurrentSuit(i + 1) - 49] << ' ' << std::endl;
			}
		}
		return stream;
	}
}


