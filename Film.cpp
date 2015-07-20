#include "classes.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb-master/stb_image_write.h"

Film::Film(Scene* scene_in) {
	scene = scene_in;
	output_image = scene->output_image;
	width = scene->width;
	height = scene->height;
	comp = 3;
	size = width * height * comp;
	stride_in_bytes = width * comp;
	data = new char[size];
	memset(data, 0, size);
}

void Film::testCircle() {
	int radius = min(width, height) / 2;
	float centerX = width / 2.0;
	float centerY = height /2.0;
	float dist;
	int idx;
	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			idx = x + (width * y);
			idx = 3 * idx;
			// data[idx] = 0;
			// data[idx+1] = 0;
			// data[idx+2] = 0;
			dist = sqrt((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY));
			if (dist <= radius) {
				data[idx+1] = 255;
			}
		}
	}
}

void Film::set(int i, int j, float r, float g, float b) {
	// int x = i;
	// int y = scene->height - j;
	// int idx = 3 * (x + y * width);
	int idx = 3 * (i + j * width);
	data[idx] = r;
	data[idx+1] = g;
	data[idx+2] = b;
}

void Film::set(int i, int j, Color clr) {
	int x = i;
	int y = height - 1 - j;
	int idx = 3 * (x + y * width);
	// int idx = 3 * (i + j * width);
	data[idx] = clr.r;
	data[idx+1] = clr.g;
	data[idx+2] = clr.b;
}

// Will write the color to (x.sample, sample.y) on the image
// void commit(Sample& sample, Color& color) {
// 	int idx = 3 * (sample.x() + (sample.y() * w));
// 	data[idx] = color.r();
// 	data[idx+1] = color.g();
// 	data[idx+2] = color.b();
// }

void Film::writeImage() {

	stbi_write_png(output_image.c_str(), width, height, comp, data, stride_in_bytes);	
}