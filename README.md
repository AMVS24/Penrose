# Penrose

## Instructions

Make sure there is a C/C++ compiler like GCC installed.

Make sure CMake is installed

Add vcpkg at some root directory and run:
```git clone https://github.com/microsoft/vcpkg.git```

Then run the following:
```
cd vcpkg
# On Windows:
bootstrap-vcpkg.bat
# On Linux/macOS:
./bootstrap-vcpkg.sh
```

Remember the path to vcpkg

**To build and run the project**

### 1. Generate the build files inside a "build" directory
```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[PATH_TO_VCPKG]/scripts/buildsystems/vcpkg.cmake
```

### 2. Compile the code

```
cmake --build build --config Debug
```

Then the build is the build/Debug/Penrose.exe file. Run it from the Debug folder itself.

### Pipeline link:
https://mermaid.ai/live/edit#pako:eNqVVm1P4zgQ_itW0J6KtnBpXlqa45DYljcd7FYtvQ9HOeQmTuvDiSPbKRSW_37j2Cltl95pKyFlnJlnnpnxM-HViXlCnMiZCVzM0W1_kiP4ffqERmrJaD4zdsywlH2SooIWBI4JSilj0Z6X-IHfbkol-COJ9jrBtJum1jx4oomaR17x3Iw54yLaS9P0ty28hChMmbRwbb9NOt4KLk0Jxp2fgQPXMlbyY3ak1XHD8GfgZkVpodzuUUD8FZTrxiTu_g_UWisNq8Y4j3mek1iRBH3hz_vGQ5ZT0_0-Vtj4loJIdDdx9Al6P5o49yZE_0YtcDienpjXEbrBShGBGr3Pn_ePf52eHE_FyYLEASq4XD0vCNPPKeNYoQzK1Jb5WwEN8RI1Lq5H1_8JA1yiKLINN6xInqxVPZhjSVArQlc5VRQz-oIV5flWzZVXS9e6w9_iNHqD8f5G_YPW3UiRoo5APZwRgTWp1SU9ODhBA8-4edZtgIWiMSNy3XM3fwiDzGAsJY3lR-S9d_Kbzuia8wI1BjCUcwHktuh7hl5g6AXQ9z8CoKgIYOvCf-RXhQU67HsPM1BN8IwKQJcA8B0NfIPkAwnMYtSbCyoVBxEx9As6jWPCdkD66OAQMIcELlkujSvgBbu7AjkuoNAhvCNitSU2--K_92XbHQ3qCe3sTmC6E5qawgjmJiUa5zTlIpNQUDVMuKrVHEGoa7GhiW2b2LZNjpcZFvFcp9eD2QjbrLFvlxLOE3Re5rGeBqh3SGdzhUY0IdvCPdW4ilQirYOh-PXjGnSjyr6VcJ0k0oJDsSBYkYe4us8PGVaCxkQ29q1Me6A4kIfxvSA5OCmC_qTkqYkGgv9DKqgmNGhBBDS_Bjg0irUbd42E9xEJakUoyUNRK2ZF4XTN8ZQxHmsGUiVRBNtBcXFsdtEJwkLg5a7EaxR8Q-HufHw7Hp7BLhtf317dXg7PTvtXXy_u6z20lboWC4EVWfWgSo5G6Hd0B9uqqdfU_aEOvCmlQjHPihLc1oUhl9mU61ErRKBdy0qEGU0KTnO1TXyNcGB37xzDjV5dS0PLLCK9j6u-N1crB-6JbscHlfS4HpaCz-szkFIc-X2UUGFGWQcA4Nz2vCjYEn0tGdORsIMxsNVhkrMFfJuhCYu_1c6Bh4a8XvFae7OMQLQpJdrR6mGZV61heqWVUouoCk_KglE9_kTfs3lN9ZaIjOb4Pf4SxHq20HkuuaAvsNYbfYGf0BeG48d99G2IzmSMC2KPR4_LKXwfP6pgU6o3uCg0mZ75rmqhmneDVrXUQGLW9qztWTuwtm_t0Np26w3a1g6R04T_jmjiRPCtI00HhpthbTqv2nXiqDnJyMSJ4DHB4nHiTPI3iClw_hfnWR0meDmbO1GKmQSrLBJoWp9iuL_Z6lRUC7LHy1w5UdjxKxAnenWeneig2z70giPPbR2FrdDvePB2Ccde6zBww3b7qOv6nY7nhv5b03mpEns6wD3qgrPrtt2wG779Cwm6JS0
