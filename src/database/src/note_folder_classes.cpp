#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

#include <sqlite_orm/sqlite_orm.h>

#include "database.hpp"

using namespace sqlite_orm;

// Storage
// This is the storage class that will be used to interact with the database
auto storage = make_storage("concept.db",
                            make_table("note",
                                       make_column("title", &Note::title),
                                       make_column("content", &Note::content),
                                       make_column("last_modified", &Note::last_modified)),
                            make_table("folder",
                                       make_column("title", &Folder::title),
                                       make_column("notes", &Folder::notes)),
                            make_table("focus_time",
                                       make_column("time_spent", &Focus_time::time_spent)),
                            make_table("commands",
                                       make_column("command_name", &Commands::command_name),
                                       make_column("command_description", &Commands::command_description)));


class Note : BaseModel
{
public:
    Note(std::string title, std::string content, std::time_t last_modified)
        : BaseModel("note", {{"title", "TEXT"}, {"content", "TEXT"}, {"last_modified", "INTEGER"}})
    {
        this->title = title;
        this->content = content;
        this->last_modified = last_modified;
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("title", &Note::title),
                                               make_column("content", &Note::content),
                                               make_column("last_modified", &Note::last_modified)));

        storage.sync_schema();

        storage.update(*this);
    }

    void update(std::string title, std::string content, std::time_t last_modified)
    {
        this->title = title;
        this->content = content;
        this->last_modified = last_modified;
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("title", &Note::title),
                                               make_column("content", &Note::content),
                                               make_column("last_modified", &Note::last_modified)));

        storage.sync_schema();

        storage.update(*this);
    }
    // Variable declaration :
    std::string title;
    std::string content;
    std::time_t last_modified;
};

// I'm not sure the below Folder Class would work as is, but it's a start ~Alex

class Folder : BaseModel
{
public:
    Folder(std::string title, std::vector<Note> notes)
        : BaseModel("folder", {{"title", "TEXT"}}), title(title), notes(notes)
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("title", &Folder::title),
                                               make_table("folder",
                                                          make_column("title", &Note::title),
                                                          make_column("notes", &Folder::notes))));
        storage.sync_schema();

        // Insert the new folder into the database
        storage.update(*this);

        // Insert all the notes into the database
        for (auto &note : notes)
        {
            storage.update(note);
        }
    }

    void update(std::string title, std::vector<Note> notes)
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("title", &Folder::title),
                                               make_table("folder",
                                                          make_column("title", &Note::title),
                                                          make_column("notes", &Folder::notes))));
        storage.sync_schema();

        // Insert the new folder into the database
        storage.update(*this);

        // Insert all the notes into the database
        for (auto &note : notes)
        {
            storage.update(note);
        }
    }

    void add_note(Note new_note, std::vector<Note> &notes)
    {
        for (auto &note : notes)
        {
            if (new_note.title == note.title)
            {
                throw std::invalid_argument("This title is already chosen in that folder");
            }
        }
        notes.push_back(new_note);
    }

    void sort_notes(bool sortByDate, bool increasing)
    {
        if (sortByDate)
        {
            std::sort(notes.begin(), notes.end(), [increasing](Note &a, Note &b)
                      { return increasing ? a.last_modified < b.last_modified : a.last_modified > b.last_modified; });
        }
        else
        {
            std::sort(notes.begin(), notes.end(), [increasing](Note &a, Note &b)
                      { return increasing ? a.title < b.title : a.title > b.title; });
        }
    }
    // Variable declaration :
    std::string title;
    std::vector<Note> notes;
};

class Focus_time : BaseModel
{
public:
    Focus_time() : BaseModel("focus_time", {{"time_spent", "INTEGER"}}), time_spent(0)
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("time_spent", &Focus_time::time_spent)));
        storage.sync_schema(true);

        // Fetch existing time_spent from the database or initialize to 0
        auto maybeTime = storage.get_optional<int>(1); // Assuming the id is 1 for simplicity
        if (maybeTime)
        {
            time_spent = *maybeTime;
        }
        else
        {
            // No previous time_spent found, insert initial value
            storage.replace(*this);
        }
    }

    int fetch()
    {
        return time_spent;
    }

    void update(int delta)
    {
        time_spent += delta;
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("time_spent", &Focus_time::time_spent)));
        storage.sync_schema(true);
        storage.replace(*this); // Update the time in the database
    }

    void reset()
    {
        time_spent = 0;
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("time_spent", &Focus_time::time_spent)));
        storage.sync_schema(true);
        storage.replace(*this); // Reset the time in the database
    }

    // Variable declaration :
    int time_spent; // assuming time is stored in seconds
};

class Commands : BaseModel
{
public:
    Commands() : BaseModel("commands", {{"command_name", "TEXT"}, {"command_description", "TEXT"}})
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("command_name", &Commands::command_name),
                                               make_column("command_description", &Commands::command_description)));
        storage.sync_schema(true);
    }

    std::string help(std::string &command_name)
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("command_name", &Commands::command_name),
                                               make_column("command_description", &Commands::command_description)));
        auto command = storage.get<Commands>(command_name);
        return command.command_description;
    }

    void add(std::string &command_name, std::string &command_description)
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("command_name", &Commands::command_name),
                                               make_column("command_description", &Commands::command_description)));
        Commands new_command;
        new_command.command_name = command_name;
        new_command.command_description = command_description;
        storage.insert(new_command);
    }

    void Commands::removeCommand(std::string &command_name)
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("command_name", &Commands::command_name),
                                               make_column("command_description", &Commands::command_description)));
        storage.remove<Commands>(&Commands::command_name, command_name);
    }

    void update(std::string &new_command_name, std::string &old_command_name)
    {
        auto storage = make_storage("concept.db",
                                    make_table(table_name,
                                               make_column("command_name", &Commands::command_name),
                                               make_column("command_description", &Commands::command_description)));
        auto command = storage.get<Commands>(old_command_name);
        command.command_name = new_command_name;
        storage.update(command);
    }

    // Variable declaration :
    std::string command_name;
    std::string command_description;
};
