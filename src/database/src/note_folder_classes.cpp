#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

// The following is subject to change a lot depending on the evolution of the global code ~Peter

class BaseModel
{
public:
    BaseModel(std::string table_name, std::vector<std::string> cols) {}

    std::vector<std::string> get_cols()
    {
        return cols;
    }

    std::string get_table_name()
    {
        return table_name;
    }

    void save() {}
    void update(std::vector<std::string> new_data)
    {
        std::string acc = "";
        for (int i = 0; i < cols.size(); i++)
        {
            acc += cols[i] + " = ? ";
            if (i != cols.size() - 1)
            {
                acc += ", ";
            }
        }
        SQLite::Statement query(db, "UPDATE notes SET" + acc + "WHERE id = ?");
        query.bind(1, title);
        query.bind(2, content);
        query.bind(3, modified_date);
        query.bind(4, id);
        query.exec();
    }

private:
    std::string table_name;
    std::vector<std::string> cols;
};

/*
class Note {
public:
    Note() : title(""), content("") {}
    Note( std::string& title, std::string& content) : title(title), content(content) {}

    void display() {
        std::cout << "Title: " << title << "\nContent: " << content << "\n\n";
    }


    //other commands to add related to the design and graphics of the WebApp
    // define commands to edit content -> communicate with the UI team
    // add member time of last edit -> communicate with timer team

private:
    std::string title;
    std::string content;
    double last_edit_time;
};
// Class (Regroup) notes in folders (and subfolders)

class Folder {
public:
    void addNote( std::string& title,  std::string& content) {
        notes.emplace_back(title, content);
    }

    void displayAllNotes()  {
        if (notes.empty()) {
            std::cout << "No notes available.\n";
        } else {
            std::cout << "All Notes:\n";
            for (std::vector<Note>::iterator note = notes.begin(); note!=notes.end();note++)  { // or for (const auto& note : notes)
                note->display();
            }
        }
    }


    //define commands to edit title and order notes (in several types of order: time of last edit, alphabetical order, ascending or descending) -> communicate with the UI team


private:
    std::vector<Note> notes;
    std::string title;
};

template <typename T>
void rename(T& object) {
    std::cout << "Enter a title: ";
    std::getline(std::cin, object.title);
}

// define and implement a potential Window class to display several notes
*/