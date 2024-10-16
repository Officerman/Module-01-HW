#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Класс книга
class Book {
private:
    string title;
    string author;
    string isbn;
    int copies;

public:
    Book(const string& title, const string& author, const string& isbn, int copies)
        : title(title), author(author), isbn(isbn), copies(copies) {}

    string getTitle() const {
        return title;
    }

    string getISBN() const {
        return isbn;
    }

    int getCopies() const {
        return copies;
    }

    void addCopies(int count) {
        copies += count;
    }

    bool borrow() {
        if (copies > 0) {
            --copies;
            return true;
        }
        return false;
    }

    void returnBook() {
        ++copies;
    }

    void show() const {
        cout << "Название: " << title << ", Автор: " << author
             << ", ISBN: " << isbn << ", Количество: " << copies << endl;
    }
};

// Класс читатель
class Reader {
private:
    string name;
    int id;

public:
    Reader(const string& name, int id) : name(name), id(id) {}

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    void show() const {
        cout << "Имя: " << name << ", ID: " << id << endl;
    }
};

// Класс библиопеки
class Library {
private:
    vector<shared_ptr<Book>> books;
    vector<shared_ptr<Reader>> readers;

public:
    // Управление книгами
    void addBook(const shared_ptr<Book>& book) {
        books.push_back(book);
    }

    void removeBook(const string& isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->getISBN() == isbn) {
                books.erase(it);
                cout << "Книга с ISBN " << isbn << " удалена." << endl;
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    void showBooks() const {
        cout << "Список книг:" << endl;
        for (const auto& book : books) {
            book->show();
        }
    }

    // Управление читателями
    void addReader(const shared_ptr<Reader>& reader) {
        readers.push_back(reader);
    }

    void removeReader(int id) {
        for (auto it = readers.begin(); it != readers.end(); ++it) {
            if ((*it)->getId() == id) {
                readers.erase(it);
                cout << "Читатель с ID " << id << " удалён." << endl;
                return;
            }
        }
        cout << "Читатель с ID " << id << " не найден." << endl;
    }

    void showReaders() const {
        cout << "Список читателей:" << endl;
        for (const auto& reader : readers) {
            reader->show();
        }
    }

    // Выдача и возврат
    void borrowBook(const string& isbn, int readerId) {
        for (const auto& book : books) {
            if (book->getISBN() == isbn) {
                if (book->borrow()) {
                    cout << "Книга " << book->getTitle() << " выдана читателю с ID " << readerId << "." << endl;
                } else {
                    cout << "Нет доступных экземпляров книги " << book->getTitle() << "." << endl;
                }
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }

    void returnBook(const string& isbn) {
        for (const auto& book : books) {
            if (book->getISBN() == isbn) {
                book->returnBook();
                cout << "Книга " << book->getTitle() << " возвращена." << endl;
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена." << endl;
    }
};

// Функция для тестирования библиотеки
void testLibrary() {
    // Создание библиотеки
    Library library;

    // Добавление книг 
    shared_ptr<Book> book1 = make_shared<Book>("Герои Вархаммера", "Гэри Гибсон", "978-1234567890", 5);
    shared_ptr<Book> book2 = make_shared<Book>("Мрак и свет", "Дэн Абнетт", "978-0987654321", 3);
    shared_ptr<Book> book3 = make_shared<Book>("Сага о Вархаммере", "Грэм МакНил", "978-1122334455", 4);
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    // Регистрация читателей
    shared_ptr<Reader> reader1 = make_shared<Reader>("Алексей", 101);
    shared_ptr<Reader> reader2 = make_shared<Reader>("Мария", 102);
    library.addReader(reader1);
    library.addReader(reader2);

    // Отображение книг и читателей
    library.showBooks();
    library.showReaders();

    // Выдача и возврат книг
    library.borrowBook("978-1234567890", 101); // Алексей берет "Герои Вархаммера"
    library.borrowBook("978-0987654321", 102); // Мария берет "Мрак и свет"
    library.returnBook("978-1234567890"); // Алексей возвращает "Герои Вархаммера"

    // Удаление книги и читателя
    library.removeBook("978-0987654321");
    library.removeReader(102);

    // Отображение после удаления
    library.showBooks();
    library.showReaders();
}

int main() {
    testLibrary();
    return 0;
}
