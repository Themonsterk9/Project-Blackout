# Project Blackout

![Version](https://img.shields.io/badge/version-0.0.1-blue.svg)
![Engine](https://img.shields.io/badge/Unreal%20Engine-5.4-orange.svg)
![Platforms](https://img.shields.io/badge/platforms-Windows%20%7C%20Android%20%7C%20iOS-brightgreen.svg)
![License](https://img.shields.io/badge/license-Proprietary-red.svg)

## Overview

**Project Blackout** is a AAA-quality online multiplayer tactical shooter offering both First-Person (FPP) and Third-Person (TPP) perspectives. Built on Unreal Engine 5.4, it emphasizes high-fidelity ballistics, fluid movement mechanics, modular weapon systems, and multiplatform optimization for PC and mobile platforms.

---

## Technical Stack & Compatibility

- **Engine Version**: Unreal Engine 5.4+
- **Primary Language**: C++ / Blueprints
- **Networking**: Unreal Online Subsystem (Steam / EOS)
- **Target Platforms**:
  - Windows 10/11 64-bit (DirectX 12 / Vulkan)
  - Android (API Level 26+ / ARM64)
  - iOS (iOS 15.0+ / Metal)

---

## Directory Architecture

```
Project Blackout/
├── Binaries/                 # Compiled binaries & dynamic libraries
├── Build/                    # Platform build receipts and signing certificates
│   ├── Android/
│   ├── IOS/
│   └── Windows/
├── Config/                   # Engine & game configuration files
│   ├── Android/              # Android-specific override settings
│   ├── IOS/                  # iOS-specific override settings
│   └── Windows/              # Windows-specific override settings
├── Content/                  # Game assets & Blueprints
│   ├── Animations/           # Character & weapon animation sequences
│   ├── Audio/                # Sound effects, voice lines, and music
│   ├── Blueprints/           # Gameplay & UI blueprints
│   ├── Characters/           # Character meshes, rigs, and skins
│   ├── Data/                 # Data tables, curves, and data assets
│   ├── Effects/              # Particle systems, Niagara effects, and VFX
│   ├── Fonts/                # UI typography fonts
│   ├── Icons/                # HUD and menu icons
│   ├── Localization/         # String tables and translation files
│   ├── Maps/                 # Level maps and environments
│   ├── Materials/            # Shaders and material instances
│   ├── Textures/             # Texture maps and atlases
│   ├── UI/                   # Slate/UMG UI layouts and widgets
│   ├── Vehicles/             # Tactical vehicle assets
│   └── Weapons/              # Firearms, attachments, and melee assets
├── Docs/                     # Architectural & development documentation
│   ├── ARCHITECTURE.md
│   └── CONTRIBUTING.md
├── Intermediate/             # Engine build files and cached shaders
├── Plugins/                  # Custom engine plugins
├── Saved/                    # Game saves, logs, and screenshots
├── Source/                   # C++ Source code
│   ├── ProjectBlackout/      # Primary runtime game module
│   ├── ProjectBlackout.Target.cs
│   └── ProjectBlackoutEditor.Target.cs
├── .gitignore                # UE5 gitignore rules
├── CHANGELOG.md              # Project change history
├── LICENSE                   # Software license terms
├── ProjectBlackout.uproject  # Engine project descriptor
├── README.md                 # Primary documentation
└── ROADMAP.md                # Development phases and milestones
```

---

## Building & Launching

### Prerequisites
1. Unreal Engine 5.4 installed via Epic Games Launcher.
2. Visual Studio 2022 (v17.0+) with "Game development with C++" workload.
3. Android NDK (r25b) and Java JDK 17+ for Android packaging.
4. Xcode 15+ and Apple Developer Provisioning Profiles for iOS packaging.

### Steps
1. Right-click `ProjectBlackout.uproject` and select **Generate Visual Studio project files**.
2. Open `ProjectBlackout.sln` in Visual Studio.
3. Set configuration to `Development Editor` | `Win64`.
4. Build the solution (F7).
5. Launch the editor via Visual Studio or double-click `ProjectBlackout.uproject`.

---

## License

Copyright © 2026 Blackout Studios. All Rights Reserved. Proprietary software.
