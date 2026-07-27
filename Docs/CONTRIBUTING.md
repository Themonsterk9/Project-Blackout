# Contributing to Project Blackout

## Code Style & Standards

1. **C++ Naming Conventions**:
   - Class prefixes follow Unreal Engine standards (`A` for Actors, `U` for UObjects, `F` for Structs, `I` for Interfaces, `E` for Enums).
   - Use PascalCase for functions, variables, and type declarations.
   - Use `UPROPERTY()` and `UFUNCTION()` macros with appropriate specifiers and categories.

2. **Branching Strategy**:
   - `main`: Production-ready releases.
   - `develop`: Nightly integration branch.
   - `feature/<name>`: Individual feature work.

3. **Commit Messages**:
   - Use conventional commit formats (e.g. `feat: add recoil component`, `fix: resolve camera collision jitter`).
