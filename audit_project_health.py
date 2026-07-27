import os
import sys
import re
import json

SOURCE_DIR = r"Source/ProjectBlackout"

def run_health_audit():
    print("==================================================")
    print("   PROJECT BLACKOUT - AUTOMATED HEALTH AUDITOR   ")
    print("==================================================")

    issues = []
    warnings = []
    audited_files = 0

    # 1. Audit Header Files (.h)
    for root, _, files in os.walk(SOURCE_DIR):
        for file in files:
            if file.endswith(".h"):
                audited_files += 1
                file_path = os.path.join(root, file)
                with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                    lines = content.splitlines()

                # Check #pragma once
                if "#pragma once" not in content:
                    issues.append(f"Header '{file}' missing #pragma once.")

                # Check generated.h position
                gen_header = file.replace(".h", ".generated.h")
                if gen_header in content:
                    # Check if generated.h is the last included header
                    includes = [l.strip() for l in lines if l.strip().startswith("#include")]
                    if includes and not includes[-1].endswith(gen_header + '"') and not includes[-1].endswith(gen_header + '>'):
                        issues.append(f"Header '{file}': '{gen_header}' must be the LAST included header.")

                # Check UCLASS / GENERATED_BODY match
                if "UCLASS(" in content or "UCLASS ()" in content:
                    if "GENERATED_BODY()" not in content:
                        issues.append(f"Header '{file}' contains UCLASS but lacks GENERATED_BODY().")

    # 2. Audit CPP Files (.cpp)
    for root, _, files in os.walk(SOURCE_DIR):
        for file in files:
            if file.endswith(".cpp"):
                audited_files += 1
                file_path = os.path.join(root, file)
                with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                    lines = content.splitlines()

                matching_header = file.replace(".cpp", ".h")
                # Ensure matching header is included
                if matching_header in os.listdir(SOURCE_DIR):
                    if not any(l.strip().startswith("#include") and matching_header in l for l in lines[:5]):
                        warnings.append(f"Source file '{file}' should include '{matching_header}' as its first include.")

    # 3. Check for leftover debug symbols or unsafe functions
    for root, _, files in os.walk(SOURCE_DIR):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".h"):
                file_path = os.path.join(root, file)
                with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                    if "strcpy(" in content or "sprintf(" in content:
                        warnings.append(f"File '{file}' uses legacy C string functions (strcpy/sprintf). Prefer UE FString formatting.")

    # 4. Check Project Settings & Config Integrity
    config_files = ["DefaultEngine.ini", "DefaultGame.ini", "DefaultInput.ini", "DefaultEditor.ini", "DefaultAudio.ini"]
    for cfg in config_files:
        cfg_path = os.path.join("Config", cfg)
        if not os.path.exists(cfg_path):
            issues.append(f"Missing configuration file: Config/{cfg}")
        else:
            with open(cfg_path, "r", encoding="utf-8") as f:
                c = f.read()
                if len(c.strip()) == 0:
                    issues.append(f"Configuration file Config/{cfg} is empty.")

    # 5. Check Project Descriptor (.uproject)
    if os.path.exists("ProjectBlackout.uproject"):
        try:
            with open("ProjectBlackout.uproject", "r") as f:
                up_data = json.load(f)
                if up_data.get("FileVersion") != 3:
                    issues.append("ProjectBlackout.uproject FileVersion is not 3.")
        except Exception as e:
            issues.append(f"ProjectBlackout.uproject is invalid JSON: {e}")
    else:
        issues.append("Missing ProjectBlackout.uproject descriptor.")

    print(f"\nAudit completed across {audited_files} source files and project configurations.")
    print("--------------------------------------------------")
    print(f"Critical Issues Found: {len(issues)}")
    print(f"Warnings Found:        {len(warnings)}")
    print("--------------------------------------------------")

    if issues:
        print("\nCRITICAL ISSUES DETECTED:")
        for iss in issues:
            print(f" [!] {iss}")

    if warnings:
        print("\nWARNINGS ENCOUNTERED:")
        for w in warnings:
            print(f" [*] {w}")

    if not issues and not warnings:
        print("\nPROJECT HEALTH: PERFECT (0 Issues, 0 Warnings)")

    return len(issues)

if __name__ == "__main__":
    sys.exit(run_health_audit())
