#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <math.h>
using namespace std;

typedef struct node Node;

struct node
{
	char znak;
	double liczba;
	int prior;
	char nawias;
	Node *next;
	Node *prev;
};

class Kalkulator
{
	string wyraz;
	Node *head;
	Node *tail;
	Node *current;
	Node *temp;
	double wynik;

public:

	Kalkulator(string wyr = "0", Node*h = NULL, Node*t = NULL, Node*c = NULL, Node*te = NULL, double w = 0)
	{
		wyraz = wyr;
		head = h;
		tail = t;
		current = c;
		temp = te;
		wynik = w;
	}

	void ala() {
		cout << "ala";
	}

	void wczytaj()
	{
		cout << "Wpisz co chcesz obliczyc: ";
		cin >> wyraz;
	}



	Node *createzero()
	{
		Node *nev;
		nev = new (Node);
		nev->znak = '0';
		nev->liczba = 0;
		nev->prior = 0;
		nev->nawias = '0';
		nev->next = NULL;
		nev->prev = NULL;

		return nev;
	}



	void addlastzero()
	{
		Node *tmp = createzero();

		if (head == NULL)
			head = tmp;
		else {
			Node *pom = head;
			while (pom->next != NULL)
				pom = pom->next;
			pom->next = tmp;
			tmp->prev = pom;
		}

		tail = tmp;
	}



	void deletecurrent()
	{
		if (current == head) {
			head = (current->next);
			(current->next)->prev = NULL;
		}
		else if (current == tail) {
			tail = (current->prev);
			(current->prev)->next = NULL;
		}
		else {
			(current->next)->prev = (current->prev);
			(current->prev)->next = (current->next);
		}

		delete current;
	}



	void moveleft()
	{
		current = current->prev;
	}



	void moveright()
	{
		current = current->next;
	}



	void showall()
	{
		if (head == NULL)
			cout << "empty!";
		else
		{
			Node *pom = head;
			while (pom->next != NULL)
			{
				cout << "liczba" << pom->liczba;
				cout << "znak" << pom->znak;
				cout << "prior" << pom->prior;
				cout << "nawias" << pom->nawias;
				cout << endl;
				pom = pom->next;
			}
			cout << "liczba" << pom->liczba;
			cout << "znak" << pom->znak;
			cout << "prior" << pom->prior;
			cout << "nawias" << pom->nawias;
			cout << endl;
		}
	}



	int countall()
	{
		int i;
		if (head == NULL)
			i = 0;
		else
		{
			Node *pom = head;
			i = 1;
			while (pom->next != NULL)
			{
				i++;
				pom = pom->next;
			}
		}
		return i;
	}



	int konwertuj()
	{
		wyraz.c_str();
		int dlugosc = 0;
		dlugosc = wyraz.length();
		int nawias_ilosc = 0;
		int nawias_id = 0;
		int n = 0;

		while (n < dlugosc)
		{
			int odkad = n;
			string pom;

			if (wyraz[n] == '(')
			{
				if (wyraz[n + 1] == '-')
				{
					n = n + 2;
					odkad = n;
					while ((wyraz[n] >= '0' && wyraz[n] <= '9') || wyraz[n] == '.')
					{
						n++;
					}
					addlastzero();
					pom = wyraz.substr(odkad, n);
					(tail->liczba) = -(atof(pom.c_str()));
					n++;
					if (wyraz[n] != NULL)
					{
						(tail->znak) = wyraz[n];

						if (wyraz[n] == ')')
						{
							(tail->prior) = 0;
						}
						else if (wyraz[n] == '+' || wyraz[n] == '-')
						{
							(tail->prior) = 1;
							n++;
						}
						else if (wyraz[n] == '*' || wyraz[n] == ':')
						{
							(tail->prior) = 2;
							n++;
						}
						else if (wyraz[n] == '^')
						{
							(tail->prior) = 3;
							n++;
						}
					}
				}

				else
				{
					addlastzero();
					(tail->nawias) = '(';

					nawias_ilosc++;
					nawias_id++;
					(tail->prior) = (3 + nawias_id);

					n++;
				}
			}

			else if (wyraz[n] == ')')
			{
				addlastzero();
				(tail->nawias) = ')';

				(tail->prior) = (3 + nawias_id);
				nawias_id--;

				n++;

				if (wyraz[n] != NULL)
				{
					(tail->znak) = wyraz[n];

					if (wyraz[n] == ')')
						;
					else
						n++;
				}
			}

			else
			{
				while ((wyraz[n] >= '0' && wyraz[n] <= '9') || wyraz[n] == '.')
				{
					n++;
				}
				addlastzero();
				pom = wyraz.substr(odkad, n);
				(tail->liczba) = atof(pom.c_str());
				if (wyraz[n] != NULL)
				{
					(tail->znak) = wyraz[n];

					if (wyraz[n] == ')')
					{
						(tail->prior) = 0;
					}
					else if (wyraz[n] == '+' || wyraz[n] == '-')
					{
						(tail->prior) = 1;
						n++;
					}
					else if (wyraz[n] == '*' || wyraz[n] == ':')
					{
						(tail->prior) = 2;
						n++;
					}
					else if (wyraz[n] == '^')
					{
						(tail->prior) = 3;
						n++;
					}
				}
			}


		}
		return nawias_ilosc;
	}




	void nawias_znajdz_max()
	{
		int maks = 0;
		if (head == NULL)
			cout << "empty!";
		else
		{
			temp = head;
			maks = temp->prior;
			while (temp->next != NULL)
			{
				if ((temp->prior)>maks)
					maks = (temp->prior);
				temp = (temp->next);
			}
			if ((temp->prior)>maks)
				maks = (temp->prior);
		}

		temp = tail;
		while (temp->prior != maks)
		{
			temp = (temp->prev);
		}
	}



	void nawias_licz()
	{
		int prior_temp = temp->prior;

		temp = temp->prev;

		while ((temp->prev)->nawias != '(')
		{
			current = temp;

			while (current->nawias != '(' && (current->prev)->prior >= current->prior && current->znak != '^')
			{
				moveleft();
			}

			if (current->nawias == '(')
			{
				moveright();
			}

			if (current->znak == '+')
				wynik = current->liczba + (current->next)->liczba;
			else if (current->znak == '-')
				wynik = current->liczba - (current->next)->liczba;
			else if (current->znak == '*')
				wynik = current->liczba * (current->next)->liczba;
			else if (current->znak == ':')
				wynik = current->liczba / (current->next)->liczba;
			else if (current->znak == '^')
				wynik = pow(current->liczba, (current->next)->liczba);

			(current->next)->liczba = wynik;

			deletecurrent();
		}
	}



	void nawias_usun()
	{
		current = (temp->prev);
		deletecurrent();

		if ((temp->next)->znak == ')')
		{
			(temp->prior) = 0;
			(temp->znak) = ')';
		}
		else if ((temp->next)->znak == '+' || (temp->next)->znak == '-')
		{
			(temp->prior) = 1;
			(temp->znak) = (temp->next)->znak;
		}
		else if ((temp->next)->znak == '*' || (temp->next)->znak == ':')
		{
			(temp->prior) = 2;
			(temp->znak) = (temp->next)->znak;
		}
		else if ((temp->next)->znak == '^')
		{
			(temp->prior) = 3;
			(temp->znak) = (temp->next)->znak;
		}
		else
		{
			(temp->prior) = 0;
			(temp->znak) = '0';
		}

		current = (temp->next);
		deletecurrent();
	}



	void oblicz()
	{
		int nawias_ilosc = konwertuj();

		if (nawias_ilosc > 0)
		{
			while (nawias_ilosc > 0)
			{
				nawias_znajdz_max();
				nawias_licz();
				nawias_usun();

				nawias_ilosc--;
			}
		}

		int licznik = countall();
		licznik--;

		while (licznik > 0)
		{
			current = tail;

			while (current != head && (current->prev)->prior >= current->prior && current->znak != '^')
			{
				moveleft();
			}

			if (current->znak == '+')
				wynik = current->liczba + (current->next)->liczba;
			else if (current->znak == '-')
				wynik = current->liczba - (current->next)->liczba;
			else if (current->znak == '*')
				wynik = current->liczba * (current->next)->liczba;
			else if (current->znak == ':')
				wynik = current->liczba / (current->next)->liczba;
			else if (current->znak == '^')
				wynik = pow(current->liczba, (current->next)->liczba);

			licznik--;

			(current->next)->liczba = wynik;

			deletecurrent();
		}

		cout << "= " << wynik << endl;
	}



	~Kalkulator()
	{
		if (head != NULL)
			delete head;
	}


};



int main()
{
	Kalkulator k;

	k.wczytaj();
	k.oblicz();

	system("pause");
	return 0;
}





