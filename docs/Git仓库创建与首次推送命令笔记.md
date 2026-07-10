# Git 仓库创建与首次推送命令笔记

> 项目：SmartEdge-Gateway  
> 环境：Windows + Git Bash  
> 远程平台：GitHub  
> 默认分支：`main`

---

## 1. Git 基本工作流程

Git 的常见工作流程如下：

```text
修改文件
  ↓
git status
  ↓
git add
  ↓
git commit
  ↓
git push
```

各阶段含义：

| 阶段   | 含义                       |
| ---- | ------------------------ |
| 工作区  | 当前正在编辑的文件                |
| 暂存区  | 已通过 `git add` 选中、准备提交的文件 |
| 本地仓库 | 已通过 `git commit` 保存的版本   |
| 远程仓库 | GitHub 上的仓库              |

---

# 2. Git 环境检查

## 2.1 查看 Git 版本

```bash
git --version
```

作用：

- 检查 Git 是否安装成功
- 查看当前 Git 版本

正常示例：

```text
git version 2.x.x
```

---

## 2.2 配置用户名和邮箱

```bash
git config --global user.name "你的GitHub用户名"
git config --global user.email "你的GitHub邮箱"
```

例如：

```bash
git config --global user.name "WhatRemainsX"
git config --global user.email "your_email@example.com"
```

作用：

- 设置 Git 提交记录中的作者姓名
- 设置 Git 提交记录中的作者邮箱
- `--global` 表示对当前电脑上的所有仓库生效

查看配置：

```bash
git config --global --list
```

只查看用户名：

```bash
git config --global user.name
```

只查看邮箱：

```bash
git config --global user.email
```

------

#---

假设项目放在：

```text
E:\WorkProject
```

在 Git Bash 中，Windows 盘符写法为：

```bash
/e/WorkProject
```

进入目录：

```bash
cd /e/WorkProject
```

查看当前位置：

```bash
pwd
```

查看目录内容：

```bash
ls
```

显示隐藏文件：

```bash
ls -la
```

---

# 3. 初始化 Git 仓库

```bash
git init
```

作用：

- 将当前文件夹初始化为 Git 仓库
- 创建隐藏目录 `.git`
- `.git` 中保存提交记录、分支、远程地址等信息

执行后通常会看到：

```text
Initialized empty Git repository in ...
```

---

## 3.1 将默认分支改为 main

```bash
git branch -M main
```

作用：

- 将当前分支重命名为 `main`
- `-M` 表示强制重命名

查看当前分支：

```bash
git branch
```

输出中的 `*` 表示当前分支：

```text
* main
```

---

# 4. 创建项目目录结构

Git Bash 中创建目录：

```bash
mkdir -p common/include
mkdir -p common/src
mkdir -p tests
mkdir -p docs
mkdir -p mcu_firmware
mkdir -p linux_daemon
```

作用：

- `mkdir`：创建目录
- `-p`：自动创建不存在的父目录，并避免目录已存在时报错

创建文件：

```bash
touch README.md
touch .gitignore
touch docs/bug_records.md
```

作用：

- `touch`：创建空文件
- 如果文件已经存在，则更新文件时间戳，不会清空文件内容

---

## 5.1 为什么需要 `.gitkeep`

Git 默认不会记录空目录。

可以在空目录中放入 `.gitkeep`：

```bash
touch common/include/.gitkeep
touch common/src/.gitkeep
touch tests/.gitkeep
touch mcu_firmware/.gitkeep
touch linux_daemon/.gitkeep
```

说明：

- `.gitkeep` 不是 Git 官方关键字
- 它只是一个约定俗成的占位文件
- 作用是让 Git 能够记录当前为空的目录

---

# 5. 查看仓库状态

```bash
git status
```

作用：

- 查看当前分支
- 查看哪些文件被修改
- 查看哪些文件未被跟踪
- 查看哪些文件已加入暂存区
- 查看本地分支和远程分支是否同步

常见状态：

## 5.1 未跟踪文件

```text
Untracked files
```

表示：

- 文件已经存在于项目中
- Git 还没有开始跟踪它

## 5.2 已加入暂存区

```text
Changes to be committed
```

表示：

- 文件已经执行过 `git add`
- 等待执行 `git commit`

## 5.3 工作区干净

```text
nothing to commit, working tree clean
```

表示：

- 当前没有未提交的修改
- 工作区与最近一次提交一致

---

# 6. 将文件加入暂存区

## 6.1 添加全部文件

```bash
git add .
```

作用：

- 将当前目录及子目录中的修改加入暂存区
- 包括新增、修改和删除的文件

注意：

```bash
git add .
```

只会加入暂存区，并不会生成版本记录。

---

## 6.2 添加单个文件

```bash
git add README.md
```

添加指定目录：

```bash
git add common/
```

适用场景：

- 只想提交一部分修改
- 避免把无关修改放进同一次提交

---

# 7. 提交本地版本

```bash
git commit -m "feat: initialize SmartEdge-Gateway project"
```

作用：

- 将暂存区内容保存到本地仓库
- 生成一次可追踪的版本记录
- `-m` 后面是提交说明

第一次提交示例：

```bash
git add .
git commit -m "feat: initialize SmartEdge-Gateway project"
```

---

## 7.1 常用提交前缀

| 前缀         | 含义     | 示例                                      |
| ---------- | ------ | --------------------------------------- |
| `feat`     | 新增功能   | `feat: add CRC16 module`                |
| `fix`      | 修复问题   | `fix: correct frame length calculation` |
| `docs`     | 修改文档   | `docs: update build instructions`       |
| `test`     | 添加测试   | `test: add ring buffer tests`           |
| `refactor` | 重构代码   | `refactor: simplify protocol parser`    |
| `build`    | 修改构建配置 | `build: add CMake configuration`        |
| `chore`    | 杂项维护   | `chore: update gitignore`               |

---

# 8. 查看提交记录

## 8.1 简洁查看

```bash
git log --oneline
```

作用：

- 每次提交显示一行
- 显示提交哈希和提交说明

示例：

```text
a3c82f1 feat: initialize SmartEdge-Gateway project
```

---

## 8.2 查看最近 5 次提交

```bash
git log --oneline -5
```

---

## 8.3 查看详细记录

```bash
git log
```

可以看到：

- 完整提交哈希
- 作者
- 邮箱
- 提交时间
- 提交说明

---

# 9. 在 GitHub 创建远程仓库

GitHub 网站操作：

1. 登录 GitHub
2. 点击右上角 `+`
3. 选择 `New repository`
4. 仓库名填写：

```text
SmartEdge-Gateway
```

5. 建议不要勾选自动生成 README
6. 不要重复创建 `.gitignore`
7. 点击 `Create repository`

原因：

- 本地已经创建 README 和 `.gitignore`
- GitHub 再创建一份可能造成首次推送冲突

---

# 10. 配置远程仓库

## 10.1 添加远程仓库

```bash
git remote add origin https://github.com/WhatRemainsX/SmartEdge-Gateway.git
```

作用：

- 给远程仓库地址设置一个别名
- `origin` 是默认使用的远程仓库名称
- 后续不必每次输入完整 URL

---

## 10.2 查看远程仓库地址

```bash
git remote -v
```

正常示例：

```text
origin  https://github.com/WhatRemainsX/SmartEdge-Gateway.git (fetch)
origin  https://github.com/WhatRemainsX/SmartEdge-Gateway.git (push)
```

其中：

- `fetch`：从远程下载
- `push`：向远程上传

---

## 10.3 修改远程仓库地址

```bash
git remote set-url origin https://github.com/WhatRemainsX/SmartEdge-Gateway.git
```

作用：

- 修改已经存在的 `origin` 地址
- 适合远程地址填写错误时使用

---

## 10.4 删除远程仓库配置

```bash
git remote remove origin
```

作用：

- 删除名为 `origin` 的远程地址
- 不会删除 GitHub 上的仓库

---

# 11. 首次推送到 GitHub

```bash
git push -u origin main
```

也可以写成：

```bash
git push --set-upstream origin main
```

作用：

- 将本地 `main` 分支推送到远程 `origin`
- 在 GitHub 创建远程 `main` 分支
- `-u` 将本地 `main` 与远程 `origin/main` 建立跟踪关系

成功后通常出现：

```text
branch 'main' set up to track 'origin/main'
```

以后再推送只需要：

```bash
git push
```

---

# 12. 为什么第一次直接 `git push` 会失败

出现过的提示：

```text
fatal: The current branch main has no upstream branch.
```

原因：

- 本地分支为 `main`
- 但 Git 还不知道应该推送到哪个远程分支
- 本地 `main` 尚未关联 `origin/main`

解决命令：

```bash
git push -u origin main
```

建立关联后，后续可直接：

```bash
git push
```

---

# 

# 16. GitHub 身份验证失败

出现过的错误：

```text
remote: Invalid username or token.
Password authentication is not supported for Git operations.
fatal: Authentication failed
```

含义：

- 网络连接已经成功
- GitHub 已收到认证请求
- 但用户名、缓存凭据或 Token 不正确
- GitHub 不支持使用账号密码进行 Git HTTPS 推送

---

## 16.1 清除旧凭据

Git Bash：

```bash
printf "protocol=https\nhost=github.com\n\n" | git credential reject
```

Windows 中也可以打开：

```text
控制面板
→ 用户账户
→ 凭据管理器
→ Windows 凭据
```

删除类似：

```text
git:https://github.com
github.com
```

然后重新推送：

```bash
git push -u origin main
```

Git Credential Manager 通常会弹出浏览器，要求登录 GitHub 并授权。

---

## 16.2 Personal Access Token

如果终端要求输入：

```text
Username for 'https://github.com':
Password for 'https://...':
```

填写：

```text
Username：GitHub 用户名
Password：Personal Access Token
```

注意：

- Password 位置不能填写 GitHub 登录密码
- 必须填写 GitHub Personal Access Token
- 输入 Token 时终端通常不会显示字符，这是正常的
- 不要将 Token 写入 README、命令历史或远程 URL

---

# 17. 查看本地分支和远程跟踪关系

```bash
git branch -vv
```

作用：

- 查看当前本地分支
- 查看本地分支跟踪的远程分支
- 查看最近一次提交

正常示例：

```text
* main a3c82f1 [origin/main] feat: initialize SmartEdge-Gateway project
```

其中：

```text
[origin/main]
```

表示本地 `main` 已经跟踪远程 `origin/main`。

---

# 18. 查看代码修改

## 18.1 查看未暂存修改

```bash
git diff
```

作用：

- 查看工作区和暂存区之间的差异
- 即尚未执行 `git add` 的修改

---

## 18.2 查看已暂存修改

```bash
git diff --cached
```

作用：

- 查看暂存区和最近一次提交之间的差异
- 即下一次 `git commit` 将提交哪些内容

---

# 19. 日常开发时的标准流程

每完成一个独立功能，建议执行：

```bash
git status
git diff
git add .
git status
git commit -m "feat: add new feature"
git push
```

推荐流程说明：

1. `git status`：确认修改范围
2. `git diff`：检查具体代码变化
3. `git add .`：加入暂存区
4. 再次 `git status`：确认将提交哪些文件
5. `git commit`：保存本地版本
6. `git push`：上传 GitHub

---

# 20. 从 GitHub 获取代码

## 20.1 克隆仓库

在另一台电脑上首次下载：

```bash
git clone https://github.com/WhatRemainsX/SmartEdge-Gateway.git
```

作用：

- 下载完整项目
- 下载所有提交记录
- 自动配置远程仓库 `origin`

进入项目：

```bash
cd SmartEdge-Gateway
```

---

## 20.2 拉取远程更新

```bash
git pull
```

作用：

- 从远程获取最新提交
- 合并到当前本地分支

多台电脑开发时，建议开始工作前先执行：

```bash
git pull
```

---

# 21. 常用撤销命令

## 21.1 放弃未暂存修改

```bash
git restore README.md
```

作用：

- 将文件恢复到最近一次提交状态
- 当前未提交修改会丢失

谨慎使用。

---

## 21.2 取消暂存

```bash
git restore --staged README.md
```

作用：

- 将文件从暂存区移回工作区
- 文件修改仍然保留

---

## 21.3 修改最近一次提交信息

```bash
git commit --amend -m "新的提交说明"
```

作用：

- 修改最近一次提交
- 适合提交说明写错的情况

如果提交已经推送到远程，初学阶段不要随意强制推送。

---

# 22. `.gitignore` 的作用

`.gitignore` 用来告诉 Git 哪些文件不应被跟踪。

示例：

```gitignore
# 编译文件
*.o
*.a
*.so
*.exe
*.out

# 构建目录
build/
cmake-build-*/
Debug/
Release/

# 编辑器配置
.vscode/
.idea/
*.swp

# 系统文件
.DS_Store
Thumbs.db

# STM32 / Keil 中间文件
Objects/
Listings/
*.uvguix.*
*.dep
*.d
*.crf
*.axf
*.hex
*.bin
*.map

# 日志文件
*.log
```

注意：

- `.gitignore` 只对尚未被 Git 跟踪的文件生效
- 已经提交过的文件，后来写入 `.gitignore` 后不会自动消失

---

# 23. 本次实际使用过的核心命令汇总

```bash
git --version
```

检查 Git 是否安装。

```bash
git config --global user.name "WhatRemainsX"
git config --global user.email "your_email@example.com"
```

配置提交者信息。

```bash
cd /e/WorkProject
```

进入项目目录。

```bash
git init
```

初始化本地仓库。

```bash
git branch -M main
```

将当前分支命名为 `main`。

```bash
git status
```

查看工作区、暂存区和分支状态。

```bash
git add .
```

将当前修改加入暂存区。

```bash
git commit -m "feat: initialize SmartEdge-Gateway project"
```

创建本地提交。

```bash
git log --oneline
```

查看提交历史。

```bash
git remote add origin https://github.com/WhatRemainsX/SmartEdge-Gateway.git
```

添加 GitHub 远程仓库。

```bash
git remote -v
```

查看远程仓库地址。

```bash
git remote set-url origin https://github.com/WhatRemainsX/SmartEdge-Gateway.git
```

修改远程仓库地址。

```bash
git push -u origin main
```

首次推送并建立上游跟踪关系。

```bash
git push
```

后续正常推送。

```bash
git branch -vv
```

查看本地分支与远程分支的跟踪关系。

---

# 24. 当前仓库验收命令

执行：

```bash
git status
git branch -vv
git remote -v
git log --oneline -5
```

理想结果应满足：

```text
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

并且：

```bash
git branch -vv
```

能够看到：

```text
[origin/main]
```

这说明：

- 本地仓库创建成功
- 本地提交创建成功
- 远程仓库配置成功
- 本地 `main` 已关联远程 `origin/main`
- 代码已经成功上传 GitHub

---

# 25. 第一周后续建议提交

后续每完成一个模块，单独提交：

```bash
git commit -m "feat: add CRC16 calculation module"
```

```bash
git commit -m "feat: add ring buffer implementation"
```

```bash
git commit -m "feat: add protocol encode and decode module"
```

```bash
git commit -m "test: add common module tests"
```

```bash
git commit -m "docs: update build and test instructions"
```

不要把一周所有代码集中到最后一次提交。

---

# 26. 最重要的 Git 使用原则

1. 一个提交只解决一个相对独立的问题。
2. 提交前先运行 `git status` 和 `git diff`。
3. 提交说明要说明做了什么，不写“修改”“更新”“123”。
4. Token、密码、密钥和私人配置不能提交。
5. 编译产物和临时文件应写入 `.gitignore`。
6. 推送前确认当前分支和远程地址。
7. 多台电脑开发时，开始工作前先执行 `git pull`。
8. 每完成一个可运行的小功能，就进行一次提交。
