#include <gtest/gtest.h>

#include "database.hpp"

TEST(Database, InitStorage)
{
    // Remove current database
    std::remove("test_init.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_init.sqlite"));
    storage->sync_schema();
    Note note = {
        -1,
        "Test",
        "Test",
        0,
    };

    int id = storage->insert(note);
    std::cout << "id: " << id << std::endl;
    EXPECT_EQ(id, 1);
}
