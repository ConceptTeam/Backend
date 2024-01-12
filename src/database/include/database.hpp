#ifndef CONCEPTAPP_DATABASE_H
#define CONCEPTAPP_DATABASE_H
#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <ctime>

#include "sqlite_orm/sqlite_orm.h"

using namespace sqlite_orm;

typedef std::pair<std::string, std::string> col_t;
typedef std::vector<col_t> cols_t;

struct Note
{
    int id;
    int folder_id;
    std::string title;
    std::string content;
    std::time_t last_modified;

    Note() = default;
};

struct Folder
{
    int id;
    std::string title;

    Folder() = default;
};

struct FocusTime
{
    int id;
    std::time_t creation_time;
    std::time_t time_spent;

    FocusTime() = default;
};

struct Command
{
    int id;
    std::string command;
    std::string description;

    Command() = default;
};

inline auto initStorage(const std::string &path)
{
    using namespace sqlite_orm;
    return make_storage(path,
                        make_table("notes",
                                   make_column("id", &Note::id, primary_key()),
                                   make_column("folder_id", &Note::folder_id),
                                   make_column("title", &Note::title),
                                   make_column("content", &Note::content),
                                   make_column("last_modified", &Note::last_modified)),
                        make_table("folders",
                                   make_column("id", &Folder::id, primary_key()),
                                   make_column("title", &Folder::title)),
                        make_table("focus_time",
                                   make_column("id", &FocusTime::id, primary_key()),
                                   make_column("creation_time", &FocusTime::creation_time),
                                   make_column("time_spent", &FocusTime::time_spent)),
                        make_table("commands",
                                   make_column("id", &Command::id, primary_key()),
                                   make_column("command", &Command::command),
                                   make_column("description", &Command::description)));
}

using Storage = decltype(initStorage(""));

static std::unique_ptr<Storage> storage;

template <typename T>
int insertObject(T &obj)
{
    return storage->insert(obj);
}

template <typename T>
void updateObject(T &obj)
{
    storage->update(obj);
}

template <typename T>
T getObjectById(int id)
{
    return storage->get<T>(id);
}

template <typename T>
void deleteObject(int id)
{
    storage->remove<T>(id);
}

std::vector<Note> searchTitle(std::string &keyword)
{
    std::vector<Note> results;

    // Search in titles
    auto titleResults = storage->get_all<Note>(
        where(like(&Note::title, "%" + keyword + "%")),
        order_by(&Note::id));

    results.insert(results.end(), titleResults.begin(), titleResults.end());

    // Search in contents
    auto contentResults = storage->get_all<Note>(
        where(like(&Note::content, "%" + keyword + "%")),
        order_by(&Note::last_modified).desc());

    results.insert(results.end(), contentResults.begin(), contentResults.end());

    return results;
}

std::vector<int> searchLine(const Note &note, std::string &keyword)
{
    std::vector<int> lineNumbers;

    if (note.title.find(keyword) != std::string::npos)
    {
        lineNumbers.push_back(0); // 0 for title
    }

    std::istringstream iss(note.content);
    std::string line;
    int lineNum = 1;

    while (std::getline(iss, line))
    {
        if (line.find(keyword) != std::string::npos)
        {
            lineNumbers.push_back(lineNum);
        }
        lineNum++;
    }

    return lineNumbers;
}

std::vector<std::pair<Note, int>> searchNotes(std::string &keyword)
{
    std::vector<std::pair<Note, int>> results;

    auto notes = searchTitle(keyword);

    for (auto &note : notes)
    {
        auto lineNumbers = searchLine(note, keyword);
        for (auto lineNumber : lineNumbers)
        {
            results.emplace_back(note, lineNumber);
        }
    }

    return results;
}

std::vector<FocusTime> getInterval(std::time_t start, std::time_t end)
{
    std::vector<FocusTime> focus_times;

    auto results = storage->get_all<FocusTime>(
        where(between(&FocusTime::creation_time, start, end)),
        multi_order_by(order_by(&FocusTime::creation_time).desc()));

    for (auto &result : results)
    {
        focus_times.push_back(result);
    }
    return focus_times;
}
#endif //CONCEPTAPP_DATABASE_H
