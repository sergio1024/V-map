//_______________________________________________________________
//_______________________________________________________________
//In this solution I used Visual Studio 2022 to compile
//______________________________________________________________
//With this solution we can implement the values of each key value pair,
//view all the values,
//filter the value that corresponds to each key,
//verify that all values are different, and
//make comparisons between values.
//_______________________________________________________________
//_______________________________________________________________


#include <iostream>
#include <string>
#include <map>

char Valf = 10; //Key from which we want to get the value on the filter function

template<typename K, typename V>

class interval_map {

	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K, V> m_map;

public:

	interval_map(V const& val)
		: m_valBegin(val)
	{}

	typename std::map<K, V>::iterator begin() {
		return m_map.begin();
	}

	typename std::map<K, V>::iterator end() {
		return m_map.end();
	}

	void assign(K const& keyBegin, K const& keyEnd, V const& val) {

		try {
			if (!(keyBegin < keyEnd)) {
				throw std::invalid_argument("keyBegin should be less than the keyEnd");
			}

			K key = keyBegin;
			V value = val;

			while (key < keyEnd) {
				m_map[key] = value;
				key++;
				value++;
			}
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "Erro: " << e.what() << '\n';
		}
		catch (...) {
			std::cerr << "An unknown error has occurred.\n";
		}
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin()) {
			return m_valBegin;
		}
		else {
			return (--it)->second;
		}
	}
};

//Creates a range map, assigns values to a range of keys, and prints all key-value pairs
void IntervalMapTest() {

	interval_map<int, char> imap(' ');
	imap.assign(0, 26, 'A');
	std::cout << "All value pairs values:\n";

	for (int i = 0; i < 26; i++) {
		std::cout << i << " => " << imap[i] << '\n';
	}

}

//Creates a range map, assigns values to a range of keys, and prints the value associated with a specific key
static void Filter() {
	interval_map<int, char> imap(' ');
	imap.assign(0, 26, 'A');
	char value = imap[Valf];
	std::cout << "\nThe result of the Filter function is as follows: \nThe value associated with key " + std::to_string(Valf) + " is: " << value << '\n'; // printing the value on the console
}

//Checks to see if there are any key pairs on the map that have the same value associated with them
static void CanonicalCheck() {
	interval_map<int, char> imap(' ');
	imap.assign(0, 26, 'A');

	std::cout << "\nThe result of the CanonicalCheck fuction is:";
	for (auto it1 = imap.begin(); it1 != imap.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != imap.end(); ++it2) {
			if (it1->second == it2->second) {
				std::cout << "\nThe values of the keys " << it1->first << " and " << it2->first << " are the same." << std::endl;
				return;
			}
		}
	}
	std::cout << " \nAll key value pair values are different." << std::endl;
}

//Check if the value associated with key 5 and 10 are the same, the value of the keys can be changed freely,
//2 global variables can also be created to make the comparison. It makes it easier to access the code.
//example :
//char a = 5;
//char b = 10;
//And then replace:
//char val1 = imap[5];
//char val2 = imap[10];
//by;
//char val1 = imap[a];
//char val2 = imap[b];
static void Conditionals() {
	interval_map<int, char> imap(' ');
	imap.assign(0, 26, 'A');

	char val1 = imap[5];
	char val2 = imap[10];

	std::cout << "\nThe result of the Conditionals function is:";
	if (val1 == val2) {
		std::cout << "\nThe values associated with keys 5 and 10 are the same.\n";
	}
	else {
		std::cout << "\nThe values associated with keys 5 and 10 are not the same.\n";
	}
}


int main()
{
	IntervalMapTest();
	Filter();
	CanonicalCheck();
	Conditionals();
}


