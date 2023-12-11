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

    int id = insertObject(note);
    int id2 = insertObject(note);
    EXPECT_EQ(id, 1);
    EXPECT_EQ(id2, 2);
}

TEST(Database, InsertObject)
{
    // Remove current database
    std::remove("test_insert.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_insert.sqlite"));
    storage->sync_schema();
    Note note = {
        -1,
        "Test",
        "Test",
        0,
    };

    int id = insertObject(note);
    EXPECT_EQ(id, 1);
}

TEST(Database, UpdateObject)
{
    // Remove current database
    std::remove("test_update.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_update.sqlite"));
    storage->sync_schema();
    Note note = {
        -1,
        "Test",
        "Test",
        0,
    };

    int id = insertObject(note);
    EXPECT_EQ(id, 1);
    note.id = 1;
    note.title = "Test2";
    updateObject(note);
    auto notes = storage->get_all<Note>();
    EXPECT_EQ(notes.size(), 1);
    EXPECT_EQ(notes[0].title, "Test2");
}

TEST(Database, GetObjectById)
{
    // Remove current database
    std::remove("test_get.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get.sqlite"));
    storage->sync_schema();
    Note note = {
        -1,
        "Test",
        "Test",
        0,
    };

    int id = insertObject(note);
    EXPECT_EQ(id, 1);
    auto note2 = storage->get<Note>(1);
    EXPECT_EQ(note2.title, "Test");
}
