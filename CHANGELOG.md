# Changelog

All notable changes to **Project Blackout** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.0.5] - 2026-07-27

### Added
- **Phase 11 Player Progression**:
  - Implemented `UBlackoutProgressionSubsystem` handling Level 1-100 XP calculation, competitive ranking (`Bronze`, `Silver`, `Gold`, `Platinum`, `Diamond`, `Master`, `Grandmaster`), Daily Mission generation & reset, Achievement tracking, and lifetime player statistics accumulation.
- **Phase 12 Customization**:
  - Implemented `UBlackoutCustomizationComponent` managing character appearance presets (face, skin tone, hair, outfits), weapon skin equipping & persistence, 8-slot emote wheel, 5 loadout slots (with save/load methods), and player profile card data.
- **Phase 13 UI / UX**:
  - Implemented `UBlackoutWidgetBase` Slate/UMG base widget framework.
  - Implemented `UBlackoutHUDWidget`, `UBlackoutMinimapWidget`, `UBlackoutInventoryWidget`, `UBlackoutMainMenuWidget`, `UBlackoutMatchSummaryWidget`, and `UBlackoutMobileLayoutWidget` (touch overlay, dynamic button layout, device auto-scaling).
- **Phase 14 Backend Services**:
  - Implemented `UBlackoutBackendService` game instance subsystem.
  - Features: Account Registration/Login/Auth token validation, Cloud Save data sync, Global/Regional/Friends Leaderboards, Match History logging, payload MD5 security hashing, and rate limiting framework.

## [0.0.4] - 2026-07-27

### Added
- **Phase 7 Game Modes**: TDM, FFA, Domination (Capture Zones), Search & Destroy, Battle Royale, Practice Mode.
- **Phase 8 AI System**: AI Perception (Sight & Hearing), Controller, AI States, Difficulty (Easy, Normal, Hard, Expert), Squad AI.
- **Phase 9 Vehicles System**: Cars, Motorcycles, Boats, Helicopters, Fuel/Health, Damage & Network Replication.
- **Phase 10 Inventory System**: Backpack, Ground Loot, Weapon Attachments, Armor, Healing Items, Network Replication.

## [0.0.3] - 2026-07-27

### Added
- **Phase 3 Camera System**: FPP/TPP camera, Head bobbing, Landing shake, Sensitivity controls.
- **Phase 4 Combat System**: Base weapon, Recoil, ADS, Reloading, Melee, Grenades, Health/Armor.
- **Phase 5 Multiplayer Framework**: GameMode, GameState, PlayerState, Session Subsystem, Replication.
- **Phase 6 Maps Framework**: Level Data Assets, Spawn Points, Weather, Day/Night system.
