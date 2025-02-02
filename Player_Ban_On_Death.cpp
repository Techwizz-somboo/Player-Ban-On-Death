#include <thread>
#include <chrono>
#include "Define.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "Unit.h"
#include "ScriptPCH.h"
#include "Player.cpp"
#include <string>
#include <cstdint>
#include <cstdlib>
#include <ctime>

class Player_Ban_On_Death: public PlayerScript {
  protected: Player_Ban_On_Death(const char * name);

  public: Player_Ban_On_Death(): PlayerScript("Player_Ban_On_Death") {}

  static void ThreadBan(Player * killed, const std::string& text) {
    killed -> Say(text, (Language) 0, nullptr);
    std::string playerName = killed -> GetName();
    uint32_t playerClassId = killed -> GetClass();
    std::string playerClass = GetClassName(playerClassId);
    uint32_t playerLevel = killed -> GetLevel();
    if (playerLevel >= 10) {
      std::string deathMessage = "Attention everyone: " + playerName + " has died! They were a level " + std::to_string(playerLevel) + " " + playerClass + "... May they rest in peace!";
      sWorld -> SendWorldText(LANG_AUTO_BROADCAST, deathMessage.c_str());
    }

    //Ban Player
    std::this_thread::sleep_for(std::chrono::seconds(10));
    char * durationStr = (char * )
    "-1";
    char * reasonStr = (char * )
    "Died";
    std::string author = "LevelReset";
    sWorld -> BanCharacter(playerName, durationStr, reasonStr, author);
  }

  void OnPVPKill(Player * killer, Player * killed) {
    std::string deathMessage = GetDeathMessage();
    std::thread first(ThreadBan, killed, deathMessage);
    first.detach();
  }

  void OnPlayerKilledByCreature(Creature * killer, Player * killed) {
    std::string deathMessage = GetDeathMessage();
    std::thread first(ThreadBan, killed, deathMessage);
    first.detach();
  }

  static std::string GetClassName(uint8 classId)
  {
    switch (classId)
    {
        case 1: return "Warrior";
        case 2: return "Paladin";
        case 3: return "Hunter";
        case 4: return "Rogue";
        case 5: return "Priest";
        case 6: return "Death Knight";
        case 7: return "Shaman";
        case 8: return "Mage";
        case 9: return "Warlock";
        case 11: return "Druid";
        default: return "Unknown";  // Return "Unknown" for any class ID not in the list
    }
  }

  static std::string GetDeathMessage() {
    std::vector<std::string> messages = 
      {"Ouch, that was sharper than I thought...", 
      "We will meet again... Mark my words!", 
      "What is this, what are you doing my son!? Ughhh", 
      "Dark times are upon us... very dark times..", 
      "Leeroy Jenkins!"};
    
    std::srand(std::time(0));
    int randomIndex = std::rand() % messages.size();

    return messages[randomIndex];
  }
};

void AddSC_Player_Ban_On_Death() {
  new Player_Ban_On_Death();
}
