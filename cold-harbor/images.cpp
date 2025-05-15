#include "images.h"
#include "logging.h"
#include "game.h"
#include <filesystem>
#include <fstream>

void* images::load_image(const char* name) {

	auto image_path = (std::filesystem::path("winter/images/") / name).replace_extension(".iwi");
	if (!std::filesystem::exists(image_path)) {
		return nullptr;
	}

	auto out_image = std::make_unique<game::GfxImage>();

	std::ifstream file(image_path, std::ios::binary);
	if (!file) {
		spdlog::error("Failed to open image file '{}'", image_path.string());
		return nullptr;
	}

	iwi_version version;
	file.read(reinterpret_cast<char*>(&version), sizeof(version));

	if (version.tag[0] != 'I' || version.tag[1] != 'W' || version.tag[2] != 'i')
	{
		spdlog::error("Invalid iwi magic number in file '{}'", image_path.string());
		return nullptr;
	}

	iwi_header header;
	file.read(reinterpret_cast<char*>(&header), sizeof(header));

	return out_image.release();
}