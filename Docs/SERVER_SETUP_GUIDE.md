# Project Blackout - Dedicated Server Setup Guide (v1.0.0)

Instructions for deploying **Project Blackout** dedicated server instances on AWS, GCP, or Azure.

---

## Dedicated Server Specifications

- Minimum CPU: 4 vCPU (3.0 GHz+)
- Minimum RAM: 8 GB RAM
- Recommended Instance: AWS `c6i.xlarge` or GCP `c2-standard-4`
- Operating System: Ubuntu Server 22.04 LTS / Windows Server 2022

## Firewall & Network Ports

| Port | Protocol | Purpose |
|------|----------|---------|
| 7777 | UDP | Unreal Engine Gameplay Replication |
| 7778 | UDP | Beacon Peer Connection |
| 27015 | UDP | Steam Query Port |
| 8080 | TCP | Backend REST API Communication |

## Quick Start Command (Linux Server)

```bash
./ProjectBlackoutServer-Linux-Shipping ProjectBlackoutMap_Training?game=TDM -log -port=7777 -QueryPort=27015
```
