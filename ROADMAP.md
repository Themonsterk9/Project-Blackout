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
- [x] Comprehensive documentation & validation test script.

---

## Phase 2 — Core Character & Camera Systems (Upcoming)
- [ ] Implement FPP / TPP camera spring arm component with smooth transition logic.
- [ ] Base Tactical Character C++ class with locomotion state machine.
- [ ] Advanced movement: Stance switching (Stand, Crouch, Prone), Sprinting, Leaning (Left/Right).
- [ ] Character animation interface & stamina/health attribute components.

---

## Phase 3 — Ballistics & Modular Weapon Framework (Upcoming)
- [ ] Modular Weapon Base class with attachment socket system.
- [ ] Realistic projectile ballistics (bullet drop, velocity curves, drag, penetration).
- [ ] Recoil patterns, weapon sway, and spread mechanics.
- [ ] Reloading states, ammo inventory management, and weapon switching.

---

## Phase 4 — Online Multiplayer & Networking Infrastructure (Upcoming)
- [ ] Dedicated Server target rules & lobby matchmaking logic.
- [ ] Network replication for character movement, weapon states, and player inventory.
- [ ] Client-side prediction & lag compensation routines.
- [ ] In-game voice chat & squad communication channels via OnlineSubsystem.

---

## Phase 5 — Tactical UI, Audio, & Map Environments (Upcoming)
- [ ] Slate/UMG Tactical HUD (Mini-map, Ammo counter, Health/Stamina bars, Kill feed).
- [ ] Main Menu system, graphics/audio setting menus, and server browser.
- [ ] Spatial 3D audio occlusion & dynamic footstep sound surfaces.
- [ ] Level design greyboxing, tactical cover placement, and lighting optimization.

---

## Phase 6 — Polishing, Optimization, & Multiplatform Packaging (Upcoming)
- [ ] Mobile touch controls & HUD layout adaptation for Android / iOS.
- [ ] Nanite & Lumen performance profiling and shader optimization.
- [ ] Anti-cheat integration & security auditing.
- [ ] Production build packaging for Windows, Google Play, and Apple App Store.
