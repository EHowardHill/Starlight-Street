import os
from PIL import Image

def process_half_image(half_image):
    # Create a green background image
    green_bg = Image.new('RGBA', half_image.size, (0, 0, 255, 255))
    # Paste the half image onto the green background using its alpha channel as a mask
    green_bg.paste(half_image, (0, 0), half_image)
    return green_bg.convert('RGB')  # Convert to RGB

def main():
    input_folder = 'references/stand'
    images = []

    # Loop over all PNG files in the "walk" folder
    for filename in sorted(os.listdir(input_folder)):
        if filename.lower().endswith('.png'):
            filepath = os.path.join(input_folder, filename)
            img = Image.open(filepath).convert('RGBA')

            # Split the image into two 64x128 images
            left = img.crop((0, 0, 64, 128))
            right = img.crop((64, 0, 128, 128))

            # Replace transparency with green background
            left = process_half_image(left)
            right = process_half_image(right)

            # Add the processed images to the list
            images.extend([left, right])

    # Calculate the total height for the final image
    total_height = len(images) * 128

    # Create a new image to hold all the processed images
    final_image = Image.new('RGB', (64, total_height))

    # Paste each image into the final image sequentially
    y_offset = 0
    for img in images:
        final_image.paste(img, (0, y_offset))
        y_offset += 128

    # Save the final image as "beryl.bmp"
    final_image.save('beryl.bmp')

if __name__ == '__main__':
    main()
