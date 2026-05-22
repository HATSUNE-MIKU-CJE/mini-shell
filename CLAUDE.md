# Mini-Shell — 命令行解释器

Phase 1 核心项目，把 fork/exec/pipe/dup2/signal 整合成一个能交互的 Shell。

## 前置依赖

学习轨迹、用户画像、交互风格见 linux-learn 的记忆文件：

- /home/miku/.claude/CLAUDE.md（用户画像 + 严格姐姐风格）
- /home/miku/.claude/projects/-home-miku-linux-learn/memory/teaching-plan.md（教学计划）
- /home/miku/.claude/projects/-home-miku-linux-learn/memory/project-portfolio.md（项目功能说明）

## 项目定位

- 600-1000 行 C，5 个源文件
- REPL 循环 + 管道 + 重定向 + 信号处理

## 功能要求

- 管道 `|`（多级）
- 重定向 `<` `>` `>>`
- 后台运行 `&`
- Ctrl+C 杀前台不杀 shell
- 内置命令：cd、exit、pwd、export、history

## 技术栈

fork / execvp / pipe / dup2 / waitpid / sigaction / open / close / chdir / getcwd
