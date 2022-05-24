#include "Libs.h"

class Product {
	string code;
	string cost;
	string group;
	string name;
	string dealer;
	string amount;

public:
	Product(){}; 
	Product(string _group, string _code, string _name, string _cost, string _dealer, string _amount) : group(_group), code(_code), name(_name), cost(_cost), dealer(_dealer), amount(_amount) {};

	friend ofstream& operator<<(ofstream& stream, Product& obj) {
		stream << obj.group << " " << obj.code << " " << obj.name << " " << obj.cost << " " << obj.dealer << " " << obj.amount << "\n";
		return stream;
	}
	friend ifstream& operator>>(ifstream& stream, Product& obj) {
		stream >> obj.group >> obj.code >> obj.name >> obj.cost >> obj.dealer >> obj.amount;
		return stream;
	}
	void getFields_to_User(char* _group, char* _name, char* _cost) {
		strcpy(_group, group.c_str());
		strcpy(_name, name.c_str());
		strcpy(_cost, cost.c_str());
	}
	void getFields_to_Admin(char* _group, char* _name, char* _cost, char* _code, char* _dealer) {
		strcpy(_group, group.c_str());
		strcpy(_code, code.c_str());
		strcpy(_dealer, dealer.c_str());
		strcpy(_name, name.c_str());
		strcpy(_cost, cost.c_str());
	}
	void getFields_to_Warehouse(char* _group, char* _name, char* _cost, char* _code, char* _dealer, char* _amount) {
		strcpy(_group, group.c_str());
		strcpy(_code, code.c_str());
		strcpy(_dealer, dealer.c_str());
		strcpy(_name, name.c_str());
		strcpy(_cost, cost.c_str());
		strcpy(_amount, amount.c_str());
	}
	string GetGroup() { return group; }
	void AddAmount(char* adding){
		char _amount[100];
		int _adding = atoi(adding);
		int _amount_ = atoi(amount.c_str());
		_itoa_s(_adding + _amount_, _amount, sizeof(_amount), 10);
		amount = _amount;
	}
	void SetAmount(char* _amount) {
		amount = _amount;
	}
	bool isExist() {
		if (amount == "0") return false;
		else return true;
	}
	string GetAmount() { return amount; }
};

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
	int volume, weight;

public:

	Air_Route() {};
	Air_Route(int _volume, int _weight) : volume(_volume), weight(_weight) {};

	friend ofstream& operator<<(ofstream& stream, Air_Route& obj)
	{
		stream << obj.Get_dell_code() << " " << obj.Get_from() << " " << obj.Get_to() << " " << obj.Get_distance() << " " << obj.Get_type() << " " << obj.volume << " " << obj.weight << "\n";
		return stream;
	}

	friend ifstream& operator>>(ifstream& stream, Air_Route& obj) 
	{
		string dell_code;
		string from;
		string to;
		string distance;
		string type;

		stream >> dell_code >> from >> to >> distance >> type >> obj.volume >> obj.weight;

		obj.Set_dell_code(dell_code);
		obj.Set_from(from);
		obj.Set_to(to);
		obj.Set_distance(distance);
		obj.Set_type(type);

		return stream;
	}

};

class Train_Route : public Route
{
	double tarif = 0.8;
	int max_volume = 75;
	int volume, weight;

public:
	Train_Route() {};
	Train_Route(int _volume, int _weight) : volume(_volume), weight(_weight) {};

	friend ofstream& operator<<(ofstream& stream, Train_Route& obj)
	{
		stream << obj.Get_dell_code() << " " << obj.Get_from() << " " << obj.Get_to() << " " << obj.Get_distance() << " " << obj.Get_type() << " " << obj.volume << " " << obj.weight << "\n";
		return stream;
	}

	friend ifstream& operator>>(ifstream& stream, Train_Route& obj)
	{
		string dell_code;
		string from;
		string to;
		string distance;
		string type;

		stream >> dell_code >> from >> to >> distance >> type >> obj.volume >> obj.weight;

		obj.Set_dell_code(dell_code);
		obj.Set_from(from);
		obj.Set_to(to);
		obj.Set_distance(distance);
		obj.Set_type(type);

		return stream;
	}

};


class Motor_Route : public Route
{
	double tarif = 1.0;
	int max_volume = 100;
	double max_weight = 22;
	int volume, weight;

public:
	Motor_Route() {};
	Motor_Route(int _volume, int _weight) : volume(_volume), weight(_weight) {};

	friend ofstream& operator<<(ofstream& stream, Motor_Route& obj)
	{
		stream << obj.Get_dell_code() << " " << obj.Get_from() << " " << obj.Get_to() << " " << obj.Get_distance() << " " << obj.Get_type() << " " << obj.volume << " " << obj.weight << "\n";
		return stream;
	}

	friend ifstream& operator>>(ifstream& stream, Motor_Route& obj)
	{
		string dell_code;
		string from;
		string to;
		string distance;
		string type;

		stream >> dell_code >> from >> to >> distance >> type >> obj.volume >> obj.weight;

		obj.Set_dell_code(dell_code);
		obj.Set_from(from);
		obj.Set_to(to);
		obj.Set_distance(distance);
		obj.Set_type(type);

		return stream;
	}

};