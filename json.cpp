// JSONexample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class Animal {
public:
	int id;
	string name;
	string breed;
	double weight;

	Animal(int id, const string& name, const string& breed, double weight)
		: id(id), name(name), breed(breed), weight(weight) {}

	json toJson() const {
		return json{
			{"id",id},
			{"name",name},
			{"breed", breed},
			{"weight",weight}
		};
	}

	Animal fromJson(const json& j) {
		return Animal(j["id"], j["name"], j["breed"], j["weight"]);
	}

};

template <typename T>
class DataSource {
private:
    string filename;
	json data;
	int currentId;

	void readFile() {
		ifstream inputFile(filename);
		if (inputFile) {
			inputFile >> data;
			currentId = data.empty() ? 1 : data.back()["id"] + 1;
		}
		else {
			currentId = 1;
		}
	}

	void writeFile(const json& j) {
		ofstream outputFile(filename);
		outputFile << j.dump(4);
	}

	/// <summary>
	/// Функция поиска по идентификатору
	/// </summary>
	/// <param name="id">Идентификатор</param>
	/// <returns>Индекс элемента или -1, если элемент не найден</returns>
	int FindById(int id) {
		int index = -1;
		for (int i = 0; i < data.size(); i++) {
			if (data[i]["id"] == id) {
				index = i;
				break;
			}
		}
		return index;
	}

public:

	DataSource(string filename) {
		readFile();
	}

	~DataSource() {
		writeFile(data);
	}

	//Создание нового элемента
	void create(const T& item) {
		Animal next(currentId, item.name, item.breed, item.weight);
		data.push_back(next.toJson());
		currentId++;
		writeFile(data);
	}

	void read() {
		cout << data.dump(4) << endl;
	}

	void update(const T& item) {
		int index = FindById(item.id);
		if (index != -1)
		{
			data[index] = item.toJson();
			writeFile(data);
		}
		else {
			cout << "Элемент с таким идентификатором не найден!" << endl;
		}
	}

	void remove(int id) {
		int index = FindById(id);
		if (index != -1) {
			data.erase(data.begin() + index);
			writeFile(data);
		}
		else {
			cout << "Элемент с таким идентификатором не найден!" << endl;
		}
	}

};



int main()
{
	setlocale(0, "ru");
	DataSource<Animal> dataSource("data.json");

	Animal animal1(1, "Bobik", "Dog", 10);
	Animal animal2(2, "Murka", "Cat", 5);

	dataSource.create(animal1);
	dataSource.create(animal2);

	cout << "Содержимое файла:" << endl;
	dataSource.read();

	//Animal updatedAnimal(3, "Bobik", "Dog", 20);
	//dataSource.update(updatedAnimal);
	//cout << "Содержимое файла:" << endl;
	//dataSource.read();

	dataSource.remove(1);
	cout << "Содержимое файла:" << endl;
	dataSource.read();

	return 0;
}
