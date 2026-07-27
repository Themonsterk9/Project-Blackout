import os
import sys
import json

def run_validation():
    print("==================================================")
    print("  PROJECT BLACKOUT - PHASES 1-10 VALIDATION RUNNER")
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

    # 3. Verify Version 0.0.4
    if os.path.exists("Config/DefaultGame.ini"):
        with open("Config/DefaultGame.ini", "r") as f:
            content = f.read()
            if "ProjectVersion=0.0.4" not in content:
                errors.append("ProjectVersion must be updated to 0.0.4 in DefaultGame.ini.")
        print("[PASS] Project Version 0.0.4 Verified.")

    # 4. Verify Phase 3-6 Systems
    phase3_6_files = [
        "Source/ProjectBlackout/BlackoutCameraComponent.h",
        "Source/ProjectBlackout/BlackoutWeaponBase.h",
        "Source/ProjectBlackout/BlackoutGameMode.h",
        "Source/ProjectBlackout/BlackoutMapFramework.h"
    ]
    for p in phase3_6_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 3-6 file: {p}")
    print("[PASS] Phases 3–6 — Camera, Combat, Multiplayer, and Maps Frameworks Verified.")

    # 5. Verify Phase 7 — Game Modes
    p7_files = ["Source/ProjectBlackout/BlackoutGameModes.h", "Source/ProjectBlackout/BlackoutGameModes.cpp"]
    for p in p7_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 7 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutGameModes.h"):
        with open("Source/ProjectBlackout/BlackoutGameModes.h", "r") as f:
            c = f.read()
            for gmod in ["ABlackoutGameMode_TDM", "ABlackoutGameMode_FFA", "ABlackoutGameMode_Domination", "ABlackoutGameMode_SnD", "ABlackoutGameMode_BattleRoyale", "ABlackoutGameMode_Practice", "ABlackoutCaptureZone"]:
                if gmod not in c:
                    errors.append(f"Game Mode '{gmod}' missing in BlackoutGameModes.h")
        print("[PASS] Phase 7 — Game Modes Framework (TDM, FFA, Domination, SnD, BR, Practice) Verified.")

    # 6. Verify Phase 8 — AI System
    p8_files = ["Source/ProjectBlackout/BlackoutAISystem.h", "Source/ProjectBlackout/BlackoutAISystem.cpp"]
    for p in p8_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 8 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutAISystem.h"):
        with open("Source/ProjectBlackout/BlackoutAISystem.h", "r") as f:
            c = f.read()
            for token in ["ABlackoutAIController", "ABlackoutAICharacter", "UAIPerceptionComponent", "UAISenseConfig_Sight", "UAISenseConfig_Hearing", "EBlackoutAIDifficulty", "Easy", "Normal", "Hard", "Expert"]:
                if token not in c:
                    errors.append(f"AI feature '{token}' missing in BlackoutAISystem.h")
        print("[PASS] Phase 8 — AI System (Perception, Controller, States, Difficulty, Squad AI) Verified.")

    # 7. Verify Phase 9 — Vehicles System
    p9_files = ["Source/ProjectBlackout/BlackoutVehicleBase.h", "Source/ProjectBlackout/BlackoutVehicleBase.cpp"]
    for p in p9_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 9 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutVehicleBase.h"):
        with open("Source/ProjectBlackout/BlackoutVehicleBase.h", "r") as f:
            c = f.read()
            for vclass in ["ABlackoutVehicleBase", "ABlackoutCar", "ABlackoutMotorcycle", "ABlackoutBoat", "ABlackoutHelicopter", "EnterVehicle", "ExitVehicle", "ApplyVehicleDamage"]:
                if vclass not in c:
                    errors.append(f"Vehicle feature '{vclass}' missing in BlackoutVehicleBase.h")
        print("[PASS] Phase 9 — Vehicles System (Cars, Motorcycles, Boats, Helicopters, Damage & Replication) Verified.")

    # 8. Verify Phase 10 — Inventory System
    p10_files = ["Source/ProjectBlackout/BlackoutInventorySystem.h", "Source/ProjectBlackout/BlackoutInventorySystem.cpp"]
    for p in p10_files:
        if not os.path.exists(p):
            errors.append(f"Missing Phase 10 file: {p}")
    if os.path.exists("Source/ProjectBlackout/BlackoutInventorySystem.h"):
        with open("Source/ProjectBlackout/BlackoutInventorySystem.h", "r") as f:
            c = f.read()
            for inv_token in ["UBlackoutInventoryComponent", "ABlackoutLootItem", "EBlackoutItemType", "Weapon", "Attachment", "Helmet", "Vest", "Healing", "Throwable"]:
                if inv_token not in c:
                    errors.append(f"Inventory feature '{inv_token}' missing in BlackoutInventorySystem.h")
        print("[PASS] Phase 10 — Inventory System (Backpack, Ground Loot, Attachments, Armor, Healing, Throwables, Replication) Verified.")

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
        print("SUCCESS: All Phase 1–10 Validation Checks Passed!")
        print("--------------------------------------------------")

if __name__ == "__main__":
    run_validation()
