# Project Blackout

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![Build](https://img.shields.io/badge/build-Production%2FShipping-brightgreen.svg)
![Engine](https://img.shields.io/badge/Unreal%20Engine-5.4-orange.svg)
![Platforms](https://img.shields.io/badge/platforms-Windows%20%7C%20Android%20%7C%20iOS-brightgreen.svg)
![License](https://img.shields.io/badge/license-Proprietary-red.svg)

## Overview

**Project Blackout** is a AAA-quality online multiplayer tactical shooter offering both First-Person (FPP) and Third-Person (TPP) perspectives. Built on Unreal Engine 5.4, it features high-fidelity ballistics, fluid 13-state locomotion mechanics, modular weapon systems, competitive ranking, AI bots, tactical vehicles, inventory management, user customization, multiplatform UI/UX, cloud backend services, zero-allocation performance object pooling, server-authoritative anti-cheat security, and live operations infrastructure.

---

## Key Features & Completed Systems (Phases 1–18)

- **Core Locomotion System**: 13-state locomotion (Walk, Run, Sprint, Crouch, Prone, Crawling, Slide, Vault, Climb).
- **Tactical Camera System**: FPP, TPP Shoulder view, Head bobbing, Landing shake, FOV zoom.
- **Combat & Weapons System**: Ballistic trajectory, hitscan, recoil patterns, ADS zoom, tactical reload, melee, grenades, health & 70% armor mitigation.
- **Dedicated Server Multiplayer**: GameMode, GameState, PlayerState, Session Subsystem, replication rules.
- **Maps & Environment**: Map framework, team spawn points, dynamic Day/Night cycle, weather system.
- **Game Modes**: Team Deathmatch (TDM), Free For All (FFA), Domination, Search & Destroy, Battle Royale, Offline Practice Mode.
- **AI System**: Perception (Sight & Hearing), Behavior States (Patrol, Combat, Cover, Retreat), Difficulty (Easy to Expert), Squad AI.
- **Vehicles System**: Tactical Cars, Motorcycles, Speed Boats, Helicopters (Flight lift, hover), vehicle damage & destruction.
- **Inventory System**: Backpack (30kg/20 slots), ground loot pickups, weapon attachments, armor durability, healing items.
- **Player Progression**: Level 1-100 system, Competitive Ranks (Bronze to Grandmaster), Achievements, Daily Missions, Lifetime Stats.
- **Customization System**: Character appearance, weapon skins manager, 8-slot emote wheel, 5 loadout slots, player profile card.
- **UI / UX Framework**: Tactical HUD, Minimap, Inventory UI, Main Menu, Settings Menu, Match Summary, Mobile touch overlay.
- **Backend Services**: Account Auth (JWT tokens), Cloud Save, Global/Regional Leaderboards, Match History, MD5 payload security.
- **Performance Optimization**: Zero-allocation Object Pooling (`UBlackoutObjectPoolSubsystem`), Low-Ultra graphics presets, network dormancy, platform tuning (Android scaling, iOS Metal, Windows DLSS/FSR).
- **Security & Anti-Cheat**: Server-authoritative movement validation (Speed hack & Teleport detection), combat validation, encryption, security audit logs.
- **Live Operations & Release**: Hotfixes, Maintenance Mode, Versioning (`v1.0.0`), Telemetry logging, Server Deployment manager, multiplatform distribution manifests.

---

## Technical Stack & Compatibility

- **Engine Version**: Unreal Engine 5.4+
- **Primary Language**: C++ / Blueprints
- **Networking**: Unreal Online Subsystem (Steam / EOS / Dedicated Server)
- **Target Platforms**:
  - Windows 10/11 64-bit (DirectX 12 / Vulkan 1.3)
  - Android 14 (API Level 26+ / ARM64)
  - iOS 15.0+ (Metal RHI)

---

## Directory Architecture

```
Project Blackout/
├── Binaries/                 # Compiled binaries & dynamic libraries
├── Build/                    # Platform build manifests and certificates
│   ├── BUILD_MANIFEST.json   # Multiplatform production shipping manifest
│   ├── Android/
│   ├── IOS/
│   └── Windows/
├── Config/                   # Engine & game configuration files
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultInput.ini
│   ├── DefaultEditor.ini
│   └── DefaultAudio.ini
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
├── Docs/                     # Production & Technical Documentation Suite
│   ├── API_DOCUMENTATION.md
│   ├── DEPLOYMENT_GUIDE.md
│   ├── OPERATIONAL_GUIDE.md
│   ├── SERVER_SETUP_GUIDE.md
│   └── USER_GUIDE.md
├── Plugins/                  # Custom engine plugins
├── Source/                   # C++ Source code
│   └── ProjectBlackout/      # Primary runtime game module
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
3. Set configuration to `Shipping` | `Win64`.
4. Build the solution (F7).
5. Launch the application or deploy via `validate_project.py`.

---

## License

Copyright © 2026 Blackout Studios. All Rights Reserved. Proprietary software.
