# DSTR Healthcare System

Healthcare Data Structure Analysis System
> **Every time you make changes to the source code, recompile before running the program.**

```powershell
g++ main.cpp -o main.exe
.\main.exe
```
# Git Workflow & Conflict Resolution Reference

## 1. Standard Push Workflow
To save, commit, and push your changes to the remote repository:
```bash
git add .
git commit -m "Your commit message here"
git push
```
## 2. Handling Incoming Changes & Stashing
If you need to pull remote changes while you have local modifications, use git stash to temporarily save your work:

```Bash
git stash
git pull origin main
```
## 3. Re-applying Stashed Changes
To bring your saved stashed changes back into your working directory:

```Bash
git stash list
git stash apply "stash@{0}"
```
## 4. Solving Conflicts (Binaries / Specific Files)
If a conflict occurs (especially on compiled files like binaries), you must explicitly choose which version to keep:

To keep incoming (remote/their) changes:

```Bash
git checkout --theirs ../main.exe
git add ../main.exe
```
To keep your local (our) changes:

```Bash
git checkout --ours ../main.exe
git add ../main.exe
```
After resolving and staging the file, complete your commit and push:

```Bash
git commit -m "Resolve conflict and apply stash"
git push
```
