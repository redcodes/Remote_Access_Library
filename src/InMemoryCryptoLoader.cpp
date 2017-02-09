#include "RAT.h"
#include <vector>
#include <assert.h>
#include "Logging.h"

namespace SL {
	namespace RAT {
		class InMemoryCryptoLoader:public ICryptoLoader {
		public:
			InMemoryCryptoLoader(const char* data, size_t size) {
				Data.resize(size);
				memcpy(Data.data(), data, size);
			}
			~InMemoryCryptoLoader() {
				memset(Data.data(), 0, Data.size());
			}
			const char* get_buffer() {
				//data cannot be empty!
				if (Data.empty()) SL_RAT_LOG(Logging_Levels::ERROR_log_level, "Data not found!");
				return Data.data();
			}
			size_t get_size() {
				//data cannot be empty!
				assert(!Data.empty());
				return Data.size();
			}
			std::vector<char> Data;

		};
		std::shared_ptr<ICryptoLoader> LoadFromMemory(const char* data, size_t size) {
			return std::static_pointer_cast<ICryptoLoader>(std::make_shared<InMemoryCryptoLoader>(data, size));
		}
	}
}

