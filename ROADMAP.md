# Project Blackout - Development Roadmap

This document outlines the phased development plan for **Project Blackout**, an online multiplayer tactical shooter.

---

## Phase 1 — Project Foundation (Completed)
- [x] Project descriptor (`ProjectBlackout.uproject`).
- [x] Source & module build target rules (`.Target.cs`, `.Build.cs`).
- [x] Engine settings, multiplatform configuration, Git initialization.

---

## Phase 2 — Core Character System (Completed)
- [x] Base Tactical Character C++ class with 13-state locomotion state machine (`EBlackoutCharacterState`).
- [x] Stances, Sprinting, Sliding, Climbing, Vaulting.

---

## Phase 3 — Camera System (Completed)
- [x] FPP / TPP camera perspectives, head bob, landing shake, FOV zoom, camera collision probe.

---

## Phase 4 — Combat System (Completed)
- [x] Weapon Base, Fire modes, Ballistics, Recoil, ADS, Reloading, Melee, Grenades, Health & Armor.

---

## Phase 5 — Multiplayer Framework (Completed)
- [x] Dedicated Server GameMode, GameState, PlayerState, Network Session Subsystem, Replication.

---

## Phase 6 — Maps & Environment Framework (Completed)
- [x] Level Data Assets, Spawn Points, Weather, Day/Night system.

---

## Phase 7 — Game Modes (Completed)
- [x] TDM, FFA, Domination (Capture Zones), Search & Destroy, Battle Royale, Practice Mode.

---

## Phase 8 — AI System (Completed)
- [x] AI Controller & AI Character with Perception (Sight/Hearing), AI States, Difficulty Settings, Squad AI.

---

## Phase 9 — Vehicles (Completed)
- [x] Cars, Motorcycles, Boats, Helicopters, Fuel/Health, Damage & Network Replication.

---

## Phase 10 — Inventory System (Completed)
- [x] Inventory Manager, Ground Loot, Weapon Attachments, Armor, Healing, Throwables.

---

## Phase 11 — Player Progression (Completed)
- [x] Level System (1-100), XP Calculation, Competitive Ranking (Bronze to Grandmaster), Achievements, Daily Missions, Season Reset, Lifetime Stats.

---

## Phase 12 — Customization (Completed)
- [x] Character Appearance (Face, Skin tone, Hair, Outfit), Weapon Skins, Emote Wheel, Loadouts (1-5), Player Profile card.

---

## Phase 13 — UI / UX (Completed)
- [x] Main Menu, Tactical HUD, Minimap, Inventory UI, Settings Menu, Match Summary, Mobile Touch Control overlay.

---

## Phase 14 — Backend Services (Completed)
- [x] Authentication (Register/Login/Token), Cloud Save Sync, Global/Regional Leaderboards, Match History logging, Payload MD5 Security.

---

## Phase 15 — Final Production Packaging & Optimization (Upcoming)
- [ ] Shipping build packaging for Windows, Android, and iOS.
