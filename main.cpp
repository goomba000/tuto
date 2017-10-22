#include <SOIL.h>
#include <iostream>
#include <sstream>
#include <fstream>

int main() {
	int width, height;
	unsigned char* image;
	const char * image_file = "..\\container2_specular.png";
	// Diffuse map
	image = SOIL_load_image(image_file, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == 0) {
		std::cout << "failed to load " << image_file << "...";
		std::cin.get();
		return 1;
	}

	std::cout << width*height << " pixels to process..." << std::endl;
	unsigned char* image_out = (unsigned char *)malloc(width*height*3);
	memcpy(image_out, image, width*height*3);
	unsigned int num_px = width*height;
	unsigned int one_third_mark = num_px / 3;
	unsigned int two_third_mark = one_third_mark * 2;
	for (unsigned int i = 0;i < num_px;i++) {
		if (i < one_third_mark) {
			if (image[i * 3] != 0)
				image_out[i * 3] = 0xFF;//Max red component
		}
		else if (i < two_third_mark) {
			if (image[i * 3] != 0)
				image_out[i * 3 + 1] = 0xFF;//Max green component
		}
		else {
			if (image[i * 3] != 0)
				image_out[i * 3 + 2] = 0xFF;//Max blue component
		}
			
		if ((i % 50000) == 0)
			std::cout << "pixel " << i << "..." << std::endl;
	}
	const char * image_file_out = "..\\container2_specular_mod.bmp";
	if(SOIL_save_image(image_file_out, SOIL_SAVE_TYPE_BMP, width, height, SOIL_LOAD_RGB, image_out) == 0)
		std::cout << "Saving " << image_file_out << " failed..." << std::endl;

	std::cout << "done...";
	std::cin.get();

	return 0;
}
