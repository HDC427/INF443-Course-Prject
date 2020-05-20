import os
from PIL import Image

for img_in in os.listdir('textures'):
    img_in = os.path.join('textures', img_in)
    name, extension = os.path.splitext(img_in)
    if extension != 'png':
        try:
            img = Image.open(img_in)
        except:
            print(img_in, 'is not an image.')
        img_out = name + '.' + 'png'
        img.save(img_out)