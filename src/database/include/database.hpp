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

    // int insert();
    // void update();
};

struct Folder
{
    int id;
    std::string name;

    Folder() = default;

    // int insert();
    // void update();
};

struct FocusTime
{
    int id;
    std::time_t start_time;
    std::time_t end_time;
    std::time_t time_spent;

    FocusTime() = default;

    // int insert();
    // void update();
};

struct Command
{
    int id;
    std::string command;
    std::string description;

    Command() = default;

    // int insert();
    // void update();
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
                                   make_column("start_time", &FocusTime::start_time),
                                   make_column("end_time", &FocusTime::end_time),
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
