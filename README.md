# at24_poc
The `at24_poc` application is designed to test the AT24 EEPROM on the 
TI J784S4X EVM board. 
This repository provides the necessary bits to add a package to Buildroot 
that tests this component.

## Overview
The purpose of this POC is to verify the functionality of the AT24 EEPROM 
on the TI J784S4X EVM board. The test conducted shows that the EEPROM on 
this board is read-only, and it is not clear what it is used for.

## Repository Contents
* **Buildroot Package Files**: These files can be applied as a patch to a 
  clean Buildroot tree to add the `at24_poc` package.
* **Binaries**: Sample binaries produced during the testing.
* **Test Sample**: An example of the test conducted on the board.

## How to Use
Applying the Patch
To build the Buildroot root filesystem with the at24_poc package, apply 
the patch to a clean Buildroot tree:
```
# quilt import br_package.patch
# quilt pushh
```
Alternatively, you can browse the files in the patch directly in the `at24_poc`
directory.

## Building the Image
Choose a kernel that supports the TI J784S4EVM board.
Build the kernel, including the filesystem created by Buildroot, using the 
kernel config option:

```
CONFIG_INITRAMFS_SOURCE="../buildroot-2024.02.1/output/images/rootfs.cpio"
```
Ensure the device tree includes the EEPROM component.

## Testing Results
The EEPROM on the TI J784S4EVM board appears to be read-only. 
The specific use of this EEPROM is unclear.
```
# at24_poc read at24 256
Data read: aa 55 33 ee 01 0b 01 10 2e 00 4a 37 38 34 53 34 58 2d 45 56 4d 00 
  00 00 00 00 45 34 30 31 34 31 30 31 45 34 41 00 30 31 30 31 33 30 32 33 00
  00 00 00 00 00 30 31 33 38 11 02 00 60 c5 11 02 00 61 c5 11 02 00 62 c5 11
  02 00 63 c5 13 c2 00 00 00 70 ff 76 1e c1 ab 00 00 00 00 00 00 00 00 00 00
  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  00 00 00 00 00 00 00 00 00 
# at24_poc write at24 pippo
Error: could not write data to device
# 
```
