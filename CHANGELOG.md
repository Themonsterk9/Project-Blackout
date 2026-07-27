# Changelog

All notable changes to **Project Blackout** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.0.4] - 2026-07-27

### Added
- **Phase 7 Game Modes**:
  - Implemented `ABlackoutGameMode_TDM` (Team Deathmatch: team creation, kill scores, win conditions).
  - Implemented `ABlackoutGameMode_FFA` (Free For All: individual score tracking, kill limits).
  - Implemented `ABlackoutGameMode_Domination` (Domination: `ABlackoutCaptureZone` capture progress, ownership, score accumulation).
  - Implemented `ABlackoutGameMode_SnD` (Search & Destroy: bomb plant/defuse timers, round switching, elimination win condition).
  - Implemented `ABlackoutGameMode_BattleRoyale` (Battle Royale: player deployment, safe-zone shrinking, last player standing logic).
  - Implemented `ABlackoutGameMode_Practice` (Offline Practice Mode with AI bot spawning).
- **Phase 8 AI System**:
  - Implemented `ABlackoutAIController` & `ABlackoutAICharacter`.
  - Configured perception system (`UAIPerceptionComponent`) with Sight & Hearing senses (`UAISenseConfig_Sight`, `UAISenseConfig_Hearing`).
  - Implemented AI States (`Patrol`, `Investigate`, `Chase`, `Combat`, `TakeCover`, `Retreat`, `Flank`).
  - Implemented Difficulty levels (`Easy`, `Normal`, `Hard`, `Expert`) adjusting sight radius, reaction time, and accuracy.
- **Phase 9 Vehicles System**:
  - Implemented `ABlackoutVehicleBase` Pawn with fuel, health (500), occupant seats (Driver, Passengers), enter/exit mechanics, and replication.
  - Implemented specialized classes: `ABlackoutCar`, `ABlackoutMotorcycle` (leaning balance), `ABlackoutBoat` (buoyancy), and `ABlackoutHelicopter` (flight lift & hover).
- **Phase 10 Inventory System**:
  - Implemented `UBlackoutInventoryComponent` (Max 20 slots, 30kg capacity, item stacking, item removal, weight calculation).
  - Implemented `ABlackoutLootItem` ground loot pickup actor.
  - Implemented Item Types (`Weapon`, `Ammo`, `Attachment`, `Helmet`, `Vest`, `Healing`, `Throwable`).
  - Configured Armor durability (Helmet & Vest) and Healing item consumption.
  - Bound network replication across inventory items and armor durability.

## [0.0.3] - 2026-07-27

### Added
- **Phase 3 Camera System**: FPP, TPP (Left/Right Shoulder), Head Bob, Landing Shake, FOV interpolation, sensitivity settings.
- **Phase 4 Combat System**: Weapon Base, Fire modes, Recoil, ADS, Reloading, Melee, Grenades, Health & Armor system.
- **Phase 5 Multiplayer Framework**: GameMode, GameState, PlayerState, Session Subsystem, Network Replication.
- **Phase 6 Maps & Environment Framework**: Level Data Assets, Spawn Points, Weather, Day/Night System.

## [0.0.2] - 2026-07-27

### Added
- **Phase 2 Core Character System**: Base Character class, 13-state locomotion, Stances, Sliding, Vaulting, Climbing, AnimInstance.

## [0.0.1] - 2026-07-27

### Added
- **Phase 1 Project Foundation**: Project descriptor, folder hierarchy, engine configs, platform targets, Git setup.
