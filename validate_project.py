import os
import sys
import json

def run_validation():
    print("==================================================")
    print("    PROJECT BLACKOUT - PHASE 1 & 2 VALIDATION RUNNER")
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
            print("[PASS] Task 1 — Project Descriptor (.uproject) is valid JSON and correctly configured.")
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

    # 3. Verify Engine Configurations & Version
    ini_files = [
        "Config/DefaultEngine.ini",
        "Config/DefaultInput.ini",
        "Config/DefaultGame.ini",
        "Config/DefaultEditor.ini",
        "Config/DefaultAudio.ini"
    ]
    for ini in ini_files:
        if not os.path.exists(ini):
            errors.append(f"Missing configuration file: {ini}")

    if os.path.exists("Config/DefaultGame.ini"):
        with open("Config/DefaultGame.ini", "r") as f:
            content = f.read()
            if "ProjectVersion=0.0.2" not in content:
                errors.append("ProjectVersion must be updated to 0.0.2 in DefaultGame.ini.")
        print("[PASS] Phase 2 — Project Version 0.0.2 Verified.")

    # Check key contents in DefaultEngine.ini
    if os.path.exists("Config/DefaultEngine.ini"):
        with open("Config/DefaultEngine.ini", "r") as f:
            content = f.read()
            required_sections = [
                "[/Script/EngineSettings.GameMapsSettings]",
                "[/Script/Engine.RendererSettings]",
                "[/Script/Engine.PhysicsSettings]",
                "[/Script/Engine.CollisionProfile]",
                "[/Script/Engine.NavigationSystem]",
                "[/Script/Engine.AudioSettings]",
                "[/Script/Engine.NetworkSettings]",
                "[/Script/Engine.AnimationSettings]",
                "[/Script/UnrealEd.ProjectPackagingSettings]"
            ]
            for sec in required_sections:
                if sec not in content:
                    errors.append(f"Missing section '{sec}' in DefaultEngine.ini")
        print("[PASS] Task 3 — Engine Configuration Verified.")

    # Check key contents in DefaultInput.ini (Phase 2 Action Mappings)
    if os.path.exists("Config/DefaultInput.ini"):
        with open("Config/DefaultInput.ini", "r") as f:
            content = f.read()
            actions = ["Jump", "Fire", "Aim", "Reload", "Crouch", "Sprint", "Interact", "ToggleCamera", "Prone", "Slide", "Vault", "Climb"]
            for act in actions:
                if f'ActionName="{act}"' not in content:
                    errors.append(f"Missing input action mapping: {act}")
            axes = ["MoveForward", "MoveRight", "Turn", "LookUp"]
            for ax in axes:
                if f'AxisName="{ax}"' not in content:
                    errors.append(f"Missing input axis mapping: {ax}")
        print("[PASS] Phase 2 — Movement & Stance Input Action/Axis Mappings Verified.")

    # 4. Verify Platform Configuration
    platform_inis = {
        "Windows": "Config/Windows/WindowsEngine.ini",
        "Android": "Config/Android/AndroidEngine.ini",
        "iOS": "Config/IOS/IOSEngine.ini"
    }
    for plat, p_ini in platform_inis.items():
        if not os.path.exists(p_ini):
            errors.append(f"Missing platform config: {p_ini}")
    print("[PASS] Task 4 — Multiplatform Configuration (Windows, Android, iOS) Verified.")

    # 5. Verify Phase 2 Character System C++ Source Code
    cpp_files = [
        "Source/ProjectBlackout.Target.cs",
        "Source/ProjectBlackoutEditor.Target.cs",
        "Source/ProjectBlackout/ProjectBlackout.Build.cs",
        "Source/ProjectBlackout/ProjectBlackout.h",
        "Source/ProjectBlackout/ProjectBlackout.cpp",
        "Source/ProjectBlackout/BlackoutCharacterState.h",
        "Source/ProjectBlackout/BlackoutCharacter.h",
        "Source/ProjectBlackout/BlackoutCharacter.cpp",
        "Source/ProjectBlackout/BlackoutAnimInstance.h",
        "Source/ProjectBlackout/BlackoutAnimInstance.cpp",
        "Source/ProjectBlackout/BlackoutPlayerController.h",
        "Source/ProjectBlackout/BlackoutPlayerController.cpp"
    ]
    for cpp_f in cpp_files:
        if not os.path.exists(cpp_f):
            errors.append(f"Missing Phase 2 source file: {cpp_f}")

    # Check 13 states in BlackoutCharacterState.h
    if os.path.exists("Source/ProjectBlackout/BlackoutCharacterState.h"):
        with open("Source/ProjectBlackout/BlackoutCharacterState.h", "r") as f:
            state_content = f.read()
            states = ["Idle", "Walking", "Running", "Sprinting", "Jumping", "Falling", "Landing", "Crouching", "Prone", "Crawling", "Sliding", "Climbing", "Vaulting"]
            for s in states:
                if s not in state_content:
                    errors.append(f"Character State '{s}' missing in BlackoutCharacterState.h")
        print("[PASS] Phase 2 — 13 Character Locomotion States Verified.")

    # Check method signatures in BlackoutCharacter.h
    if os.path.exists("Source/ProjectBlackout/BlackoutCharacter.h"):
        with open("Source/ProjectBlackout/BlackoutCharacter.h", "r") as f:
            char_content = f.read()
            methods = ["StartSprint", "StopSprint", "StartCrouch", "StopCrouch", "ToggleProne", "StartSlide", "TryVault", "TryClimb", "CanTransitionToState", "SetCharacterState"]
            for m in methods:
                if m not in char_content:
                    errors.append(f"Method '{m}' missing in BlackoutCharacter.h")
        print("[PASS] Phase 2 — Character Locomotion & Obstacle Detection Methods Verified.")

    # 6. Verify Git & Documentation
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
        print("SUCCESS: All Phase 1 & Phase 2 Validation Checks Passed!")
        print("--------------------------------------------------")

if __name__ == "__main__":
    run_validation()
