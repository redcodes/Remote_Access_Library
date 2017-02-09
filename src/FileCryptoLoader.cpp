#include "RAT.h"
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>
#include "Logging.h"

namespace SL {
	namespace RAT {
		class FileCryptoLoader: public ICryptoLoader {
		public:
			FileCryptoLoader(const std::string& filepath) :FilePath(filepath) {}
			~FileCryptoLoader() {
				memset(Data.data(), 0, Data.size());
			}
			const char* get_buffer() {
				LoadData();
				return Data.data();
			}
			size_t get_size() {
				LoadData();
				return Data.size();
			}
			void LoadData() {
				if (Data.empty()) {
					std::ifstream file(FilePath, std::ios::binary | std::ios::ate);
					//if file is not found, ASSERT!.. FILE NOT FOUND!
					if (file) {
						std::streamsize size = file.tellg();
						file.seekg(0, std::ios::beg);
						Data.resize(static_cast<size_t>(size));
						if (!file.read(Data.data(), size)) {
							Data.resize(0);
						}
					}
					else {
						SL_RAT_LOG(Logging_Levels::ERROR_log_level, "File " << FilePath << "not found!");
					}

				}
			}
			std::vector<char> Data;
			std::string FilePath;

		};
		std::shared_ptr<ICryptoLoader> LoadFromFile(const std::string& file) {
			return std::static_pointer_cast<ICryptoLoader>(std::make_shared<FileCryptoLoader>(file));
		}
	}
}
