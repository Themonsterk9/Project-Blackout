# Changelog

All notable changes to **Project Blackout** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.0.2] - 2026-07-27

### Added
- **Phase 2 Core Character System**:
  - Implemented `ABlackoutCharacter` base C++ character class derived from `ACharacter`.
  - Implemented 13-state movement state machine (`EBlackoutCharacterState`) covering `Idle`, `Walking`, `Running`, `Sprinting`, `Jumping`, `Falling`, `Landing`, `Crouching`, `Prone`, `Crawling`, `Sliding`, `Climbing`, `Vaulting`.
  - Configured movement physics (MaxStepHeight 45cm, WalkableFloorAngle 45°, GroundFriction 8.0, BrakingDecelerationWalking 2048.0).
  - Implemented locomotion mechanics: Sprinting (650 cm/s), Crouching (180 cm/s), Prone/Crawling (100 cm/s), Sliding (decay impulse), Vaulting (low obstacle detection raycast), and Climbing (climbable wall detection raycast).
  - Implemented custom Animation Instance `UBlackoutAnimInstance` with property bindings for speed, direction, in-air, stance states, sliding, vaulting, and climbing.
  - Implemented `ABlackoutPlayerController` with mobile touch control readiness and input mapping bindings.
  - Updated `validate_project.py` test suite for Phase 2 validation.

## [0.0.1] - 2026-07-27

### Added
- **Phase 1 Project Foundation**:
  - Created `.uproject` descriptor specifying Unreal Engine 5.4 association, core plugins, and multiplatform targets.
  - Implemented C++ module build rules (`ProjectBlackout.Target.cs`, `ProjectBlackoutEditor.Target.cs`, `ProjectBlackout.Build.cs`).
  - Implemented core module entry points (`ProjectBlackout.h`, `ProjectBlackout.cpp`).
  - Configured core engine systems in `Config/DefaultEngine.ini`.
  - Established platform-specific overrides for Windows, Android, and iOS.
  - Created standard asset directory hierarchy across 15+ specialized subfolders.
  - Initialized Git version control.
