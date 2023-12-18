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
    std::string name;

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
                                   make_column("title", &Folder::name)),
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
void getObjectById(int id)
{
    storage->get<T>(id);
}

template <typename T>
void deleteObject(int id)
{
    storage->remove<T>(id);
}

std::vector<Note> searchNotes(std::string &keyword)
{
    std::vector<Note> notes;

    auto results = storage->get_all<Note>(
        where(like(&Note::content, "%" + keyword + "%")),
        multi_order_by(order_by(&Note::last_modified).desc(), order_by(&Note::title)));

    for (auto &result : results)
    {
        notes.push_back(result);
    }
    return notes;
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
