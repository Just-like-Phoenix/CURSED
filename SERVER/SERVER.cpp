#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <winsock2.h>
#include "Classes.h"
#include "Libs.h"

#pragma warning(disable : 4996)

using namespace std;

int numcl = 0;
bool isInit = false;
ifstream Afile;
ifstream Ufile;

vector<Air_Route> air;
vector<Train_Route> train;
vector<Motor_Route> motor;

void Init() {
	vector<Air_Route>::iterator aptr = air.begin();
	vector<Train_Route>::iterator tptr = train.begin();
	vector<Motor_Route>::iterator mptr = motor.begin();
	
	ifstream Air, Train, Motor;

	Air_Route atmp;
	Train_Route ttmp;
	Motor_Route mtmp;

	Air.open("Air.txt", ios::in);
	while (Air) {
		Air >> atmp;
		air.push_back(atmp);
	}
	if (Air.eof())
	{
		air.erase(air.end() - 1);
	}
	Air.close();

	Train.open("Train.txt", ios::in);
	while (Train) {
		Train >> ttmp;
		train.push_back(ttmp);
	}
	if (Train.eof())
	{
		train.erase(train.end() - 1);
	}
	Train.close();

	Motor.open("Motor.txt", ios::in);
	while (Motor) {
		Motor >> mtmp;
		motor.push_back(mtmp);
	}
	if (Motor.eof())
	{
		motor.erase(motor.end() - 1);
	}
	Motor.close();
}
void Save() {
	vector<Air_Route>::iterator aptr = air.begin();
	vector<Train_Route>::iterator tptr = train.begin();
	vector<Motor_Route>::iterator mptr = motor.begin();

	ofstream Air, Train, Motor;

	Air.open("Air.txt", ios::out);
	Train.open("Train.txt", ios::out);
	Motor.open("Motor.txt", ios::out);

	for (; aptr != air.end(); aptr++) {
		if (aptr->Get_type() == "Воздушный") Air << *aptr;
	}
	for (; tptr != train.end(); tptr++) {
		if (tptr->Get_type() == "Железнодорожный") Train << *tptr;
	}
	for (; mptr != motor.end(); mptr++) {
		if (mptr->Get_type() == "Дорожный") Motor << *mptr;
	}

	Air.close();
	Train.close();
	Motor.close();
}

int FindMax(double* arr, int size) {
	int maxID = 0;
	double max = 0;

	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
			maxID = i;
		}
	}

	return maxID;
}
int ExpertMethod(int fast[3], int cheap[3], int balanced[3])
{
	vector<string> type_for_colum = { "Воздушный", "Железнодорожный", "Дорожный" };

	int* total = new int[3];
	int sum = 0;
	
	cout << "\nИсходная матрица:\n";
	printf("     |%15s|%15s|%15s|\n", "Воздушный", "Железнодорожный", "Дорожный");
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15d|%15d|%15d|\n", "Э1", fast[0], fast[1], fast[2]);
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15d|%15d|%15d|\n", "Э2", cheap[0], cheap[1], cheap[2]);
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15d|%15d|%15d|\n", "Э3", balanced[0], balanced[1], balanced[2]);
	printf("+----+---------------+---------------+---------------+\n");

	for (int i = 0; i < 3; i++) {
		fast[i] = 3 - fast[i];
		cheap[i] = 3 - cheap[i];
		balanced[i] = 3 - balanced[i];
		total[i] = fast[i] + cheap[i] + balanced[i];
		sum += total[i];
	}
	cout << "\nМодифицированная матрица:\n";
	printf("     |%15s|%15s|%15s|\n", "Воздушный", "Железнодорожный", "Дорожный");
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15d|%15d|%15d|\n", "Э1", fast[0], fast[1], fast[2]);
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15d|%15d|%15d|\n", "Э2", cheap[0], cheap[1], cheap[2]);
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15d|%15d|%15d|\n", "Э3", balanced[0], balanced[1], balanced[2]);
	printf("+----+---------------+---------------+---------------+\n");

	cout << "\nСуммарные оценки:\n";
	printf("     |%15s|%15s|%15s|\n", "Воздушный", "Железнодорожный", "Дорожный");
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15d|%15d|%15d|\n", "Сума", total[0], total[1], total[2]);
	printf("+----+---------------+---------------+---------------+\n");
	double* weights = new double[3];
	for (int i = 0; i < 3; i++) {
		weights[i] = (double)total[i] / (double)sum;
	}

	cout << "\nИсходные веса целей:\n";
	printf("     |%15s|%15s|%15s|\n", "Воздушный", "Железнодорожный", "Дорожный");
	printf("+----+---------------+---------------+---------------+\n");
	printf("|%4s|%15.4f|%15.4f|%15.4f|\n", "Веса", weights[0], weights[1], weights[2]);
	printf("+----+---------------+---------------+---------------+\n");


	cout << "\nПриоритетный тип доставки -" << type_for_colum[FindMax(weights, 3)] << endl;
	return FindMax(weights, 3);
}

void AirAdd(SOCKET s2, char* buf) {
	*buf = '\0';
	string dell_code, from, to, distance, type, volume, weight;
	double price;
	
	recv(s2, buf, 100, 0); dell_code = buf; *buf = '\0';
	recv(s2, buf, 100, 0); from = buf; *buf = '\0';
	recv(s2, buf, 100, 0); to = buf; *buf = '\0';
	recv(s2, buf, 100, 0); distance = buf; *buf = '\0';
	recv(s2, buf, 100, 0); volume = buf; *buf = '\0';
	recv(s2, buf, 100, 0); weight = buf; *buf = '\0';
	
	if ((atoi(weight.c_str())*1000) < 168)
	{
		price = atoi(volume.c_str()) * 167 * 2.2;
	}
	else
	{
		price = atoi(weight.c_str()) * 2.2 * 1000;
	}
	
	Air_Route air_rote(atoi(volume.c_str()), strtod(weight.c_str(), NULL), price);
	air_rote.Set_type("Воздушный");
	air_rote.Set_dell_code(dell_code);
	air_rote.Set_from(from);
	air_rote.Set_to(to);
	air_rote.Set_distance(distance);
	
	air.push_back(air_rote);
}
void TrainAdd(SOCKET s2, char* buf) {
	*buf = '\0';
	string dell_code, from, to, distance, type, volume, weight;
	double price;

	recv(s2, buf, 100, 0); dell_code = buf; *buf = '\0';
	recv(s2, buf, 100, 0); from = buf; *buf = '\0';
	recv(s2, buf, 100, 0); to = buf; *buf = '\0';
	recv(s2, buf, 100, 0); distance = buf; *buf = '\0';
	recv(s2, buf, 100, 0); volume = buf; *buf = '\0';
	recv(s2, buf, 100, 0); weight = buf; *buf = '\0';

	price = atoi(distance.c_str()) * 0.8;

	Train_Route train_rote(atoi(volume.c_str()), atoi(weight.c_str()), price);
	train_rote.Set_type("Железнодорожный");
	train_rote.Set_dell_code(dell_code);
	train_rote.Set_from(from);
	train_rote.Set_to(to);
	train_rote.Set_distance(distance);

	train.push_back(train_rote);
}
void MotorAdd(SOCKET s2, char* buf) {
	*buf = '\0';
	string dell_code, from, to, distance, type, volume, weight;
	double price;

	recv(s2, buf, 100, 0); dell_code = buf; *buf = '\0';
	recv(s2, buf, 100, 0); from = buf; *buf = '\0';
	recv(s2, buf, 100, 0); to = buf; *buf = '\0';
	recv(s2, buf, 100, 0); distance = buf; *buf = '\0';
	recv(s2, buf, 100, 0); volume = buf; *buf = '\0';
	recv(s2, buf, 100, 0); weight = buf; *buf = '\0';

	price = atoi(distance.c_str()) * 1;

	Motor_Route motor_rote(atoi(volume.c_str()), atoi(weight.c_str()), price);
	motor_rote.Set_type("Дорожный");
	motor_rote.Set_dell_code(dell_code);
	motor_rote.Set_from(from);
	motor_rote.Set_to(to);
	motor_rote.Set_distance(distance);

	motor.push_back(motor_rote);
}

int RouteAdd(SOCKET s2, char* buf)
{
	string for_type_c;
	int fast[3];
	int cheap[3];
	int balanced[3];

	int id;

	recv(s2, buf, 100, 0); for_type_c = buf; *buf = '\0';

	if (atoi(for_type_c.c_str()) == 1)
	{
		fast[0] = 1; fast[1] = 3; fast[2] = 2;
		cheap[0] = 3; cheap[1] = 1; cheap[2] = 2;
		balanced[0] = 1; balanced[1] = 3; balanced[2] = 2;
	}
	else if (atoi(for_type_c.c_str()) == 2)
	{
		fast[0] = 3; fast[1] = 2; fast[2] = 1;
		cheap[0] = 3; cheap[1] = 1; cheap[2] = 2;
		balanced[0] = 3; balanced[1] = 1; balanced[2] = 2;
	}
	else if (atoi(for_type_c.c_str()) == 3)
	{
		fast[0] = 2; fast[1] = 3; fast[2] = 1;
		cheap[0] = 3; cheap[1] = 2; cheap[2] = 1;
		balanced[0] = 2; balanced[1] = 3; balanced[2] = 1;
	}

	id = ExpertMethod(fast, cheap, balanced);

	return id;
}

void AirShow(SOCKET s2, char* buf)
{
	vector<Air_Route>::iterator ptr = air.begin();

	for (; ptr != air.end(); ptr++) {
		char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], weight[100], price[100];
		ptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);
		
		if (strlen(dell_code) > 0)
		{
			send(s2, dell_code, sizeof(dell_code), 0);
			send(s2, from, sizeof(from), 0);
			send(s2, to, sizeof(to), 0);
			send(s2, distance, sizeof(distance), 0);
			send(s2, type, sizeof(type), 0);
			send(s2, volume, sizeof(volume), 0);
			send(s2, weight, sizeof(weight), 0);
			send(s2, price, sizeof(price), 0);
		}
	}
}
void TrainShow(SOCKET s2, char* buf)
{
	vector<Train_Route>::iterator ptr = train.begin();

	for (; ptr != train.end(); ptr++) {
		char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], weight[100], price[100];
		ptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);
		
		if (strlen(dell_code) > 0)
		{
			send(s2, dell_code, sizeof(dell_code), 0);
			send(s2, from, sizeof(from), 0);
			send(s2, to, sizeof(to), 0);
			send(s2, distance, sizeof(distance), 0);
			send(s2, type, sizeof(type), 0);
			send(s2, volume, sizeof(volume), 0);
			send(s2, weight, sizeof(weight), 0);
			send(s2, price, sizeof(price), 0);
		}
	}
}
void MotorShow(SOCKET s2, char* buf)
{
	vector<Motor_Route>::iterator ptr = motor.begin();

	for (; ptr != motor.end(); ptr++) {
		char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], weight[100], price[100];
		ptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);

		if (strlen(dell_code) > 0)
		{
			send(s2, dell_code, sizeof(dell_code), 0);
			send(s2, from, sizeof(from), 0);
			send(s2, to, sizeof(to), 0);
			send(s2, distance, sizeof(distance), 0);
			send(s2, type, sizeof(type), 0);
			send(s2, volume, sizeof(volume), 0);
			send(s2, weight, sizeof(weight), 0);
			send(s2, price, sizeof(price), 0);
		}
	}
}

void Show(SOCKET s2, char* buf)
{
	AirShow(s2, buf);
	TrainShow(s2, buf);
	MotorShow(s2, buf);
}

void Search(SOCKET s2, char* buf)
{
	char str[100];

	recv(s2, str, sizeof(str), 0);

	vector<Air_Route>::iterator aptr = air.begin();
	vector<Train_Route>::iterator tptr = train.begin();
	vector<Motor_Route>::iterator mptr = motor.begin();

	for (; aptr != air.end(); aptr++)
	{
		char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], weight[100], price[100];
		aptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);

		if (strstr(dell_code, str) || strstr(from, str) || strstr(to, str) || strstr(type, str))
		{
			send(s2, dell_code, sizeof(dell_code), 0);
			send(s2, from, sizeof(from), 0);
			send(s2, to, sizeof(to), 0);
			send(s2, distance, sizeof(distance), 0);
			send(s2, type, sizeof(type), 0);
			send(s2, volume, sizeof(volume), 0);
			send(s2, weight, sizeof(weight), 0);
			send(s2, price, sizeof(price), 0);
		}

		for (; tptr != train.end(); tptr++)
		{
			tptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);

			if (strstr(dell_code, str) || strstr(from, str) || strstr(to, str) || strstr(type, str))
			{
				send(s2, dell_code, sizeof(dell_code), 0);
				send(s2, from, sizeof(from), 0);
				send(s2, to, sizeof(to), 0);
				send(s2, distance, sizeof(distance), 0);
				send(s2, type, sizeof(type), 0);
				send(s2, volume, sizeof(volume), 0);
				send(s2, weight, sizeof(weight), 0);
				send(s2, price, sizeof(price), 0);
			}

			for (; mptr != motor.end(); mptr++) {
				mptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);

				if (strstr(dell_code, str) || strstr(from, str) || strstr(to, str) || strstr(type, str))
				{
					send(s2, dell_code, sizeof(dell_code), 0);
					send(s2, from, sizeof(from), 0);
					send(s2, to, sizeof(to), 0);
					send(s2, distance, sizeof(distance), 0);
					send(s2, type, sizeof(type), 0);
					send(s2, volume, sizeof(volume), 0);
					send(s2, weight, sizeof(weight), 0);
					send(s2, price, sizeof(price), 0);
				}
			}
		}
	}
}

void AirSort(SOCKET s2, char* buf, int operation, int field)
{
	if (operation == 1)
	{
		if (field == 1)
		{
			sort(air.begin(), air.end(), [](Air_Route& a1, Air_Route& a2) {return a1.Get_from() > a2.Get_from(); });
		}
		else if(field == 2)
		{
			sort(air.begin(), air.end(), [](Air_Route& a1, Air_Route& a2) {return a1.Get_to() > a2.Get_to(); });
		}
	}
	else if(operation == 2)
	{
		if (field == 1)
		{
			sort(air.begin(), air.end(), [](Air_Route& a1, Air_Route& a2) {return a1.Get_from() < a2.Get_from(); });
		}
		else if (field == 2)
		{
			sort(air.begin(), air.end(), [](Air_Route& a1, Air_Route& a2) {return a1.Get_to() < a2.Get_to(); });
		}
	}
}
void TrainSort(SOCKET s2, char* buf, int operation, int field)
{
	if (operation == 1)
	{
		if (field == 1)
		{
			sort(train.begin(), train.end(), [](Train_Route& a1, Train_Route& a2) {return a1.Get_from() > a2.Get_from(); });
		}
		else if (field == 2)
		{
			sort(train.begin(), train.end(), [](Train_Route& a1, Train_Route& a2) {return a1.Get_to() > a2.Get_to(); });
		}
	}
	else if (operation == 2)
	{
		if (field == 1)
		{
			sort(train.begin(), train.end(), [](Train_Route& a1, Train_Route& a2) {return a1.Get_from() < a2.Get_from(); });
		}
		else if (field == 2)
		{
			sort(train.begin(), train.end(), [](Train_Route& a1, Train_Route& a2) {return a1.Get_to() < a2.Get_to(); });
		}
	}
}
void MotorSort(SOCKET s2, char* buf, int operation, int field)
{
	if (operation == 1)
	{
		if (field == 1)
		{
			sort(motor.begin(), motor.end(), [](Motor_Route& a1, Motor_Route& a2) {return a1.Get_from() > a2.Get_from(); });
		}
		else if (field == 2)
		{
			sort(motor.begin(), motor.end(), [](Motor_Route& a1, Motor_Route& a2) {return a1.Get_to() > a2.Get_to(); });
		}
	}
	else if (operation == 2)
	{
		if (field == 1)
		{
			sort(motor.begin(), motor.end(), [](Motor_Route& a1, Motor_Route& a2) {return a1.Get_from() < a2.Get_from(); });
		}
		else if (field == 2)
		{
			sort(motor.begin(), motor.end(), [](Motor_Route& a1, Motor_Route& a2) {return a1.Get_to() < a2.Get_to(); });
		}
	}
}

void Delete(SOCKET s2, char* buf, int type)
{
	char dbuf[100];

	recv(s2, dbuf, sizeof(dbuf), 0);

	if (type == 1)
	{
		air.erase(air.begin() + atoi(dbuf) - 1);
	}
	else if (type == 2)
	{
		train.erase(train.begin() + atoi(dbuf) - 1);
	}
	else if (type == 3)
	{
		motor.erase(motor.begin() + atoi(dbuf) - 1);
	}
}

void UpdateDellCodeAir(SOCKET s2, char* buf)
{
	vector<Air_Route>::iterator aptr = air.begin();

	char comp[100], ibuf[100];
	*comp = '\0';
	*ibuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, ibuf, sizeof(ibuf), 0);
	
	for (; aptr != air.end(); aptr++)
	{
		if (air.end() - aptr == atoi(comp))
		{
			aptr->Set_dell_code(ibuf);
		}
	}
}
void UpdateDellCodeTrain(SOCKET s2, char* buf)
{
	vector<Train_Route>::iterator tptr = train.begin();

	char comp[100], ibuf[100];
	*comp = '\0';
	*ibuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, ibuf, sizeof(ibuf), 0);

	for (; tptr != train.end(); tptr++)
	{
		if (train.end() - tptr == atoi(comp))
		{
			tptr->Set_dell_code(ibuf);
		}
	}
}
void UpdateDellCodeMotor(SOCKET s2, char* buf)
{
	vector<Motor_Route>::iterator mptr = motor.begin();

	char comp[100], ibuf[100];
	*comp = '\0';
	*ibuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, ibuf, sizeof(ibuf), 0);

	for (; mptr != motor.end(); mptr++)
	{
		if (motor.end() - mptr== atoi(comp))
		{
			mptr->Set_dell_code(ibuf);
		}
	}
}
void UpdateDistanceAir(SOCKET s2, char* buf)
{
	vector<Air_Route>::iterator aptr = air.begin();

	char comp[100], fbuf[100], tbuf[100], dbuf[100];
	*comp = '\0';
	*fbuf = '\0';
	*tbuf = '\0';
	*dbuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, fbuf, sizeof(fbuf), 0);
	recv(s2, tbuf, sizeof(tbuf), 0);
	recv(s2, dbuf, sizeof(dbuf), 0);

	for (; aptr != air.end(); aptr++)
	{
		if (air.end() - aptr == atoi(comp))
		{
			aptr->Set_from(fbuf);
			aptr->Set_to(tbuf);
			aptr->Set_distance(dbuf);
		}
	}
}
void UpdateDistanceTrain(SOCKET s2, char* buf)
{
	vector<Train_Route>::iterator tptr = train.begin();

	char comp[100], fbuf[100], tbuf[100], dbuf[100];
	*comp = '\0';
	*fbuf = '\0';
	*tbuf = '\0';
	*dbuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, fbuf, sizeof(fbuf), 0);
	recv(s2, tbuf, sizeof(tbuf), 0);
	recv(s2, dbuf, sizeof(dbuf), 0);

	for (; tptr != train.end(); tptr++)
	{
		if (train.end() - tptr == atoi(comp))
		{
			tptr->Set_from(fbuf);
			tptr->Set_to(tbuf);
			tptr->Set_distance(dbuf);
			tptr->Set_price(atoi(dbuf) * 0.8);
		}
	}
}
void UpdateDistanceMotor(SOCKET s2, char* buf)
{
	vector<Motor_Route>::iterator mptr = motor.begin();

	char comp[100], fbuf[100], tbuf[100], dbuf[100];
	*comp = '\0';
	*fbuf = '\0';
	*tbuf = '\0';
	*dbuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, fbuf, sizeof(fbuf), 0);
	recv(s2, tbuf, sizeof(tbuf), 0);
	recv(s2, dbuf, sizeof(dbuf), 0);

	for (; mptr != motor.end(); mptr++)
	{
		if (motor.end() - mptr == atoi(comp))
		{
			mptr->Set_from(fbuf);
			mptr->Set_to(tbuf);
			mptr->Set_distance(dbuf);
			mptr->Set_price(atoi(dbuf) * 1);
		}
	}
}
void UpdateSpecAir(SOCKET s2, char* buf)
{
	vector<Air_Route>::iterator aptr = air.begin();

	char comp[100], wbuf[100], vbuf[100];
	double price;
	*comp = '\0';
	*wbuf = '\0';
	*vbuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, vbuf, sizeof(vbuf), 0);
	recv(s2, wbuf, sizeof(wbuf), 0);

	for (; aptr != air.end(); aptr++)
	{
		if (air.end() - aptr == atoi(comp))
		{
			if ((strtod(wbuf, NULL) * 1000) < 168)
			{
				price = atoi(vbuf) * 167 * 2.2;
			}
			else
			{
				price = strtod(wbuf, NULL) * 2.2 * 1000;
			}

			aptr->Set_weight(strtod(wbuf, NULL));
			aptr->Set_volume(atoi(vbuf));
			aptr->Set_price(price);
		}
	}
}
void UpdateSpecTrain(SOCKET s2, char* buf)
{
	vector<Train_Route>::iterator tptr = train.begin();

	char comp[100], wbuf[100], vbuf[100];
	*comp = '\0';
	*wbuf = '\0';
	*vbuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, vbuf, sizeof(vbuf), 0);
	recv(s2, wbuf, sizeof(wbuf), 0);

	for (; tptr != train.end(); tptr++)
	{
		if (train.end() - tptr == atoi(comp))
		{
			tptr->Set_weight(strtod(wbuf, NULL));
			tptr->Set_volume(atoi(vbuf));
		}
	}
}
void UpdateSpecMotor(SOCKET s2, char* buf)
{
	vector<Motor_Route>::iterator mptr = motor.begin();

	char comp[100], wbuf[100], vbuf[100];
	*comp = '\0';
	*wbuf = '\0';
	*vbuf = '\0';

	recv(s2, comp, sizeof(comp), 0);
	recv(s2, vbuf, sizeof(vbuf), 0);
	recv(s2, wbuf, sizeof(wbuf), 0);

	for (; mptr != motor.end(); mptr++)
	{
		if (motor.end() - mptr == atoi(comp))
		{
			mptr->Set_weight(strtod(wbuf, NULL));
			mptr->Set_volume(atoi(vbuf));
		}
	}
}

void Filtr(SOCKET s2, char* buf, int filtr)
{
	char str[100];
	recv(s2, str, sizeof(str), 0);

	vector<Air_Route>::iterator aptr = air.begin();
	vector<Train_Route>::iterator tptr = train.begin();
	vector<Motor_Route>::iterator mptr = motor.begin();

	for (; aptr != air.end(); aptr++)
	{
		char dell_code[100], from[100], to[100], distance[100], type[100], volume[100], weight[100], price[100], buf[100];
		aptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);
		
		if (filtr == 1)
		{
			strcpy(buf,from);
		}
		else if(filtr == 2)
		{
			strcpy(buf, to);
		}
		else if (filtr == 3)
		{
			strcpy(buf, type);
		}

		if (strstr(buf, str))
		{
			send(s2, dell_code, sizeof(dell_code), 0);
			send(s2, from, sizeof(from), 0);
			send(s2, to, sizeof(to), 0);
			send(s2, distance, sizeof(distance), 0);
			send(s2, type, sizeof(type), 0);
			send(s2, volume, sizeof(volume), 0);
			send(s2, weight, sizeof(weight), 0);
			send(s2, price, sizeof(price), 0);
		}

		for (; tptr != train.end(); tptr++)
		{
			tptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);

			if (filtr == 1)
			{
				strcpy(buf, from);
			}
			else if (filtr == 2)
			{
				strcpy(buf, to);
			}
			else if (filtr == 3)
			{
				strcpy(buf, type);
			}

			if (strstr(buf, str))
			{
				send(s2, dell_code, sizeof(dell_code), 0);
				send(s2, from, sizeof(from), 0);
				send(s2, to, sizeof(to), 0);
				send(s2, distance, sizeof(distance), 0);
				send(s2, type, sizeof(type), 0);
				send(s2, volume, sizeof(volume), 0);
				send(s2, weight, sizeof(weight), 0);
				send(s2, price, sizeof(price), 0);
			}

			for (; mptr != motor.end(); mptr++) {
				mptr->Get_Fields(dell_code, from, to, distance, type, volume, weight, price);
				
				if (filtr == 1)
				{
					strcpy(buf, from);
				}
				else if (filtr == 2)
				{
					strcpy(buf, to);
				}
				else if (filtr == 3)
				{
					strcpy(buf, type);
				}

				if (strstr(buf, str))
				{
					send(s2, dell_code, sizeof(dell_code), 0);
					send(s2, from, sizeof(from), 0);
					send(s2, to, sizeof(to), 0);
					send(s2, distance, sizeof(distance), 0);
					send(s2, type, sizeof(type), 0);
					send(s2, volume, sizeof(volume), 0);
					send(s2, weight, sizeof(weight), 0);
					send(s2, price, sizeof(price), 0);
				}
			}
		}
	}
}

DWORD WINAPI ThreadFunc(LPVOID client_socket)
{
	if (isInit == false)
	{
		Init();
		isInit = true;
	}
	

	int num = numcl;
	SOCKET s2 = ((SOCKET*)client_socket)[0];
	char buf[100];
	string _log;
	while (recv(s2, buf, sizeof(buf), 0))
	{
		if (buf[0] == '0') 
		{
			if (!strcmp(buf, "0_0")) cout << "N-" << numcl << " unauthorised\n";
			else if (!strcmp(buf, "0_1")) {
				bool exist = false;
				char lbuf[100], pbuf[100];
				
				recv(s2, lbuf, 100, 0);
				recv(s2, pbuf, 100, 0);

				if (!strcmp(lbuf, "admin") && !strcmp(pbuf, "admin")) {
					exist = true;
					send(s2, "11", sizeof("11"), 0);
				}

				while (!exist) {
					string log, pass;

					if (exist == false)
					{
						Afile.open("admin.txt", ios::in);
						while (Afile)
						{
							Afile >> log;
							Afile >> pass;

							if (!strcmp(log.c_str(), lbuf) && !strcmp(pass.c_str(), pbuf)) {
								send(s2, "11", sizeof("11"), 0);
								_log = log;
								cout << "client N-" << num << " authorised like " << "\"" << log << "\"\n" << "";
								exist = true;
								Afile.close();
								break;
							}
						}
						Afile.close();
					}

					if (exist == false) 
					{
						Ufile.open("user.txt", ios::in);
						while (Ufile) {
							Ufile >> log;
							Ufile >> pass;

							if (!strcmp(log.c_str(), lbuf) && !strcmp(pass.c_str(), pbuf)) {
								send(s2, "21", sizeof("21"), 0);
								_log = log;
								cout << "client N-" << num << " authorised like " << "\"" << log << "\"\n" << "";
								exist = true;
								Ufile.close();
								break;
							}
						}
						Ufile.close();
					}

					if (exist == false) {
						send(s2, "00", sizeof("00"), 0);
						cout << "client N-" << num << " failed his authorisation\n";
						exist = true;
					}
				}
			}
			Save();
		}
		else if (buf[0] == '1') 
		{
			if (!strcmp(buf, "1_1"))
			{
				Show(s2, buf);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "1_2"))
			{
				int id = RouteAdd(s2, buf);
				if (id == 0)
				{
					AirAdd(s2, buf);
				}
				else if (id == 1)
				{
					TrainAdd(s2, buf);
				}
				else if (id == 2)
				{
					MotorAdd(s2, buf);
				}
			}
			else if (!strcmp(buf, "1_311"))
			{
				AirShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateDellCodeAir(s2, buf);
			}
			else if (!strcmp(buf, "1_312"))
			{
				AirShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateDistanceAir(s2, buf);
			}
			else if (!strcmp(buf, "1_313"))
			{
				AirShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateSpecAir(s2, buf);
			}
			else if (!strcmp(buf, "1_321"))
			{
				TrainShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateDellCodeTrain(s2, buf);
			}
			else if (!strcmp(buf, "1_322"))
			{
				TrainShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateDistanceTrain(s2, buf);
			}
			else if (!strcmp(buf, "1_323"))
			{
				TrainShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateSpecTrain(s2, buf);
			}
			else if (!strcmp(buf, "1_331"))
			{
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateDellCodeMotor(s2, buf);
			}
			else if (!strcmp(buf, "1_332"))
			{
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateDistanceMotor(s2, buf);
			}
			else if (!strcmp(buf, "1_333"))
			{
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				UpdateSpecMotor(s2, buf);
			}
			else if(!strcmp(buf, "1_41"))
			{
				char pbuf[10];
				if (air.size() > 0) strcpy(pbuf,"1");
				else strcpy(pbuf, "0");
		
				send(s2, pbuf, sizeof(pbuf), 0);
				AirShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				Delete(s2, buf, 1);
			}
			else if (!strcmp(buf, "1_42"))
			{
				char pbuf[10];

				if (train.size() > 0) strcpy(pbuf, "1");
				else strcpy(pbuf, "0");

				send(s2, pbuf, sizeof(pbuf), 0);
				TrainShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				Delete(s2, buf, 2);
			}
			else if (!strcmp(buf, "1_43"))
			{
				char pbuf[10];

				if (motor.size() > 0) strcpy(pbuf, "1");
				else strcpy(pbuf, "0");

				send(s2, pbuf, sizeof(pbuf), 0);
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
				Delete(s2, buf, 3);
			}
			Save();
		}
		else if (buf[0] == '2')
		{
			if (!strcmp(buf, "2_1")) 
			{
				AirShow(s2, buf);
				TrainShow(s2, buf);
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_2"))
			{
				Search(s2, buf);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_311"))
			{
				AirSort(s2, buf,1,1);
				TrainSort(s2, buf, 1, 1);
				MotorSort(s2, buf, 1, 1);
				AirShow(s2, buf);
				TrainShow(s2, buf);
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_312"))
			{
				AirSort(s2, buf, 2, 1);
				TrainSort(s2, buf, 2, 1);
				MotorSort(s2, buf, 2, 1);
				AirShow(s2, buf);
				TrainShow(s2, buf);
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_321"))
			{
				AirSort(s2, buf, 1, 2);
				TrainSort(s2, buf, 1, 2);
				MotorSort(s2, buf, 1, 2);
				AirShow(s2, buf);
				TrainShow(s2, buf);
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_322"))
			{
				AirSort(s2, buf, 2, 2);
				TrainSort(s2, buf, 2, 2);
				MotorSort(s2, buf, 2, 2);
				AirShow(s2, buf);
				TrainShow(s2, buf);
				MotorShow(s2, buf);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_41"))
			{
				Filtr (s2, buf,1);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_42"))
			{
				Filtr(s2, buf, 2);
				send(s2, "0", sizeof("0"), 0);
			}
			else if (!strcmp(buf, "2_43"))
			{
				Filtr(s2, buf, 3);
				send(s2, "0", sizeof("0"), 0);
			}
		}
		*buf = '\0';
	}
	
	Save();

	closesocket(s2);
	cout << "client N-" << num << " disconnected\n";

	return 0;
}

void print()
{
	if (numcl) cout << "client N-" << numcl << " connected\n";
	else printf("No clients connected\n");
}

void main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1280);
	local_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr*)&local_addr, sizeof(local_addr));
	int c = listen(s, 5);
	cout << "Server receive ready" << endl;
	cout << endl;
	SOCKET client_socket;
	sockaddr_in client_addr;
	int client_addr_size = sizeof(client_addr);
	while ((client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))) {
		numcl++;
		print();
		DWORD thID;
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}
}