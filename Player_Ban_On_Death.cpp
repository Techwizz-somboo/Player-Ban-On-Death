#include <thread>
#include <chrono>
#include "Define.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "Unit.h"
#include "ScriptPCH.h"
#include "Player.cpp"

class Player_Ban_On_Death : public PlayerScript
{
protected:
Player_Ban_On_Death(const char* name);

public:
Player_Ban_On_Death() : PlayerScript("Player_Ban_On_Death") { }

static void ThreadBan(Player* killed,char* text){
killed->Say(text, (Language)0, nullptr);
std::string name = killed->GetName();
std::string deathMessage = "Attention everyone: " + name + " has died! May they rest in peace!";
sWorld->SendWorldText(LANG_AUTO_BROADCAST, deathMessage.c_str());

//Ban Player
std::this_thread::sleep_for (std::chrono::seconds(10));
char* durationStr = (char*)"-1";
char* reasonStr = (char*)"Died";
std::string author = "LevelReset";
sWorld->BanCharacter(name, durationStr, reasonStr, author);
}

void OnPVPKill(Player* killer, Player* killed) {
std::thread first (ThreadBan,killed,(char*)"You killed me, blah!");
first.detach();
}

void OnPlayerKilledByCreature(Creature* killer, Player* killed) {
std::thread first (ThreadBan,killed,(char*)"It was good living, blah!");
first.detach();
}
};

void AddSC_Player_Ban_On_Death() {
new Player_Ban_On_Death();
}
