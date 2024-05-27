cmake_minimum_required(VERSION 3.22)
project(ex4)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex4 tool/main.cpp Mtmchkin.cpp Mtmchkin.h Cards/Gang.cpp Cards/Gang.h utilities.cpp utilities.h Players/Player.cpp Players/Player.h Players/Wizard.cpp Players/Wizard.h Players/Rogue.cpp Players/Rogue.h Players/Fighter.cpp Players/Fighter.h Cards/Card.cpp Cards/Card.h Cards/Vampire.cpp Cards/Vampire.h Cards/Goblin.cpp Cards/Goblin.h Cards/Dragon.cpp Cards/Dragon.h Cards/Fairy.cpp Cards/Fairy.h Cards/Barfight.cpp Cards/Barfight.h Cards/Pitfall.cpp Cards/Pitfall.h Cards/Treasure.cpp Cards/Treasure.h Cards/Merchant.cpp Cards/Merchant.h Exception.h Cards/BattleCard.cpp Cards/BattleCard.h)
