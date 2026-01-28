import pygame
import sys
import math

# Initialize Pygame
pygame.init()

# Screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Set up the display
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Third Implementation - Python')

# Colors
PINK = (255, 192, 203)  # Pink background
BLUE = (0, 0, 255)      # Blue star color

# Main loop
running = True
clock = pygame.time.Clock()

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    # Fill the screen with pink color
    screen.fill(PINK)
    
    # Draw a blue star
    center_x, center_y = SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2
    radius = 80
    points = []
    num_points = 5  # For a 5-pointed star
    
    for i in range(num_points * 2):
        angle = math.pi / num_points * i - math.pi / 2
        if i % 2 == 0:
            # Outer points
            x = center_x + int(math.cos(angle) * radius)
            y = center_y + int(math.sin(angle) * radius)
        else:
            # Inner points
            x = center_x + int(math.cos(angle) * radius / 2)
            y = center_y + int(math.sin(angle) * radius / 2)
        points.append((x, y))
    
    pygame.draw.polygon(screen, BLUE, points)
    
    # Update the display
    pygame.display.flip()
    clock.tick(60)

# Quit
pygame.quit()
sys.exit()