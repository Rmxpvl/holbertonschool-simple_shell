# Changelog

All notable changes to the Simple Shell project will be documented in this file.

## [v1.0] - 2026-04-22 (Task 6)
### Added
- Added `env` built-in correctly according to Task 6 Simple Shell 1.0 requirements.

## [v0.4] - 2026-04-21 (Task 5)
### Added
- Implemented the `exit` built-in, that exits the shell without relying on parameters.

## [v0.3] - (Task 4)
### Added
- Handling of the `PATH` environment variable using a custom `_getenv` function.
- The `fork` function is no longer called if the command cannot be found in the current directory or the `PATH`.
- Implementation of the `env` built-in command which prints the current environment.

## [v0.2] - (Task 2)
### Changed
- Upgraded the command parser to handle command lines with arguments (using `strtok`).
- Now executes commands successfully by parsing `args[512]`.

## [v0.1] - (Task 1)
### Added
- Basic interactive Simple shell (`($)` prompt) using `getline`.
- Ability to run commands using their absolute path (`/bin/ls`).
- Proper error handling and exact error messages mapping `sh`.
