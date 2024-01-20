<p align="center">
  <a href="" rel="noopener">
  <!-- For when I create a logo for AurixOS :p -->
 <!-- <img width=200px height=200px src="" alt="AurixOS logo"> -->
 </a>
</p>

<h3 align="center">AurixOS</h3>

<div align="center">

  [![Status](https://img.shields.io/badge/status-active-success.svg)]() 
  [![License](https://img.shields.io/github/license/schkwve/aurix)](/LICENSE)

</div>

---

<p align="center"> A small, lightweight Operating System
    <br> 
</p>

## Table of Contents
- [About](#about)
- [Building](#building)
- [Running](#running)
- [TODO](docs/TODO.md)
- [Contributing](docs/CONTRIBUTING.md)

## About <a name = "about"></a>

This project officially begun as [LuxeOS](https://github.com/luxeos/luxe-kernel-old), a kernel that I've initially started developing in July of 2023. Since then, LuxeOS has grown to be a bunch of messy, undocumented code that was specific to one architecture only.
AurixOS is a complete rewrite of that, aiming to be better in every way possible.

## Building <a name = "building"></a>

These instructions will show you how to set up your environment and build AurixOS.

### Prerequisites

Building AurixOS is only supported on UNIX-like systems.

Install the required packages before building AurixOS:

<details>
<summary>Package list</summary>

- `git`
- `make` (`gmake` on BSD systems)
- `dd`
- `mtools`
- `xorriso`
- `clang` (x86_64 builds only)
- `lld-link` (x86_64 builds only)
- `nasm` (x86_64 builds only)
- `ARCH-elf-gas`
- `ARCH-elf-gcc`
- `ARCH-elf-ld`

For `ARCH-elf-...` packages, replace `ARCH` with the target architecture.
</details>

### Building

To build the bootloader and kernel, run `make`.
The default build target is `x86_64/generic-pc`.

To specify a custom build target, you can specify the `ARCH` and `MACHINE` variables when invoking `make`:
```bash
ARCH=armv8 MACHINE=rpi4 make
```

All files are outputted into the `build/` directory. Files in `build/output` are final build files ready to be shipped into the final image.

### Generating bootable images

Currently, AurixOS supports creating 3 types of media: CD images, Hard Drive images, and SD Card images.

To create a full release (creates all available media) run `make full_release`.
Make targets `release_iso`, `release_hdd` and `release_sdcard` are available as well.

All bootable media are placed under the `release/` directory, where every file is named as follows:
```
aurixos-media-hash_arch_machine.XXX
```
For example, an SD Card image for armv8 (with Raspberry Pi 4 target) and the latest commit hash `fb89c2f153` would be named:
```
aurixos-sdcard-fb89c2f153_armv8_rpi4.iso
```

Please note that if you've built AurixOS with custom `ARCH` and/or `MACHINE` variables, you need to specify them as well when generating these images.

## Running <a name="running"></a>

To easily run AurixOS in a virtual machine, run `make run` (or `make rundbg` to start QEMU with a GDB server).

Running on real hardware can be more tricky, so whenever you encounter an error or a bug, feel free to open an issue on Codeberg.

## Contributing <a name="contributing"></a>

#### NOTE: Pull Requests opened on GitHub will not be accepted! Please use [Codeberg](https://codeberg.org/schkwve/aurix) to submit issues and Pull Requests.

Please see [CONTRIBUTING.md](docs/CONTRIBUTING.md) for instructions on how to contribute to the AurixOS project.

## License <a name="license"></a>

AurixOS is distributed under the [CC BY-NC-SA 4.0](LICENSE) license. For additional details, please refer to the [Creative Commons Deed](https://creativecommons.org/licenses/by-nc-sa/4.0/).
