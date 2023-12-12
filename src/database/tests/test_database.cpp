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

TEST(Database, DeleteObject)
{
    // Remove current database
    std::remove("test_delete.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_delete.sqlite"));
    storage->sync_schema();
    Note note = {
        -1,
        "Test",
        "Test",
        0,
    };

    int id = insertObject(note);
    EXPECT_EQ(id, 1);
    deleteObject<Note>(id);
    auto notes = storage->get_all<Note>();
    EXPECT_EQ(notes.size(), 0);
}

TEST(Database, InsertFolder)
{
    // Remove current database
    std::remove("test_insert_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_insert_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
}

TEST(Database, UpdateFolder)
{
    // Remove current database
    std::remove("test_update_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_update_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
    folder.id = 1;
    folder.name = "Test2";
    updateObject(folder);
    auto folders = storage->get_all<Folder>();
    EXPECT_EQ(folders.size(), 1);
    EXPECT_EQ(folders[0].name, "Test2");
}

TEST(Database, GetFolderById)
{
    // Remove current database
    std::remove("test_get_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
    auto folder2 = storage->get<Folder>(1);
    EXPECT_EQ(folder2.name, "Test");
}

TEST(Database, DeleteFolder)
{
    // Remove current database
    std::remove("test_delete_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_delete_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
    deleteObject<Folder>(id);
    auto folders = storage->get_all<Folder>();
    EXPECT_EQ(folders.size(), 0);
}

TEST(Database, DeleteObject)
{
    // Remove current database
    std::remove("test_delete.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_delete.sqlite"));
    storage->sync_schema();
    Note note = {
        -1,
        "Test",
        "Test",
        0,
    };

    int id = insertObject(note);
    EXPECT_EQ(id, 1);
    deleteObject<Note>(id);
    auto notes = storage->get_all<Note>();
    EXPECT_EQ(notes.size(), 0);
}

TEST(Database, InsertFolder)
{
    // Remove current database
    std::remove("test_insert_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_insert_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
}

TEST(Database, UpdateFolder)
{
    // Remove current database
    std::remove("test_update_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_update_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
    folder.id = 1;
    folder.name = "Test2";
    updateObject(folder);
    auto folders = storage->get_all<Folder>();
    EXPECT_EQ(folders.size(), 1);
    EXPECT_EQ(folders[0].name, "Test2");
}

TEST(Database, GetFolderById)
{
    // Remove current database
    std::remove("test_get_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
    auto folder2 = storage->get<Folder>(1);
    EXPECT_EQ(folder2.name, "Test");
}

TEST(Database, DeleteFolder)
{
    // Remove current database
    std::remove("test_delete_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_delete_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {
        -1,
        "Test",
        {},
    };

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
    deleteObject<Folder>(id);
    auto folders = storage->get_all<Folder>();
    EXPECT_EQ(folders.size(), 0);
}

TEST(Database, GetAllNotes)
{
    // Remove current database
    std::remove("test_get_all_notes.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get_all_notes.sqlite"));
    storage->sync_schema();
    Note note1 = {
        -1,
        "Test1",
        "Test1",
        0,
    };
    Note note2 = {
        -1,
        "Test2",
        "Test2",
        0,
    };

    insertObject(note1);
    insertObject(note2);
    auto notes = storage->get_all<Note>();
    EXPECT_EQ(notes.size(), 2);
}

TEST(Database, GetAllFolders)
{
    // Remove current database
    std::remove("test_get_all_folders.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get_all_folders.sqlite"));
    storage->sync_schema();
    Folder folder1 = {
        -1,
        "Test1",
        {},
    };
    Folder folder2 = {
        -1,
        "Test2",
        {},
    };

    insertObject(folder1);
    insertObject(folder2);
    auto folders = storage->get_all<Folder>();
    EXPECT_EQ(folders.size(), 2);
}