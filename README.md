# Bolt ⚡
> A fast, simple C++ package manager that finds libraries on GitHub and automatically integrates them into your CMake or Meson project.

---

## What is Bolt?

Managing dependencies in C++ has always been painful. No standard package manager, manual CMake editing, and hours wasted on setup.

Bolt fixes that.

Just type `bolt add fmt` and Bolt:
- Searches GitHub for the library
- Downloads it into your project
- Automatically edits your CMakeLists.txt or meson.build
- Saves it to bolt.toml for future installs

---

## Installation

### Requirements
- CMake 3.15+
- Git
- libcurl
- nlohmann-json

### Arch Linux

sudo pacman -S cmake git curl nlohmann-json


### Ubuntu/Debian

sudo apt install cmake git libcurl4-openssl-dev nlohmann-json3-dev


### Build from source

git clone https://github.com/Cronobi/bolt

cd bolt

mkdir build && cd build

cmake ..

make

sudo cp Bolt /usr/local/bin/bolt



---

## Usage

### Add a package


bolt add fmt


Searches GitHub for fmt, shows results, lets you pick one, downloads and injects into your build file.

### Remove a package


bolt remove fmt


Deletes the package folder, removes from CMakeLists.txt and bolt.toml.

### Search for a package


bolt search json


Shows matching C++ libraries from GitHub without installing.

### Install all dependencies


bolt install


Reads bolt.toml and reinstalls all dependencies. Useful when cloning a project that uses Bolt.

### Help


bolt -h


---

## bolt.toml format


[dependencies]

fmt = "https://github.com/fmtlib/fmt.git"

nlohmann-json = "https://github.com/nlohmann/json.git"



---

## Roadmap

- [x] Search GitHub for C++ libraries
- [x] Download and install packages
- [x] Auto inject into CMakeLists.txt
- [x] Auto inject into meson.build
- [x] bolt.toml manifest
- [x] bolt install from manifest
- [x] bolt remove
- [ ] Dependency resolver
- [ ] Version tracking
- [ ] bolt update
- [ ] Private GitHub repo support

---

## Built with

- C++17
- libcurl — HTTP requests
- nlohmann/json — JSON parsing
- GitHub Search API

---

## Author

**Jayadev** — [@Cronobi](https://github.com/Cronobi)

---

## License

MIT License — free to use, modify, and distribute.
