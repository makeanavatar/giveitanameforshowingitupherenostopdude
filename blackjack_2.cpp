#include <iostream>
#include <string>
#include <random>
#include <math.h>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <conio.h>
using namespace std;

void no_repeat(vector<int> &v);
int add_cards(char hand[], int num_cards);
void display_hand(char phand[][20], int Np[20], char dhand[], int Nd, int Nh);
int split(char phand[][20], int Np);

unsigned long long wallet = 500;
unsigned long long bet = 0;

int main()
{
	while (1)
	{
		system("cls");
		char user;
		int n = 0;
		int Nt = 0;
		int Np[20] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
		int Nd;
		vector<int> v(52);
		char deck[53];
		 // char cards[53] = "88888888888888888888888888888888888888888888889TJQKA";
		char cards[53] = "23456789TJQKA23456789TJQKA23456789TJQKA23456789TJQKA";
		bool check = false;
		bool found = false;
		char phand[20][20];
		char dhand[20];
		int player = 0;
		int dealer = 0;
		int Nh = 1;

		// Shuffle
		no_repeat(v);
		for (int i = 0; i < 52; i++)
		{
			deck[i] = cards[v[i] - 1];
			//cout << deck[i];
		}
		//cout << endl << endl;
		if (wallet < 10)
		{
			cout << "You dont have enough money to play... Leaving the table." << endl;
			system("pause");
			return 0;
		}
		cout << "Cash: $" << wallet << endl;
		cout << "Place bet: ";
		cin >> bet;
		if (bet > wallet)
		{
			cout << "Not enough cash..." << endl;
			goto stop;
		}
		else if (bet < 10)
		{
			cout << "Minimum bet is $10" << endl;
			goto stop;
		}
		system("cls");

		// Initial Deal
		phand[0][0] = deck[0];
		dhand[0] = deck[1];
		phand[0][1] = deck[2];
		dhand[1] = deck[3];
		//Np = 2;
		Nd = 2;
		Nt = 4;
		//display_hand(phand, Np, dhand, 1);
		player = add_cards(phand[0], Np[n]);
		dealer = add_cards(dhand, Nd);
		if (player == 21 && dealer == 21)
		{
			system("cls");
			display_hand(phand, Np, dhand, Nd, 1);
			cout << "PUSH" << endl;
		}
		else if (dealer == 21)
		{
			system("cls");
			display_hand(phand, Np, dhand, Nd, 1);
			cout << "Dealer has blackjack! You lose" << endl;
			wallet -= bet;
		}
		else if (player == 21)
		{
			display_hand(phand, Np, dhand, Nd, 1);
			cout << "You have a blackjack! You win" << endl;
			wallet += bet*1.5;
		}
		else
		{

			// Hit loop ( the BIG LOOP )
			while (n < Nh)
			{split:
				while (!check)
				{
					system("cls");
					display_hand(phand, Np, dhand, 1, Nh);
					cout << "Press Enter to hit\n\"SPACEBAR\" to stand";
					if (Np[n] == 2)
					{
						cout << "\n\"D\" to double down";
						if (phand[0][0] == phand[0][1])
						{
							cout << "\n\"S\" to split";
						}
					}
					cout << ": ";

					user = _getch();
					if (Np[n] == 2)
					{
						if (toupper(user) == 'D')
						{
							bet *= 2;
							check = true;
							user = '\r';

						}
						if (toupper(user) == 'S' && phand[0][0] == phand[0][1])
						{
							Nh++;
							bet *= 2;
							phand[1][0] = phand[0][1];						//split again????????????????????
							phand[0][1] = deck[Nt];
							Nt++;
							phand[1][1] = deck[Nt];
							Nt++;
							goto split;
							//display_hand(phand, Np, dhand, 1, Nh);
							//player = add_cards(phand[0], Np);
							//user = '\r';
						}
					}
					if (user == '\r')
					{
						system("cls");
						Np[n]++;
						phand[n][Np[n] - 1] = deck[Nt];  // NEEDS CARD COUNTER
						Nt++;
						display_hand(phand, Np, dhand, 1, Nh);
						player = add_cards(phand[n], Np[n]);
						if (player == 21)
						{
							check = true;
						}
						if (player > 21)
						{
							found = false;
							for (int i = 0; i < Np[n]; i++)
							{
								if (phand[n][i] == 'A')
								{
									phand[n][i] = '1';
									found = true;
									break;
								}

							}
							if (!found)
							{
								system("cls");
								display_hand(phand, Np, dhand, 2, Nh);
								cout << "YOU BUSTED" << endl;
								wallet -= bet;
								if (Nh > 1)							//FIX THIS -- GOTO STOP......FIND SOLUTION.....
								{
									n++;
									goto split;
								}
								else
									check = true;
							}
							else
							{
								system("cls");
								display_hand(phand, Np, dhand, 1, Nh);
							}
						}
					}
					else if (user == ' ')
					{
						check = true;
					}
					else
					{
						cout << endl << "BAD INPUT" << endl;
						Sleep(1500);
					}
				}
				n++;
			}
			ace:
			Sleep(500);
			system("cls");
			display_hand(phand, Np, dhand, Nd, Nh);
			while (dealer < 17)
			{
				Sleep(1500);
				system("cls");
				Nd++;
				dhand[Nd - 1] = deck[Np[n] + Nd - 1]; //NEEDS CARD COUNTER
				dealer = add_cards(dhand, Nd);
				display_hand(phand, Np, dhand, Nd, Nh);
			}
			if (dealer > 21)
			{
				found = false;
				for (int i = 0; i < Nd; i++)
				{
					if (dhand[i] == 'A')
					{
						dhand[i] = '1';
						found = true;
						break;
					}
				}
				if (!found)
				{
					cout << "DEALER BUSTED" << endl;
					wallet += bet;
				}
				else
				{
					dealer = add_cards(dhand, Nd);
					goto ace;
				}
				
			}
			else if (player > dealer)
			{
				cout << "YOU WIN!" << endl;
				wallet += bet;
			}
			else if (dealer > player)
			{
				cout << "YOU LOSE!" << endl;
				wallet -= bet;
			}
			else
			{
				cout << "PUSH" << endl;
			}
		}
		stop:
		system("pause");
	}
}

void display_hand(char phand[][20], int Np[20], char dhand[], int Nd, int Nh)
{
	cout << "Player hand              Dealers hand               " << "Cash: $" << wallet - bet << endl;
	cout << "_____________________________________               " << "Bet:  $" << bet << endl;
	cout << "    ";
	for (int i = 0; i < Nh; i++)
	{
		for (int j = 0; j < Np[i] ; j++)
		{
			cout << phand[i][j];
		}
		cout << "     ";
	}
	cout << "                        ";
	for (int i = 0; i < Nd; i++)
	{
		cout << dhand[i];
	}
	cout << endl;
}


int add_cards(char hand[], int num_cards)
{
	int total = 0;
	for (int i = 0; i < num_cards; i++)
	{
		if (hand[i] == 'T' || hand[i] == 'J' || hand[i] == 'Q' || hand[i] == 'K')
		{
			total += 10;
		}
		else if (hand[i] == 'A')
		{
			total += 11;
		}
		else
		{
			total += (hand[i] - 48);
		}
	}
	return total;
}

void no_repeat(vector<int> &v)
{
	int n = 0;
	srand(time(NULL));

	while (n < 52)
	{
		int seed = rand() % 53;
		if (find(v.begin(),v.end(),seed) == v.end())
		{
			v[n] = seed;
			n++;
		}
	}
}
		
int split(char phand[],int Np)
{
	char split_hand[20];
	split_hand[0] = phand[0];
	return 0;

}


