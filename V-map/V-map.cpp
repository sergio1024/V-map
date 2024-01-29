
#include <iostream>
#include <string>
#include <map>

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

	std::string userInput;
	std::cout << "1 - Type 'c' to print all value pairs:\n";
	std::getline(std::cin, userInput);

	if (userInput == "c") {
		std::cout << "All value pairs:\n\n";
		for (int i = 0; i < 26; i++) {
			std::cout << i << " => " << imap[i] << '\n';
		}
	}
	else {
		std::cout << "You have chosen not print the values.\n\n";
	}
}



//Creates a range map, assigns values to a range of keys, and prints the value associated with a specific key
static void Filter() {
	interval_map<int, char> imap(' ');
	imap.assign(0, 26, 'A');

	int key;
	bool validInput = false;

	while (!validInput) {
		std::cout << "3 - Enter now a value between 0 to 25: ";
		std::cin >> key;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta a entrada incorreta
			std::cout << "Invalid input! Please enter a number between 0 and 25.\n\n";
		}
		else if (key < 0 || key > 25) {
			std::cout << "Invalid key! Please enter a key between 0 and 25.\n\n";
		}
		else {
			validInput = true;
		}
	}

	char value = imap[key];
	std::cout << "\n\nThe result of the Filter function is as follows: \nThe value associated with key " + std::to_string(key) + " is: " << value << '\n'; // printing the value on the console
}




//Checks to see if there are any key pairs on the map that have the same value associated with them
static void CanonicalCheck() {
	interval_map<int, char> imap(' ');
	imap.assign(0, 26, 'A');

	std::cout << "\nThe result of the Canonical Check fuction is:";
	for (auto it1 = imap.begin(); it1 != imap.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != imap.end(); ++it2) {
			if (it1->second == it2->second) {
				std::cout << "\nThe values of the keys " << it1->first << " and " << it2->first << " are the same." << std::endl;
				return;
			}
		}
	}
	std::cout << " \nAll key value pair values are different.\n" << std::endl;
}

//Check if the value associated with key 5 and 10 are the same, the value of the keys can be changed freely,
static void Conditionals() {
	interval_map<int, char> imap(' ');
	imap.assign(0, 26, 'A');

	int key1, key2;

	while (true) {
		std::cout << "2 - Enter the first key value between 0 and 25:\n ";
		if (!(std::cin >> key1) || key1 < 0 || key1 > 25) {
			std::cout << "Invalid input! Please enter a number between 0 and 25.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}

	while (true) {
		std::cout << "2 - Enter the second key value between 0 and 25: ";
		if (!(std::cin >> key2) || key2 < 0 || key2 > 25 || key2 == key1) {
			std::cout << "Invalid input! Please enter a number between 0 and 25 that is different from the first key.\n\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			break;
		}
	}

	char val1 = imap[key1];
	char val2 = imap[key2];

	std::cout << "\nThe result of the Conditionals function is:";
	if (val1 == val2) {
		std::cout << "\nThe values associated with keys " << key1 << " and " << key2 << " are the same.\n";
	}
	else {
		std::cout << "\nThe values associated with keys " << key1 << " and " << key2 << " are not the same.\n";
	}
}




int main()
{
	std::cout << "Welcome!\n\n"
		"This is a map range that automatically assigns values to a range of keys and their respective pairs.\n"
		"The key value pair values are automatically assigned, and correspond to the letters of the alphabet\n\n"
		"Here you can check the content and take the test under 2 conditions:\n\n"
		"1 - Check the content\n"
		"2 - Are the values canonical? In other words, are they consecutive and non-repeating values?\n"
		"here the values of 2 keys will be compared, and it will be checked if all values are canonical\n"
		"3 - Displays the associated value of any key between 0 and 25\n\n"
		"Let's go:\n\n";

	IntervalMapTest();	
	Conditionals();
	CanonicalCheck();
	Filter();
}

// Sergio Arantes

