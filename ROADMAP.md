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

---

## Phase 4 — Combat System (Completed)
- [x] Weapon Base Class (`ABlackoutWeaponBase`) & Weapon Manager (`UBlackoutWeaponManagerComponent`).
- [x] Fire Modes: Single, Burst, Automatic.
- [x] Hitscan & Ballistic bullet trajectory mechanics.
- [x] Damage System with Headshot (2.5x), Limb (0.75x) multipliers & Armor absorption (70%).
- [x] Tactical & Empty Reloading, Vertical/Horizontal Recoil, ADS zoom.
- [x] Melee Component (`UBlackoutMeleeComponent`) & Tactical Throwable Grenades (`ABlackoutThrowable`).
- [x] Health & Armor System (`UBlackoutHealthComponent`).

---

## Phase 5 — Multiplayer Framework (Completed)
- [x] Dedicated Server GameMode (`ABlackoutGameMode`).
- [x] Replicated GameState (`ABlackoutGameState`) & PlayerState (`ABlackoutPlayerState`).
- [x] Network Session Manager (`UBlackoutSessionManager`).
- [x] Network replication across Movement, Camera, Weapon States, and Health.

---

## Phase 6 — Maps & Environment Framework (Completed)
- [x] Level Data Assets (`UBlackoutMapDataAsset`).
- [x] Team Spawn System (`ABlackoutSpawnPoint`).
- [x] Environmental System (`ABlackoutEnvironmentSystem`) for Day/Night cycles and Weather parameters.

---

## Phase 7 — Game Modes (Completed)
- [x] Team Deathmatch (`ABlackoutGameMode_TDM`).
- [x] Free For All (`ABlackoutGameMode_FFA`).
- [x] Domination (`ABlackoutGameMode_Domination` & `ABlackoutCaptureZone`).
- [x] Search & Destroy (`ABlackoutGameMode_SnD`).
- [x] Battle Royale (`ABlackoutGameMode_BattleRoyale`).
- [x] Practice Mode (`ABlackoutGameMode_Practice`).

---

## Phase 8 — AI System (Completed)
- [x] AI Controller (`ABlackoutAIController`) & AI Character (`ABlackoutAICharacter`).
- [x] Perception System (`UAIPerceptionComponent`) with Sight & Hearing config.
- [x] AI States: Patrol, Investigate, Chase, Combat, TakeCover, Retreat, Flank.
- [x] Difficulty Settings: Easy, Normal, Hard, Expert.

---

## Phase 9 — Vehicles (Completed)
- [x] Vehicle Base Class (`ABlackoutVehicleBase`) with Fuel, Health, Occupants, and Replication.
- [x] Specialized Vehicles: Cars (`ABlackoutCar`), Motorcycles (`ABlackoutMotorcycle`), Boats (`ABlackoutBoat`), Helicopters (`ABlackoutHelicopter`).
- [x] Vehicle Damage & Destruction framework.

---

## Phase 10 — Inventory System (Completed)
- [x] Inventory Manager Component (`UBlackoutInventoryComponent`) & Storage Slots.
- [x] Ground Loot Pickups (`ABlackoutLootItem`).
- [x] Weapon Attachment Framework, Armor Durability (Helmets & Vests), and Healing Items.
- [x] Network replication for inventory items and equipment.

---

## Phase 11 — UI, Audio, & Final Production Packaging (Upcoming)
- [ ] Production build packaging for Windows, Google Play, and Apple App Store.
