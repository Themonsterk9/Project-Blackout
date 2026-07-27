# Project Blackout - Architecture & Technical Design

## Architecture Overview

Project Blackout follows a modular C++ architecture designed for high scalability, multiplayer network efficiency, and multiplatform target support.

```
                  +-----------------------------------+
                  |      ProjectBlackout.uproject      |
                  +-----------------------------------+
                                    |
            +-----------------------+-----------------------+
            |                                               |
+------------------------+                       +--------------------+
|  ProjectBlackout.Target|                       |Editor.Target.cs    |
+------------------------+                       +--------------------+
            |                                               |
            +-----------------------+-----------------------+
                                    |
                    +-------------------------------+
                    |   ProjectBlackout.Build.cs    |
                    +-------------------------------+
                                    |
            +-----------------------+-----------------------+
            |                                               |
+------------------------+                       +--------------------+
| Core Engine Framework  |                       | OnlineSubsystem    |
| (Engine, Physics, UI)  |                       | (Steam/EOS/Sockets)|
+------------------------+                       +--------------------+
```

## Key Modules & Responsibilities

1. **Runtime Module (`ProjectBlackout`)**:
   - Contains all gameplay C++ logic, character components, weapon frameworks, and game state management.
   - Built against Unreal 5.4 Include Order and C++20 standards.

2. **Configuration Subsystem (`Config/`)**:
   - `DefaultEngine.ini`: Defines rendering pipelines (Lumen, Nanite, Virtual Shadows), physics substepping, navigation mesh rules, network tick rates (128Hz), and collision response profiles.
   - `DefaultInput.ini`: Configures input action and axis mappings for tactical movement, camera perspective toggling (FPP/TPP), and combat actions.
   - `DefaultGame.ini`: Project metadata, company credentials, version tracking.
   - `DefaultAudio.ini`: Audio bus mix and stereo 3D spatialization parameters.

3. **Platform Layer (`Config/{Windows,Android,IOS}/`)**:
   - Windows: DX12 RHI target, SM6 shader model.
   - Android: Vulkan/ES3.2, Min SDK 26, Target SDK 34, ARM64 packaging, app signing parameters.
   - iOS: Metal RHI, iOS 15.0 minimum SDK, automatic provisioning and bundle registration (`com.blackoutstudios.projectblackout`).
