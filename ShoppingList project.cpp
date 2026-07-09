https://youtu.be/HBhUwqfXfWw?si=WoYm-M7M-NNb8Jln #include <iostream>
#include <string>
#include <limits>
using namespace std;

class Item {
public:
	string name;
	int quantity;
	double price;

	Item() {
		name = "";
		quantity = 0;
		price = 0;
	}

	Item(string n, int q, double p) {
		name = n;
		quantity = q;
		price = p;
	}

	void input() {
		cout << "Enter item name (one word): ";
		cin >> name;
		while (true) {
			cout << "Enter quantity: ";
			if (cin >> quantity && quantity >= 0) break;
			else {
				cout << "Invalid input! Enter a positive number.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		while (true) {
			cout << "Enter price: ";
			if (cin >> price && price >= 0) break;
			else {
				cout << "Invalid input! Enter a positive number.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}

	void show() {
		cout << "Name: " << name << endl;
		cout << "Quantity: " << quantity << endl;
		cout << "Price: $" << price << endl;
		cout << "Total price: $" << quantity * price << endl;
	}

	double totalPrice() {
		return quantity * price;
	}
};

class ShoppingList {
private:
	Item items[100];
	int n;

public:
	ShoppingList() {
		n = 0;
		initializeDefaultItems();
	}

	bool isEmpty() { return n == 0; }
	bool isFull() { return n >= 100; }

	void initializeDefaultItems() {
		addDefaultItem("Apple", 5, 1.99);
		addDefaultItem("Potato", 10, 0.89);
		addDefaultItem("Banana", 6, 1.29);
		addDefaultItem("Cucumber", 4, 1.49);
		addDefaultItem("Blueberry", 2, 3.99);
		addDefaultItem("Strawberry", 3, 4.49);
	}

	void addDefaultItem(string name, int qty, double price) {
		if (isFull()) return;
		items[n] = Item(name, qty, price);
		n++;
	}

	void addItem() {
		if (isFull()) {
			cout << "List is full!\n";
			return;
		}
		items[n].input();
		n++;
		cout << "Item added successfully!\n";
	}

	void showAllItems() {
		if (isEmpty()) {
			cout << "List is empty!\n";
			return;
		}
		for (int i = 0; i < n; i++) {
			cout << "\nItem " << i + 1 << ":\n";
			items[i].show();
			cout << "------------------------\n";
		}
	}

	void showItemByNumber() {
		if (isEmpty()) {
			cout << "List is empty!\n";
			return;
		}
		int num;
		cout << "Enter item number: ";
		cin >> num;
		if (num < 1 || num > n) {
			cout << "Invalid number!\n";
			return;
		}
		items[num - 1].show();
	}

	void showItemByName() {
		if (isEmpty()) {
			cout << "List is empty!\n";
			return;
		}
		string name;
		cout << "Enter item name (one word): ";
		cin >> name;
		bool found = false;
		for (int i = 0; i < n; i++) {
			if (items[i].name == name) {
				items[i].show();
				found = true;
			}
		}
		if (!found)
			cout << "Item not found!\n";
	}

	void removeItemByName() {
		if (isEmpty()) {
			cout << "List is empty!\n";
			return;
		}
		string name;
		cout << "Enter item name (one word) to remove: ";
		cin >> name;
		bool removed = false;
		for (int i = 0; i < n; i++) {
			if (items[i].name == name) {
				for (int j = i; j < n - 1; j++)
					items[j] = items[j + 1];
				n--;
				removed = true;
				i--;
			}
		}
		if (removed)
			cout << "Item(s) removed!\n";
		else
			cout << "Item not found!\n";
	}
	void updateItem() {
		if (isEmpty()) {
			cout << "List is empty!\n";
			return;
		}
		string name;
		cout << "Enter item name (one word) to update: ";
		cin >> name;
		bool updated = false;
		for (int i = 0; i < n; i++) {
			if (items[i].name == name) {
				while (true) {
					cout << "Enter new quantity: ";
					if (cin >> items[i].quantity && items[i].quantity >= 0) break;
					else {
						cout << "Invalid input! Enter a positive number.\n";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
				while (true) {
					cout << "Enter new price: ";
					if (cin >> items[i].price && items[i].price >= 0) break;
					else {
						cout << "Invalid input! Enter a positive number.\n";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
				updated = true;
			}
		}
		if (updated)
			cout << "Item(s) updated!\n";
		else
			cout << "Item not found!\n";
	}

	double calculateTotalPrice() {
		double sum = 0;
		for (int i = 0; i < n; i++)
			sum += items[i].totalPrice();
		return sum;
	}

	void showOnlyNames() {
		if (isEmpty()) {
			cout << "List is empty!\n";
			return;
		}
		for (int i = 0; i < n; i++)
			cout << i + 1 << ". " << items[i].name << endl;
	}

	void showOnlyTotals() {
		if (isEmpty()) {
			cout << "List is empty!\n";
			return;
		}
		for (int i = 0; i < n; i++)
			cout << items[i].name << " -> $" << items[i].totalPrice() << endl;
	}

	void showDefaultItems() {
		cout << "\n===== Default Shopping List =====\n";
		showAllItems();
	}
};

void showMainMenu() {
	cout << "\n===== MAIN MENU =====\n";
	cout << "1. Add item\n";
	cout << "2. Show items menu\n";
	cout << "3. Update item\n";
	cout << "4. Remove item\n";
	cout << "5. Show total price\n";
	cout << "0. Exit\n";
	cout << "Choice: ";
}

void showDisplayMenu() {
	cout << "\n--- DISPLAY MENU ---\n";
	cout << "1. Show all items\n";
	cout << "2. Show item by name\n";
	cout << "3. Show item by number\n";
	cout << "4. Show only item names\n";
	cout << "5. Show item totals\n";
	cout << "0. Back to main menu\n";
	cout << "Choice: ";
}

int main() {
	ShoppingList list;

	// Show default items immediately at startup
	list.showDefaultItems();

	int choice;
	bool exitProgram = false;

	while (!exitProgram) {
		showMainMenu();
		cin >> choice;

		if (choice == 1) list.addItem();
		else if (choice == 2) {
			int subChoice;
			bool backToMain = false;
			while (!backToMain) {
				showDisplayMenu();
				cin >> subChoice;
				if (subChoice == 1) list.showAllItems();
				else if (subChoice == 2) list.showItemByName();
				else if (subChoice == 3) list.showItemByNumber();
				else if (subChoice == 4) list.showOnlyNames();
				else if (subChoice == 5) list.showOnlyTotals();
				else if (subChoice == 0) backToMain = true;
				else cout << "Wrong choice!\n";
			}
		}
		else if (choice == 3) list.updateItem();
		else if (choice == 4) list.removeItemByName();
		else if (choice == 5) cout << "Total price = $" << list.calculateTotalPrice() << endl;
		else if (choice == 0) exitProgram = true;
		else cout << "Wrong choice!\n";
	}

	cout << "Exiting program...\n";
	return 0;
}