#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <ctime>

#include "sqlite_orm/sqlite_orm.h"

using namespace sqlite_orm;

typedef std::pair<std::string, std::string> col_t;
typedef std::vector<col_t> cols_t;

class BaseModel
{
public:
    BaseModel(std::string table_name, cols_t cols)
        : table_name(table_name), cols(cols) {}
    // Might be able to get rid of these 2 as the members are protected and not private
    cols_t get_cols() { return cols; };
    std::string get_table_name() { return table_name; };

    // Insert and return the id of the inserted row
    virtual int insert();
    void update();

    // TODO: Implement these
    // void remove();
    // void select();

    int id;

protected:
    std::string table_name;
    cols_t cols;
};

// class Note : public BaseModel
// {
// public:
//     Note(
//         std::optional<std::string> title,
//         std::optional<std::string> content,
//         std::optional<std::time_t> last_modified
//     ) : BaseModel("notes", {{"title", "TEXT"}, {"content", "TEXT"}, {"last_modified", "INTEGER"}}) {
//         this->title = title.value_or("");
//         this->content = content.value_or("");
//         this->last_modified = last_modified.value_or(std::time(nullptr));
//     };

//     std::string title;
//     std::string content;
//     std::time_t last_modified;
// };

struct Note {
    int id;
    std::string title;
    std::string content;
    std::time_t last_modified;
};

// class Folder : public BaseModel
// {
// public:
//     Folder(
//         std::optional<std::string> title,
//         std::optional<std::vector<Note>> notes
//     );

//     std::string name;
//     std::vector<Note> notes;
// };

// class FocusTime : public BaseModel
// {
// public:
//     FocusTime(
//         std::optional<std::time_t> start_time,
//         std::optional<std::time_t> end_time,
//         std::optional<std::time_t> time_spent
//     );

//     std::time_t start_time;
//     std::time_t end_time;
//     std::time_t time_spent;
// };

// class Command : public BaseModel
// {
// public:
//     Command(
//         std::optional<std::string> name,
//         std::optional<std::string> description
//     );

//     std::string command;
//     std::string description;
// };

// struct Note
// {
//     int id;
//     std::string title;
//     std::string content;
//     std::time_t last_modified;
// };

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

// storage = std::make_unique<Storage>(initStorage("update.sqlite"));
