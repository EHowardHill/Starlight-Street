from PIL import Image, ImageDraw, ImageFont
import json

# List of characters
chars = list('ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,."!?')

# Font settings
font_path = 'Luna.ttf'  # Update this path to where your Luna font file is located
font_size = 20
font = ImageFont.truetype(font_path, font_size)

# Initialize variables
char_metrics = {}
grid_width = 32
grid_height = 32

# Store individual character images and total image height
char_images = []
total_image_height = 0

# Draw each character
for char in chars:
    # Measure text bounding box
    bbox = font.getbbox(char)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    char_width = text_width

    # Calculate vertical offset (the amount the character extends below the grid slot)
    # If the character extends below the bottom of the grid slot, vertical_offset will be positive
    vertical_extension = max(0, bbox[3] - grid_height)

    # Store character metrics
    char_metrics[char] = {
        'width': char_width,
        'v_offset': vertical_extension
    }

    # Create an image tall enough to include the full character, including any descender
    char_image_height = grid_height + vertical_extension
    char_image = Image.new('RGBA', (grid_width, char_image_height), (0, 0, 0, 0))
    draw = ImageDraw.Draw(char_image)

    # Position the character flat with the bottom of the 32x32 grid slot
    x = (grid_width - text_width) // 2 - bbox[0]
    y = grid_height - text_height - bbox[1]

    # Draw the character
    draw.text((x, y), char, font=font, fill=(255, 255, 255, 255))

    # Add the character image to the list
    char_images.append(char_image)

    # Update the total image height
    total_image_height += char_image_height

# Create the sprite sheet with the total height
sprite_sheet = Image.new('RGBA', (grid_width, total_image_height), (0, 0, 0, 0))

# Paste each character image into the sprite sheet
current_height = 0
for char_image in char_images:
    sprite_sheet.paste(char_image, (0, current_height), char_image)
    current_height += char_image.height

# Save the sprite sheet
sprite_sheet.save('font.png')

# Save the character metrics
with open('font.json', 'w') as f:
    json.dump(char_metrics, f, indent=4)
