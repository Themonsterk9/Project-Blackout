# Project Blackout - Development Roadmap

This document outlines the phased development plan for **Project Blackout**, an online multiplayer tactical shooter.

---

## Phase 1 — Project Foundation (Completed)
- [x] Create project descriptor (`ProjectBlackout.uproject`).
- [x] Configure complete C++ source and module build target infrastructure.
- [x] Establish engine settings (Rendering, Physics, Collision, Input, Navigation, Audio, Networking, Packaging).
- [x] Configure platform-specific targets (Windows, Android, iOS).
- [x] Initialize Git repository & version control files (`.gitignore`, `LICENSE`, `README.md`).
- [x] Build complete asset folder hierarchy in `Content/`.

---

## Phase 2 — Core Character & Locomotion Systems (Completed)
- [x] Implement FPP / TPP camera spring arm component with smooth transition logic.
- [x] Base Tactical Character C++ class with 13-state locomotion state machine (`EBlackoutCharacterState`).
- [x] Stances: Standing, Crouching, Prone, Crawling.
- [x] Advanced movement: Sprinting, Sliding, Climbing, Vaulting.
- [x] Custom Animation Instance `UBlackoutAnimInstance` & `ABlackoutPlayerController`.

---

## Phase 3 — Camera System (Completed)
- [x] FPP (Head view) & TPP (Left/Right Shoulder) views.
- [x] Camera Manager & Camera Component (`UBlackoutCameraComponent`).
- [x] Procedural Head Bob, Landing Camera Shake, FOV interpolation.
- [x] Camera collision probe & obstacle avoidance.
- [x] Configurable Mouse, Controller, and Touch sensitivity settings.

---

## Phase 4 — Combat System (Completed)
- [x] Weapon Base Class (`ABlackoutWeaponBase`) & Weapon Manager (`UBlackoutWeaponManagerComponent`).
- [x] Fire Modes: Single, Burst, Automatic.
- [x] Hitscan & Ballistic bullet trajectory mechanics.
- [x] Damage System with Headshot (2.5x), Limb (0.75x) multipliers & Armor absorption (70%).
- [x] Tactical & Empty Reloading, Vertical/Horizontal Recoil, ADS zoom.
- [x] Melee Component (`UBlackoutMeleeComponent`) & Tactical Throwable Grenades (`ABlackoutThrowable`).
- [x] Health & Armor System (`UBlackoutHealthComponent`) with death & respawn delegates.

---

## Phase 5 — Multiplayer Framework (Completed)
- [x] Dedicated Server GameMode (`ABlackoutGameMode`).
- [x] Replicated GameState (`ABlackoutGameState`) & PlayerState (`ABlackoutPlayerState`).
- [x] Network Session Manager (`UBlackoutSessionManager`) for Lobby, Quick Match, Custom Matches, Friends, Party, and Team Voice.
- [x] Network replication across Movement, Camera, Weapon States, and Health.

---

## Phase 6 — Maps & Environment Framework (Completed)
- [x] Level Data Assets (`UBlackoutMapDataAsset`) for:
  - Training Ground
  - Small MP Map (Factory)
  - Medium MP Map (District)
  - Large Open World Map
  - Battle Royale Map (Island)
- [x] Team Spawn System (`ABlackoutSpawnPoint`).
- [x] Environmental System (`ABlackoutEnvironmentSystem`) for Day/Night cycles, Weather parameters (`Clear`, `Rain`, `Fog`, `Storm`), and lighting.

---

## Phase 7 — UI, Audio, & Production Packaging (Next Phase)
- [ ] Tactical Slate/UMG HUD (Minimap, Ammo, Health, Kill Feed).
- [ ] Production build packaging for Windows, Google Play, and Apple App Store.
