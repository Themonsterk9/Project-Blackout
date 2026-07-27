# Project Blackout - Deployment Guide (v1.0.0)

This document provides technical deployment procedures for **Project Blackout** (v1.0.0 Production Release).

---

## 1. Windows Deployment

### Build Artifacts
- Binary: `Binaries/Win64/ProjectBlackout-Win64-Shipping.exe`
- Packaging Output: `Saved/StagedBuilds/Windows/`

### System Prerequisites
- OS: Windows 10/11 64-bit
- GPU: DirectX 12 or Vulkan 1.3 compatible graphics adapter
- VC++ Redistributable: Microsoft Visual C++ 2022 Redistributable (x64)

### Launcher & Installer Setup
1. Package staged files into the Windows Installer package.
2. Sign `ProjectBlackout-Win64-Shipping.exe` with EV Code Signing Certificate.
3. Deploy to Steam / Epic Games Store distribution pipeline.

---

## 2. Android Deployment (Google Play)

### Build Artifacts
- App Bundle: `Build/Android/ProjectBlackout-v1.0.0.aab`
- Universal APK: `Build/Android/ProjectBlackout-v1.0.0.apk`

### Play Console Upload Checklist
1. Target API Level: 34 (Android 14).
2. Upload `.aab` to Play Console Production Track.
3. Configure Play Asset Delivery for high-resolution texture packs.
4. Verify App Signing by Google Play.

---

## 3. iOS Deployment (Apple App Store)

### Build Artifacts
- IPA Package: `Build/IOS/ProjectBlackout-v1.0.0.ipa`
- XCArchive: `Build/IOS/ProjectBlackout-v1.0.0.xcarchive`

### App Store Connect Upload Checklist
1. Open Transporter or Xcode Organizer.
2. Select distribution profile `Blackout Studios Distribution Profile`.
3. Submit build to App Store Connect Production Branch.
