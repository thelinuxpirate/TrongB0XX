# TrongB0XX Nix Flake
{
  description = "Nix Flake packaging the TrongB0XX firmware";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: let
    pkgs = import nixpkgs {
      inherit system;
    };
  in {
    nixosModules.haybox = { config, pkgs, ... }: {
      services.udev.packages = with pkgs; [
        platformio-core.udev
      ];
    };

    devShells.default = pkgs.mkShell rec {
      name = "haybox";

      packages = with pkgs; [
        # Build Tools
        platformio-core
        pico-sdk
        avrdude
        openocd
        # Build Dependencies
        gcc-arm-embedded
        udev
      ];
    };

    packages.buildBox = pkgs.buildFHSUserEnv {
      name = "gcc-arm-env";
      targetPkgs = pkgs: [
        pkgs.platformio-core
        pkgs.pico-sdk
        pkgs.avrdude
        pkgs.openocd
        pkgs.gcc-arm-embedded
        pkgs.udev
      ];
    };
  });
}
