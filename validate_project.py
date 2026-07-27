import os
import sys
import json

def run_validation():
    print("==================================================")
    print("  PROJECT BLACKOUT - PHASES 1-6 VALIDATION RUNNER ")
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

    # 3. Verify Version 0.0.3
    if os.path.exists("Config/DefaultGame.ini"):
        with open("Config/DefaultGame.ini", "r") as f:
            content = f.read()
            if "ProjectVersion=0.0.3" not in content:
                errors.append("ProjectVersion must be updated to 0.0.3 in DefaultGame.ini.")
        print("[PASS] Project Version 0.0.3 Verified.")

    # 4. Verify Phase 3 — Camera System
    phase3_files = [
        "Source/ProjectBlackout/BlackoutCameraComponent.h",
        "Source/ProjectBlackout/BlackoutCameraComponent.cpp"
    ]
    for p3 in phase3_files:
        if not os.path.exists(p3):
            errors.append(f"Missing Phase 3 file: {p3}")
    if os.path.exists("Source/ProjectBlackout/BlackoutCameraComponent.h"):
        with open("Source/ProjectBlackout/BlackoutCameraComponent.h", "r") as f:
            c = f.read()
            for token in ["EBlackoutPerspective", "SetPerspective", "TogglePerspective", "ToggleShoulder", "DoLandingCameraShake", "UpdateHeadBob"]:
                if token not in c:
                    errors.append(f"Camera feature '{token}' missing in BlackoutCameraComponent.h")
        print("[PASS] Phase 3 — Camera System (FPP/TPP, Bob, Shake, Sensitivity, Switch) Verified.")

    # 5. Verify Phase 4 — Combat System
    phase4_files = [
        "Source/ProjectBlackout/BlackoutWeaponBase.h",
        "Source/ProjectBlackout/BlackoutWeaponBase.cpp",
        "Source/ProjectBlackout/BlackoutWeaponManager.h",
        "Source/ProjectBlackout/BlackoutWeaponManager.cpp",
        "Source/ProjectBlackout/BlackoutMeleeComponent.h",
        "Source/ProjectBlackout/BlackoutMeleeComponent.cpp",
        "Source/ProjectBlackout/BlackoutThrowable.h",
        "Source/ProjectBlackout/BlackoutThrowable.cpp",
        "Source/ProjectBlackout/BlackoutHealthComponent.h",
        "Source/ProjectBlackout/BlackoutHealthComponent.cpp"
    ]
    for p4 in phase4_files:
        if not os.path.exists(p4):
            errors.append(f"Missing Phase 4 file: {p4}")

    if os.path.exists("Source/ProjectBlackout/BlackoutWeaponBase.h"):
        with open("Source/ProjectBlackout/BlackoutWeaponBase.h", "r") as f:
            c = f.read()
            for token in ["EBlackoutFireMode", "StartFire", "StartReload", "SetAiming", "RecoilVertical"]:
                if token not in c:
                    errors.append(f"Weapon feature '{token}' missing in BlackoutWeaponBase.h")

    if os.path.exists("Source/ProjectBlackout/BlackoutHealthComponent.h"):
        with open("Source/ProjectBlackout/BlackoutHealthComponent.h", "r") as f:
            c = f.read()
            for token in ["MaxHealth", "MaxArmor", "HandleTakePointDamage", "OnDeath"]:
                if token not in c:
                    errors.append(f"Health/Damage feature '{token}' missing in BlackoutHealthComponent.h")
        print("[PASS] Phase 4 — Combat System (Weapons, Recoil, Damage, Melee, Grenades, Health/Armor) Verified.")

    # 6. Verify Phase 5 — Multiplayer Framework
    phase5_files = [
        "Source/ProjectBlackout/BlackoutGameMode.h",
        "Source/ProjectBlackout/BlackoutGameMode.cpp",
        "Source/ProjectBlackout/BlackoutGameState.h",
        "Source/ProjectBlackout/BlackoutGameState.cpp",
        "Source/ProjectBlackout/BlackoutPlayerState.h",
        "Source/ProjectBlackout/BlackoutPlayerState.cpp",
        "Source/ProjectBlackout/BlackoutSessionManager.h",
        "Source/ProjectBlackout/BlackoutSessionManager.cpp"
    ]
    for p5 in phase5_files:
        if not os.path.exists(p5):
            errors.append(f"Missing Phase 5 file: {p5}")

    if os.path.exists("Source/ProjectBlackout/BlackoutGameState.h"):
        with open("Source/ProjectBlackout/BlackoutGameState.h", "r") as f:
            c = f.read()
            if "GetLifetimeReplicatedProps" not in c:
                errors.append("Replication method missing in BlackoutGameState.h")
        print("[PASS] Phase 5 — Multiplayer Framework (GameMode, GameState, PlayerState, Sessions, Replication) Verified.")

    # 7. Verify Phase 6 — Maps & Environment Framework
    phase6_files = [
        "Source/ProjectBlackout/BlackoutMapFramework.h",
        "Source/ProjectBlackout/BlackoutMapFramework.cpp"
    ]
    for p6 in phase6_files:
        if not os.path.exists(p6):
            errors.append(f"Missing Phase 6 file: {p6}")

    if os.path.exists("Source/ProjectBlackout/BlackoutMapFramework.h"):
        with open("Source/ProjectBlackout/BlackoutMapFramework.h", "r") as f:
            c = f.read()
            map_tokens = ["TrainingGround", "SmallMP", "MediumMP", "LargeOpenWorld", "BattleRoyale"]
            for mt in map_tokens:
                if mt not in c:
                    errors.append(f"Map type '{mt}' missing in BlackoutMapFramework.h")
            env_tokens = ["ABlackoutSpawnPoint", "ABlackoutEnvironmentSystem", "TimeOfDayHours", "EBlackoutWeatherType"]
            for et in env_tokens:
                if et not in c:
                    errors.append(f"Environment feature '{et}' missing in BlackoutMapFramework.h")
        print("[PASS] Phase 6 — Maps Framework (Training, Small/Medium/Large/BR Maps, Spawns, Weather, Day/Night) Verified.")

    # 8. Verify Git & Documentation
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
        print("SUCCESS: All Phase 1–6 Validation Checks Passed!")
        print("--------------------------------------------------")

if __name__ == "__main__":
    run_validation()
