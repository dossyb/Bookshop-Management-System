#include <string>
#include <vector>
#include <iostream>
#include "include/input.h"

using std::string;
using std::vector;

enum book_update_option
{
    UPDATE_NAME,
    UPDATE_AUTHOR,
    UPDATE_PRICE,
    ADD_GENRES,
    UPDATE_SERIES,
    UPDATE_STOCK,
    FINISH_BOOK_UPDATE
};

struct book_data
{
    string name;
    string author;
    double price;
    string series;
    int series_no = -1;
    vector<string> genres;
    int stock;
};

book_data read_book()
{
    book_data result;

    result.name = read_string("Enter name of book: ");
    result.author = read_string("Enter the book's author: ");
    result.price = read_double("Enter the book's price: ");
    result.stock = read_integer("Enter how many copies are in stock: ");

    system("CLS");
    write_line("Book added.");
    write_line(" ");

    return result;
}

void write_book_summary(const book_data &book)
{
    write(book.name + " by " + book.author + " | $");
    write_double(book.price);
    write_line(" | " + std::to_string(book.stock) + " in stock");
}

void write_book_full(const book_data &book)
{
    write(book.name + " by " + book.author + " | $");
    write_double(book.price);
    write_line(" | " + std::to_string(book.stock) + " in stock");
    write_line("==============================================");
    if ( book.series_no != -1)
    {
        write_line("Book " + std::to_string(book.series_no) + " of the " + book.series + " series");
        write_line(" ");
    }
    write_line("This book has the following genres:");
    for (int i = 0; i < book.genres.size(); i++)
    {
        write_line(book.genres[i]);
    }
}

book_update_option read_book_update_option()
{
    int result;

    write_line("1: Update name");
    write_line("2: Update author");
    write_line("3: Update price");
    write_line("4: Add genres");
    write_line("5: Add series info");
    write_line("6: Update stock");
    write_line("7: Finish update");
    write_line(" ");
    result = read_integer("Select option: ");

    return static_cast<book_update_option>(result - 1);
}

void update_book(book_data &book)
{
    book_update_option option;
    string genre; 
    do
    {
        system("CLS");  
        write_line(" ");
        write_line("== Update Book ==");
        write_line(" ");
        write_book_full(book);
        write_line(" ");
        option = read_book_update_option();

        switch (option)
        {
        case UPDATE_NAME:
            book.name = read_string("Enter new name: ");
            break;
        case UPDATE_AUTHOR:
            book.author = read_string("Enter new author: ");
            break;
        case UPDATE_PRICE:
            book.price = read_double("Enter new price: ");
            break;
        case ADD_GENRES:
            genre = read_string("Add a genre to this book: ");
            book.genres.push_back(genre);
            break;
        case UPDATE_SERIES:
            book.series = read_string("Enter series name: ");
            book.series_no = read_integer("Enter number of book in series: ");
            break;
        case UPDATE_STOCK:
            book.stock = read_integer("Enter new stock: ");
            break;
        case FINISH_BOOK_UPDATE:
            break;
        }
    } while (option != FINISH_BOOK_UPDATE); 
    system("CLS");
}

enum shop_update_option
{
    ADD_BOOK,
    DELETE_BOOK,
    UPDATE_BOOK,
    GET_BOOK_DETAILS,
    SHOW_INVENTORY,
    FINISH_SHOP_UPDATE
};

struct shop_data
{
    string name;
    vector<book_data> books;
};

shop_update_option read_shop_update_option()
{
    int result;

    write_line("1: Add book");
    write_line("2: Delete book");
    write_line("3: Update book");
    write_line("4: Get book details");
    write_line("5: Show books in stock");
    write_line("6: Finish update");
    write_line(" ");
    result = read_integer("Select option: ");

    return static_cast<shop_update_option>(result - 1);
}

void write_inventory(const shop_data &shop)
{
    system("CLS");
    write_line(" ");
    write_line("============== Shop Inventory ================");
    for (int i = 0; i < shop.books.size(); i++)
    {
        write_book_summary(shop.books[i]);
    }
    write_line("==============================================");
    write_line(" ");
}

int select_book(const shop_data &shop)
{
    system("CLS");
    int sel;
    write_line(" ");
    for (int i = 0; i < shop.books.size(); i++)
    {
        write(shop.books[i].name);
        write(" by " + shop.books[i].author);
        write_line(" | ID " + std::to_string(i));
    }
    write_line(" ");
    sel = read_integer("Please select a book by entering its ID number: ");
    while ( sel > shop.books.size())
    {
        sel = read_integer("Please enter a valid ID number: ");
    }
    return sel;
}

void delete_book(shop_data &shop, int index)
{
    if ( index >= 0 and index < shop.books.size())
    {
        int last_index = shop.books.size() - 1;
        shop.books[index] = shop.books[last_index];
        shop.books.pop_back();
    }
    system("CLS");
    write_line("Book deleted.");
    write_line(" ");
}

void query_book(const shop_data &shop)
{
    book_data book;
    book = shop.books[select_book(shop)];
    system("CLS");
    write_line(" ");
    write_book_full(book);
    write_line(" ");
}

void add_book(shop_data &shop)
{
    book_data new_book = read_book();
    shop.books.push_back(new_book);
}

void update_shop(shop_data &shop)
{
    shop_update_option option;
    int sel;
    system("CLS");
    do
    {
        write_line("==============================================");
        write_line("       Welcome to The Cognitive Realm");
        write_line("==============================================");
        write_line(" ");
        write_line("== Manage " + shop.name + "'s Inventory ==");
        write_line(" ");
        option = read_shop_update_option();

        switch (option)
        {
        case ADD_BOOK:
            add_book(shop);
            break;
        case DELETE_BOOK:
            sel = select_book(shop);
            delete_book(shop, sel);
            break;
        case UPDATE_BOOK:
            update_book(shop.books[select_book(shop)]);
            break;
        case GET_BOOK_DETAILS:
            query_book(shop);
            break;
        case SHOW_INVENTORY:
            write_inventory(shop);
            break;
        case FINISH_SHOP_UPDATE:
            break;
        }
    } while (option != FINISH_SHOP_UPDATE);
    
}

int main()
{
    shop_data my_shop;
    my_shop.name = "The Cognitive Realm";

    update_shop(my_shop);

    return 0;
}