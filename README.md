# Blazingly fast project searcher.

`pf` is a program to find directories in your filesystem.

## How to use
```bash
pf path1 path2 ...
```
This will search for directories in the given paths that match the `PROJECT_FINDER_MATCHES` env variable.

## Change default behavior
You can define your own matches with the `PROJECT_FINDER_MATCHES` env variable.
You can define your own ignores with the `PROJECT_FINDER_IGNORES` env variable.

Defaults are:
```bash
PROJECT_FINDER_MATCHES=.git,pom.xml,package.json,Makefile,build.zig,composer.json,Cargo.toml
PROJECT_FINDER_IGNORES=.,..,node_modules,.git,target,build,vendor,.metadata,.idea,.plugins
```
