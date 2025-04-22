#include <gtest/gtest.h>
#include "../src/npc.cpp" 


TEST(NPCFactoryTest, test_00) {
    auto npc = NPCFactory::create_npc("Elf", "Legolas", 100, 200);
    EXPECT_EQ(npc->get_name(), "Legolas");
    EXPECT_EQ(npc->get_type(), "Elf");
}

TEST(NPCFactoryTest, test_01) {
    auto npc = NPCFactory::create_npc("Dragon", "Smaug", 200, 300);
    EXPECT_EQ(npc->get_name(), "Smaug");
    EXPECT_EQ(npc->get_type(), "Dragon");
}

TEST(NPCFactoryTest, test_02) {
    auto npc = NPCFactory::create_npc("Druid", "Gandalf", 300, 400);
    EXPECT_EQ(npc->get_name(), "Gandalf");
    EXPECT_EQ(npc->get_type(), "Druid");
}

TEST(NPCFactoryTest, test_03) {
    EXPECT_THROW(NPCFactory::create_npc("Unknown", "UnknownNPC", 500, 600), std::invalid_argument);
}

TEST(NPCFactoryTest, test_04) {
    std::ofstream file("test_npc.txt");
    file << "Elf Legolas 100 200\n";
    file << "Dragon Smaug 300 400\n";
    file.close();

    auto npcs = NPCFactory::create_npcs_from_file("test_npc.txt");

    ASSERT_EQ(npcs.size(), 2);

    EXPECT_EQ(npcs[0]->get_name(), "Legolas");
    EXPECT_EQ(npcs[0]->get_type(), "Elf");
    EXPECT_EQ(npcs[0]->x, 100);
    EXPECT_EQ(npcs[0]->y, 200);

    EXPECT_EQ(npcs[1]->get_name(), "Smaug");
    EXPECT_EQ(npcs[1]->get_type(), "Dragon");
    EXPECT_EQ(npcs[1]->x, 300);
    EXPECT_EQ(npcs[1]->y, 400);
}

TEST(NPCAttackTest, test_00) {
    auto elf = NPCFactory::create_npc("Elf", "Legolas", 100, 200);
    auto druid = NPCFactory::create_npc("Druid", "Gandalf", 150, 250);
    
    std::stringstream ss;
    std::streambuf* orig_cout = std::cout.rdbuf(ss.rdbuf());  // Redirect std::cout to a stringstream

    elf->attack(druid.get());
    std::string expected_output = "Legolas attacks Gandalf\n";
    EXPECT_EQ(ss.str(), expected_output);

    std::cout.rdbuf(orig_cout);
}

TEST(NPCAttackTest, test_01) {
    auto dragon = NPCFactory::create_npc("Dragon", "Smaug", 200, 300);
    auto elf = NPCFactory::create_npc("Elf", "Legolas", 100, 200);
    
    std::stringstream ss;
    std::streambuf* orig_cout = std::cout.rdbuf(ss.rdbuf());  // Redirect std::cout to a stringstream

    dragon->attack(elf.get());
    std::string expected_output = "Smaug attacks Legolas\n";
    EXPECT_EQ(ss.str(), expected_output);
    std::cout.rdbuf(orig_cout);
}

TEST(BattleVisitorTest, test_00) {
    auto elf = NPCFactory::create_npc("Elf", "Legolas", 100, 200);
    auto druid = NPCFactory::create_npc("Druid", "Gandalf", 150, 250);
    BattleVisitor battle(100);

    std::stringstream ss;
    std::streambuf* orig_cout = std::cout.rdbuf(ss.rdbuf());

    battle.visit(elf.get(), druid.get());

    EXPECT_EQ(ss.str(), "Legolas attacks Gandalf\n");

    std::cout.rdbuf(orig_cout);
}

TEST(BattleVisitorTest, test_01) {
    auto elf = NPCFactory::create_npc("Elf", "Legolas", 100, 200);
    auto dragon = NPCFactory::create_npc("Dragon", "Smaug", 400, 500);
    BattleVisitor battle(100); 

    std::stringstream ss;
    std::streambuf* orig_cout = std::cout.rdbuf(ss.rdbuf());

    battle.visit(elf.get(), dragon.get());
    EXPECT_EQ(ss.str(), "");

    std::cout.rdbuf(orig_cout);
}

TEST(ObserverPatternTest, test_00) {
    std::shared_ptr<FileObserver> fileObserver = std::make_shared<FileObserver>("test_log.txt");
    BattleArena arena(100);
    arena.add_observer(fileObserver);

    auto elf = NPCFactory::create_npc("Elf", "Legolas", 100, 200);
    auto druid = NPCFactory::create_npc("Druid", "Gandalf", 150, 250);
    arena.add_npc(std::move(elf));
    arena.add_npc(std::move(druid));
    arena.battle();
    std::ifstream logFile("test_log.txt");
    std::string logLine;
    std::getline(logFile, logLine);

    EXPECT_EQ(logLine, "Battle occurred between Legolas and Gandalf");
}

TEST(ObserverPatternTest, test_01) {
    std::shared_ptr<ScreenObserver> screenObserver = std::make_shared<ScreenObserver>();
    BattleArena arena(100);
    arena.add_observer(screenObserver);

    auto elf = NPCFactory::create_npc("Elf", "Legolas", 100, 200);
    auto druid = NPCFactory::create_npc("Druid", "Gandalf", 150, 250);
    arena.add_npc(std::move(elf));
    arena.add_npc(std::move(druid));

    std::stringstream ss;
    std::streambuf* orig_cout = std::cout.rdbuf(ss.rdbuf());

    arena.battle();

    EXPECT_EQ(ss.str(), "Legolas attacks Gandalf\nBattle occurred between Legolas and Gandalf\n");

    std::cout.rdbuf(orig_cout);
}
