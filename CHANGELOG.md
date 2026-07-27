# Changelog

All notable changes to **Project Blackout** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.9.0] - 2026-07-27

### Added
- **Phase 15 Performance Optimization**:
  - Implemented `UBlackoutObjectPoolSubsystem` for zero-allocation actor and particle reuse during combat.
  - Implemented `UBlackoutPerformanceSubsystem` managing Low/Medium/High/Ultra graphics quality presets, network replication dormancy (`DORM_DormantAll`), net update frequency tuning, and level preloading.
  - Configured platform-specific performance options: Windows (DLSS/FSR integration, 144Hz+ support), Android (Adaptive Resolution 0.85x, Thermal/Battery throttling protection), iOS (Metal RHI optimization).
  - Bound Animation Update Rate Optimizations (`bEnableUpdateRateOptimizations = true`).
- **Phase 16 Security & Anti-Cheat**:
  - Implemented `UBlackoutAntiCheatSubsystem` for server-authoritative movement validation (speed hack cap 1000cm/s, teleport detection 1500 units/frame).
  - Implemented combat validation (fire-rate interval validation, damage sanity checks).
  - Implemented data protection (Base64 payload encryption/decryption, input string sanitization).
  - Implemented audit logging (`LogSecurityViolation`) and security event tracking.
- **Phase 17 Testing & Quality Assurance**:
  - Comprehensive QA & Regression Test Suite in `validate_project.py` validating all 17 phases.
  - Stress testing simulation (64 players, heavy combat, vehicle traffic, backend load).

## [0.0.5] - 2026-07-27

### Added
- **Phase 11 Player Progression**: XP, Level 1-100, Ranks (Bronze to Grandmaster), Achievements, Daily Missions, Lifetime Stats.
- **Phase 12 Customization**: Appearance, Weapon Skins, Emote Wheel, Loadouts 1-5, Player Profile card.
- **Phase 13 UI / UX**: Main Menu, Tactical HUD, Minimap, Inventory UI, Match Summary, Mobile Touch controls.
- **Phase 14 Backend Services**: Account Auth, Cloud Save, Leaderboards, Match History, Payload Security.

## [0.0.4] - 2026-07-27

### Added
- **Phase 7 Game Modes**: TDM, FFA, Domination, Search & Destroy, Battle Royale, Practice Mode.
- **Phase 8 AI System**: AI Perception, AI Controller, AI States, Difficulty levels, Squad AI.
- **Phase 9 Vehicles System**: Cars, Motorcycles, Boats, Helicopters, Damage & Replication.
- **Phase 10 Inventory System**: Backpack, Ground Loot, Attachments, Armor, Healing, Throwables.

## [0.0.3] - 2026-07-27

### Added
- **Phase 3 Camera System**: FPP/TPP, Head Bobbing, Landing Shake, Sensitivity.
- **Phase 4 Combat System**: Weapons, Recoil, ADS, Reloading, Melee, Grenades, Health/Armor.
- **Phase 5 Multiplayer Framework**: GameMode, GameState, PlayerState, Sessions, Replication.
- **Phase 6 Maps Framework**: Level Data Assets, Spawn Points, Weather, Day/Night system.
