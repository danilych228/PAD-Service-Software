#!/usr/bin/env python3
"""
Composite application demonstrating the multi-language SDL project
This script orchestrates the different language implementations
"""

import subprocess
import sys
import os
import threading
import time


def run_c_app():
    """Run the C SDL application"""
    try:
        print("Starting C SDL Application...")
        subprocess.run(["./build/src/c/c_sdl_app"], check=True)
    except subprocess.CalledProcessError as e:
        print(f"C application failed: {e}")
    except FileNotFoundError:
        print("C application not found. Make sure to build the project first.")


def run_cpp_app():
    """Run the C++ SDL application"""
    try:
        print("Starting C++ SDL Application...")
        subprocess.run(["./build/src/cpp/cpp_sdl_app"], check=True)
    except subprocess.CalledProcessError as e:
        print(f"C++ application failed: {e}")
    except FileNotFoundError:
        print("C++ application not found. Make sure to build the project first.")


def run_asm_app():
    """Run the Assembly SDL application"""
    try:
        print("Starting Assembly SDL Application...")
        subprocess.run(["./build/src/asm/asm_sdl_app"], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Assembly application failed: {e}")
    except FileNotFoundError:
        print("Assembly application not found. Make sure to build the project first.")


def run_python_app():
    """Run the Python SDL application"""
    try:
        print("Starting Python SDL Application...")
        subprocess.run(["python3", "./src/python/sdl_app.py"], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Python application failed: {e}")
    except FileNotFoundError:
        print("Python application not found.")


def main():
    print("Multi-Language SDL Project - Composite Application")
    print("=" * 50)
    print("This script demonstrates the applications built in different languages:")
    print("- C: Blue background with red rectangle")
    print("- C++: Green background with yellow circle")
    print("- Assembly: Purple background with white triangle")
    print("- Python: Orange background with blue star")
    print("=" * 50)
    
    # Check if build exists
    if not os.path.exists("./build"):
        print("Build directory not found. Attempting to build project...")
        try:
            subprocess.run(["./build_package.sh"], check=True)
        except subprocess.CalledProcessError:
            print("Build failed. Please run './build_package.sh' manually.")
            sys.exit(1)
    
    # Check if executables exist
    apps = {
        "C": "./build/src/c/c_sdl_app",
        "C++": "./build/src/cpp/cpp_sdl_app", 
        "Assembly": "./build/src/asm/asm_sdl_app"
    }
    
    missing_apps = []
    for lang, path in apps.items():
        if not os.path.exists(path):
            missing_apps.append(lang)
    
    if missing_apps:
        print(f"Missing applications: {', '.join(missing_apps)}")
        print("Please run './build_package.sh' to build the project.")
        sys.exit(1)
    
    print("\nAll applications built successfully!")
    print("\nOptions:")
    print("1. Run all applications sequentially")
    print("2. Run specific application")
    print("3. Show project information")
    
    choice = input("\nEnter your choice (1/2/3): ").strip()
    
    if choice == "1":
        print("\nRunning all applications sequentially...")
        print("(Close each window to proceed to the next application)")
        
        print("\n1. Running C application...")
        run_c_app()
        
        print("\n2. Running C++ application...")
        run_cpp_app()
        
        print("\n3. Running Assembly application...")
        run_asm_app()
        
        print("\n4. Running Python application...")
        run_python_app()
        
        print("\nAll applications completed.")
        
    elif choice == "2":
        print("\nSelect application to run:")
        print("c - C application")
        print("cpp - C++ application") 
        print("asm - Assembly application")
        print("py - Python application")
        
        app_choice = input("Enter choice (c/cpp/asm/py): ").strip().lower()
        
        if app_choice == "c":
            run_c_app()
        elif app_choice == "cpp":
            run_cpp_app()
        elif app_choice == "asm":
            run_asm_app()
        elif app_choice == "py":
            run_python_app()
        else:
            print("Invalid choice.")
            
    elif choice == "3":
        print("\nProject Information:")
        print("- Project: Multi-Language SDL Project")
        print("- Purpose: Demonstrate same application in multiple languages")
        print("- Languages: C, C++, Assembly (with C helpers), Python")
        print("- Graphics: SDL2 (or pygame for Python)")
        print("- Build system: CMake")
        print("- Packaging: Supports .deb, .tar.gz, and self-extracting .sh")
        print("- Source structure:")
        print("  - src/c/: C implementation")
        print("  - src/cpp/: C++ implementation") 
        print("  - src/asm/: Assembly implementation with C helpers")
        print("  - src/python/: Python implementation using pygame")
        
    else:
        print("Invalid choice.")


if __name__ == "__main__":
    main()