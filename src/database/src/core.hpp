#include <iostream>
#include <vector>
#include <sqlite_orm/sqlite_orm.h>

using namespace sqlite_orm;

class BaseModel {
public:
    struct base_model_t {
        int id;
        int created_at;
        int updated_at;
    };

    BaseModel() = default;

    static auto create_table();
private:
    static std::string table_name;
};

auto create_storage();
