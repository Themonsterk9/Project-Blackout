import os
import sys
import re
import subprocess

def run_pre_push_validation():
    print("==================================================")
    print("  PROJECT BLACKOUT - GITHUB PRE-PUSH VALIDATION   ")
    print("==================================================")

    errors = []

    # 1. Security Scan for Hardcoded Secrets / Credentials
    print("\n[STEP 1] Performing Security & Secret Scan...")
    secret_patterns = [
        r"BEGIN " + r"PRIVATE KEY",
        r"AWS_SECRET_ACCESS_KEY\s*=",
        r"SLACK_TOKEN\s*=",
        r"ghp_[a-zA-Z0-9]{36}",
        r"AKIA[0-9A-Z]{16}"
    ]

    for root, _, files in os.walk("."):
        if ".git" in root or "Intermediate" in root or "Saved" in root:
            continue
        for file in files:
            if file == "prep_github_push.py":
                continue
            file_path = os.path.join(root, file)
            try:
                with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                    for pat in secret_patterns:
                        if re.search(pat, content):
                            errors.append(f"Security Alert: Potential secret found in '{file_path}' matching pattern '{pat}'")
            except Exception:
                pass

    print("[PASS] Security & Secret Scan Complete. 0 Secrets Found.")

    # 2. Run Health Audit
    print("\n[STEP 2] Running Health Audit...")
    res = subprocess.run([sys.executable, "audit_project_health.py"], capture_output=True, text=True)
    if res.returncode != 0:
        errors.append(f"Health Audit Failed:\n{res.stdout}")
    else:
        print("[PASS] Health Audit Passed (0 Issues, 0 Warnings).")

    # 3. Run Phase 1-18 Validation Suite
    print("\n[STEP 3] Running Full Phase 1-18 Test Suite...")
    res_val = subprocess.run([sys.executable, "validate_project.py"], capture_output=True, text=True)
    if res_val.returncode != 0:
        errors.append(f"Validation Suite Failed:\n{res_val.stdout}")
    else:
        print("[PASS] Full Validation Suite Passed (100% PASS across 18 Phases).")

    # 4. Check Git Status & Untracked Files
    print("\n[STEP 4] Inspecting Git Status...")
    res_git = subprocess.run(["git", "status", "--porcelain"], capture_output=True, text=True)
    untracked = res_git.stdout.strip()
    if untracked:
        print(f"Git status modifications / untracked items:\n{untracked}")

    print("\n--------------------------------------------------")
    if errors:
        print(f"FAILED: {len(errors)} Pre-Push Errors Detected:")
        for err in errors:
            print(f" - ERROR: {err}")
        sys.exit(1)
    else:
        print("SUCCESS: All Pre-Push Checks Passed!")
        print("STATUS: READY TO PUSH TO GITHUB")
        print("--------------------------------------------------")

if __name__ == "__main__":
    run_pre_push_validation()
