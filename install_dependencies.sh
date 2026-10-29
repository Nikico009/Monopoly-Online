#!/bin/bash

# =========================================================================
# PACKAGE LIST
# Add or remove packages here easily.
# Works for both official repositories and AUR packages (managed by yay).
# =========================================================================
PACKAGES=(
    "raylib"
)

echo "=== Checking system dependencies ==="

# Ensure yay is installed before proceeding
if ! command -v yay &> /dev/null; then
    echo "[X] Error: 'yay' is not installed on the system."
    echo "Please install it first or modify the script to use pacman directly."
    exit 1
fi

# Loop through the package list
for pkg in "${PACKAGES[@]}"; do
    # pacman -Q checks if the package is installed locally
    if pacman -Q "$pkg" &>/dev/null; then
        echo "[OK] '$pkg' is already installed."
    else
        echo "[INFO] '$pkg' is not installed. Installing..."
        
        # -S: install, --needed: avoids reinstalling if up-to-date, --noconfirm: skips prompts
        yay -S --needed --noconfirm "$pkg"
        
        if [ $? -eq 0 ]; then
            echo "[SUCCESS] '$pkg' installed successfully."
        else
            echo "[ERROR] Failed to install '$pkg'."
        fi
    fi
    echo "---------------------------------------------------"
done

echo "Dependency check and installation complete!"