//
// Created by daniel on 26/05/22.
//

#include "gtest/gtest.h"
#include "Hashing/hash_table.h"
#include <string>
#include <vector>

TEST(TestHashTable, Constructor)
{
    HashTable table(10);
    EXPECT_EQ(table.size(), 10);
}

TEST(TestHashTable, HashFunction)
{
    HashTable table(5);
    EXPECT_EQ(table.hashFunction("world"), 4);
    EXPECT_EQ(table.hashFunction("HellO"), 4);
    EXPECT_EQ(table.hashFunction("luck"), 2);
    EXPECT_EQ(table.hashFunction("GooD"), 2);
}

TEST(TestHashTable, FindItem)
{
    HashTable table(10);
    table.add("Duck");
    table.add("Penguin");
    table.add("Rooster");
    table.add("Chicken");

    EXPECT_EQ(table.find("Duck"), true);
    EXPECT_EQ(table.find("Penguin"), true);
    EXPECT_EQ(table.find("Rooster"), true);
    EXPECT_EQ(table.find("Chicken"), true);
    EXPECT_EQ(table.find("Lion"), false);
    EXPECT_EQ(table.find("Zebra"), false);

    HashTable table_2(5);
    table_2.add("Hell0");
    table_2.add("world");
    table_2.add("GooD");
    table_2.add("luck");

    EXPECT_EQ(table_2.find("Hell0"), true);
    EXPECT_EQ(table_2.find("world"), true);
    EXPECT_EQ(table_2.find("GooD"), true);
    EXPECT_EQ(table_2.find("luck"), true);
    EXPECT_EQ(table_2.find("horse"), false);

}

TEST(TestHashTable, AddItem)
{
    HashTable table(5);
    table.add("world");
    std::vector<std::string> chain {"world"};
    ASSERT_EQ(table.check(4), chain);

    chain.insert(chain.begin(), "Hell0");
    table.add("Hell0");
    EXPECT_EQ(table.check(4), chain);

    std::vector<std::string> chain_2 {"luck"};
    table.add("luck");
    ASSERT_EQ(table.check(2), chain_2);

    chain_2.insert(chain_2.begin(), "GooD");
    table.add("GooD");
    EXPECT_EQ(table.check(2), chain_2);
}

TEST(TestHashTable, AddRepeatedItem)
{
    HashTable table(5);
    table.add("world");
    table.add("world");
    table.add("Hell0");
    table.add("Hell0");
    std::vector<std::string> chain {"Hell0", "world"};
    ASSERT_EQ(table.check(4), chain);

    std::vector<std::string> chain_2 {"luck", "GooD"};
    table.add("GooD");
    table.add("GooD");
    table.add("GooD");
    table.add("luck");
    table.add("luck");
    EXPECT_EQ(table.check(2), chain_2);
}

TEST(TestHashTable, RemoveItem)
{
    HashTable table(5);
    table.add("world");
    table.add("Hell0");
    table.remove("world");

    std::vector<std::string> chain {"Hell0"};
    EXPECT_EQ(table.check(4), chain);

    table.remove("Hell0");
    EXPECT_EQ(table.check(4).empty(), true);

    table.add("GooD");
    table.add("luck");
    table.remove("luck");

    chain = {"GooD"};
    EXPECT_EQ(table.check(2), chain);

    table.remove("GooD");
    EXPECT_EQ(table.check(2).empty(), true);
}

TEST(TestHashTable, DeleteItemNotPresent)
{
    HashTable table(5);
    table.add("world");
    table.add("Hell0");

    table.remove("Duck");
    table.remove("Horse");

    EXPECT_EQ(table.find("Hell0"), true);
    EXPECT_EQ(table.find("world"), true);
}


TEST(TestHashTable, ProcessQueries)
{
    // Process queries_1
    HashTable table_1(5);
    table_1.processQuery("add world");
    table_1.processQuery("add HellO");

    std::vector<std::string> chain {"HellO", "world"};
    EXPECT_EQ(table_1.check(4), chain);
    EXPECT_EQ(table_1.find("World"), false);
    EXPECT_EQ(table_1.find("world"), true);

    table_1.processQuery("del world");
    chain.pop_back();
    EXPECT_EQ(table_1.check(4), chain);

    table_1.processQuery("del HellO");
    table_1.processQuery("add luck");
    table_1.processQuery("add GooD");
    chain = {"GooD", "luck"};
    EXPECT_EQ(table_1.check(2), chain);
    table_1.processQuery("del good");

    // Process queries_2
    HashTable table_2(4);
    table_2.processQuery("add test");
    table_2.processQuery("add test");
    EXPECT_EQ(table_2.find("test"), true);
    table_2.processQuery("del test");
    EXPECT_EQ(table_2.find("test"), false);
    EXPECT_EQ(table_2.find("Test"), false);
    table_2.processQuery("add Test");
    EXPECT_EQ(table_2.find("Test"), true);

    // Process queries_3
    HashTable table_3(3);
    chain = {"add", "help"};

    EXPECT_EQ(table_3.check(0).empty(), true);
    EXPECT_EQ(table_3.find("help"), false);
    table_3.processQuery("add help");
    table_3.processQuery("add del");
    table_3.processQuery("add add");
    EXPECT_EQ(table_3.find("add"), true);
    EXPECT_EQ(table_3.find("del"), true);
    table_3.processQuery("del del");
    EXPECT_EQ(table_3.find("del"), false);
    EXPECT_EQ(table_3.check(0).empty(), true);
    EXPECT_EQ(table_3.check(1), chain);
    EXPECT_EQ(table_3.check(2).empty(), true);
}