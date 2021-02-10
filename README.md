# Player-Ban-On-Death
TrinityCore (WoW) script to ban player on upon dying

To add this to your server, simply download the script. Place it in the directory TrinityCore/src/server/scripts/Custom. Then after that, open your custom_script_loader.cpp in the same directory (Custom) then where you see `// This is where scripts' loading functions should be declared:` add (under it) `void AddSC_Player_Ban_On_Death();` and where it says `void AddCustomScripts() {` add `AddSC_Player_Ban_On_Death();` Then open CMakeLists.txt (TrinityCore/src/server/scripts/CMakeLists.txt) Where it says (Around line 245) `${scripts_STAT_SRCS}` Add `Custom/Player_Ban_On_Death.cpp` Recompile your server. That should be all. Enjoy!

For my level reset script as an alternative to this script, go here https://github.com/Techwizz-somboo/Player-Level-Reset-On-Death-TrinityCore

See it in action! https://youtu.be/UTZfX5QIaDM
