#!/usr/bin/env python3

"""
Composite application that demonstrates all implementations
"""

import os
import sys
import subprocess
import threading
import time
import signal

def run_python_impl():
    """Run the Python implementation"""
    python_file = "/workspace/third_implementation/src/python/main.py"
    subprocess.run(["python3", python_file])

def run_c_impl():
    """Run the C implementation"""
    c_executable = "/workspace/third_implementation/build_test/c_third_app"
    if os.path.exists(c_executable):
        subprocess.run([c_executable])
    else:
        print(f"C executable not found: {c_executable}")

def run_cpp_impl():
    """Run the C++ implementation"""
    cpp_executable = "/workspace/third_implementation/build_test/cpp_third_app"
    if os.path.exists(cpp_executable):
        subprocess.run([cpp_executable])
    else:
        print(f"C++ executable not found: {cpp_executable}")

def run_asm_impl():
    """Run the Assembly implementation"""
    asm_executable = "/workspace/third_implementation/build_test/asm_third_app"
    if os.path.exists(asm_executable):
        subprocess.run([asm_executable])
    else:
        print(f"Assembly executable not found: {asm_executable}")

def main():
    print("Multi-Language SDL Project - Third Implementation")
    print("="*50)
    print("Available implementations:")
    print("1. C - Cyan background with magenta rectangle")
    print("2. C++ - Lime green background with orange circle")
    print("3. Python - Pink background with blue star")
    print("4. Assembly - Yellow background with red diamond")
    print("5. All - Run all implementations simultaneously")
    print("6. Exit")
    print()

    while True:
        try:
            choice = input("Select an option (1-6): ").strip()
            
            if choice == "1":
                print("Running C implementation...")
                run_c_impl()
                
            elif choice == "2":
                print("Running C++ implementation...")
                run_cpp_impl()
                
            elif choice == "3":
                print("Running Python implementation...")
                run_python_impl()
                
            elif choice == "4":
                print("Running Assembly implementation...")
                run_asm_impl()
                
            elif choice == "5":
                print("Running all implementations simultaneously...")
                threads = []
                
                # Start all implementations in separate threads
                t1 = threading.Thread(target=run_c_impl)
                t2 = threading.Thread(target=run_cpp_impl)
                t3 = threading.Thread(target=run_python_impl)
                t4 = threading.Thread(target=run_asm_impl)
                
                threads.extend([t1, t2, t3, t4])
                
                for t in threads:
                    t.start()
                
                # Wait for all threads to finish
                for t in threads:
                    t.join()
                    
            elif choice == "6":
                print("Exiting...")
                break
                
            else:
                print("Invalid choice. Please select 1-6.")
                
        except KeyboardInterrupt:
            print("\nExiting...")
            break

if __name__ == "__main__":
    main()