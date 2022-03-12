#include <iostream>
#include <string>

#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>

static constexpr size_t max_main_size = 0x20000000;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	constexpr size_t root_len = 3;
#else
	constexpr size_t root_len = 1;
#endif

static std::vector<std::filesystem::path> list_dir(const std::filesystem::path& dir) {
	std::vector<std::filesystem::path> ret;

	for (const auto& entry : std::filesystem::directory_iterator(dir)) {
		const auto& temp = entry.path();

		if (!std::filesystem::is_directory(temp)) {
			ret.push_back(temp);
		}
		else {
			auto listed = list_dir(temp);
			ret.insert(ret.end(), listed.begin(), listed.end());
		}
	}

	return ret;
}

static inline void copy_file_core(const std::filesystem::path& in, const std::filesystem::path& out) {
	std::cout << "Copying file: " << in.string() << "...\n";

	std::string rootless_abs_path = std::filesystem::canonical(in).string().substr(root_len);
	std::filesystem::path final_out_path = out / rootless_abs_path;

	std::filesystem::create_directories(final_out_path.parent_path());

	try {
		if (std::filesystem::exists(final_out_path)) {
			std::filesystem::remove(final_out_path);
		}

		std::filesystem::copy_file(in, final_out_path);
	} catch (std::exception& e) {
		std::cout << "Error while copying file: " << e.what() << "\n";
	}
}

static void copy_file_instance(const std::filesystem::path& in_path, const std::filesystem::path& out_path) {
	if (std::filesystem::is_directory(in_path)) {
		std::vector<std::filesystem::path> all_files = list_dir(in_path);

		for (const auto& e : all_files) {
			copy_file_core(e, out_path);
		}
	} else {
		copy_file_core(in_path, out_path);
	}
}

int main(int argc, char* argv[]) {
	bool force_exec = argc >= 2 ? false : true;	
	
	std::ifstream backup_config("./backup_list.txt");
	if (!backup_config) {
		std::cerr << "Error: missing config file: backup_list.txt" << std::endl;
		std::exit(1);
	}
	
	std::vector<std::string> backup_paths;
	
	{
		std::string str;
		while (std::getline(backup_config, str)) {
			backup_paths.push_back(str);
		}
	}
	
	if (backup_paths.empty()) {
		return 0;
	}

	std::string output_raw_path = backup_paths.back();
	if (!std::filesystem::exists(output_raw_path)) {
		std::cout << "Creating output directory: " << output_raw_path << "\n";
		std::filesystem::create_directories(output_raw_path);
	}
	const std::filesystem::path base_out_path = std::filesystem::canonical(output_raw_path);
	backup_paths.pop_back();

	std::vector<std::thread> threads;

	for (size_t i = 0; i < backup_paths.size(); ++i) {		
		if (std::filesystem::file_size(backup_paths[i]) > max_main_size) {			
			threads.emplace_back(copy_file_instance, backup_paths[i], base_out_path);
		}
		else {
			copy_file_instance(backup_paths[i], base_out_path);
		}
	}


	if (!threads.empty()) {
		std::cout << "Waiting for threads to finish...\n";
		for (auto& e : threads) {
			e.join();
		}
	}

	std::cout << "Task done" << std::endl;
	return 0;
}