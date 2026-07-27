# Changelog

All notable changes to **Project Blackout** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.0.3] - 2026-07-27

### Added
- **Phase 3 Camera System**:
  - Implemented `UBlackoutCameraComponent` supporting FPP, TPP (Left & Right Shoulder), instant/smooth switching, Procedural Head Bob, Landing Shake, Spring Arm collision probe, and sensitivity controls.
- **Phase 4 Combat System**:
  - Implemented `ABlackoutWeaponBase` supporting Single, Burst, Automatic fire modes, Hitscan & Ballistic bullet physics, Magazine reload timer, Vertical/Horizontal recoil kick, and ADS zoom.
  - Implemented `UBlackoutWeaponManagerComponent` for managing equipped weapon slots.
  - Implemented `UBlackoutMeleeComponent` for close-quarters knife attacks.
  - Implemented `ABlackoutThrowable` for tactical grenades.
  - Implemented `UBlackoutHealthComponent` with Headshot (2.5x), Limb (0.75x) multipliers, armor absorption (70%), death events, and healing.
- **Phase 5 Multiplayer Framework**:
  - Implemented `ABlackoutGameMode`, `ABlackoutGameState`, `ABlackoutPlayerState` with dedicated server session handling and network replication (`GetLifetimeReplicatedProps`).
  - Implemented `UBlackoutSessionManager` subsystem for Lobby, Matchmaking, Party, Friends, and Team Voice Chat hooks.
- **Phase 6 Maps & Environment Framework**:
  - Implemented `ABlackoutSpawnPoint` team spawn actor.
  - Implemented `ABlackoutEnvironmentSystem` for Day/Night cycles, Weather parameters (`Clear`, `Rain`, `Fog`, `Storm`), and atmospheric lighting.
  - Implemented `UBlackoutMapDataAsset` level descriptors for `TrainingGround`, `SmallMP_Factory`, `MediumMP_District`, `Large_CountrySide`, and `BattleRoyale_Island`.

## [0.0.2] - 2026-07-27

### Added
- **Phase 2 Core Character System**:
  - Implemented `ABlackoutCharacter` base C++ character class derived from `ACharacter`.
  - Implemented 13-state movement state machine (`EBlackoutCharacterState`).
  - Implemented Locomotion, Stances, Sliding, Vaulting, and Climbing mechanics.
  - Implemented `UBlackoutAnimInstance` and `ABlackoutPlayerController`.

## [0.0.1] - 2026-07-27

### Added
- **Phase 1 Project Foundation**:
  - Created `.uproject` descriptor, folder structure, engine configuration, platform settings, Git setup, and validation tools.
