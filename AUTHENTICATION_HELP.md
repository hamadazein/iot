# 🔑 Setup GitHub Authentication

## Masalah Authentication
Anda mendapat error 403 karena login dengan akun yang berbeda (`mysitleh` vs `hamadazein`).

## Solusi 1: Personal Access Token (Recommended)

### 1. Buat Personal Access Token
1. Buka [GitHub Settings > Developer settings > Personal access tokens](https://github.com/settings/tokens)
2. Klik "Generate new token (classic)"
3. Beri nama: "Arduino IoT Projects"
4. Pilih scope:
   - `repo` (Full control of private repositories)
   - `workflow` (Update GitHub Action workflows)
5. Klik "Generate token"
6. **COPY TOKEN** (hanya muncul sekali!)

### 2. Update Remote URL dengan Token
```bash
git remote set-url origin https://YOUR_TOKEN@github.com/hamadazein/iot.git
```

### 3. Push ke GitHub
```bash
git push -u origin main
```

## Solusi 2: SSH Key (Alternative)

### 1. Generate SSH Key
```bash
ssh-keygen -t rsa -b 4096 -C "hamada@email.com"
```

### 2. Add SSH Key to GitHub
```bash
cat ~/.ssh/id_rsa.pub
```
Copy output dan paste di GitHub Settings > SSH Keys

### 3. Update Remote URL
```bash
git remote set-url origin git@github.com:hamadazein/iot.git
```

## Solusi 3: GitHub CLI
```bash
gh auth login
git push -u origin main
```

## ✅ Setelah Authentication Berhasil

Repository Anda akan berisi:
- ✅ 7 proyek Arduino yang rapi dan profesional
- ✅ Documentation lengkap untuk setiap proyek  
- ✅ Website GitHub Pages (index.html)
- ✅ Struktur folder yang konsisten
- ✅ Kode yang clean dan well-documented
- ✅ MIT License
- ✅ Professional README.md

## 🌐 GitHub Pages Setup

Setelah push berhasil:
1. Buka repository di GitHub
2. Go to Settings > Pages
3. Source: Deploy from branch
4. Branch: main / (root)
5. Save

Website akan tersedia di: `https://hamadazein.github.io/iot`