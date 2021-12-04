#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <static_todo.hpp>

#include "mod.hpp"

namespace ARMA3::Definitions
{
    static std::string home_directory = getenv("HOME");

    static constexpr char const *app_id = "221100";

    static const std::array<char const *, 28> exclusions{"Addons", "AoW", "Argo", "BattlEye", "Contact", "Curator", "Dll", "Dta", "Enoch", "Expansion", "fontconfig", "GM", "CSLA", "Heli", "Jets", "Kart", "Keys", "Launcher", "MPMissions", "Mark", "Missions", "Orange", "Tacops", "Tank", "vn", "WS", "legal", "steam_shader_cache"};
    TODO_BEFORE(2, 2022, "Use dta/product.bin for exclusion list");

    #ifdef __linux
    static constexpr std::array<char const *, 3> const executable_names {"arma3.x86_64", "DayZ_x64.exe","DayZ_BE.exe"};
    static constexpr char const *local_share_prefix = ".local/share";
    static constexpr char const *bohemia_interactive_prefix = "bohemiainteractive/dayz";
    static constexpr char const *game_config_path = "GameDocuments/DayZ/DayZ.cfg";
    #else //__APPLE__
    static constexpr std::array<char const *, 1> const executable_names {"ArmA3.app"};
    static constexpr char const *local_share_prefix = "Library/Application Support";
    static constexpr char const *bohemia_interactive_prefix = "com.vpltd.Arma3";
    static constexpr char const *game_config_path = "GameDocuments/DayZ/DayZ.cfg";
    #endif

    static constexpr char const *flatpak_prefix = ".var/app/com.valvesoftware.Steam";
    static constexpr char const *proton_config_relative_path =
        "../../compatdata/221100/pfx/drive_c/users/steamuser/My Documents/DayZ/DayZ.cfg";
}

namespace ARMA3
{
    class Client
    {
        public:
            Client(std::filesystem::path const &arma_path, std::filesystem::path const &target_workshop_path);

            void CreateArmaCfg(std::vector<std::filesystem::path> const &mod_paths, std::filesystem::path cfg_path = "");
            bool IsProton();
            void Start(std::string const &arguments, std::string const &user_environment_variables, bool launch_directly = false,
                       bool disable_esync = false);

            std::vector<Mod> GetHomeMods();
            std::vector<Mod> GetWorkshopMods();

            std::filesystem::path const &GetPath();
            std::filesystem::path const &GetPathExecutable();
            std::filesystem::path const &GetPathWorkshop();

        private:
            std::vector<Mod> GetModsFromDirectory(std::filesystem::path const &dir);
            std::filesystem::path GetCfgPath();
            char GetFakeDriveLetter();
            std::string GenerateCfgCppForMod(std::filesystem::path const &path, int mod_index);
            bool IsFlatpak();

            std::filesystem::path path_;
            std::filesystem::path path_custom_;
            std::filesystem::path path_executable_;
            std::filesystem::path path_workshop_local_;
            std::filesystem::path path_workshop_target_;
    };
}
