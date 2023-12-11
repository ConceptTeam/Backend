#include "database.hpp"

auto init_storage(const std::string& path)
{
    return make_storage(
        path,
        make_table("notes",
            make_column("id", &Note::id, primary_key()),
            make_column("title", &Note::title),
            make_column("content", &Note::content),
            make_column("last_modified", &Note::last_modified)),
        make_table("folders",
            make_column("id", &Folder::id, primary_key()),
            make_column("name", &Folder::title)),
        make_table("focus_times",
            make_column("id", &FocusTime::id, primary_key()),
            make_column("start_time", &FocusTime::start_time),
            make_column("end_time", &FocusTime::end_time),
            make_column("time_spent", &FocusTime::time_spent)),
        make_table("commands",
            make_column("id", &Command::id, primary_key()),
            make_column("command", &Command::command),
            make_column("description", &Command::description))
        );
}

using Storage = decltype(init_storage(""));

Storage storage = init_storage("");

BaseModel::BaseModel(std::string table_name, cols_t cols)
    : table_name(table_name), cols(cols) {}

cols_t BaseModel::get_cols() { return cols; }

std::string BaseModel::get_table_name() { return table_name; }

int BaseModel::insert()
{
    return storage.insert(*this);
}

void BaseModel::update()
{
    storage.update(*this);
}
