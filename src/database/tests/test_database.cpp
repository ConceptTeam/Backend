#include <gtest/gtest.h>
#include <sqlite3.h>

#include "database.hpp"

TEST(Database, InitStorage)
{
    std::cout << sqlite3_version << std::endl;
    // Remove current database
    std::remove("test_init.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_init.sqlite"));
    storage->sync_schema();
    Note note = {
        -1,
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
        -1,
        "Test",
        "Test",
        0,
    };

    int id = insertObject(note);
    EXPECT_EQ(id, 1);
    Note note2 = storage->get<Note>(1);
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
    Folder folder = {-1,
                     "Test"};

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
}

TEST(Database, UpdateFolder)
{
    // Remove current database
    std::remove("test_update_folder.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_update_folder.sqlite"));
    storage->sync_schema();
    Folder folder = {-1,
                     "Test"};

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
    Folder folder = {-1,
                     "Test"};

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
    Folder folder = {-1,
                     "Test"};

    int id = insertObject(folder);
    EXPECT_EQ(id, 1);
    deleteObject<Folder>(id);
    auto folders = storage->get_all<Folder>();
    EXPECT_EQ(folders.size(), 0);
}

TEST(Database, InsertFocusTime)
{
    // Remove current database
    std::remove("test_insert_focus_time.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_insert_focus_time.sqlite"));
    storage->sync_schema();
    FocusTime focusTime = {
        -1,
        0,
        0,
        0,
    };

    int id = insertObject(focusTime);
    EXPECT_EQ(id, 1);
}

TEST(Database, UpdateFocusTime)
{
    // Remove current database
    std::remove("test_update_focus_time.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_update_focus_time.sqlite"));
    storage->sync_schema();
    FocusTime focusTime = {
        -1,
        0,
        0,
        0,
    };

    int id = insertObject(focusTime);
    EXPECT_EQ(id, 1);
    focusTime.id = 1;
    focusTime.start_time = 1;
    focusTime.end_time = 1;
    focusTime.time_spent = 1;
    updateObject(focusTime);
    auto focusTimes = storage->get_all<FocusTime>();
    EXPECT_EQ(focusTimes.size(), 1);
    EXPECT_EQ(focusTimes[0].start_time, 1);
    EXPECT_EQ(focusTimes[0].end_time, 1);
    EXPECT_EQ(focusTimes[0].time_spent, 1);
}

TEST(Database, GetFocusTimeById)
{
    // Remove current database
    std::remove("test_get_focus_time.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get_focus_time.sqlite"));
    storage->sync_schema();
    FocusTime focusTime = {
        -1,
        0,
        0,
        0,
    };

    int id = insertObject(focusTime);
    EXPECT_EQ(id, 1);
    auto focusTime2 = storage->get<FocusTime>(1);
    EXPECT_EQ(focusTime2.start_time, 0);
    EXPECT_EQ(focusTime2.end_time, 0);
    EXPECT_EQ(focusTime2.time_spent, 0);
}

TEST(Database, DeleteFocusTime)
{
    // Remove current database
    std::remove("test_delete_focus_time.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_delete_focus_time.sqlite"));
    storage->sync_schema();
    FocusTime focusTime = {
        -1,
        0,
        0,
        0,
    };

    int id = insertObject(focusTime);
    EXPECT_EQ(id, 1);
    deleteObject<FocusTime>(id);
    auto focusTimes = storage->get_all<FocusTime>();
    EXPECT_EQ(focusTimes.size(), 0);
}

TEST(Database, InsertCommand)
{
    // Remove current database
    std::remove("test_insert_command.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_insert_command.sqlite"));
    storage->sync_schema();
    Command command = {
        -1,
        "Test",
        "Test",
    };

    int id = insertObject(command);
    EXPECT_EQ(id, 1);
}

TEST(Database, UpdateCommand)
{
    // Remove current database
    std::remove("test_update_command.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_update_command.sqlite"));
    storage->sync_schema();
    Command command = {
        -1,
        "Test",
        "Test",
    };

    int id = insertObject(command);
    EXPECT_EQ(id, 1);
    command.id = 1;
    command.command = "Test2";
    command.description = "Test2";
    updateObject(command);
    auto commands = storage->get_all<Command>();
    EXPECT_EQ(commands.size(), 1);
    EXPECT_EQ(commands[0].command, "Test2");
    EXPECT_EQ(commands[0].description, "Test2");
}

TEST(Database, GetCommandById)
{
    // Remove current database
    std::remove("test_get_command.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get_command.sqlite"));
    storage->sync_schema();
    Command command = {
        -1,
        "Test",
        "Test",
    };

    int id = insertObject(command);
    EXPECT_EQ(id, 1);
    auto command2 = storage->get<Command>(1);
    EXPECT_EQ(command2.command, "Test");
    EXPECT_EQ(command2.description, "Test");
}

TEST(Database, DeleteCommand)
{
    // Remove current database
    std::remove("test_delete_command.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_delete_command.sqlite"));
    storage->sync_schema();
    Command command = {
        -1,
        "Test",
        "Test",
    };

    int id = insertObject(command);
    EXPECT_EQ(id, 1);
    deleteObject<Command>(id);
    auto commands = storage->get_all<Command>();
    EXPECT_EQ(commands.size(), 0);
}

TEST(Database, GetAllNotes)
{
    // Remove current database
    std::remove("test_get_all_notes.sqlite");
    storage = std::make_unique<Storage>(initStorage("test_get_all_notes.sqlite"));
    storage->sync_schema();
    Note note1 = {
        -1,
        -1,
        "Test1",
        "Test1",
        0,
    };
    Note note2 = {
        -1,
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
        "Test1"};
    Folder folder2 = {
        -1,
        "Test2"};

    insertObject(folder1);
    insertObject(folder2);
    auto folders = storage->get_all<Folder>();
    EXPECT_EQ(folders.size(), 2);
}
