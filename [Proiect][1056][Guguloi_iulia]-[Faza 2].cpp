#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <list>
using namespace std;

enum perioadaZi { micDejun = 1, pranz = 2, cina = 3 };
class fisiere {
	virtual void writeToFile(fstream& f) = 0;
	virtual void readFromFile(fstream& f) = 0;
};
class MateriiPrime {
	char* ingredient;
	float cantitate = 0;


public:
	MateriiPrime() {
		this->ingredient = nullptr;
		this->cantitate = 0;
	}
	MateriiPrime(const char* ingredient, float cantitate) {
		this->ingredient = new char[strlen(ingredient) + 1];
		strcpy(this->ingredient, ingredient);
		if (cantitate >= 0) {
			this->cantitate = cantitate;
		}
	}
	MateriiPrime(const MateriiPrime& mp) {
		this->ingredient = new char[strlen(mp.ingredient) + 1];
		strcpy(this->ingredient, mp.ingredient);
		if (mp.cantitate >= 0) {
			this->cantitate = mp.cantitate;
		}
	}

	void afisareMateriiPrime() {
		cout << "\n--------Lista--Ingrediente--------";
		cout << "\nIngredient: " << this->ingredient;
		cout << "\nCantitatea:" << this->cantitate;
		cout << "\n------------------------------";
	}
	friend ostream& operator<<(ostream& out, const MateriiPrime& mp) {
		out << "\n--------Lista--Ingrediente--------";
		out << "\nIngredient: " << mp.ingredient;
		out << "\nCantitatea:" << mp.cantitate;
		out << "\n------------------------------";
		return out;
	}
	void citireMateriiPrime() {
		if (this->ingredient != nullptr) {
			delete[] this->ingredient;
			this->ingredient = nullptr;
		}
		cout << "\nIntroduceti ingredientul: ";
		char buffer[100];
		cin >> buffer;
		this->ingredient = new char[strlen(buffer) + 1];
		strcpy(this->ingredient, buffer);
		cout << "\nIntroduceti cantitatea: ";
		cin >> this->cantitate;
	}
	friend istream& operator>>(istream& in, MateriiPrime& mp) {
		if (mp.ingredient != nullptr) {
			delete[] mp.ingredient;
			mp.ingredient = nullptr;
		}
		cout << "\nIntroduceti ingredientul: ";
		char buffer[100];
		in >> buffer;
		mp.ingredient = new char[strlen(buffer) + 1];
		strcpy(mp.ingredient, buffer);
		cout << "\nIntroduceti cantitatea: ";
		in >> mp.cantitate;
		return in;
	}
	MateriiPrime& operator=(const MateriiPrime& mp) {
		if (this != &mp) {
			delete[] this->ingredient;
			this->ingredient = nullptr;
			this->ingredient = new char[strlen(mp.ingredient) + 1];
			strcpy(this->ingredient, mp.ingredient);
			if (mp.cantitate >= 0) {
				this->cantitate = mp.cantitate;
			}
		}
		return *this;
	}
	
	void setIngredient(const char* ingredient) {
		if (ingredient != nullptr) {
			delete[] this->ingredient;
			this->ingredient = nullptr;
			this->ingredient = new char[strlen(ingredient) + 1];
			strcpy(this->ingredient, ingredient);
		}
	}
	char* getIngredient() {
		return this->ingredient;
	}
	void setCantitate(float cantitate) {
		this->cantitate = cantitate;
	}
	float getCantitate() {
		return this->cantitate;
	}
	float actualizareCantitate() {
		if (this->cantitate > 0)
			return this->cantitate--;
	}
	MateriiPrime& operator--() {
		if (this->cantitate > 0)
			this->cantitate--;
		return *this;
	}
	MateriiPrime operator--(int) {
		MateriiPrime copie = *this;
		this->cantitate--;
		return copie;
	}

	friend bool operator<(const MateriiPrime& mp1, const MateriiPrime& mp2) {
		return mp1.cantitate < mp2.cantitate;
	}

	friend ofstream& operator<<(ofstream& outf, const MateriiPrime& mp) {
		outf.open("ingrediente.txt", ios::out);
		if(outf){
		outf << mp.ingredient;
		outf << mp.cantitate;
		}
		outf.close();
		return outf;
	}
	friend ifstream &operator>>(ifstream& in, MateriiPrime& mp) {
		if (mp.ingredient != nullptr) {
			delete[] mp.ingredient;
			mp.ingredient = nullptr;
		}
		cout << "Ingredintul: ";
		char buffer[100];
		in >> buffer;
		mp.ingredient = new char[strlen(buffer) + 1];
		strcpy(mp.ingredient, buffer);
		cout << "Cantitatea: ";
		in >> mp.cantitate;
		return in;
	}

	void writeToFile(fstream& f) {
		int lg = strlen(this->ingredient);
		f.write((char*)&lg, sizeof(int));
		f.write(this->ingredient, lg);
		f.write((char*)&this->cantitate, sizeof(float));
	}
	void readFromFile(fstream& f) {
		if (this->ingredient != nullptr) {
			delete[]this->ingredient;
		}
		int lg = 0;
		f.read((char*)&lg, sizeof(lg));
		this->ingredient = new char[lg + 1];
		f.read(this->ingredient, lg+1 );
		f.read((char*)&this->cantitate, sizeof(float));
	}
	
	~MateriiPrime() {
		if (this->ingredient != nullptr) {
			delete[] this->ingredient;
			this->ingredient = nullptr;
		}
	}
};



class Produs:public fisiere {
	string felMancare = "Anonim";
	float pret = 0;
	int nrIngrediente = 0;
	MateriiPrime** ingrediente = nullptr;
	unsigned int timpPreparare = 0;

public:
	Produs() {

	}
	Produs(string felMancare, float pret) {
		this->felMancare = felMancare;
		this->pret = pret;
	}
	Produs(string felMancare, float pret, int nrIngrediente, MateriiPrime** ingrediente, unsigned int timpPreparare) {
		this->felMancare = felMancare;
		this->pret = pret;
		this->timpPreparare = timpPreparare;
		if (nrIngrediente > 0 && ingrediente != nullptr) {

			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new MateriiPrime * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->ingrediente[i] = new MateriiPrime(*ingrediente[i]);
			}
		}
	}
	Produs(const Produs& p) {
		this->felMancare = p.felMancare;
		this->pret = p.pret;
		this->timpPreparare = p.timpPreparare;
		if (p.nrIngrediente > 0 && p.ingrediente != nullptr) {

			this->nrIngrediente = p.nrIngrediente;
			this->ingrediente = new MateriiPrime * [p.nrIngrediente];
			for (int i = 0; i < p.nrIngrediente; i++)
			{
				this->ingrediente[i] = new MateriiPrime(*p.ingrediente[i]);
			}
		}

	}
	void setFelMancare(string felMancare) {
		this->felMancare = felMancare;
	}
	string getfelMancare() {
		return this->felMancare;
	}
	void setPret(float pret) {
		this->pret = pret;
	}
	float getPret() {
		return this->pret;
	}
	void setNrIngrediente(int nrIngrediente) {
		this->nrIngrediente = nrIngrediente;
	}
	int getNrIngrediente() {
		return this->nrIngrediente;
	}
	void setIngrediente(int nrIngrediente, MateriiPrime** ingrediente) {
		if (ingrediente != nullptr && nrIngrediente > 0) {
			delete[]this->ingrediente;
			this->ingrediente = nullptr;
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new MateriiPrime * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->ingrediente[i] = new MateriiPrime(*ingrediente[i]);
			}
		}
	}
	MateriiPrime** getIngrediente()
	{
		return this->ingrediente;
	}
	void setTimpPreparare(int timpPreparare) {
		this->timpPreparare = timpPreparare;
	}
	int getTimpPreparare() {
		return this->timpPreparare;
	}
	void actualizareProduse() {

		for (int i = 0; i < this->nrIngrediente; i++)
		{

			this->ingrediente[i]->actualizareCantitate();
		}

	}

	Produs& operator=(const Produs& p) {
		if (this != &p) {
			delete[] this->ingrediente;
			this->ingrediente = nullptr;
			this->felMancare = p.felMancare;
			this->pret = p.pret;
			this->timpPreparare = p.timpPreparare;
			if (p.nrIngrediente > 0 && p.ingrediente != nullptr) {

				this->nrIngrediente = p.nrIngrediente;
				this->ingrediente = new MateriiPrime * [p.nrIngrediente];
				for (int i = 0; i < p.nrIngrediente; i++)
				{
					this->ingrediente[i] = new MateriiPrime(*p.ingrediente[i]);
				}
			}
		}
		return *this;
	}
	void afisareProdus() {
		cout << "\n---Produs-----";
		cout << "\nDenumire fel de mancare: " << this->felMancare;
		cout << "\nPret: " << this->pret << " lei";
		cout << "\nNumar ingrediente: " << this->nrIngrediente;
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			cout << "\nIngrediente:" << *this->ingrediente[i];
		}
		cout << "\nTimp de Preparare: " << this->timpPreparare;
	}
	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n---Produs-----";
		out << "\nDenumire fel de mancare: " << p.felMancare;
		out << "\nPret: " << p.pret << " lei";
		out << "\nNumar ingrediente: " << p.nrIngrediente;
		for (int i = 0; i < p.nrIngrediente; i++)
		{
			out << "\nIngrediente:" << *p.ingrediente[i];
		}
		out << "\nTimp de Preparare: " << p.timpPreparare;
		return out;
	}
	void citireProdus() {
		if (this->ingrediente != nullptr)
		{
			delete[] this->ingrediente;
			this->ingrediente = nullptr;

		}
		cout << "\nIntroduceti felul de mancare: ";
		string buffer;
		cin >> buffer;
		this->setFelMancare(buffer);
		cout << "\nIntrofuceti Pretul: ";
		cin >> this->pret;
		cout << "\nIntroduceti nr ingrediente: ";
		cin >> this->nrIngrediente;
		cout << "\nIntroduceti ingredientele: ";
		this->ingrediente = new MateriiPrime * [this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			MateriiPrime* mp = new MateriiPrime();
			cin >> *mp;
			this->ingrediente[i] = mp;
		}
		cout << "\nIntroduceti timpul preparare: ";
		cin >> this->timpPreparare;
	}
	friend istream& operator>>(istream& in, Produs& p) {
		if (p.ingrediente != nullptr)
		{
			delete[] p.ingrediente;
			p.ingrediente = nullptr;

		}
		cout << "\nIntroduceti felul de mancare: ";
		string buffer;
		in >> buffer;
		p.setFelMancare(buffer);
		cout << "\nIntrofuceti Pretul: ";
		in >> p.pret;
		cout << "\nIntroduceti nr ingrediente: ";
		in >> p.nrIngrediente;
		cout << "\nIntroduceti ingredientele: ";
		p.ingrediente = new MateriiPrime * [p.nrIngrediente];
		for (int i = 0; i < p.nrIngrediente; i++)
		{
			MateriiPrime* mp = new MateriiPrime();
			in >> *mp;
			p.ingrediente[i] = mp;
		}
		cout << "\nIntroduceti timpul preparare: ";
		in >> p.timpPreparare;
		return in;
	}
	Produs operator+(float pret) {
		Produs copy = *this;
		copy.pret += pret;
		return copy;
	}
	friend bool operator==(Produs p, Produs p1)
	{
		if (p.timpPreparare == p1.timpPreparare)
			return true;
		else
			return false;
	}
	~Produs() {
		if (this->ingrediente != nullptr)
		{
			delete[] this->ingrediente;
			this->ingrediente = nullptr;

		}
	}
	bool verificareStoc() {
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			if (this->ingrediente[i]->getCantitate() == 0) {

				cout << "\nNu mai exista in stoc ingredientul" << *this->getIngrediente()[i];
				return false;
			}
			else
				return true;
		}

	}

	friend ofstream& operator<<(ofstream& out, const Produs& p) {
		
		out << p.felMancare;
		out << p.pret;
		out << p.nrIngrediente;
		for (int i = 0; i < p.nrIngrediente; i++)
		{
			out << *p.ingrediente[i];
		}
		out << p.timpPreparare;
		return out;
	}

	virtual void writeToFile(fstream& f) {
		int lg = this->felMancare.size()+1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->felMancare.data(), lg);
		f.write((char*)&this->pret, sizeof(float));
		f.write((char*)&this->nrIngrediente, sizeof(int));
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			this->ingrediente[i]->writeToFile(f);
		}
		f.write((char*)&this->timpPreparare, sizeof(int));
	}

	virtual void readFromFile(fstream& f) {
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buffer;
		buffer = new char[lg];
		f.read(buffer,lg);
		this->felMancare = buffer;
		delete[]buffer;
		buffer = nullptr;
		f.read((char*)&this->pret, sizeof(float));
		f.read((char*)&this->nrIngrediente, sizeof(int));
		if (this->ingrediente != nullptr) {
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				delete this->ingrediente[i];
			}
			delete[]this->ingrediente;
		}
			this->ingrediente = new MateriiPrime * [this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->ingrediente[i] = new MateriiPrime();
				this->ingrediente[i]->readFromFile(f);
			}
			f.read((char*)&this->timpPreparare, sizeof(int));
	}

	friend class Meniu;

};

class ProdusDulce :public Produs, public fisiere {
	int nivelZahar=0;
	bool contineGluten;
	string tipZahar;
public:
	ProdusDulce() :Produs() {

	}
	ProdusDulce(string felMancare, float pret, int nrIngrediente, MateriiPrime** ingrediente, unsigned int timpPreparare, int nivelZahar, bool contineGluten,string tipZahar):Produs(felMancare,pret,nrIngrediente,ingrediente,timpPreparare) {
		this->nivelZahar = nivelZahar;
		this->contineGluten = contineGluten;
		this->tipZahar = tipZahar;
	}
	ProdusDulce(const ProdusDulce& pd):Produs(pd) {
		nivelZahar = pd.nivelZahar;
		contineGluten = pd.contineGluten;
		tipZahar = pd.tipZahar;
	}
	friend ostream& operator<<(ostream& out, const ProdusDulce& pd) {
		out << (Produs&)pd;
		out << "\nNivelul de zahar: " << pd.nivelZahar<<" %";
		out << "\nContineGluten: " << pd.contineGluten;
		out << "\nTipul de zahar:" << pd.tipZahar;
		return out;
	}

	void writeToFile(fstream& f) {
		Produs::writeToFile(f);
		f.write((char*)&nivelZahar, sizeof(int));
		f.write((char*)&contineGluten, sizeof(bool));
		int lg =tipZahar.size()+1;
		f.write((char*)&lg, sizeof(int));
		f.write(tipZahar.data(), lg);
	}
	void readFromFile(fstream& f) {
		Produs::readFromFile(f);
		f.read((char*)&nivelZahar, sizeof(int));
		f.read((char*)&contineGluten, sizeof(bool));
		int lg = 0;
		f.read((char*)&lg, sizeof(int));
		char* buffer;
		buffer = new char[lg];
		f.read(buffer, lg);
		tipZahar = buffer;
		delete[]buffer;
		buffer = nullptr;
	}
	friend ofstream& operator<<(ofstream& out, const ProdusDulce& pd){
		out << (Produs&)(pd);
		out << "\nNivelul de zahar: " << pd.nivelZahar << " %";
		out << "\nContineGluten: " << pd.contineGluten;
		out << "\nTipul de zahar:" << pd.tipZahar;
		return out;
	}
	~ProdusDulce() {

	}
	
};

class Meniu {
	const int id;
	int nrFeluriMancare = 0;
	perioadaZi* per;
	int nrPer = 0;
	Produs** listaFeluriMancare = nullptr;
public:
	Meniu(int id) :id(id) {

	}
	Meniu() :id(0) {

	}
	Meniu(int id, perioadaZi* per, int nrPer, int nrFeluriMancare, Produs** listaFeluriMancare) :id(id) {
		if (per != nullptr && nrPer > 0) {
			this->nrPer = nrPer;
			this->per = new perioadaZi[this->nrPer];
			for (int i = 0; i < this->nrPer; i++)
			{
				this->per[i] = per[i];
			}
		}

		if (listaFeluriMancare != nullptr && nrFeluriMancare > 0) {
			this->nrFeluriMancare = nrFeluriMancare;
			this->listaFeluriMancare = new Produs * [this->nrFeluriMancare];
			for (int i = 0; i < this->nrFeluriMancare; i++)
			{
				this->listaFeluriMancare[i] = new Produs(*listaFeluriMancare[i]);
			}
		}
	}
	Meniu(const Meniu& m) :id(m.id) {
		if (m.per != nullptr && m.nrPer > 0) {
			this->nrPer = m.nrPer;
			this->per = new perioadaZi[this->nrPer];
			for (int i = 0; i < this->nrPer; i++)
			{
				this->per[i] = m.per[i];
			}
		}
		if (m.nrFeluriMancare > 0 && m.listaFeluriMancare != nullptr) {
			this->nrFeluriMancare = m.nrFeluriMancare;
			this->listaFeluriMancare = new Produs * [m.nrFeluriMancare];
			for (int i = 0; i < m.nrFeluriMancare; i++)
			{
				this->listaFeluriMancare[i] = new Produs(*m.listaFeluriMancare[i]);
			}
		}
	}
	int getId() {
		return this->id;
	}
	void setNrFeluriMancare(int nrFeluriMancare) {
		this->nrFeluriMancare = nrFeluriMancare;
	}
	int getNrFeluriMancare() {
		return this->nrFeluriMancare;
	}
	void  setListaFeluriMancare(int nrFeluriMancare, Produs** listaFeluriMancare) {
		if (nrFeluriMancare > 0 && listaFeluriMancare != nullptr) {
			delete[]this->listaFeluriMancare;
			this->listaFeluriMancare = nullptr;
			this->nrFeluriMancare = nrFeluriMancare;
			this->listaFeluriMancare = new Produs * [this->nrFeluriMancare];
			for (int i = 0; i < this->nrFeluriMancare; i++)
			{
				this->listaFeluriMancare[i] = new Produs(*listaFeluriMancare[i]);
			}
		}
	}
	Produs** getListaFeluriMancare() {
		return this->listaFeluriMancare;
	}

	void setNrPer(int nrPer) {
		this->nrPer = nrPer;
	}

	int getNrPer() {
		return this->nrPer;
	}

	void setPer(perioadaZi* per, int nrPer) {
		if (per != nullptr && nrPer > 0) {
			delete[]this->per;
			this->per = nullptr;
			this->per = new perioadaZi[this->nrPer];
			for (int i = 0; i < this->nrPer; i++)
			{
				this->per[i] = per[i];
			}
		}
	}

	Meniu& operator=(const Meniu m) {
		if (this != &m) {
			delete[]this->per;
			this->per = nullptr;
			delete[]this->listaFeluriMancare;
			this->listaFeluriMancare = nullptr;
			if (m.per != nullptr && m.nrPer > 0) {
				this->nrPer = m.nrPer;
				this->per = new perioadaZi[this->nrPer];
				for (int i = 0; i < this->nrPer; i++)
				{
					this->per[i] = m.per[i];
				}
			}
			if (m.nrFeluriMancare > 0 && m.listaFeluriMancare != nullptr) {
				this->nrFeluriMancare = m.nrFeluriMancare;
				this->listaFeluriMancare = new Produs * [m.nrFeluriMancare];
				for (int i = 0; i < m.nrFeluriMancare; i++)
				{
					this->listaFeluriMancare[i] = new Produs(*m.listaFeluriMancare[i]);
				}
			}
		}
		return *this;
	}

	int PretMeniu() {
		int sum = 0;
		Produs** p = new Produs * [this->nrFeluriMancare];
		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			p[i] = new Produs(*(listaFeluriMancare[i]));
			sum += (*p[i]).getPret();
		}
		cout << "\n****************************";
		cout << "\nPret Meniu: " << sum;
		return sum;
	}

	void totalTimpPreparare(Produs** p) {
		int sumaTimp = 0;
		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			p[i] = new Produs(*(this->listaFeluriMancare[i]));
			sumaTimp += (*p[i]).timpPreparare;
		}
		cout << "\n****************************";
		cout << "\n Total timp preparare: " << sumaTimp;
	}
	void afisareMeniu() {
		cout << "\n--------Meniu-----------";
		for (int i = 0; i < this->nrPer; i++)
		{
			cout << "\nPerioadaZi: " << this->per[i];
		}
		cout << "\nNr produse: " << this->nrFeluriMancare;
		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			cout << "\nproduse:" << *this->listaFeluriMancare[i];
		}
	}
	friend ostream& operator<<(ostream& out, const Meniu& m) {
		out << "\n--------Meniu-----------";
		out << "\nID: " << m.id;
		for (int i = 0; i < m.nrPer; i++)
		{
			out << "\nPerioadaZi: " << m.per[i];
		}
		out << "\nNr produse: " << m.nrFeluriMancare;
		for (int i = 0; i < m.nrFeluriMancare; i++)
		{
			out << "\nproduse:" << *m.listaFeluriMancare[i];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Meniu& m) {
		if (m.listaFeluriMancare != nullptr)
		{
			delete[]m.listaFeluriMancare;
			m.listaFeluriMancare = nullptr;
		}
		cout << "\nIntroduceti numarul de feluri de mancare: ";
		in >> m.nrFeluriMancare;
		m.listaFeluriMancare = new Produs * [m.nrFeluriMancare];
		for (int i = 0; i < m.nrFeluriMancare; i++)
		{
			Produs* p = new Produs("", 0);
			in >> *p;
			m.listaFeluriMancare[i] = p;
		}
		m.per = new perioadaZi[m.nrPer];
		for (int i = 0; i < m.nrPer; i++)
		{
			int per;
			cout << "\nIntroduceti perioada din zi(mic dejun - 1,pranz - 2, cina - 3 ): ";
			in >> per;
			if (per < 1 || per>3)
				cout << "\nNu exista aceasta perioada";
			else
				m.per[i] = static_cast<perioadaZi>(per);
		}
		return in;
	}
	Produs* operator[](int pozitie) {
		if (pozitie > 0 && pozitie < this->nrFeluriMancare)
		{
			if (this->listaFeluriMancare != nullptr) {
				return this->listaFeluriMancare[pozitie];
			}
		}
	}
	bool verificareProduse() {
		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			if (this->listaFeluriMancare[i]->verificareStoc()) {
				return true;
			}
			else
				return false;
		}

	}
	void actualizareMeniu() {

		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			this->listaFeluriMancare[i]->actualizareProduse();
		}
	}

	friend ofstream& operator<<(ofstream& out, const Meniu& m) {
		out << m.id;
		for (int i = 0; i < m.nrPer; i++)
		{
			out << m.per[i];
		}
		out<< m.nrFeluriMancare;
		for (int i = 0; i < m.nrFeluriMancare; i++)
		{
			out << *m.listaFeluriMancare[i];
		}
		return out;
	}


	~Meniu() {
		if (this->per != nullptr) {
			delete[]this->per;
			this->per = nullptr;
		}
		if (this->listaFeluriMancare != nullptr)
		{
			delete[]this->listaFeluriMancare;
			this->listaFeluriMancare = nullptr;
		}
	}
};

class Comanda {
	const int id;
	int nrFeluriMancare = 0;
	Meniu** feluriMancare = nullptr;
	static int costDesertGratis;
	unsigned int timpLivrare = 0;
public:

	Comanda(int id) :id(id) {
	}
	Comanda() :id(0) {
	}
	Comanda(int id, int nrFeluriMancare, Meniu** feluriMancare) :id(id) {
		if (nrFeluriMancare > 0 && feluriMancare != nullptr) {
			this->nrFeluriMancare = nrFeluriMancare;
			this->feluriMancare = new Meniu * [this->nrFeluriMancare];
			for (int i = 0; i < this->nrFeluriMancare; i++)
			{
				this->feluriMancare[i] = new Meniu(*feluriMancare[i]);
			}
		}
	}
	Comanda(const Comanda& c) :id(c.id) {
		if (c.nrFeluriMancare > 0 && c.feluriMancare != nullptr) {
			this->nrFeluriMancare = c.nrFeluriMancare;
			this->feluriMancare = new Meniu * [this->nrFeluriMancare];
			for (int i = 0; i < this->nrFeluriMancare; i++)
			{
				this->feluriMancare[i] = new Meniu(*c.feluriMancare[i]);
			}
		}
	}
	static void setCostDesertGratis(int costDesertGratis) {
		if (costDesertGratis > 0) {
			Comanda::costDesertGratis = costDesertGratis;
		}
	}
	static int getCostDesertGratis() {
		return Comanda::costDesertGratis;
	}
	void setNrFeluriMancare(int nrFeluriMancare) {
		this->nrFeluriMancare = nrFeluriMancare;
	}
	int getNrFeluriMancare() {
		return this->nrFeluriMancare;
	}
	void setTimpLivrare(unsigned int timpLivrare) {
		this->timpLivrare = timpLivrare;
	}
	unsigned int getTimpLivrare() {
		return this->timpLivrare;
	}
	Meniu** getFeluriMancare() {
		return this->feluriMancare;
	}
	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			delete[]this->feluriMancare;
			this->feluriMancare = nullptr;
			if (c.nrFeluriMancare > 0 && c.feluriMancare != nullptr) {
				this->nrFeluriMancare = c.nrFeluriMancare;
				this->feluriMancare = new Meniu * [this->nrFeluriMancare];
				for (int i = 0; i < this->nrFeluriMancare; i++)
				{
					this->feluriMancare[i] = new Meniu(*c.feluriMancare[i]);
				}
			}
		}
		return *this;
	}
	void afisareComanda() {
		cout << "\n----------------COMANDA------------------";
		cout << "\nComanda: " << this->id;
		if (this->nrFeluriMancare >= 0 && this->feluriMancare != nullptr) {
			cout << "\nNr feluri mancare: " << this->nrFeluriMancare;
			for (int i = 0; i < this->nrFeluriMancare; i++)
			{
				cout << "\n" << *this->feluriMancare[i];
			}
		}
		cout << "\nTimp livrare:" << this->timpLivrare;
	}
	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << "\n----------------COMANDA------------------";
		out << "\nComanda: " << c.id;
		if (c.nrFeluriMancare >= 0 && c.feluriMancare != nullptr) {
			out << "\nNr feluri mancare: " << c.nrFeluriMancare;
			for (int i = 0; i < c.nrFeluriMancare; i++)
			{
				out << "\n" << *c.feluriMancare[i];
			}
		}
		out << "\nTimp livrare:" << c.timpLivrare;
		return out;
	}
	void citireComanda() {
		if (this->feluriMancare != nullptr) {
			delete[]this->feluriMancare;
			this->feluriMancare = nullptr;
		}
		cout << "\nNr meniuri: ";
		cin >> this->nrFeluriMancare;
		this->feluriMancare = new Meniu * [this->nrFeluriMancare];
		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			Meniu* m = new Meniu(0);
			cin >> *m;
			this->feluriMancare[i] = m;
		}
		cout << "\nTimp de livrare: ";
		cin >> this->timpLivrare;
	}
	friend istream& operator>>(istream& in, Comanda& c) {
		if (c.feluriMancare != nullptr) {
			delete[]c.feluriMancare;
			c.feluriMancare = nullptr;
		}
		cout << "\nNr meniuri: ";
		in >> c.nrFeluriMancare;
		c.feluriMancare = new Meniu * [c.nrFeluriMancare];
		for (int i = 0; i < c.nrFeluriMancare; i++)
		{
			Meniu* m = new Meniu(0);
			in >> *m;
			c.feluriMancare[i] = m;
		}
		cout << "\nTimp de livrare: ";
		in >> c.timpLivrare;
		return in;
	}

	int PretComanda() {
		int sumaComanda = 0;
		Meniu** m = new Meniu * [this->nrFeluriMancare];
		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			m[i] = new Meniu(*(this->feluriMancare[i]));
			sumaComanda += (*m[i]).PretMeniu();

		}
		cout << "\n****************************";
		cout << "\nPret Comanda: " << sumaComanda;
		return sumaComanda;

	}
	void adaugaMeniu(Meniu* m) {
		Meniu** copie = new Meniu * [this->nrFeluriMancare + 1];
		for (int i = 0; i < this->nrFeluriMancare; i++)
			copie[i] = new Meniu(*this->feluriMancare[i]);
		copie[nrFeluriMancare] = new Meniu(*m);
		for (int i = 0; i < this->nrFeluriMancare; i++)
		{
			delete this->feluriMancare[i];
		}
		delete[]this->feluriMancare;
		this->feluriMancare = copie;
		this->nrFeluriMancare++;
	}
	friend bool operator>=(Comanda c, Comanda c1) {
		if (c.PretComanda() >= c1.PretComanda())
			return true;
		else
			return false;
	}

	explicit operator int() {
		return this->timpLivrare;
	}
	bool operator!() {
		return this->timpLivrare > 50;
	}


	~Comanda() {
		if (this->feluriMancare != nullptr) {
			delete[]this->feluriMancare;
			this->feluriMancare = nullptr;
		}
	}

};
int Comanda::costDesertGratis = 150;
class Client {
	char* nume;
	string email;
	string nrTelefon;
	int nrProduse;
	Comanda** tipuriProduse;

public:
	Client() {
		this->nume = nullptr;
		this->email = "anonim";
		this->nrTelefon = "necunoscut";
		this->nrProduse = 0;
		Comanda** tipuriProduse = nullptr;
	}

	Client(int nrProduse, Comanda** tipuriProduse) {
		if (nrProduse > 0 && tipuriProduse != nullptr) {
			this->nrProduse = nrProduse;
			this->tipuriProduse = new Comanda * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->tipuriProduse[i] = new Comanda(*tipuriProduse[i]);
			}
		}
	}

	Client(const Client& ct) {
		if (nrProduse > 0 && tipuriProduse != nullptr) {
			this->nrProduse = ct.nrProduse;
			this->tipuriProduse = new Comanda * [this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			{
				this->tipuriProduse[i] = new Comanda(*ct.tipuriProduse[i]);
			}
		}
	}

	void setEmail(string email) {
		this->email = email;
	}
	string getEmail() {
		return this->email;
	}
	void setNrTelefon(string nrTelefon) {
		if (nrTelefon.size() == 10) {
			this->nrTelefon = nrTelefon;
		}
		else
			this->nrTelefon = "necunoscut";
	}
	string getNrTelefon() {
		return this->nrTelefon;
	}
	Client& operator=(const Client& ct) {
		if (this != &ct) {
			delete[]this->tipuriProduse;
			this->tipuriProduse = nullptr;
			if (nrProduse > 0 && tipuriProduse != nullptr) {
				this->nrProduse = ct.nrProduse;
				this->tipuriProduse = new Comanda * [this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
				{
					this->tipuriProduse[i] = new Comanda(*ct.tipuriProduse[i]);
				}
			}
		}
		return *this;
	}
	void afisareClient() {
		cout << "\n---------------Client------------------";
		cout << "\nNume Client: " << this->nume;
		cout << "\nE-mail: " << this->email;
		if (this->nrTelefon.size() == 10) {
			cout << "\nNr telefon: " << this->nrTelefon;
		}
		else
			cout << "\nNr telefon invalid";
		if (this->nrProduse > 0 && this->tipuriProduse != nullptr) {
			cout << "\nNr produse: " << this->nrProduse;
			for (int i = 0; i < this->nrProduse; i++)
			{
				cout << "\nProdus[" << i << "]" << *this->tipuriProduse[i];
			}
		}
	}
	friend ostream& operator<<(ostream& out, const Client& ct) {
		out << "\n---------------Client------------------";
		out << "\nNume Client: " << ct.nume;
		out << "\nE-mail: " << ct.email;
		if (ct.nrTelefon.size() == 10) {
			out << "\nNr telefon: " << ct.nrTelefon;
		}
		else
			out << "\nNr telefon invalid";
		if (ct.nrProduse > 0 && ct.tipuriProduse != nullptr) {
			out << "\nNr produse: " << ct.nrProduse;
			for (int i = 0; i < ct.nrProduse; i++)
			{
				out << "\nProdus[" << i << "]" << *ct.tipuriProduse[i];
			}
		}
		return out;
	}

	void citireClient() {
		if (this->nume != nullptr) {
			delete[]this->nume;
			this->nume = nullptr;
		}
		cout << "\nIntroduceti numele dumneavoastra: ";
		char buffer[100];
		cin >> buffer;
		this->nume = new char[strlen(buffer) + 1];
		strcpy(this->nume, buffer);
		cout << "\nIntroduceti numarul de telefon: ";
		cin >> buffer;
		setNrTelefon(buffer);
		cout << "\nIntroduceti e-mailul: ";
		cin >> buffer;
		setEmail(buffer);

	}
	friend istream& operator>>(istream& in, Client& ct) {
		if (ct.nume != nullptr) {
			delete[]ct.nume;
			ct.nume = nullptr;
		}
		if (ct.tipuriProduse != nullptr)
		{
			delete[]ct.tipuriProduse;
			ct.tipuriProduse = nullptr;
		}
		cout << "\nIntroduceti numele dumneavoastra: ";
		char buffer[100];
		in >> buffer;
		ct.nume = new char[strlen(buffer) + 1];
		strcpy(ct.nume, buffer);
		cout << "\nIntroduceti numarul de telefon: ";
		in >> buffer;
		ct.setNrTelefon(buffer);
		cout << "\nIntroduceti e-mailul: ";
		in >> buffer;
		ct.setEmail(buffer);
		cout << "\nIntroudceti nr de comenzi pe care vreti sa le faceti: ";
		cin >> ct.nrProduse;
		cout << "\nIntroduceti Comenzile: ";
		ct.tipuriProduse = new Comanda * [ct.nrProduse];
		for (int i = 0; i < ct.nrProduse; i++)
		{
			Comanda* c = new Comanda(0);
			cin >> *c;
			ct.tipuriProduse[i] = c;

		}
		return in;
	}
	~Client() {
		if (this->nume != nullptr) {
			delete[]this->nume;
			this->nume = nullptr;
		}
		if (this->tipuriProduse != nullptr)
		{
			delete[]this->tipuriProduse;
			this->tipuriProduse = nullptr;
		}
	}
};

class GenerareRaport {
	vector<MateriiPrime>& ingrediente;
	vector<Produs>& produse;
	vector<Meniu>& meniuri;
	vector<Comanda>& comenzi;
public:
	GenerareRaport(vector<MateriiPrime>& ingrediente, vector<Produs>& produse, vector<Meniu>& meniuri, vector<Comanda>& comenzi)
		:ingrediente(ingrediente),produse(produse),meniuri(meniuri),comenzi(comenzi)
	{ }
	void raportUtilizare() {
		system("cls");
		int tasta;
		do {
			cout << "\n-------------GENERARE-----RAPOARTE---------------";
			cout << "\nApasati tasta 0 pentru a iesi din meniu. ";
			cout << "\nApasati tasta 1 pentru a genera raportul ultimelor 3 comenzi realizate. ";
			cout << "\nApasati tasta 2 pentru a genera raportul produselor realizate in mai mult de 20 de min.";
			cout << "\nApasati pe tasta dorita: ";

			cin >> tasta;
			
			switch (tasta)
			{
			case 0:
				break;
			case 1:
				
				for (int i = comenzi.size() - (comenzi.size() - 3); i < comenzi.size(); i++)
					{
					for (int j = 0; j < comenzi[i].getNrFeluriMancare(); j++)
					{
						cout << *comenzi[i].getFeluriMancare()[j];
					}
					
				}
				break;
			case 2:
				for (auto& Produs:produse)
				{
					if (Produs.getTimpPreparare() > 20)
						cout << "Produs: " << Produs.getfelMancare() << "; " << "Timp preparare: " << Produs.getTimpPreparare()<<endl;
				}
				break;
				
				
			}
		} while (tasta != 0);
	}
	void Raport() {
		system("cls");
		int tasta;
		ofstream Raport("raport.txt");
		do {
			cout << "\n-------------GENERARE-----RAPOARTE---------------";
			cout << "\nApasati tasta 0 pentru a iesi din meniu. ";
			cout << "\nApasati tasta 1 pentru a genera raportul ingredientelor. ";
			cout << "\nApasati tasta 2 pentru a genera raportul produselor.";
			cout << "\nApasati tasta 3 pentru a genera raportul meniurilor.";
			cout << "\nApasati pe tasta dorita: ";

		cin >> tasta;
		
		switch (tasta)
		{
		case 0:
			break;
		case 1:
			cout << "\n--------Raport---Ingrediente----------";
			Raport << "Raport Ingrediente" << endl;
			for (auto& MateriiPrime:ingrediente)
			{
				MateriiPrime.afisareMateriiPrime();
				Raport << "Ingredient: " << MateriiPrime.getIngredient() << " Cantitate: " << MateriiPrime.getCantitate() << endl;
			}
			break;
		case 2:
			cout << "\n-----------Raport----Produse------------";
			Raport << "Raport Produse" << endl;
			for (auto& Produs:produse)
			{
				Produs.afisareProdus();
				Raport <<
					"\nFel mancare: " << Produs.getfelMancare() << endl <<
					"Pret: " << Produs.getPret() << endl <<
					"Nr ingrediente: " << Produs.getNrIngrediente() << endl <<
					"Timp preparare: " << Produs.getTimpPreparare();
				for (int i = 0; i < Produs.getNrIngrediente(); i++)
				{
					Raport << endl << *Produs.getIngrediente()[i];
				}
				Raport << "\n********************\n";
			}
			break;
		case 3:
			cout << "\n------------Raport----Meniuri-------------";
			Raport << "Raport Meniuri" << endl;
			for (auto& Meniu:meniuri)
			{
				Meniu.afisareMeniu();
				Raport <<
					"\nID: " << Meniu.getId() << endl <<
					"Numar Produse: " << Meniu.getNrFeluriMancare();
				for (int i = 0; i < Meniu.getNrFeluriMancare(); i++)
				{
					Raport << endl << *Meniu.getListaFeluriMancare()[i];
				}
				Raport << "\n******************\n";
			}
			break;
		default:
			cout << "\nNu exista acest raport";
		}
		Raport.close();
		} while (tasta != 0);

		
	}
};


int main()
{
	
	MateriiPrime mp ("vita", 4);
	MateriiPrime mp1("rosii", 3);
	MateriiPrime mp2("chifla", 10);
	MateriiPrime mp3("cartofi", 5);
	MateriiPrime mp4("cascaval", 2);
	MateriiPrime mp5("pui", 4);
	MateriiPrime mp6("porumb", 6);
	MateriiPrime mp7("lipie", 6);
	MateriiPrime mp8("paste", 10);
	MateriiPrime mp9("parmezan", 3);
	MateriiPrime mp10("oua", 5);
	MateriiPrime mp11("pesmet", 3);
	MateriiPrime mp12("cafea", 8);
	MateriiPrime mp13("zmeura", 2);
	MateriiPrime mp14("lamai", 4);
	MateriiPrime mp15("menta", 2);
	MateriiPrime mp16("zahar", 6);
	MateriiPrime mp17("faina", 9);
	MateriiPrime mp18("cacao", 4);
	MateriiPrime* listaP1[] = { &mp,&mp1,&mp2 };
	MateriiPrime* listaP2[] = { &mp3 };
	MateriiPrime* listaP3[] = { &mp,&mp1,&mp2,&mp4 };
	MateriiPrime* listaP4[] = { &mp1,&mp5,&mp6,&mp7 };
	MateriiPrime* listaP5[] = { &mp5,&mp8,&mp9,&mp10 };
	MateriiPrime* listaP6[] = { &mp,&mp1,&mp8 };
	MateriiPrime* listaP7[] = { &mp5,&mp9 };
	MateriiPrime* listaP8[] = { &mp12 };
	MateriiPrime* listaP9[] = { &mp13 };
	MateriiPrime* listaP10[] = { &mp14,&mp15 };
	MateriiPrime* listaP11[] = {&mp16,&mp10,&mp17,&mp18};
	Produs p1("Buger", 50, 3, listaP1, 30);
	Produs p2("Cartofi", 20, 1, listaP2, 20);
	Produs p3("Cheeseburger", 55, 4, listaP3, 30);
	Produs p4("Quesadilla", 60, 4, listaP4, 35);
	Produs p5("Carbonara", 40, 4, listaP5, 30);
	Produs p6("Bolognese", 45, 3, listaP6, 30);
	Produs p7("Nuggets", 30, 2, listaP7, 20);
	Produs p8("Cafea", 14, 1, listaP8, 10);
	Produs p9("Ceai", 15, 1, listaP9, 10);
	Produs p10("Limonada", 14, 2, listaP10, 10);
	ProdusDulce pd("Negresa", 20, 4, listaP11, 30, 50,true,"Brun");
	Produs* listaM1[] = { &p1,&p2 };
	Produs* listaM2[] = { &p3,&p2 };
	Produs* listaM3[] = { &p1,&p2,&p10 };
	Produs* listaM4[] = { &p5,&p8,&p9 };
	Produs* listaM5[] = { &p6,&p4 };
	Produs* listaM6[] = { &p7,&p2,&p9 };
	Produs* listaMeniuTotal[] = { &p1,&p2,&p3,&p4,&p5,&p6,&p7,&p8,&p9,&p10 };
	perioadaZi per[] = { perioadaZi::micDejun,perioadaZi::pranz,perioadaZi::cina };
	Meniu m1(1, &per[1], 1, 2, listaM1);
	Meniu m2(2, &per[1], 1, 2, listaM2);
	Meniu m3(3, &per[2], 1, 3, listaM3);
	Meniu m4(4, &per[2], 1, 3, listaM4);
	Meniu m5(5, &per[2], 1, 2, listaM5);
	Meniu m6(6, &per[2], 1, 3, listaM6);
	Meniu m7(7, per, 3, 10, listaMeniuTotal);
	Meniu* meniuTotal[] = { &m1,&m2,&m3,&m4,&m5,&m6 };
	Meniu* listaC1[] = { &m1, &m2 };
	Meniu* listaC2[] = {&m3,&m1};
	Meniu* listaC3[] = { &m4,&m5 };
	Meniu* listaC4[] = { &m4,&m2 };
	Meniu* listaC5[] = { &m6,&m1 };
	Comanda c(1, 1, meniuTotal);
	Comanda c1(2, 2, listaC1);
	Comanda c2(3, 2, listaC2);
	Comanda c3(4, 2, listaC3);
	Comanda c4(5, 2, listaC4);
	Comanda c5(6, 2, listaC5);
	vector<Comanda>VectComanda = { c,c1,c2,c3,c4,c5 };
	Comanda* client[] = { &c1 };
	Client ct(1, client);
	vector<MateriiPrime>VectMP = {
	mp,mp1,mp2,mp3,mp4,mp5,mp6,mp7,mp8,mp9,mp10,mp11,mp12,mp13,mp14,mp15 }; 
	vector<MateriiPrime> VectMPNou;
	MateriiPrime mpNou;
	vector<Produs>VectProd = {
		p1,p2,p3,p4,p5,p6,p7,p8,p9,p10
	};
	vector<Meniu> VectMeniu = {
	m1,m2,m3,m4,m5,m6
	};
	GenerareRaport raport(VectMP, VectProd, VectMeniu,VectComanda);
	raport.Raport();
	//raport.raportUtilizare();
	


	//FISIERE TEXT
	
	ofstream fMP("ingrediente.txt");
	for (auto& MateriiPrime : VectMP) {
		fMP <<"Ingredient: "<< MateriiPrime.getIngredient()<< " Cantitate: "<< MateriiPrime.getCantitate() << endl;
	}
	fMP.close();

	ofstream fProd("produse.txt");
	for (auto& Produs:VectProd)
	{
		fProd <<
			"\nFel mancare: " << Produs.getfelMancare() << endl <<
			"Pret: " << Produs.getPret() << endl <<
			"Nr ingrediente: " << Produs.getNrIngrediente() << endl <<
			"Timp preparare: " << Produs.getTimpPreparare();
		for (int i = 0; i < Produs.getNrIngrediente(); i++)
		{
			fProd<<endl<< *Produs.getIngrediente()[i];
				
		}
		fProd << "\n********************\n";
	}

	ofstream fMeniu("meniu.txt");
	for (auto& Meniu : VectMeniu) {
		fMeniu <<
			"\nID: " << Meniu.getId() << endl <<
			"Numar Produse: " << Meniu.getNrFeluriMancare();
		for (int i = 0; i < Meniu.getNrFeluriMancare(); i++)
		{
			fMeniu << endl << *Meniu.getListaFeluriMancare()[i];
		}
		fMeniu << "\n******************\n";
	}
	

	//FISIERE BINARE

	fstream fOut("ingredienteN.bin", ios::out | ios::binary);
	for (auto& MateriiPrime : VectMP) {
		MateriiPrime.writeToFile(fOut);
	}
	fOut.close();

	fstream fIn("ingredienteN.bin", ios::in | ios::binary);
	while (!fIn.eof()) {
		mpNou.readFromFile(fIn);
		VectMPNou.push_back(mpNou);
	}
	
	fIn.close();

	/*for (auto& MateriiPrime : VectMPNou) {
		MateriiPrime.afisareMateriiPrime();
	}*/
	
	fstream gOut("produseN.bin", ios::out | ios::binary);
	for (auto& Produs : VectProd) {
		Produs.writeToFile(gOut);
	}

	gOut.close();

	fstream hOut("produsDulce.bin", ios::out | ios::binary);
	pd.writeToFile(hOut);
	hOut.close();

	ProdusDulce pdNou;
	fstream hIn("produsDulce.bin", ios:: in | ios::binary);
	pdNou.readFromFile(hIn);
	//cout << pdNou;
	hIn.close();

	//fisier CSV
	ifstream fCSV;
	cout << "\n--------FISIER---CSV----------"<<endl;
	fCSV.open("meniu.csv");
	string line;
	while (getline(fCSV, line)) {
	cout << line << endl;
	}
	fCSV.close();
	cout << "\n--------------------------------STL vector Meniu---------------------------------------";
	vector<Meniu>vectorMeniu;
	vectorMeniu.push_back(m1);
	vectorMeniu.push_back(m2);
	vectorMeniu.push_back(m3);
	vector<Meniu>:: iterator itVect;
	for ( itVect = vectorMeniu.begin(); itVect != vectorMeniu.end(); itVect++)
	{
		cout << " " << *itVect;
	}

	cout << "\n--------------------------------STL lista Produse---------------------------------------";
	list<string>produse;
	produse.push_back(p2.getfelMancare());
	produse.push_back(p3.getfelMancare());
	produse.push_back(p4.getfelMancare());
	produse.push_back(p5.getfelMancare());

	cout << "\nNumar: " << produse.size();
	list<string>::iterator itList;
	for (itList = produse.begin(); itList != produse.end(); itList++)
		cout << "\n" << *itList;

	produse.sort();

	cout << "\nLista sortata: ";
	for (string crt :produse)
		cout << crt << " ";

	cout<< "\n--------------------------------STL map Comanda---------------------------------------";
	map<int, Comanda>mapClient;
	mapClient[1] = c;
	mapClient[2] = c1;
	map<int, Comanda>::iterator itMap;
	for ( itMap = mapClient.begin(); itMap != mapClient.end(); itMap++)
	{
		cout << endl <<"\n****************" << "\nKey: " << itMap->first << " " << itMap->second;
	}

	cout << "\n--------------------------------STL set Ingrediente---------------------------------------";
	set<MateriiPrime>setMatPrim;
	setMatPrim.insert(mp1);
	setMatPrim.insert(mp2);
	setMatPrim.insert(mp3);
	setMatPrim.insert(mp4);
	setMatPrim.insert(mp5);
	set<MateriiPrime>::iterator itSet;
	for ( itSet = setMatPrim.begin(); itSet != setMatPrim.end(); itSet++)
	{
		cout << *itSet << " ";
	}
	itSet = setMatPrim.find(mp3);
	if (itSet != setMatPrim.end()) {
		cout << "\nS-a gasit ingredientul 3";
		cout << mp3;
	}
	else {
		cout << "Nu exista ingredientul 3";
	}
	

	cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
	cout << "\n Bun venit la restaurantul nostru!";
	cout << "Pentru a vedea meniul va rugam sa apasati tasta 1: ";
	char tasta;
	cin >> tasta;

	if (tasta == '1')
	{
		cout << m1 << endl << m2 << endl << m3 << endl << m4 << endl << m5 << endl << m6 << endl;
		cout << "\nDoriti sa comandati? Raspundeti cu da sau nu: ";
		string raspuns;
		cin >> raspuns;
		if (raspuns == "da" || raspuns == "Da")
		{/*
			cout << "\nPentru a putea comanda avem nevoie de datele dumneavoastra";
			ct.citireClient();*/
			cout << "\nIntroduceti cate comenzi doriti sa realizati: ";
			int nrCom;
			cin >> nrCom;
			for (int i = 0; i < nrCom; i++)
			{
				Comanda* comandaDorita = new Comanda(2);
				int nrMen;
				cout << "\nIntroduceti cate meniuri doriti pentru comanda " << i + 1 << ":";
				cin >> nrMen;
				for (int k = 0; k < nrMen; k++)
				{
					int id;
					Meniu* meniuDorit = nullptr;
					cout << "\nIntroduceti id-ul meniul " << k + 1 << ":";
					cin >> id;
					if (id >= 1 && id <= 6) {
						meniuDorit = meniuTotal[id - 1];
						comandaDorita[i].adaugaMeniu(meniuDorit);

						if (meniuDorit->verificareProduse() == 1) {
							meniuDorit->actualizareMeniu();
							cout << *meniuDorit;
							cout << "\nMeniul a fost adaugat!";

						}
						else {
							cout << "\nMeniul nu mai este in stoc. Continuati cu urmatorul meniu?" << endl;
							string raspuns2;
							cin >> raspuns2;
							if (raspuns2 != "da" && raspuns2 != "Da") {

								break;
							}
						}
						comandaDorita[i].PretComanda();

					}
					else {
						cout << "\nNu exista meniul";
					}
					cout << "\nDoriti sa vedeti intreaga comanda?";
					string raspuns3;
					cin >> raspuns3;
					if (raspuns3 == "da" || raspuns3 == "Da") {
						comandaDorita[i].afisareComanda();
					}
					cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
					cout << "\nVa multumim ca ati ales sa comandati de la noi";

				}
				/*int sum = 0;
				sum += comandaDorita[i].PretComanda();
				cout << "\n***TOTAL COMANDA***:" << sum;*/
			}
		}

		else {
			cout << "\nNe pare rau ca nu ati dorit sa cumparati de la noi!";
		}
	}
	else {
		cout << "\nAti gresit tasta";
	}

	//MateriiPrime mp("oua", 20), mp1("apa", 30),mp2,mp3("varza",2),mp4("carne",30),mp5("orez",10),mp6("sos rosii",5);
	//mp2.setIngredient("malai");
	//mp2.setCantitate(2);
	////cout << mp<<mp1;
	////mp1.citireMateriiPrime();
	//MateriiPrime* Mamaliga[2] = {&mp2,&mp1};
	//MateriiPrime* Sarmale[5] = { &mp1,&mp3,&mp4,&mp5,&mp6 };
	////cout << mp.actualizareCantitate();
	////cout << Mamaliga[1];
	//Produs p("Mamaliga",20,2,Mamaliga,15);
	//Produs p1("Sarmale", 50, 5, Sarmale,30);
	//Produs p2("Clatite",18);
	////cin >> p2;
	//cout << "\n@@@@@@@@@@@@@@@@@@";
	//p2 = p + 5;
	//if (p1 == p) {
	//	cout << "\nSe vor realiza simultan";
	//}
	//else
	//	cout << "\nNu se vor realiza simultan";
	//
	//cout << p2;
	//for (int i = 0; i < p1.getNrIngrediente(); i++)
	//{
	//	//cout << *p.actualizareProduse()[i];
	//	//cout << *p1.actualizareProduse()[i];
	//	//cout << *p.getIngrediente()[i];
	//}
	//MateriiPrime* Cereale[1] = {&mp5};
	//p.setIngrediente(1,Cereale);
	////cout << p;
	//
	////cout << p;
	////cout << p1;
	///*Meniu* m1 = {}
	//Comanda* tipuriProduse[3] = { };*/
	////Client c( "pop@gmail.com","0753214664",);
	//Produs* feluriMancare[] = { &p,&p1 };
	////cout << feluriMancare;
	//perioadaZi per[] = { perioadaZi::micDejun,perioadaZi::pranz,perioadaZi::cina };
	//Meniu m(1,&per[1], 1, 2, feluriMancare);
	//Meniu m1(2);

	//cout <<"\n%%%%%%%%%"<< * m[1];
	//m1 = m;
	////cin >> m;
	//cout << m;
	//m.PretMeniu();
	//m.totalTimpPreparare(feluriMancare);
	//Meniu* mancare[] = { &m,&m1 };
	//Comanda c(1);
	//Comanda c2(3);
	//Comanda c1(2, 2, mancare);
	//cout << "\n&&&&&&&&&&&&&&&&&&";
	//if (!c == 1) {
	//	cout << "\nMai mare de 50";
	//}
	//else
	//	cout << "\nMai mic de 50";
	//if (c >= c1) {
	//	cout << "\neste mai mare";
	//}
	//else
	//	cout << "\neste mai mica";
	//c.setTimpLivrare(20);
	//c1.setTimpLivrare(30);
	//int timplivrare = int(c);
	//cout << timplivrare;
	//cout <<endl<< c.getTimpLivrare();
	////cout << c1;
	////cout <<endl<< c1.getNrFeluriMancare();
	//
	//
	//c1.PretComanda();
	//cin >> c1;
	//cout<< "\napasa tasta 1 pentru a vedea meniul:";
	//int buffer;
	//cin >> buffer;
	//if (buffer==1)
	//	cout << m;
	//else
	//	cout << "nu avem meniu";
	//cout << "Alege un meniu:";
	return 0;
}


