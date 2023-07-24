#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Time {
	int Seconds;
	int Minutes;
	int Hours;
public:
	Time(int s, int m, int h) {
		this->Seconds = s;
		this->Minutes = m;
		this->Hours = h;
	}

	Time() :Time(0, 0, 0) {};

	Time(const Time& t) {
		this->Seconds = t.Seconds;
		this->Minutes = t.Minutes;
		this->Hours = t.Hours;
	}

	bool operator!=(Time& t) {
		return this->Seconds == t.Seconds && this->Minutes == t.Minutes && this->Hours == t.Hours ? false : true;
	}

	bool operator==(Time& t) {
		return this->Seconds == t.Seconds && this->Minutes == t.Minutes && this->Hours == t.Hours ? true : false;
	}

	bool operator==(short& t) {
		return  this->Minutes == t? true : false;
	}

	bool operator <(Time& t) {
		return this->Hours < t.Hours ? true : this->Hours == t.Hours ? this->Minutes < t.Minutes ? true : this->Minutes == t.Minutes ? this->Seconds < t.Seconds ? true : false : false : false;
	}

	bool operator >(Time& t) {
		return this->Hours > t.Hours ? true : this->Hours == t.Hours ? this->Minutes > t.Minutes ? true : this->Minutes == t.Minutes ? this->Seconds > t.Seconds ? true : false : false : false;
	}

	void operator+=(size_t seconds) {
		if (seconds >= 60) {
			if (seconds >= 3600) {
				int h = seconds / 3600;
				this->Hours += h;
				seconds -= h * 3600;
			}
			int m = seconds / 60;
			this->Minutes += m;
			seconds -= m * 60;
		}
		this->Seconds += seconds;
	}

	void operator()(int s, int m, int h) {
		this->Seconds = s;
		this->Minutes = m;
		this->Hours = h;
	}

	friend ostream& operator<<(ostream& out, Time& t);;
	friend void operator++(Time& t);
};

void operator++(Time& t) {
	t.Minutes++;
	if (t.Minutes >= 60) {
		t.Minutes -= 60;
		t.Hours++;
	}
}

ostream& operator<<(ostream& out, Time& t) {
	out << t.Hours << ":" << t.Minutes << ":" << t.Seconds;
	return out;
}

class Human {			//добав цей клас,щоб не було просто масиву int*
	string name;
public:
	Human() {
		int r = rand() % 10 + 1;
		switch (r)
		{
		case 1:
			this->name = "Vova";
			break;
		case 2:
			this->name = "Anriy";
			break;
		case 3:
			this->name = "Vika";
			break;
		case 4:
			this->name = "Iryna";
			break;
		case 5:
			this->name = "Sergiy";
			break;
		case 6:
			this->name = "Oleksandr";
			break;
		case 7:
			this->name = "Oleksandra";
			break;
		case 8:
			this->name = "Sophia";
			break;
		case 9:
			this->name = "Roma";
			break;
		case 10:
			this->name = "Dima";
			break;
		}

	}
};

class Queue {
	int size;
	Human* arr;
public:
	Queue(int t, Human* a){
		this->size = t;
		arr = new Human[t];
		for (int i = 0; i < t; i++) {
			arr[i] = a[i];
		}
	}

	Queue() {
		this->size = 0;
		arr = nullptr;
	}

	~Queue() {
		if (arr != nullptr) {
			delete[]arr;
		}
	}

	int getSize()const {
		return size;
	}

	void clear() {
		if (arr != nullptr) {
			delete[] arr;
			arr = nullptr;
		}
		size = 0;
	}

	friend void operator++(Queue& q);
	friend void operator--(Queue& q);
};

void operator++(Queue& q){
	Human* newArr = new Human[q.size + 1];
	for (int i = 0; i < q.size; i++) {
		newArr[i] = q.arr[i];
	}
	Human human;
	newArr[q.size] = human;
	if (q.arr != nullptr) {
		delete[] q.arr;
	}
	q.arr = newArr;
	q.size++;
}

void operator--(Queue& q){
	if (q.size > 0) {
		Human* newArr = new Human[q.size - 1];
		for (int i = 1; i < q.size; i++) {
			newArr[i - 1] = q.arr[i];
		}
		delete[] q.arr;
		q.arr = newArr;
		q.size--;
	}
}

class Bus {
	Queue queue;
	int numberOfSeats;
	int numberOfFreeSeats;
public:
	Bus() {
		this->numberOfSeats = 15 + (rand() % 11);
		this->numberOfFreeSeats = numberOfSeats;
		for (int i = 0; i < (numberOfSeats - 14) % 6; i++) {
			++queue;
			numberOfFreeSeats--;
		}
	}

	void randomize() {
		this->numberOfSeats = 15 + (rand() % 11);
		this->numberOfFreeSeats = numberOfSeats - (rand() % (numberOfSeats + 1));
		for (int i = 0; i < numberOfSeats - numberOfFreeSeats; i++) {
			++queue;
		}
	}

	Queue& stop(Queue& queue) {
		int NOFS = numberOfFreeSeats;
		numberOfFreeSeats = numberOfFreeSeats - queue.getSize() <= 0 ? 0 : numberOfFreeSeats - queue.getSize();
		for (int i = 0; i < NOFS - numberOfFreeSeats; i++) {
			--queue;
			++this->queue;
		}
		return queue;
	}

	void info()const {
		cout << "Passengers : " << numberOfSeats - numberOfFreeSeats << endl;
		cout << "Numbrer of seats : " << numberOfSeats << endl;
	}
};

class BusStop {
	int averageArrivalTimeOfPassengers;
	int averageArrivalTimeOfBuses;
	bool stopType;
	Queue queue;
public:
	BusStop(int AATOPIM, int AATOPIA, int AATOPIE, int AATOBIM, int AATOBIA, int AATOBIE, bool ST) {
		this->averageArrivalTimeOfPassengers = (AATOPIM + AATOPIA + AATOPIE) / 3;
		this->averageArrivalTimeOfBuses = (AATOBIM + AATOBIA + AATOBIE) / 3;
		this->stopType = ST;
	}

	BusStop(int AATOPIM, int AATOPIA, int AATOPIE, int AATOBIM, int AATOBIA, int AATOBIE, bool ST, int MN, int numberOfPeople) {
		this->averageArrivalTimeOfPassengers = (AATOPIM + AATOPIA + AATOPIE) / 3;
		this->averageArrivalTimeOfBuses = (AATOBIM + AATOBIA + AATOBIE) / 3;
		this->stopType = ST;
		for (int i = 0; i < numberOfPeople; i++) {
			++queue;
		}
	}

	void info()const{
		cout << "People at the station: " << queue.getSize() << endl;
	}

	int getSatisfactoryAverage(int maxNumberOfPeopleInStation){		//ну тут,мабуть, можна було зробити набагато легше обрахувавши середні значені ну і почаклувавши над ними
		Time time(0, 0, 0);											//але зробив якось так, щось типу симуляції, правда далеко не самої точної
		Bus bus;
		int average = 1;
		short nextPassenger = 0;
		short nextBus = 0;
		for (int i = 0;;++time, i++) {
			if (time == nextPassenger) {
				++queue;
				nextPassenger = (nextPassenger + averageArrivalTimeOfPassengers) % 60;
				if (i >= 15 && queue.getSize() < maxNumberOfPeopleInStation) {
					i = 0;
					average++;
				}
				else if (queue.getSize() > maxNumberOfPeopleInStation) {
					return --average;
					time(0, 0, 0);
					nextPassenger = 0;
					nextBus = 0;
					queue.clear();
					continue;
				}
			}
			if (time == nextBus) {
				queue = bus.stop(queue);
				nextBus = (nextBus + average) % 60;
			}
			
		}
	}
};

struct Client {
	string name;
	short priority;

	Client(string n, short p) :name(n), priority(p) {};

	Client() :Client("No name", 999) {};

	void operator()(string n, short p) {
		this->name = n;
		this->priority = p;
	}

	void operator()(Client& c) {
		this->name = c.name;
		this->priority = c.priority;
	}
};

class Statistics {
	string* names;
	Time* time;
	int size;
public:
	Statistics() {
		names = nullptr;
		time = nullptr;
		size = 0;
	}

	void initStatistics(Client* c, int s) {
		if (names != nullptr) {
			delete[] names;
			delete[] time;
		}
		names = new string[s];
		time = new Time[s];
		for (int i = 0; i < s; i++) {
			names[i] = c[i].name;
			time[i] += rand() % 20 < 16 ? 20 + rand() % 101 : 20 + rand() % 461;
		}
		this->size = s;
	}

	void info()const {
		for (int i = 0; i < size; i++) {
			cout <<i << ")\t" << names[i] << "\t:\t" << time[i] << endl;
		}
		cout << endl;
	}

	~Statistics() {
		if (names != nullptr) {
			delete[] names;
			delete[] time;
		};
	}
};

class PrinterQueue {
	Client* queue;
	Statistics statistics;
	int size;
public:
	PrinterQueue() {
		queue = nullptr;
		size = 0;
	}

	void operator()(string name, short priority) {
		Client* newQueue = new Client[size + 1];
		for (int i = 0; i < size; i++) {
			newQueue[i] = queue[i];
		}
		newQueue[size](name, priority);
		for (int i = 0; i < size; i++) {
			if (queue[i].priority > priority) {
				for (int j = i; j < size; j++) {
					swap(newQueue[j], newQueue[size]);
				}
				break;
			}
		}
		if (queue != nullptr) {
			delete[] queue;
		}
		queue = newQueue;
		size++;
	}

	void showStatistics() {
		statistics.initStatistics(queue, size);
		statistics.info();
	}

	~PrinterQueue() {
		if (queue != nullptr) {
			delete[] queue;
		}
	}
};

void swap(Client& c1, Client& c2) {
	Client c(c1);
	c1(c2);
	c2(c);
}

void main() {
	srand(time(NULL));
	BusStop bus_stop(6, 8, 10, 30, 25, 30, 1);
	int a = 15;
	cout << "Buses have to arrived every "<< bus_stop.getSatisfactoryAverage(a) << " minutes to number of people dont exceed then " << a << endl;
	cout << "############################################################################################################" << endl << endl;
	PrinterQueue queue;
	queue("Vova", 2);
	queue("Kolya", 1);
	queue("Sergiy", 5);
	queue("Sasha", 2);
	queue("Vika", 3);
	queue("Viktor", 1);
	queue("Natalia", 2);
	queue("Vitya", 5);
	queue("Luka", 4);
	queue.showStatistics();
}