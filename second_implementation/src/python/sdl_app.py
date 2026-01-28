#!/usr/bin/env python3
"""
Second Python SDL Application using pygame as SDL is primarily a C library
"""

import pygame
import sys
import math

def main():
    # Initialize Pygame (acts as SDL for Python)
    pygame.init()
    
    # Screen dimensions
    SCREEN_WIDTH = 800
    SCREEN_HEIGHT = 600
    
    # Create window
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption("Second Python Implementation - Spiral")
    
    # Clock for controlling frame rate
    clock = pygame.time.Clock()
    
    print("Second Python SDL-like Application running...")
    print("Close the window to exit.")
    
    # Main loop
    running = True
    while running:
        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        # Fill screen with light blue color
        screen.fill((173, 216, 230))  # Light blue background
        
        # Draw a colorful spiral
        center_x, center_y = SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2
        max_radius = 150
        
        # Draw spiral
        points = []
        for i in range(0, 360 * 3, 5):  # 3 full rotations
            angle = math.radians(i)
            radius = max_radius * (1 - i/(360 * 3))
            x = center_x + radius * math.cos(angle)
            y = center_y + radius * math.sin(angle)
            points.append((int(x), int(y)))
        
        if len(points) >= 2:
            for i in range(len(points)-1):
                # Calculate color based on position
                color_val = (i * 10) % 255
                color = (color_val, 255 - color_val, min(255, i % 255))
                pygame.draw.line(screen, color, points[i], points[i+1], 2)
        
        # Update display
        pygame.display.flip()
        
        # Cap the frame rate
        clock.tick(60)
    
    # Quit
    pygame.quit()
    print("Second Python SDL-like Application exited.")
    sys.exit()

if __name__ == "__main__":
    main()