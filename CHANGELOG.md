# Changelog

All notable changes to **Project Blackout** will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.0.1] - 2026-07-27

### Added
- **Phase 1 Project Foundation**:
  - Created `.uproject` descriptor specifying Unreal Engine 5.4 association, core plugins, and multiplatform targets.
  - Implemented C++ module build rules (`ProjectBlackout.Target.cs`, `ProjectBlackoutEditor.Target.cs`, `ProjectBlackout.Build.cs`).
  - Implemented core module entry points (`ProjectBlackout.h`, `ProjectBlackout.cpp`).
  - Configured core engine systems in `Config/DefaultEngine.ini` (Rendering, Physics, Collision, Navigation, Audio, Networking, Animation, Packaging).
  - Configured input mappings for FPP/TPP tactical controls in `Config/DefaultInput.ini`.
  - Configured general project metadata in `Config/DefaultGame.ini`.
  - Established platform-specific overrides for Windows, Android, and iOS.
  - Created standard asset directory hierarchy across 15+ specialized subfolders.
  - Initialized Git version control with custom `.gitignore` tailored for UE5 C++ development.
  - Added documentation (`README.md`, `CHANGELOG.md`, `ROADMAP.md`, `ARCHITECTURE.md`, `CONTRIBUTING.md`).
  - Created `validate_project.py` automated project verification tool.
