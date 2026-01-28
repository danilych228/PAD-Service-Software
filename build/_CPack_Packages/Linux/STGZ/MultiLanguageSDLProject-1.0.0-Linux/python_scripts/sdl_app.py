#!/usr/bin/env python3
"""
Python SDL Application using pygame as SDL is primarily a C library
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
    pygame.display.set_caption("Python SDL-like Application")
    
    # Clock for controlling frame rate
    clock = pygame.time.Clock()
    
    print("Python SDL-like Application running...")
    print("Close the window to exit.")
    
    # Main loop
    running = True
    while running:
        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        # Fill screen with orange color
        screen.fill((255, 165, 0))  # Orange background
        
        # Draw a blue star
        center_x, center_y = SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2
        size = 80
        
        # Draw star points
        for angle in range(0, 360, 15):  # Every 15 degrees
            rad = math.radians(angle)
            x = center_x + size * math.cos(rad)
            y = center_y + size * math.sin(rad)
            pygame.draw.circle(screen, (0, 0, 255), (int(x), int(y)), 5)  # Blue points
        
        # Draw connecting lines for star
        points = []
        for angle in range(0, 360, 72):  # Pentagram angles
            rad = math.radians(angle)
            x = center_x + size * math.cos(rad)
            y = center_y + size * math.sin(rad)
            points.append((int(x), int(y)))
        
        if len(points) >= 2:
            pygame.draw.lines(screen, (0, 0, 255), True, points, 3)
        
        # Update display
        pygame.display.flip()
        
        # Cap the frame rate
        clock.tick(60)
    
    # Quit
    pygame.quit()
    print("Python SDL-like Application exited.")
    sys.exit()

if __name__ == "__main__":
    main()