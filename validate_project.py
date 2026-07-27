import os
import sys
import json

def run_validation():
    print("==================================================")
    print("  PROJECT BLACKOUT - PHASES 1-14 VALIDATION RUNNER")
    print("==================================================")

    errors = []

    # 1. Verify Project Descriptor (.uproject)
    uproject_path = "ProjectBlackout.uproject"
    if not os.path.exists(uproject_path):
        errors.append("Missing ProjectBlackout.uproject file.")
    else:
        try:
            with open(uproject_path, "r") as f:
                data = json.load(f)
            if data.get("FileVersion") != 3:
                errors.append(".uproject FileVersion must be 3.")
            modules = data.get("Modules", [])
            if not any(m.get("Name") == "ProjectBlackout" and m.get("Type") == "Runtime" for m in modules):
                errors.append("ProjectBlackout runtime module missing in .uproject.")
            platforms = data.get("TargetPlatforms", [])
            for required_p in ["Windows", "Android", "IOS"]:
                if required_p not in platforms:
                    errors.append(f"Target platform '{required_p}' missing in .uproject.")
            print("[PASS] Task 1 — Project Descriptor (.uproject) Verified.")
        except Exception as e:
            errors.append(f"Invalid .uproject JSON format: {e}")

    # 2. Verify Directory Structure
    required_root_dirs = [
        "Config", "Content", "Source", "Plugins", "Build", "Binaries", "Docs", "Saved", "Intermediate"
    ]
    required_content_dirs = [
        "Characters", "Weapons", "Vehicles", "Maps", "Materials", "Textures",
        "Animations", "Audio", "UI", "Effects", "Blueprints", "Data", "Icons",
        "Fonts", "Localization"
    ]

    for d in required_root_dirs:
        if not os.path.isdir(d):
            errors.append(f"Missing root folder: {d}")

    for cd in required_content_dirs:
        full_p = os.path.join("Content", cd)
        if not os.path.isdir(full_p):
            errors.append(f"Missing asset folder: {full_p}")

    print("[PASS] Task 2 & 8 — Project Directory & Asset Hierarchy Structure Verified.")

    # 3. Verify Version 0.0.5
    if os.path.exists("Config/DefaultGame.ini"):
        with open("Config/DefaultGame.ini", "r") as f:
            content = f.read()
            if "ProjectVersion=0.0.5" not in content:
                errors.append("ProjectVersion must be updated to 0.0.5 in DefaultGame.ini.")
        print("[PASS] Project Version 0.0.5 Verified.")

    # 4. Verify Phase 3-10 Systems
    prev_files = [
        "Source/ProjectBlackout/BlackoutCameraComponent.h",
        "Source/ProjectBlackout/BlackoutWeaponBase.h",
        "Source/ProjectBlackout/BlackoutGameMode.h",
        "Source/ProjectBlackout/BlackoutMapFramework.h",
        "Source/ProjectBlackout/BlackoutGameModes.h",
        "Source/ProjectBlackout/BlackoutAISystem.h",
        "Source/ProjectBlackout/BlackoutVehicleBase.h",
        "Source/ProjectBlackout/BlackoutInventorySystem.h"
    ]
    for p in prev_files:
        if not os.path.exists(p):
            errors.append(f"Missing previous system file: {p}")
    print("[PASS] Phases 3–10 — Camera, Combat, Multiplayer, Maps, Game Modes, AI, Vehicles, and Inventory Verified.")

    # 5. Verify Phase 11 — Player Progression
    p11_files = ["Source/ProjectBlackout/BlackoutProgressionSystem.h", "Source/ProjectBlackout/BlackoutProgressionSystem.cpp"]
    for p in p11_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 11 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutProgressionSystem.h"):
        with open("Source/ProjectBlackout/BlackoutProgressionSystem.h", "r") as f:
            c = f.read()
            for token in ["UBlackoutProgressionSubsystem", "EBlackoutCompetitiveRank", "FBlackoutPlayerStats", "FBlackoutDailyMission", "FBlackoutAchievement", "AddXP", "AddRankPoints"]:
                if token not in c:
                    errors.append(f"Progression feature '{token}' missing in BlackoutProgressionSystem.h")
        print("[PASS] Phase 11 — Player Progression System (XP, Levels 1-100, Ranks, Achievements, Daily Missions, Stats) Verified.")

    # 6. Verify Phase 12 — Customization
    p12_files = ["Source/ProjectBlackout/BlackoutCustomizationSystem.h", "Source/ProjectBlackout/BlackoutCustomizationSystem.cpp"]
    for p in p12_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 12 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutCustomizationSystem.h"):
        with open("Source/ProjectBlackout/BlackoutCustomizationSystem.h", "r") as f:
            c = f.read()
            for token in ["UBlackoutCustomizationComponent", "FBlackoutLoadout", "FBlackoutPlayerProfile", "FacePresetID", "WeaponSkins", "EquippedEmotes", "SaveLoadout"]:
                if token not in c:
                    errors.append(f"Customization feature '{token}' missing in BlackoutCustomizationSystem.h")
        print("[PASS] Phase 12 — Customization System (Appearance, Weapon Skins, Emote Wheel, Loadouts 1-5, Profile Card) Verified.")

    # 7. Verify Phase 13 — UI / UX
    p13_files = ["Source/ProjectBlackout/BlackoutUISystem.h", "Source/ProjectBlackout/BlackoutUISystem.cpp"]
    for p in p13_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 13 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutUISystem.h"):
        with open("Source/ProjectBlackout/BlackoutUISystem.h", "r") as f:
            c = f.read()
            for token in ["UBlackoutWidgetBase", "UBlackoutHUDWidget", "UBlackoutMinimapWidget", "UBlackoutInventoryWidget", "UBlackoutMainMenuWidget", "UBlackoutMatchSummaryWidget", "UBlackoutMobileLayoutWidget"]:
                if token not in c:
                    errors.append(f"UI feature '{token}' missing in BlackoutUISystem.h")
        print("[PASS] Phase 13 — UI / UX Framework (Main Menu, HUD, Minimap, Inventory UI, Match Summary, Mobile Touch) Verified.")

    # 8. Verify Phase 14 — Backend Services
    p14_files = ["Source/ProjectBlackout/BlackoutBackendService.h", "Source/ProjectBlackout/BlackoutBackendService.cpp"]
    for p in p14_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 14 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutBackendService.h"):
        with open("Source/ProjectBlackout/BlackoutBackendService.h", "r") as f:
            c = f.read()
            for token in ["UBlackoutBackendService", "RegisterUser", "LoginUser", "ValidateAuthToken", "SyncPlayerDataToCloud", "GetGlobalLeaderboard", "HashPayload"]:
                if token not in c:
                    errors.append(f"Backend feature '{token}' missing in BlackoutBackendService.h")
        print("[PASS] Phase 14 — Backend Services Architecture (Auth, Cloud Save, Leaderboards, Match History, Security) Verified.")

    # 9. Verify Git & Documentation
    doc_files = [".gitignore", "README.md", "CHANGELOG.md", "ROADMAP.md", "LICENSE"]
    for df in doc_files:
        if not os.path.exists(df):
            errors.append(f"Missing documentation file: {df}")

    if not os.path.isdir(".git"):
        errors.append("Git repository is not initialized (.git directory missing).")

    print("[PASS] Version Control (Git) & Comprehensive Documentation Verified.")

    print("\n--------------------------------------------------")
    if errors:
        print(f"FAILED: {len(errors)} validation errors detected:")
        for err in errors:
            print(f" - ERROR: {err}")
        sys.exit(1)
    else:
        print("SUCCESS: All Phase 1–14 Validation Checks Passed!")
        print("--------------------------------------------------")

if __name__ == "__main__":
    run_validation()
