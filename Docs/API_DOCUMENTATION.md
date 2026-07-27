# Project Blackout - REST API Documentation (v1.0.0)

Production API specifications for backend services integration.

---

## Base URL
`https://api.blackoutstudios.com/v1`

---

## Endpoints

### 1. Authentication
- `POST /auth/register` — Register new user account.
- `POST /auth/login` — Login and retrieve JWT Bearer token.
- `GET /auth/validate` — Validate session token.

### 2. Cloud Save
- `POST /cloudsave/sync` — Synchronize player progress, loadouts, and settings.
- `GET /cloudsave/fetch` — Fetch saved cloud profile.

### 3. Leaderboards
- `GET /leaderboards/global` — Fetch top 100 global rankings.
- `GET /leaderboards/regional` — Fetch regional rankings.

### 4. LiveOps & Health
- `GET /liveops/maintenance` — Query server maintenance status.
- `GET /liveops/version` — Validate client compatibility (v1.0.0).
