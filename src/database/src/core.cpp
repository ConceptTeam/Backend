#include <core.hpp>

auto BaseModel::create_table() {
    return make_table(
        table_name,
        make_column("id", &base_model_t::id, primary_key().autoincrement()),
        make_column("created_at", &base_model_t::created_at),
        make_column("updated_at", &base_model_t::updated_at)
    );
}

auto create_storage() {
    return make_storage(
        "database.sqlite",
        BaseModel::create_table()
    );
}
