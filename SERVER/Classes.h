#include "Libs.h"

class Route
{
	string dell_code;
	string from;
	string to;
	string distance;
	string type;

public:
	Route() {};
	Route(string _dell_code, string _from, string _to, string _distance, string _type) : dell_code(_dell_code), from(_from), to(_to), distance(_distance), type(_type) {};

	string Get_dell_code() { return dell_code; }
	string Get_from() { return from; }
	string Get_to() { return to; }
	string Get_distance() { return distance; }
	string Get_type() { return type; }

	void Set_dell_code(string _dell_code) { dell_code = _dell_code; }
	void Set_from(string _from) { from = _from; }
	void Set_to(string _to) { to = _to; }
	void Set_distance(string _distance) { distance = _distance; }
	void Set_type(string _type) { type = _type; }
};

class Air_Route : public Route
{
	double tarif = 2.2;
	int density = 167;
	int volume;
	double price, weight;

public:

	Air_Route() {};
	Air_Route(int _volume, int _weight, double _price) : volume(_volume), weight(_weight), price(_price) {};

	void Get_Fields(char* _dell_code, char* _from, char* _to, char* _distance, char* _type, char* _volume, char* _weight, char* _price)
	{
		char buf[100] = "\0";

		strcpy(_dell_code, Get_dell_code().c_str());
		strcpy(_from, Get_from().c_str());
		strcpy(_to, Get_to().c_str());
		strcpy(_distance, Get_distance().c_str());
		strcpy(_type, Get_type().c_str());
		_itoa_s(volume, buf, sizeof(buf), 10);
		strcpy(_volume, buf);
		_gcvt_s(buf, sizeof(buf), weight, 17);
		strcpy(_weight, buf);
		_gcvt_s(buf, sizeof(buf), price, 17);
		strcpy(_price, buf);
	}

	friend ofstream& operator<<(ofstream& stream, Air_Route& obj)
	{
		stream << obj.Get_dell_code() << "▀" << obj.Get_from() << "▀" << obj.Get_to() << "▀" << obj.Get_distance() << "▀" << obj.Get_type() << "▀" << obj.volume << "▀" << obj.weight << "▀" << obj.price << "\n";
		return stream;
	}
	friend ifstream& operator>>(ifstream& stream, Air_Route& obj) 
	{
		string dell_code, from, to, distance, type, svolume, sweight, sprice;

		getline(stream, dell_code, '▀');
		getline(stream, from, '▀');
		getline(stream, to, '▀');
		getline(stream, distance, '▀');
		getline(stream, type, '▀');
		getline(stream, svolume, '▀');
		getline(stream, sweight, '▀');
		getline(stream, sprice, '▀');

		obj.Set_dell_code(dell_code);
		obj.Set_from(from);
		obj.Set_to(to);
		obj.Set_distance(distance);
		obj.Set_type(type);
		obj.volume = atoi(svolume.c_str());
		obj.weight = atof(sweight.c_str());
		obj.price = atof(sprice.c_str());

		return stream;
	}

	void Set_price(double _price) { price = _price; }
	void Set_weight(double _weight) { weight = _weight; }
	void Set_volume(int _volume) { volume = _volume; }
};

class Train_Route : public Route
{
	double tarif = 0.8;
	int max_volume = 75;
	int volume;
	double price, weight;

public:
	Train_Route() {};
	Train_Route(int _volume, int _weight,double _price) : volume(_volume), weight(_weight), price(_price) {};

	void Get_Fields(char* _dell_code, char* _from, char* _to, char* _distance, char* _type, char* _volume, char* _weight, char* _price)
	{
		char buf[100] = "\0";

		strcpy(_dell_code, Get_dell_code().c_str());
		strcpy(_from, Get_from().c_str());
		strcpy(_to, Get_to().c_str());
		strcpy(_distance, Get_distance().c_str());
		strcpy(_type, Get_type().c_str());
		_itoa_s(volume, buf, sizeof(buf), 10);
		strcpy(_volume, buf);
		_gcvt_s(buf, sizeof(buf), weight, 17);
		strcpy(_weight, buf);
		_gcvt_s(buf, sizeof(buf), price, 17);
		strcpy(_price, buf);
	}

	friend ofstream& operator<<(ofstream& stream, Train_Route& obj)
	{
		stream << obj.Get_dell_code() << "▀" << obj.Get_from() << "▀" << obj.Get_to() << "▀" << obj.Get_distance() << "▀" << obj.Get_type() << "▀" << obj.volume << "▀" << obj.weight << "▀" << obj.price << "\n";
		return stream;
	}
	friend ifstream& operator>>(ifstream& stream, Train_Route& obj)
	{
		string dell_code, from, to, distance, type, svolume, sweight, sprice;

		getline(stream, dell_code, '▀');
		getline(stream, from, '▀');
		getline(stream, to, '▀');
		getline(stream, distance, '▀');
		getline(stream, type, '▀');
		getline(stream, svolume, '▀');
		getline(stream, sweight, '▀');
		getline(stream, sprice, '▀');

		obj.Set_dell_code(dell_code);
		obj.Set_from(from);
		obj.Set_to(to);
		obj.Set_distance(distance);
		obj.Set_type(type);
		obj.volume = atoi(svolume.c_str());
		obj.weight = atof(sweight.c_str());
		obj.price = atof(sprice.c_str());

		return stream;
	}

	void Set_price(double _price) { price = _price; }
	void Set_weight(double _weight) { weight = _weight; }
	void Set_volume(int _volume) { volume = _volume; }
};


class Motor_Route : public Route
{
	double tarif = 1.0;
	int max_volume = 100;
	double max_weight = 22;
	int volume;
	double price, weight;

public:
	Motor_Route() {};
	Motor_Route(int _volume, int _weight, double _price) : volume(_volume), weight(_weight), price(_price) {};

	void Get_Fields(char* _dell_code, char* _from, char* _to, char* _distance, char* _type, char* _volume, char* _weight, char* _price)
	{
		char buf[100] = "\0";

		strcpy(_dell_code, Get_dell_code().c_str());
		strcpy(_from, Get_from().c_str());
		strcpy(_to, Get_to().c_str());
		strcpy(_distance, Get_distance().c_str());
		strcpy(_type, Get_type().c_str());
		_itoa_s(volume, buf, sizeof(buf), 10);
		strcpy(_volume, buf);
		_gcvt_s(buf, sizeof(buf), weight, 17);
		strcpy(_weight, buf);
		_gcvt_s(buf, sizeof(buf), price, 17);
		strcpy(_price, buf);
	}

	friend ofstream& operator<<(ofstream& stream, Motor_Route& obj)
	{
		stream << obj.Get_dell_code() << "▀" << obj.Get_from() << "▀" << obj.Get_to() << "▀" << obj.Get_distance() << "▀" << obj.Get_type() << "▀" << obj.volume << "▀" << obj.weight << "▀" << obj.price << "\n";
		return stream;
	}
	friend ifstream& operator>>(ifstream& stream, Motor_Route& obj)
	{
		string dell_code, from, to, distance, type, svolume, sweight, sprice;

		getline(stream, dell_code, '▀');
		getline(stream, from, '▀');
		getline(stream, to, '▀');
		getline(stream, distance, '▀');
		getline(stream, type, '▀');
		getline(stream, svolume, '▀');
		getline(stream, sweight, '▀');
		getline(stream, sprice, '▀');

		obj.Set_dell_code(dell_code);
		obj.Set_from(from);
		obj.Set_to(to);
		obj.Set_distance(distance);
		obj.Set_type(type);
		obj.volume = atoi(svolume.c_str());
		obj.weight = atof(sweight.c_str());
		obj.price = atof(sprice.c_str());

		return stream;
	}

	void Set_price(double _price) { price = _price; }
	void Set_weight(double _weight) { weight = _weight; }
	void Set_volume(int _volume) { volume = _volume; }
};