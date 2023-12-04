/*
 *
 * @file  main.cpp
 * @brief A few short examples in a row.
 *
 *  Demonstrates how-to use the SQLite++ wrapper
 *
 * Copyright (c) 2012-2023 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

namespace SQLite
{
    /// definition of the assertion handler enabled when SQLITECPP_ENABLE_ASSERT_HANDLER is defined in the project (CMakeList.txt)
    void assertion_failed(const char *apFile, const long apLine, const char *apFunc, const char *apExpr, const char *apMsg)
    {
        // Print a message to the standard error output stream, and abort the program.
        std::cerr << apFile << ":" << apLine << ":"
                  << " error: assertion failed (" << apExpr << ") in " << apFunc << "() with message \"" << apMsg << "\"\n";
        std::abort();
    }
}

void initializeDatabase(SQLite::Database &db)
{
    db.exec("CREATE TABLE IF NOT EXISTS notes (id INTEGER PRIMARY KEY, title TEXT, content TEXT, modified_date TEXT)");
}

void insertNote(SQLite::Database &db, const std::string &title, const std::string &content, const std::string &modified_date)
{
    SQLite::Statement query(db, "INSERT INTO notes (title, content, modified_date) VALUES (?, ?, ?)");
    query.bind(1, title);
    query.bind(2, content);
    query.bind(3, modified_date);
    query.exec();
}

void updateNote(SQLite::Database &db, int id, const std::string &title, const std::string &content, const std::string &modified_date)
{
    SQLite::Statement query(db, "UPDATE notes SET title = ?, content = ?, modified_date = ? WHERE id = ?");
    query.bind(1, title);
    query.bind(2, content);
    query.bind(3, modified_date);
    query.bind(4, id);
    query.exec();
}

void deleteNote(SQLite::Database &db, int id)
{
    SQLite::Statement query(db, "DELETE FROM notes WHERE id = ?");
    query.bind(1, id);
    query.exec();
}

int main()
{
    try
    {

        SQLite::Database db("notes.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        initializeDatabase(db);

        // Insert a note
        insertNote(db, "Note Title", "Note Content", "2022-01-01");

        // Update a note
        updateNote(db, 1, "Updated Note Title", "Updated Note Content", "2022-01-02");

        // Delete a note
        deleteNote(db, 1);

        /*
                // Define event handlers for each button
        Button insertButton = getButton("insertButton");
        insertButton.onClick([&]() {
            insertNote(db, getFormFieldValue("title"), getFormFieldValue("content"), getFormFieldValue("date"));
        });

        Button updateButton = getButton("updateButton");
        updateButton.onClick([&]() {
            updateNote(db, getFormFieldValue("id"), getFormFieldValue("title"), getFormFieldValue("content"), getFormFieldValue("date"));
        });

        Button deleteButton = getButton("deleteButton");
        deleteButton.onClick([&]() {
            deleteNote(db, getFormFieldValue("id"));
        });

        // Start the UI event loop
        startEventLoop();*/
    }
    catch (std::exception &e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return EXIT_FAILURE; // unexpected error : exit the example program
    }
    std::cout << "everything ok, quitting\n";
    return 0;
}
