#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <ctime>

#include "sqlite_orm/sqlite_orm.h"

using namespace sqlite_orm;

typedef std::pair<std::string, std::string> col_t;
typedef std::vector<col_t> cols_t;

struct Note {
    int id;
    std::string title;
    std::string content;
    std::time_t last_modified;

    Note() = default;

    int insert();
    void update();
};

struct Folder {
    int id;
    std::string name;
    std::vector<Note> notes;

    Folder() = default;

    int insert();
    void update();
};

struct FocusTime {
    std::time_t start_time;
    std::time_t end_time;
    std::time_t time_spent;

    FocusTime() = default;

    int insert();
    void update();
};

struct Command {
    std::string command;
    std::string description;

    Command() = default;

    int insert();
    void update();
};

inline auto initStorage(const std::string& path) {
    using namespace sqlite_orm;
    return make_storage(path,
                        make_table("notes",
                                   make_column("id", &Note::id, primary_key()),
                                   make_column("title", &Note::title),
                                   make_column("content", &Note::content),
                                   make_column("last_modified", &Note::last_modified)));
}

using Storage = decltype(initStorage(""));

static std::unique_ptr<Storage> storage;

template <typename T>
int insertObject(T& obj) {
    return storage->insert(obj);
}

template <typename T>
void updateObject(T& obj) {
    storage->update(obj);
}

template <typename T>
void getObjectById(int id) {
    storage->get<T>(id);
}
